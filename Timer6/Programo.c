#include "stm32l4xx.h"

void ActivateTIM6() {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
}

void EnableCountingToTim6() {
	TIM6->CR1 |= 0x1;
}

uint16_t ReadTIM6Counter() {
	return (uint16_t)TIM6->CNT;
}

void SetPrescaler(uint16_t prescalerValue) {
	TIM6->PSC = prescalerValue;
}

void LoadTIM6TimerValue(uint16_t counterValue) {
	TIM6->ARR = counterValue;
}

void ActivatePORTB() {
	SET_BIT(RCC->AHB2ENR , 2);	
}

void ActivateBoardLed() {
	GPIOB->MODER |= 0x40;
	GPIOB->MODER &= ~0x80;
}

void LedOn() {
	GPIOB->ODR |= 0x08;
}

void LedOff() {
	GPIOB->ODR &= ~0x08;
}

void delay(unsigned dly)
{
    while(dly--);
}

#define THRESHOLD 5000
int main(void) {
	ActivatePORTB();
	ActivateBoardLed();
	ActivateTIM6();
	delay(10000);
	SetPrescaler(1000);
	LoadTIM6TimerValue(10000);
	EnableCountingToTim6();
	while(1) {
		if (ReadTIM6Counter() > THRESHOLD ) {
			LedOff();
		} else {
			LedOn();
		}
	}
}
