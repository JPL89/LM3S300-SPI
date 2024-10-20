/*
*	@File        MAIN.C	 		
*	@Author		JOSIMAR PEREIRA LEITE
*	@country	Brazil
*	@Date		20/10/2024
*
*	Copyright (C) 2024  JOSIMAR PEREIRA LEITE
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*/

#include "LM3S3xx.h"

void SPI_init(void);
void SPI_write(unsigned char data);

void SPI_init(void)
{
	RCGC1 |= (1UL << 4UL); /* SSI GLOCK */
	
	RCGC2 |= (1UL << 0UL); /* GPIOA CLOCK */

	GPIOAPUR |= ((1UL << 2UL)|(1UL << 3UL)|(1UL << 4UL)|(1UL << 5UL));
	GPIOAFSEL |= ((1UL << 2UL)|(1UL << 3UL)|(1UL << 4UL)|(1UL << 5UL));
	
	SSICPSR 	= 0x00000002;
	
	SSICR1 		= 0x000000000;
	
	SSICPSR		= 0x00000002;
		
	SSICR0		= 0x000000957; 
	
	SSICR1 		= 0x000000002;
}

/*************************************** MAIN ********************************************/

void SPI_write(unsigned char data)
{
	SSIDR = data;
	while((SSISR & 0x00000004) == 1);
}

int main (void)
{					
	/* CLOCK DIVIDER BY 10 ( 200MHZ / 10 = 20MHZ ) */
	RCC &=~((1UL << 23)|(1UL << 24)|(1UL << 24)|(1UL << 25)|(1UL << 26));
	RCC |=((1UL << 26)|(1UL << 25));
	
	RCC |=(1UL << 22UL); /* USES CLOCK DIVIDER */
	
	/* USES PPL */
	RCC &=~(1UL << 13);
	
	/* CLEAR CRYSTAL BITS AND SET 8MHZ CRYSTAL */
	RCC &=~((1UL << 6)|(1 << 7UL)|(1UL << 8UL)|(1UL << 9UL));	
	RCC |= ((1UL << 6UL)|(1UL << 8UL)|(1UL << 9UL)); 
	
	/* CLEAR OSCILATION SOURCE AND SET MAIN OSCILATION */
	RCC &=~((1UL << 4UL)|(1UL << 5UL));	
	
	SPI_init();
	
	SPI_write(0x45);
	
	while (1)
	{	
		
	}
}
