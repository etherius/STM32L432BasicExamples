#include "stm32l4xx.h"
uint8_t isOn = 0;

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

void EnableTIM6Interrupt() {
	TIM6->DIER |= 0x01;
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void ClearTIM6Interrupt() {
	TIM6->SR &= ~0x1;
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

void TIM6_DAC_IRQHandler() {
	ClearTIM6Interrupt();
	if(isOn) {
		isOn = 0;
		LedOff();
	} else {
		isOn = 1;
		LedOn();
	}
}

int main(void) {
	ActivatePORTB();
	ActivateBoardLed();
	ActivateTIM6();
	delay(10000);
	
	EnableTIM6Interrupt();
	SetPrescaler(100);
	LoadTIM6TimerValue(10000);
	EnableCountingToTim6();
	while(1) {}
}
