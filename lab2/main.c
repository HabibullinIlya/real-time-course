#include "C:\Keil\ARM\INC\ST\STM32F4xx\stm32f4xx.h"

void wait(unsigned int mx){
	int i;
	for(i = 0;i<mx;i++){}
}
#define delay 100000

void SystemInit(){
	//RCC
	RCC->AHB1ENR |= 0x00000009;
	
	RCC->APB1ENR |= 0x00000001;
	GPIOD->MODER |= 0x01000000;
	
	
	//button init
//	RCC->AHB1ENR |=0x00000001;
//	GPIOA->MODER |=0x00000000;
	
	
	TIM2->CNT = 0;
	TIM2->PSC = 0x800;
	TIM2->ARR = 0x8000;
	TIM2->DIER |= 0x00000001;
	TIM2->CR1 |= 0x00000001;
	
	NVIC->ISER[0] |= 0x10000000;
	
	//UART
	RCC->APB1ENR |= 0x00020000;
	GPIOA->MODER |= 0x000000a0;
	

	GPIOA->AFR[0] |= 0x00007700;
	USART2->BRR |= 0x100;
	
	USART2->CR1 |= 0x0000200c;
	
	
	
	
}
int main(){
	
//	int button = 0;
//	int counter = 0;
//	int delay_old = delay;
//	int delay_new = delay+counter;
//	while(1){
//		
//	  button = ((GPIOA->IDR & 0x00000001)==0)?(0):(1);

//		if(button==1){
//			counter+=100000;
//			GPIOD->ODR|=0x00001000;
//		
//			wait(delay_old);
//			__disable_irq();
//			GPIOD->ODR&=~0x00001000;
//			__enable_irq();
//			wait(delay_old);
//			delay_new = delay_old+counter;
//			
//		}else{
//			
//			GPIOD->ODR|=0x00001000;
//		
//			wait(delay_new);
//			__disable_irq();
//			GPIOD->ODR&=~0x00001000;
//			__enable_irq();
//			wait(delay_new);
//			delay_old = delay_new;
//		}
	 
	//}
	
	volatile int data = 0;
	while(1){
		
		volatile int bit = ((USART2->SR & 0x00000020) == 0)? (0):(1);
		wait(delay);
		//if(bit == 1){
			GPIOD->ODR|=0x00001000;
			wait(delay);
			data = USART2->DR;
		data=0xf0;
			USART2->DR = data;
		//}
		GPIOD->ODR&=~0x00001000;
		
		wait(delay);
	
	}
		
}
