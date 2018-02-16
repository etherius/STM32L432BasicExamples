#include "stm32l4xx.h"

void ActivateTIM15() {
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
}

void EnableCountingToTim15() {
	TIM15->CR1 |= 0x1;
}

void ActivatePORTA() {
	SET_BIT(RCC->AHB2ENR , 1);
}

void ActivatePWMLed() {
	GPIOA->MODER &= ~0x10;
	GPIOA->MODER |= 0x20;
	GPIOA->AFR[0] |= 0xE00;
}

void PWMLedOn() {
	GPIOA->ODR |= 0x04;
}

void PWMLedOff() {
	GPIOA->ODR &= ~0x04;
}

void SetPWM(uint16_t prescaler , uint16_t frequency , uint16_t dutyCycle) {
	TIM15->PSC = prescaler;
	TIM15->ARR = frequency;
	TIM15->CCR1 = dutyCycle;
	TIM15->BDTR |= 0x8800;
	TIM15->CCMR1 |= 0x78;
	TIM15->CCER |= 0x1;
	TIM15->EGR |= 0x1;
	TIM15->CR1 |= 0x80;
}

void delay(unsigned dly)
{
    while(dly--);
}

int main(void) {
	ActivatePORTA();
	ActivatePWMLed();
	ActivateTIM15();
	delay(10000);
	SetPWM(1000 , 2000 , 1950);
	EnableCountingToTim15();
	while(1) {}
}
