# logicProber

This is a simple arduino sketch ( in platform.io)  that outputs the arduino pin number to the GPIO so that if you use a 
logic analyser on a pin it'll out the the pins number, on the pin itself. The best mode is SPI , where you just need one known pin for a clock and select, assign those 
to the SPI decoders CLOCK/SS then the line you are probing with would be the data line, so all you have to do is poke each IO pin and then see what it decodes as


Define the arduino wiring pin mapping into the gpioPins array , find a pin for the clock, then run it and probe away.

Here is an example of this mapping, pin 17 is listed twice (for testing) and 22 is the known clock

const int gpioPins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,17,18,29,20,21,17,23,24,25,26,27,28,29,30,31};

![image](https://github.com/charlie-x/logicProber/assets/2334094/0d11cfa5-5904-43e8-a59e-3a5add3d25ac)

you should be able to copy and paste the main.cpp into a arduino .ino as well.

# examples

![image](https://github.com/charlie-x/logicProber/assets/2334094/460ddb4e-da29-4d57-90a0-dafa0521bb18)

![image](https://github.com/charlie-x/logicProber/assets/2334094/5c785fc5-13ed-44da-8e62-85cdbc0f9962)


DUT with a flying lead probe to check each pin, and SCLK and SS on other known pins

![image](https://github.com/charlie-x/logicProber/assets/2334094/e8856484-654d-433d-87e6-bd98a2b5a036)

Pin 31 being probed
![image](https://github.com/charlie-x/logicProber/assets/2334094/fc31403e-4693-4be1-8e3d-030d4196184d)

SPI Setup
![image](https://github.com/charlie-x/logicProber/assets/2334094/78cf6381-4dc7-4148-b6e8-0326e475f15c)
