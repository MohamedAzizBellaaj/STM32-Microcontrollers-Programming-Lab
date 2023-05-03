#include "gpio.h"

int GPIO_TestPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	uint16_t test = GPIOx->IDR & GPIO_Pin;
	if (test == 1)
		return 0;
	else
		return 1;
}

void GPIO_SetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRR = GPIO_Pin;
}

void GPIO_ResetPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BRR = GPIO_Pin;
}
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_Struct *GPIO_InitStruct)
{
	uint16_t i;
	for (i = 0; i < 16; i++)
	{
		uint16_t IsPin = (GPIO_InitStruct->GPIO_PIN) & (1 << i);
		if (IsPin == 1 << i)
		{
			if (i < 8)
			{
				GPIOx->CRL &= ~((uint32_t)0xF << 4 * i);
				GPIOx->CRL |= GPIO_InitStruct->GPIO_Mode << 4 * i;
			}
			else
			{
				GPIOx->CRH &= ~((uint32_t)0xF << 4 * (i - 8));
				GPIOx->CRH |= GPIO_InitStruct->GPIO_Mode << 4 * (i - 8);
			}
		}
	}
}
