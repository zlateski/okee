#ifndef OKIE_OKIE_HPP
#define OKIE_OKIE_HPP

#include <SerialStream.h>
#include <string>
#include "screen.hpp"


namespace okie {

class okie_screen: public screen_base
{
private:
    LibSerial::SerialStream s_   ;
    bool                    good_;

public:
    okie_screen(const std::string& s)
        : s_()
        , good_(false)
    {
        s_.Open(s);
        good_ = s_.good();

        if ( good_ )
        {
            s_.SetCharSize( LibSerial::SerialStreamBuf::CHAR_SIZE_8 );
        }

        good_ = s_.good();
    }

    ~okie_screen()
    {
        if ( good_ )
        {
            s_.Close();
        }
    }

    void set_pixel(int r, int c, bool v)
    {
        if ( good_ )
        {
            char c = static_cast<char>(((r*5+c)<<1)+(v?1:0));
            s_.write(&c,1);
        }
    }

}; // class okie_screen


} // namespace okie

#endif // OKIE_OKIE_HPP
