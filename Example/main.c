#include "stm32f10x.h"

#include "16x2_LCD_4bit.h"


int main(void)
{
	//enable port
	RCC ->APB2ENR |= RCC_APB2ENR_IOPBEN;


	//connected pin details		RS		R/W		E		4		5	6		7
	GPIO_TypeDef *Ports[7] = { GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB };
	int PinNumbers[7]     = {    14,      15,    9,    10,    11,    12,    13 };


	begin_LCD(Ports,PinNumbers); //initiate the lcd


	clear();	//clear the lcd
	cursor();	//enable cursor
	blink();	//enable the cursor blink


	char Hello[] = "Hello world";
	for(int i=0;i<11;i++){
		printC(Hello[i]);				// print character
		for(int j=0;j<1000000;j++){}	//add some delay
	}

	home();							//set home
	printI(1234567890);				//print integer

	for(int j=0;j<10000000;j++){} 	// add some delay


	setCursor(1, 0);	//set cursor position
	float num = 1.234;
	printF(num, 3);		//print float number
	noBlink();			// stop cursor blinking and cursor
	cursor();			//enable cursor

	for(int j=0;j<10000000;j++){} // add some delay

	setCursor(1,0);			//set cursor to 2nd line
	printF(1.23, 8);		//print float number

	for(int j=0;j<10000000;j++){} // add some delay

	clear();	//clear the lcd
	printS("Hello world");


    while(1)
    {
    }
}
