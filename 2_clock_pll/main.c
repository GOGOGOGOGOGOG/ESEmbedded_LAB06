#include <stdint.h>
#include "reg.h"
#include "blink.h"

void op_sysclk(unsigned int div);

int main(void)
{
	op_sysclk(4);
	blink(LED_BLUE);
}

/**
 * 
 * output sysclk (PC9)
 * 
 */
void op_sysclk(unsigned int div)
{
	
	//RCC
	CLEAR_BIT(RCC_BASE + RCC_CFGR_OFFSET, MCO2_1_BIT);
	CLEAR_BIT(RCC_BASE + RCC_CFGR_OFFSET, MCO2_0_BIT);



	if (div == 1)
		CLEAR_BIT(RCC_BASE + RCC_CFGR_OFFSET, MCO2PRE_2_BIT);

	else if (div >= 2 && div <= 5)
	{
		SET_BIT(RCC_BASE + RCC_CFGR_OFFSET, MCO2PRE_2_BIT);
		REG(RCC_BASE + RCC_CFGR_OFFSET) = (REG(RCC_BASE + RCC_CFGR_OFFSET) & ~(((uint32_t)0b11) << (MCO2PRE_0_BIT))) | ((uint32_t)(div - 2) << (MCO2PRE_0_BIT));
	}
	else
		while(1)
			;

	GPIO_InitDef GPIO_initstructure ;
    GPIO_initstructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_initstructure.GPIO_OType = GPIO_Type_pp;
	GPIO_initstructure.GPIO_PuPd = GPIO_PuPd_nopull;
	GPIO_initstructure.GPIO_Speed = GPIO_High_speed;
	GPIO_init(GPIO_PORTC,GPIO_Pin(9),&GPIO_initstructure);

	//SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTC));

	//GPIO MODER


	//Output push-pull
	
	//OSPEEDR9 = 11 => Very high speed
	

	//PUPDR9 = 00 => No pull-up, pull-down

}

