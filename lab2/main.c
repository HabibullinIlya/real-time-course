#include "C:\Keil\ARM\INC\ST\STM32F4xx\stm32f4xx.h"

void wait(unsigned int mx){
	int i;
	for(i = 0;i<mx;i++){}
}
#define delay 1000000

void SystemInit(){
	//RCC
	RCC->AHB1ENR|=0x00000008;
	RCC->APB1ENR |= 0x00000001;
	GPIOD->MODER|=0x01000000;
	
	
	TIM2->CNT = 0;
	TIM2->PSC = 0x800;
	TIM2->ARR = 0x8000;
	TIM2->DIER |= 0x00000001;
	TIM2->CR1 |= 0x00000001;
	
	NVIC->ISER[0] |= 0x10000000;
	
	
}
int main(){
	while(1){
		GPIOD-> ODR|=0x00001000;
		wait(delay);
		GPIOD->ODR&=~0x00001000;
		wait(delay);
	}
}
