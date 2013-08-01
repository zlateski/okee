import serial
import time
import random
port = "/dev/ttyACM0" # or whatever the USB device shows up as
s = serial.Serial(port)

# index = bulb_number, value is 0 or 1 for "off" or "on"
# the next line turns a bulb on or off

for j in range(123123):
    for i in [0, 1, 2, 3, 4, 9, 14, 19, 24, 23, 22, 21, 20, 15, 10, 5, 6, 7, 8, 13, 18, 17, 16, 11, 12, 13]:
        print i;
        time.sleep(1.0/111130);

        index = i; #random.randint(0, 25);
        value = 0;
        s.write(chr((index << 1)^(value)))
    for i in [0, 1, 2, 3, 4, 9, 14, 19, 24, 23, 22, 21, 20, 15, 10, 5, 6, 7, 8, 13, 18, 17, 16, 11, 12, 13]:
        print i;
        time.sleep(1.0/(10+j*3));

        index = i; #random.randint(0, 25);
        value = 1;
        s.write(chr((index << 1)^(value)))
        time.sleep(1.0/111130);
        time.sleep(1.0/111130);
        time.sleep(1.0/110);


