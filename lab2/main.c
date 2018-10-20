#include "C:\Keil\ARM\INC\ST\STM32F4xx\stm32f4xx.h"

void wait(unsigned int mx){
	int i;
	for(i = 0;i<mx;i++){
		
	}
}
#define delay 1000000

void SystemInit(){
	//RCC
	RCC->AHB1ENR|=0x00000008;
	GPIOD->MODER|=0x01000000;
}
int main(){
	while(1){
		GPIOD-> ODR|=0x00001000;
		wait(delay);
		GPIOD->ODR&=~0x00001000;
		wait(delay);
	}
	

}
