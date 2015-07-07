#define __STEPMOTOR_C_
#include "includes.h"

int stepspeed=30;

/*-----------------------------------------------------------------------*/
/* 初始化步进电机PIT中断                                                         */
/* 1ms                                                                  */
/*-----------------------------------------------------------------------*/
void init_motorpit(void)
{
	/* NOTE:  DIVIDER FROM SYSCLK TO PIT ASSUMES DEFAULT DIVIDE BY 1 */
	PIT.PITMCR.R = 0x00000001;	/* Enable PIT and configure timers to stop in debug modem */
	PIT.CH[2].LDVAL.R = 80000;	/* 80000==1ms */
	PIT.CH[2].TCTRL.R = 0x00000003;	/* Enable PIT1 interrupt and make PIT active to count */
	INTC_InstallINTCInterruptHandler(MotorPit,61,3);	/* PIT 2 interrupt vector with priority 3 */
}

void MotorPit(void)
{
	static int timer=0;
	static int ABCD=0;
	if(timer==stepspeed)
	{
		if(ABCD==0)
		{
			Motor_A();
		}
		else if(ABCD==1)
		{
			Motor_B();
		}
		else if(ABCD==2)
		{
			Motor_C();
		}
		else if(ABCD==3)
		{
			Motor_D();
		}
		
		timer=0;
		ABCD++;
		ABCD=ABCD%4;
	}
	else
		timer++;
	D6=~D6;
	D8=~D8;
		
	PIT.CH[2].TFLG.B.TIF = 1;	// MPC56xxB/P/S: Clear PIT 1 flag by writing 1
}
/*-----------------------------------------------------------------------*/
/* 初始化步进电机ABCD相                                                         */
/* PB11 PB12 PB13 PB15                                                   */
/*-----------------------------------------------------------------------*/
void init_Stepmotor(void)
{
 	SIU.PCR[16].R = 0x0203;	/* A相 PB0  */
  	SIU.PCR[17].R = 0x0203; /* B相 PB1 */
 	SIU.PCR[72].R = 0x0203; /* C相 PE8 */
	SIU.PCR[73].R = 0x0203;	/* D相 PE9  */	

	Motor_stop();
}
void Motor_stop(void)
{
	SMotor_A=1;
	SMotor_B=1;
	SMotor_C=1;
	SMotor_D=1;
}
void Motor_A(void)
{
	SMotor_A=0;
	SMotor_B=1;
	SMotor_C=1;
	SMotor_D=1;
}
void Motor_B(void)
{
	SMotor_A=1;
	SMotor_B=0;
	SMotor_C=1;
	SMotor_D=1;
}
void Motor_C(void)
{
	SMotor_A=1;
	SMotor_B=1;
	SMotor_C=0;
	SMotor_D=1;
}
void Motor_D(void)
{
	SMotor_A=1;
	SMotor_B=1;
	SMotor_C=1;
	SMotor_D=0;
}
