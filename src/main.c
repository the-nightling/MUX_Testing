/**
 *****************************************************************************
 **
 **  File        : main.c
 **
 **  Abstract    : main function.
 **
 ** EEE3074W Project
 ** Laser Guitar Synthesizer
 ** MUX Testing
 ** Team 10
 **
 *****************************************************************************
 */

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* Private macro */
/* Private variables */
uint8_t counter = 0;

/* Private function prototypes */
void RCC_Configuration(void);
void GPIO_Configuration(void);
void Timer_Configuration(void);
void NVIC_Configuration(void);

/* IRQ Handlers */
void TIM2_IRQHandler(void)
{
	// Clear TIM10 interrupt pending bit
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		if(counter == 0)
		{
			GPIOE->BSRRH = GPIO_Pin_7;
			GPIOE->BSRRH = GPIO_Pin_9;
			GPIOE->BSRRH = GPIO_Pin_11;
		}
		else if (counter == 1)
		{
			GPIOE->BSRRH = GPIO_Pin_7;
			GPIOE->BSRRH = GPIO_Pin_9;
			GPIOE->BSRRL = GPIO_Pin_11;
		}
		else if (counter == 2)
		{
			GPIOE->BSRRH = GPIO_Pin_7;
			GPIOE->BSRRL = GPIO_Pin_9;
			GPIOE->BSRRH = GPIO_Pin_11;
		}
		else if (counter == 3)
		{
			GPIOE->BSRRH = GPIO_Pin_7;
			GPIOE->BSRRL = GPIO_Pin_9;
			GPIOE->BSRRL = GPIO_Pin_11;
		}
		else if (counter == 4)
		{
			GPIOE->BSRRL = GPIO_Pin_7;
			GPIOE->BSRRH = GPIO_Pin_9;
			GPIOE->BSRRH = GPIO_Pin_11;
		}
		else if (counter == 5)
		{
			GPIOE->BSRRL = GPIO_Pin_7;
			GPIOE->BSRRH = GPIO_Pin_9;
			GPIOE->BSRRL = GPIO_Pin_11;
		}


		counter++;
		if(counter > 5)
		{
			counter = 0;
		}
	}
}

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void)
{
	RCC_Configuration();
	NVIC_Configuration();
	GPIO_Configuration();
	Timer_Configuration();


	/* Infinite loop */
	while (1)
	{

	}
}

void RCC_Configuration(void)
{
	/* Enable the GPIO_LED Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOB, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	//GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the TIM10 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

void Timer_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period = 84000000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 1-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Enable the Interrupt Request */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	/* TODO, implement your code here */
	return -1;
}
