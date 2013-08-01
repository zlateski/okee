#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <SerialStream.h>
#include <vector>
#include <map>

const char l_a[25] =
{ 0,0,1,0,0,
  0,1,0,1,0,
  0,1,0,1,0,
  0,1,0,1,0,
  0,0,1,0,0 };

const char l_b[25] =
{ 0,1,0,0,0,
  0,1,0,0,0,
  0,1,1,1,0,
  0,1,0,1,0,
  0,1,1,1,0 };

const char l_k[25] =
{ 0,1,0,0,1,
  0,1,0,1,0,
  0,1,1,0,0,
  0,1,0,1,0,
  0,1,0,0,1 };


inline void write_letter(LibSerial::SerialStream& ss, const char* l)
{
    for ( char c = 0; c < 25; ++c )
    {
        char d = (c<<1);
        if ( l[c] ) d |= 1;
        ss.write(&d, 1);
    }
}

int main()
{
    LibSerial::SerialStream ss;
    ss.Open("/dev/ttyACM0"); //serial/by-id/usb-LeafLabs_Maple-if00");

    if ( !ss.good() )
    {
        std::cout << "Not good" << std::endl;
        exit(1);
    }

    ss.SetCharSize( LibSerial::SerialStreamBuf::CHAR_SIZE_8 ) ;
    if ( !ss.good() )
    {
        std::cout << "can't set char size" << std::endl;
        exit(1);
    }

    char c = 0x1;

    write_letter(ss,l_a);

    usleep(1000000);

    write_letter(ss,l_b);

    //ss.write(&c, 0);
}
