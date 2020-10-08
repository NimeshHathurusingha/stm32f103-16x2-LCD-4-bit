#ifndef LiquidCrystal
#define LiquidCrystal



GPIO_TypeDef *Ports[7] ;//RS ,W/R ,E ,4 ,5 ,6 ,7
int PinNumbers[7];



uint8_t numbers[10] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};



void set_bit(GPIO_TypeDef *port, int pin, uint8_t bits){
  if(bits){
	  port -> ODR |= 1 << pin;
  }
  else {
	  port -> ODR &= ~(1 << pin);
  }
}

void set_bus(char character){
	set_bit(Ports[3], PinNumbers[3], character & 0x10);
	set_bit(Ports[4], PinNumbers[4], character & 0x20);
	set_bit(Ports[5], PinNumbers[5], character & 0x40);
	set_bit(Ports[6], PinNumbers[6], character & 0x80);
}

void check_Busy(){
  set_bus(0x00);
  set_bit(Ports[0],PinNumbers[0],0);
  while( Ports[6]->IDR & (1<<PinNumbers[6])){}
  set_bus(0xff);
}

void send_(){

	set_bit(Ports[2], PinNumbers[2], 1);
	for(int i=0;i<5000;i++){}
	set_bit(Ports[2], PinNumbers[2], 0);
	for(int i=0;i<5000;i++){}
}

void send_A_command(char command){
	check_Busy();
	set_bus(command);
	set_bit(Ports[0],PinNumbers[0],0);
	send_();
	set_bus(command<<4);
	send_();
	set_bus(0);
	for(int i=0;i<7000;i++){}
}

void send_A_character(char character){
  check_Busy();
  set_bus(character);
  set_bit(Ports[0],PinNumbers[0],1);
  send_();
  set_bus(character<<4);
  send_();
  set_bus(0);
}

void clear(){
  send_A_command(0x01);
  for(int i=0;i<2000;i++){}
}

void home(){
	send_A_command(0x02);
	for(int i=0;i<2000;i++){}
}

void setCursor(int row, int col){
	home();
	for(int i=0;i<2000;i++){}
	int step = row*40+col;
	for(int i=0;i<step;i++){
		send_A_command(0x14);
		for(int i=0;i<2000;i++){}
	}
}

void printC(char ch){
	send_A_character(ch);
}

void printS(char *str){
	while(*str > 0){
		send_A_character(*str++);
	}
}

void printI(int num){
	int num1 = 0;
	int count=0;
	while(num>0){
		num1 = num1*10+num%10;
		count++;
		num /= 10;
	}
	for(int i=0;i<count;i++){
		send_A_character(numbers[num1%10]);
		num1 /= 10;
	}
}


void printF(float num, int size){
	int num1 = num;
	printI(num1);
	int po = 1;
	for(int i=0;i<size;i++){ po *= 10; }
	printC('.');
	int num2 = num * po;
	num2 = num2 - num1 * po;
	printI(num2);
}


void cursor(){
	send_A_command(0x0E);
	for(int i=0;i<11000;i++){}
}

void noCursor(){
	send_A_command(0x0C);
	for(int i=0;i<11000;i++){}
}

void blink(){
	send_A_command(0x0f);
	for(int i=0;i<11000;i++){}
}

void noBlink(){
	send_A_command(0x0C);
	for(int i=0;i<11000;i++){}
}

void scrollDisplayLeft(){
	send_A_command(0x18);
	for(int i=0;i<11000;i++){}
}

void scrollDisplayRight(){
	send_A_command(0x1C);
	for(int i=0;i<11000;i++){}
}




void EnablePort(GPIO_TypeDef *port){

	if(port == GPIOA){
		RCC ->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	else if(port == GPIOB){
		RCC ->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else if(port == GPIOC){
		RCC ->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	else if(port == GPIOD){
		RCC ->APB2ENR |= RCC_APB2ENR_IOPDEN;
	}
	else if(port == GPIOE){
		RCC ->APB2ENR |= RCC_APB2ENR_IOPEEN;
	}
	else if(port == GPIOF){
		RCC ->APB2ENR |= RCC_APB2ENR_IOPFEN;
	}
	else if(port == GPIOG){
		RCC ->APB2ENR |= RCC_APB2ENR_IOPGEN;
	}
}

void setPortAndPinOutput(GPIO_TypeDef *port, int pin){

	if(pin<8){
		pin = pin *4;
		port -> CRL &= ~(0b1111<<pin);
		port -> CRL |= (1<<pin);
	}
	else{
		pin = (pin - 8) *4;
		port -> CRH &= ~(0b1111<<pin);
		port -> CRH |= (1<<pin);
	}
}


void begin_LCD(GPIO_TypeDef *ports[],int pinnumbers[]){

	for(int i=0;i<7;i++){
		Ports[i] = ports[i];
		PinNumbers[i] = pinnumbers[i];
		//EnablePort(Ports[i]);			//enable ports if you need this uncommenct this part or enable port your self
		setPortAndPinOutput(Ports[i], PinNumbers[i]);
	}

    send_A_command(0x02);	//return home
    for(int i=0;i<11000;i++){}

    send_A_command(0x28);	//2 Line Mode
    for(int i=0;i<11000;i++){}

    send_A_command(0x0C);	//Display ON
    for(int i=0;i<11000;i++){}

}



#endif
