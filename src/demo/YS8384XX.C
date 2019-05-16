	/*****************************************************
; �ش��Ƽ�YS8384ϵ�д�����
;File Name :YS65F804.C
;20180507
;Version : 1.1
*****************************************************/
#include "YS8384XXU.h"
#include "83_84Touch.h"
#include "TouchLib.h"
#include "Uart.h"
#include "User.h"

#ifdef UART_EN
void InitTimer(void)
{
	OPT_REG = 0x00;  	// 2��Ƶ
	TMR0 = 256 - 52;	// 9600������
	UART_H();
	INTS = 0X00;
	TMR0EN = 1;		//ʹ�ܶ�ʱ��0
	SET_UART_OUTPUT();
}
#endif 

void InitPort(void)
{
	CPIOA = 0X00;
	PAPHR = 0X00;
	PAINTR = 0X00;
	PORTA = 0X00;
	
	CPIOB = 0X00;
	PBPHR = 0X00;
	PBINTR = 0X00;
	PORTB = 0X00;

	CPIOC = 0X00;
	PCPHR = 0X00;
	PORTC = 0X00;

	ADINS = 0X00;
	
	CPIOD = 0X00;
	PDPHR = 0X00;
	PORTD = 0X00;
}
	


void main(void)
{
	INTS = 0X00;
	
	SET_HIRC(IRCF_8M);
	
	RAM_BANK3();
	
	InitPort();
	InitTouch();
	CheckLowClk(TOUCH_SCAN_TIME);
	
	#ifdef UART_EN
	InitTimer(); 
	#endif 

	while(1)
	{
		CLR_WDT();
		
		if(CSIF)
		{
			CSIF = 0;
			TouchPro();  //�����㷨����
			User();  //�û�����


			#ifdef UART_EN
		//	UartSendCap(&Cap, 0);  //ͨ��Uart���͵���ֵ
			UartSendUintByHex(&TouchResult,1);  //ͨ��Uart���ʹ������ֵ
			#endif
		}
	}
}

void interrupt Isr(void)
{
	;
}