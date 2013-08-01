#ifndef OKIE_SCREEN_HPP
#define OKIE_SCREEN_HPP

#include <list>
#include <boost/shared_ptr.hpp>
#include <zi/utility/singleton.hpp>
#include <zi/utility/for_each.hpp>

namespace okie {

class screen_base
{
public:
    virtual ~screen_base() {};
    virtual void set_pixel(int x, int y, bool b) = 0;

    virtual void set_pixel(int idx, bool v)
    {
        int row = idx / 5;
        int col = idx % 5;
        this->set_pixel(row,col,v);
    }

    virtual void direct(char c)
    {
        this->set_pixel(static_cast<int>(c)>>1,c&1);
    }

    virtual void direct(const char* c, int l)
    {
        for ( int i = 0; i < l; ++i )
        {
            direct(c[i]);
        }
    }

}; // class screen_base

class screens_impl
{
private:
    std::list<screen_base*> screens_;
    std::vector<bool>       pixels_;

public:
    screens_impl()
        : screens_()
        , pixels_(25)
    { }

    ~screens_impl()
    {
        FOR_EACH(it, screens_)
        {
            delete (*it);
        }
    }

    void register_screen(screen_base* s)
    {
        screens_.push_back(s);
    }

    void set_pixel(int r, int c, bool v)
    {
        pixels_[r*5+c] = v;
        FOR_EACH(it, screens_)
        {
            (*it)->set_pixel(r,c,v);
        }
    }

    bool get_pixel(int r, int c)
    {
        return pixels_[r*5+c];
    }

    void set_pixel(int idx, bool v)
    {
        int row = idx / 5;
        int col = idx % 5;
        set_pixel(row,col,v);
    }

    bool get_pixel(int idx)
    {
        return pixels_[idx];
    }

    void set_all(const char* c, int len = 25)
    {
        for ( int i = 0; i < len; ++i )
        {
            set_pixel(c[i]>>1,c[i]&1);
        }
    }

    void command(char c)
    {
        set_pixel(static_cast<int>(c)>>1,c&1);
    }

    void direct(char c)
    {
        bool b = c&1;
        c >>= 1;
        pixels_[static_cast<int>(c)] = b;
        FOR_EACH(it, screens_)
        {
            (*it)->direct(c);
        }
    }

    void direct(const char* c, int l)
    {
        for ( int i = 0; i < l; ++i )
        {
            char d = c[i];
            bool b = d&1;
            d >>= 1;
            pixels_[static_cast<int>(d)] = b;
            FOR_EACH(it, screens_)
            {
                (*it)->direct(c, l);
            }
        }
    }

    void invert()
    {
        for ( int i = 0; i < 25; ++i )
        {
            set_pixel(i,!pixels_[i]);
        }
    }


}; // class screens_impl

namespace {
screens_impl& screens = zi::singleton<screens_impl>::instance();
}


} // namespace okie

#endif // OKIE_SCREEN_HPP
