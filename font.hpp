#ifndef OKIE_FONT_HPP
#define OKIE_FONT_HPP

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <zi/utility/for_each.hpp>
#include <zi/utility/singleton.hpp>
#include <zi/concurrency.hpp>

#include "screen.hpp"

namespace okie {

class font_impl
{
private:
    std::map<char, std::string> font_    ;
    std::map<char, std::string> commands_;

public:
    font_impl() : font_()
    {
        font_[' '] = font_[' '] = "0000000000000000000000000";
        font_['#'] = font_['#'] = "0101011111010101111101010";
        font_['a'] = font_['A'] = "1111110001111111000110001";
        font_['b'] = font_['B'] = "1111110001111101000111111";
        font_['c'] = font_['C'] = "1111110000100001000011111";
        font_['d'] = font_['D'] = "1111010001100011000111110";
        font_['e'] = font_['E'] = "1111110000111001000011111";
        font_['f'] = font_['F'] = "1111110000111001000010000";
        font_['g'] = font_['G'] = "1111110000101111000111111";
        font_['h'] = font_['H'] = "1000110001111111000110001";
        font_['i'] = font_['I'] = "1111100100001000010011111";
        font_['j'] = font_['J'] = "0000100001000011000111111";
        font_['k'] = font_['K'] = "1000110010111001001010001";
        font_['l'] = font_['L'] = "1000010000100001000011111";
        font_['m'] = font_['M'] = "1000111011101011000110001";
        font_['n'] = font_['N'] = "1000111001101011001110001";
        font_['o'] = font_['O'] = "1111110001100011000111111";
        font_['p'] = font_['P'] = "1111010001111111000010000";
        font_['q'] = font_['Q'] = "1111110001100011010111111";
        font_['r'] = font_['R'] = "1111010001111111001010001";
        font_['s'] = font_['S'] = "1111110000111110000111111";
        font_['t'] = font_['T'] = "1111100100001000010000100";
        font_['u'] = font_['U'] = "1000110001100011000111111";
        font_['v'] = font_['V'] = "1000110001100010101000100";
        font_['w'] = font_['W'] = "1000110001101011101110001";
        font_['x'] = font_['X'] = "1000101010001000101010001";
        font_['y'] = font_['Y'] = "1000101010001000010000100";
        font_['z'] = font_['Z'] = "1111100010001000100011111";

        font_['0'] = "1111110001100011000111111";
        font_['1'] = "0011000010000100001000010";
        font_['2'] = "1111100001111111000011111";
        font_['3'] = "1111100001001110000111111";
        font_['4'] = "1000110001111110000100001";
        font_['5'] = "1111110000111110000111111";
        font_['6'] = "1111110000111111000111111";
        font_['7'] = "1111100001000010000100001";
        font_['8'] = "1111110001111111000111111";
        font_['9'] = "1111110001111110000100001";


        font_['+'] = "0010000100111110010000100";
        font_['-'] = "0000000000111110000000000";
        font_['/'] = "0000100010001000100010000";
        font_['\\'] = "1000001000001000001000001";
        font_['%'] = "0010000000011100000000100";
        font_['='] = "0000011111000001111100000";
        font_['"'] = "0101001010000000000000000";
        font_['\''] = "0010000100000000000000000";
        font_['@'] = "1111110001101111010110111";
        font_['_'] = "0000000000000000000011111";
        font_['('] = "0010001000010000100000100";
        font_[')'] = "0010000010000100001000100";
        font_[','] = "0000000000000000010000100";
        font_['.'] = "0000000000000000010000000";
        font_[';'] = "0010000000000000010000100";
        font_[':'] = "0010000000000000010000000";
        font_['?'] = "1111100001001110000000100";
        font_['!'] = "0010000100001000000000100";
        font_['|'] = "0010000100001000010000100";
        font_['{'] = "0011000100011000010000110";
        font_['}'] = "0110000100001100010001100";
        font_['<'] = "0001000100010000010000010";
        font_['>'] = "0100000100000100010001000";
        font_['['] = "0110001000010000100001100";
        font_[']'] = "0011000010000100001000110";
        font_['^'] = "0010001010000000000000000";
        font_['~'] = "0000011100101010011100000";


        FOR_EACH( it, font_ )
        {
            for ( char c = 0; c < 25; ++c )
            {
                char d = c << 1;
                if ( it->second[c] == '1' ) d |= 1;
                commands_[it->first] += (d);
            }
        }

        FOR_EACH( it, commands_ )
        {
            std::random_shuffle(it->second.begin(), it->second.end());
        }
    }

    void putchar(char c)
    {
        if ( commands_.count(c) )
        {
            screens.direct(commands_[c].c_str(), 25);
            // FOR_EACH( it, commands_[c] )
            // {
            //     screens.direct(*it);
            // }
        }
    }

    void slide_text(const std::string& s, int u = 500000, int v = 5000)
    {
        std::string all;
        FOR_EACH( it, s )
        {
            if ( font_.count(*it) ) all += font_[*it] + "00000";
        }

        for ( int x = 0; x < static_cast<int>(all.size()) - 25; x += 5 )
        {
            for ( char c = 0; c < 25; ++c )
            {
                char d = c<<1;
                if ( all[x+c] == '1' ) d |= 1;
                screens.command(d);
            }
            if ( x % 6 == 0 )
            {
                zi::this_thread::usleep(u);
            }
            else
            {
                zi::this_thread::usleep(v + (5-x%6) * 20000);
            }
        }
    }

    void playstring(const std::string& s, int u = 500000)
    {
        FOR_EACH(it, s)
        {
            this->putchar(*it);
            zi::this_thread::usleep(u);
        }
    }

    void blinkstring(const std::string& s, int u = 300000, int v = 100000)
    {
        FOR_EACH(it, s)
        {
            this->putchar(*it);
            zi::this_thread::usleep(v);
            this->putchar(' ');
            zi::this_thread::usleep(v);
            this->putchar(*it);
            zi::this_thread::usleep(u);
        }
    }

    void iblinkstring(const std::string& s, int u = 300000, int v = 100000)
    {
        FOR_EACH(it, s)
        {
            this->putchar(*it);
            zi::this_thread::usleep(v);
            screens.invert();
            zi::this_thread::usleep(v);
            screens.invert();
            zi::this_thread::usleep(u);
        }
    }

}; // class font_impl


namespace {
font_impl& font = zi::singleton<font_impl>::instance();
}


} // namespace okie

#endif // OKIE_FONT_HPP
