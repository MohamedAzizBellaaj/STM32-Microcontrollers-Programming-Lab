#include <gpio.h>

#define RCC_APB2ENR (uint32_t *)0x40021018
uint8_t EtatBouton;
GPIO_Struct GPIO_InitStruct;
int main()
{
	// Activate GPIOs Clocks

	*RCC_APB2ENR |= 0x14; // Activation de l'horloge du PORT A/C

	// Configure GPIO Pins (Push Button)=PA0:Input Floating Mode

	// 	 GPIOA->CRL &=~((uint32_t)0xf); // Input Floating
	//  GPIOA->CRL |=0x4;

	GPIO_InitStruct.GPIO_PIN = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_InputFloating;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Configure GPIO Pins (LED)=PC9/PC8:Output Push Pull 2 MHZ

	// 	 GPIOC->CRH &=~((uint32_t)0xff);
	//  GPIOC->CRH|=0x11;

	GPIO_InitStruct.GPIO_PIN = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OutputPP2Mhz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	while (1)
	{
		// Test Push Button
		// Read Push Button State (0=Pressed, 1=Released)
		EtatBouton = GPIO_TestPin(GPIOA, GPIO_Pin_0);

		if (EtatBouton == 0) // If Pressed, Led ON
			GPIO_SetPin(GPIOC, GPIO_Pin_8 | GPIO_Pin_9);
		else // Released, Led OFF
			GPIO_ResetPin(GPIOC, GPIO_Pin_8 | GPIO_Pin_9);
	}
}
