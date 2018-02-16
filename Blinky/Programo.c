#include "stm32l4xx.h"
void delay(unsigned dly)
{
    while(dly--);
}

void ActivatePORTB(){
	SET_BIT(RCC->AHB2ENR , 2);
}

void ActivatePORTBLed() {
		GPIOB->MODER |= 0x40;
		GPIOB->MODER &= ~0x80;	
		GPIOB->MODER |= 0x100;
		GPIOB->MODER &= ~0x200;	
		GPIOB->MODER |= 0x400;
		GPIOB->MODER &= ~0x800;
}

void ActivatePORTA() {
	SET_BIT(RCC->AHB2ENR , 1);
}

void ActivatePORTALed() {
		GPIOA->MODER |= 0x10000;
		GPIOA->MODER &= ~0x20000;
}

void LedPORTBOn() {
	GPIOB->ODR |= 0x08;
	GPIOB->ODR |= 0x10;
	GPIOB->ODR |= 0x20;
}

void LedPORTBOff() {
	GPIOB->ODR &= ~0x08;
	GPIOB->ODR &= ~0x10;
	GPIOB->ODR &= ~0x20;
}

void LedPORTAOn(){
	GPIOA->ODR |= 0x100;
}

void LedPORTAOff() {
	GPIOA->ODR &= ~0x100;
}

int main()
{
		ActivatePORTB();
		ActivatePORTA();
		delay(1000000);
		ActivatePORTBLed();
		ActivatePORTALed();

		
	while(1) {
			LedPORTBOn();
			LedPORTAOn();
			delay(1000000);
			LedPORTBOff();
			LedPORTAOff();
			delay(1000000);
		}
}
