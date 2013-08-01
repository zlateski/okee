#include "font.hpp"
#include "ncurses.hpp"
#include "game_of_life.hpp"
#include "screen.hpp"
#include "okie_screen.hpp"

int main()
{
    //boost::shared_ptr<okie::ncurses_screen> nc(new ncurses_screen);
    okie::screens.register_screen(new okie::ncurses_screen);
    okie::screens.register_screen(new okie::okie_screen("/dev/ttyACM0"));

    okie::font.slide_text("welcome to the magazine house!", 750000);
    okie::font.playstring("cabron@mit.edu", 500000);
    //okie::game_of_life.play("0000000110011000010000000");
};
