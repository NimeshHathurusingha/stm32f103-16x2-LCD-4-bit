# stm32f103-16x2-LCD-4-bit

use my blog to more details blog - 

example - There is CooCox project using this header file. 

Required header files - #include "stm32f10x.h" 

LiquidCrystal.h 

Fucntions 

begin_LCD(GPIO_TypeDef *ports[],int pinnumbers[]) = Initializes the interface to the LCD screen, and specifies the pin connections. This function needs two parameters for identify the pin connection 

GPIO_TypeDef *ports[] = This is GPIO_TypeDef type array that hold 7 ports. There is special pattern to fill this array. 

int pinnumbers[] = This is same as the ports[] array. This array holds the pin numbers that lcd connected 

ports[0] / pinnumbers[0] - Port / Pin that lcd RS pin connected 

ports[1] / pinnumbers[1] - Port / Pin that lcd R/W pin connected 

ports[2] / pinnumbers[2] - Port / Pin that lcd E pin connected 

ports[3] / pinnumbers[3] - Port / Pin that lcd data 4 pin connected 

ports[4] / pinnumbers[4] - Port / Pin that lcd data 5 pin connected 

ports[5] / pinnumbers[5] - Port / Pin that lcd data 6 pin connected 

ports[6] / pinnumbers[6] - Port / Pin that lcd data 7 pin connected 

clear() = clear the LCD display and set cursor to initial position. 

home() = Set cursor to initial position but it does not clear the lcd display data 

setCursor(int row, int col) = Position the LCD cursor to user defined position. User must send the row number and column number to the function. 

Int row – 0 or 1 

Int col – 0 to 15 

printC(char ch) = Print a character 

printS(char *str) = print a string or char array 

printI(int num) = Print integer number 

printF(float num, int size) = print float number 

Float num – float number that need to print 

Int size – number of decimal points that need to print 

cursor() = show the LCD cursor 

noCursor() = Hide the LCD cursor 

blink() = Show the blinking LCD cursor 

noBlink() = Hide the LCD cursor 

scrollDisplayLeft() = Shift the content and cursor to left by one space 

scrollDisplayRight() = Shift the content and cursor to right by one space 

 
