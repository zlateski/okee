#ifndef OKIE_NCURSES_HPP
#define OKIE_NCURSES_HPP

#include <ncurses.h>
#include <zi/utility/singleton.hpp>
#include <zi/concurrency.hpp>
#include "screen.hpp"

namespace okie {

class ncurses_screen: public screen_base
{
public:
    ncurses_screen()
    {
        initscr();
    }

    ~ncurses_screen()
    {
        endwin();
    }

    void set_pixel(int r, int c, bool v)
    {
        char ch = v ? '#' : ' ';
        mvaddch(r,c,ch);
        refresh();
    }

}; // class ncurses_screen


} // namespace okie

#endif // OKIE_NCURSES_HPP
