# logicProber

This is a simple arduino sketch ( in platform.io)  that outputs the arduino pin number to the GPIO so that if you use a 
logic analyser on a pin it'll out the the pins number, on the pin itself. The best mode is SPI , where you just need one known pin for a clock, assign that 
to the SPI decoders CLOCK then the line you are probing with would be the data line, so all you have to do is poke each IO pin and then see what it decodes as


Here is an example of this mapping, pin 17 is listed twice (for testing) and 22 is the known clock
const int gpioPins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,17,18,29,20,21,17,23,24,25,26,27,28,29,30,31};

![image](https://github.com/charlie-x/logicProber/assets/2334094/0d11cfa5-5904-43e8-a59e-3a5add3d25ac)
