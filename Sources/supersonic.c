#define __SUPERSONIC_C_
#include "includes.h"


//**********************超声0***************************
void init_supersonic_trigger_0(void)
{
	EMIOS_0.CH[0].CCR.B.BSL = 0x3;//use internal counter
	EMIOS_0.CH[0].CCR.B.UCPRE=0;//internal prescaler clock divider as 1
	EMIOS_0.CH[0].CCR.B.UCPEN = 1;//enable prescaler 
	EMIOS_0.CH[0].CCR.B.FREN = 0;
	EMIOS_0.CH[0].CCR.B.EDPOL=0;
	EMIOS_0.CH[0].CCR.B.EDSEL = 0;
	EMIOS_0.CH[0].CCR.B.FEN=0;
	
	EMIOS_0.CH[0].CADR.B;
	SIU.PCR[0].R =0x0603;	//trigger A0 65us
	
	EMIOS_0.CH[0].CADR.B.CADR = 0x0000ff;
	
	EMIOS_0.CH[0].CCR.B.MODE = 0x03;
	//tmp_time.R = 0x00000000;
	
}

void init_supersonic_trigger_0_2(void)
{
	SIU.PCR[0].R =0x0203;	//GPIO
}
void supersonic_trigger_0_2(void)
{
	SIU.GPDO[0].B.PDO=1;
	delay_us(20);
	SIU.GPDO[0].B.PDO=0;
	//tmp_time.R = 0x00000000;
}
void init_supersonic_receive_0(void)
{
	EMIOS_0.CH[1].CCR.B.MODE = 0x04; // Mode is Input Pulse Width Measurement 
	EMIOS_0.CH[1].CCR.B.BSL = 0x3;   // Use internal counter
	EMIOS_0.CH[1].CCR.B.UCPRE=0; //Set channel prescaler to divide by 1
	EMIOS_0.CH[1].CCR.B.UCPEN = 1;	//Enable prescaler; uses default divide by 1
	EMIOS_0.CH[1].CCR.B.FREN = 0;	//Freeze channel counting when in debug mode
	EMIOS_0.CH[1].CCR.B.EDPOL=1; //Edge Select rising edge
	EMIOS_0.CH[1].CCR.B.FEN=1;  //interupt enbale

	SIU.PCR[1].R = 0x0100;  //E PA1
	INTC_InstallINTCInterruptHandler(intc_get_supersonic_time_0, 141, 4);
}

void trigger_supersonic_0(void)
{
	EMIOS_0.CH[0].CCR.B.MODE = 0x01;
	EMIOS_0.CH[0].CCR.B.MODE = 0x03;
}

void intc_get_supersonic_time_0(void)
{
	DWORD tmp_a, tmp_b;
	tmp_a = EMIOS_0.CH[1].CADR.R;
	tmp_b = EMIOS_0.CH[1].CBDR.R;
	
	if(tmp_a >= tmp_b)
	{
		tmp_time.R = tmp_a - tmp_b;
	}
	else
	{
		tmp_time.R = 0x00ffffff - tmp_b + tmp_a;
	}
	
	EMIOS_0.CH[1].CSR.B.FLAG = 1;	//清除中断标志位
	
	//关中断
	//EMIOS_0.CH[3].CCR.B.FEN = 0;
}

