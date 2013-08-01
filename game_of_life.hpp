#ifndef OKIE_GAME_OF_LIFE_HPP
#define OKIE_GAME_OF_LIFE_HPP

#include <zi/utility/singleton.hpp>
#include <zi/concurrency.hpp>
#include <string>

#include "screen.hpp"

namespace okie {

class game_of_life_impl
{
private:
    int count_neighbors(int x, int y, const std::string& s)
    {
        int r = 0;
        for ( int i = x-1; i <= x+1; ++i )
        {
            for ( int j = y-1; j <= y+1; ++j )
            {
                if ( (i >= 0) && (i < 5) && (j >= 0) && (j < 5) && (i != x || j != y) )
                {
                    if ( s[i*5+j] != '0' ) ++r;
                }
            }
        }
        return r;
    }

    bool is_alive(const std::string& s)
    {
        for ( int i = 0; i < 25; ++i )
        {
            if (s[i] != '0') return true;
        }
        return false;
    }

public:
    void play(const std::string& initial, int delay = 500000)
    {
        std::string current = initial;
        std::string next    = current;

        screens.set_all(current.c_str(),25);
        zi::this_thread::usleep(delay);

        while ( is_alive(current) )
        {
            for ( int i = 0; i < 25; ++i )
            {
                int r = count_neighbors(i/5,i%5,current);
                if ( current[i] != '0' )
                {
                    next[i] = '0';
                    if ( (r==2)||(r==3) ) next[i] = '1';
                }
                else
                {
                    next[i] = '0';
                    if ( r == 3 ) next[i] = '1';
                }
            }
            current = next;
            screens.set_all(current.c_str(),25);
            zi::this_thread::usleep(delay);
        }
    }

}; // class game_of_life_impl

namespace {
game_of_life_impl& game_of_life = zi::singleton<game_of_life_impl>::instance();
}


} // namespace okie

#endif // OKIE_GAME_OF_LIFE_HPP
