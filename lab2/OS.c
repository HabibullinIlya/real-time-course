#include "C:\Keil\ARM\INC\ST\STM32F4xx\stm32f4xx.h"

//-------stacks------
unsigned char Stacks[8][0x200];

//-------contexts----
struct{
	unsigned int GPR[12];
	void * PC;
	void * LR;
	void * SP;
	unsigned int PSW;
} contexts[8];


//tasks
extern void * Tasks[];
unsigned char tnum;
unsigned char tcur;
typedef void (*func)(void);


void OSInit(){
	
	int i;
//RCC
	RCC->AHB1ENR |= 0x00000009;
	
	RCC->APB1ENR |= 0x00000001;
	GPIOD->MODER |= 0x01000000;
	
	
	//button init
	//RCC->AHB1ENR |=0x00000001;
	//GPIOA->MODER |=0x00000000;
	
	
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
	USART2->BRR |= 0x116;
	
	USART2->CR1 |= 0x0000200c;
	
	
	i = 0;
	while(Tasks[i]!=0){
		contexts[i+1].PC = (void *)(((int)(Tasks[i])) |  (1));
		contexts[i+1].SP = &Stacks[i][0x200-4];
		contexts[i+1].PSW = 0x01000000;
		i++;
	}
	tnum = i;
	tcur = 0;
	
	return;
}

