#include "stm32l4xx.h"

void ActivateTIM1() {
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
}

void EnableCountingToTim1() {
	TIM1->CR1 |= 0x1;
}

uint16_t ReadTIM1Counter() {
	return (uint16_t)TIM1->CNT;
}

void SetPrescaler(uint16_t prescalerValue) {
	TIM1->PSC = prescalerValue;
}

void LoadTIM1TimerValue(uint16_t counterValue) {
	TIM1->ARR = counterValue;
}

void delay(unsigned dly)
{
    while(dly--);
}

void ActivatePORTB() {
	SET_BIT(RCC->AHB2ENR , 2);
}

void ActivatePORTBLed() {
	GPIOB->MODER |= 0x40;
	GPIOB->MODER &= ~0x80;
}

void LedPORTBOn() {
	GPIOB->ODR |= 0x08;
}

void LedPORTBOff() {
	GPIOB->ODR &= ~0x08;
}

#define THRESHOLD 5000
int main(void) {
	ActivatePORTB();
	delay(1000000);
	ActivatePORTBLed();
	ActivateTIM1();
	SetPrescaler(1000);
	LoadTIM1TimerValue(10000);
	EnableCountingToTim1();
	
	while(1) {
		uint16_t counterValue = ReadTIM1Counter();
		if (counterValue > THRESHOLD ){
			LedPORTBOn();
		} else {
			LedPORTBOff();
		}
	}
}
