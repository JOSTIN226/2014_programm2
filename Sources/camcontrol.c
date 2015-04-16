﻿#include "includes.h"

//*****************************************************************************************************************
//************************************************控制参数************************************************    	  *
//*****************************************************************************************************************

//**********************舵机参数**********************************************
signed long target_offset=0,last_offset=0;	//舵机偏差值记录
double Steer_kp=0,Steer_kd=0;//舵机P、D值
WORD Steer_PWM[4]={0,0,0,0};//舵机输出值记录


//**********************电机参数**********************************************
word speedcounter1=0,speedcounter2=0;
signed int currentspeed=0,targetspeed=0;		//当前速度、目标速度
signed int Error=0,PreError=0,SumError=0;

double Speed_kp=0,Speed_ki=0,Speed_kd=0;	//电机PID值
signed int Motor_PWM=0;				//电机底层控制量

//********************辅助调试参数******************************************
unsigned int Counter_Error=0;		//光编接触不牢靠错误计数量
unsigned int StartTime2s=0;			//起始线时间计算(起车2s,延时一段时间再检测起始线,第二次见到起始线停车)
////********************起始线停车参数******************************************
byte stop_flag=0;
byte stop_delay=0;
	

//*****************************************************************************************************************
//************************************************角度控制************************************************    	  *
//*****************************************************************************************************************
void SteerControl()
{
	//*1***********出错图像角度控制,输出为前三次平均值**************
	if(RoadType==NoLine||RoadType==Wrong) {
		Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
		set_steer_helm_basement(Steer_PWM[3]);
		//存舵机值
		Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
		return;
	}
	//最低速
	if(Slope==1)					{Steer_kp=10;Steer_kd=5;}
	else if(Slope==2)				{Steer_kp=8;Steer_kd=5;}
	
	else if(ABS(target_offset)<6) 	{Steer_kp=5;Steer_kd=5;}
	else if(ABS(target_offset)<26)  {Steer_kp=15.2+target_offset*target_offset/100;Steer_kd=10;}
	else {Steer_kp=15.8+target_offset*target_offset/500;Steer_kd=5;}


	
	Steer_PWM[3]=STEER_HELM_CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
	//if(ABS(Steer_PWM[3]-Steer_PWM[2])>250) Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
	//感觉不太靠谱，调的不好
	
	//舵机限值+舵机输出
	if(Steer_PWM[3]>STEER_HELM_LEFT) Steer_PWM[3]=STEER_HELM_LEFT;
	else if(Steer_PWM[3]<STEER_HELM_RIGHT) Steer_PWM[3]=STEER_HELM_RIGHT;
	set_steer_helm_basement(Steer_PWM[3]);
	
	//存舵机值和offset值
	Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
	last_offset=target_offset;
}


//*****************************************************************************************************************
//************************************************PIT中断************************************************    	  *
//*****************************************************************************************************************
#if 0
void PitISR(void)//10ms一个控制周期
{  
    	//得到光编反馈值的绝对值及符号
		speedcounter1=EMIOS_0.CH[24].CCNTR.R;
		if(speedcounter1<speedcounter2)
		{
			currentspeed=speedcounter1+65536-speedcounter2;
		}
		else currentspeed=speedcounter1-speedcounter2;
		
		if(data_encoder.is_forward) currentspeed=currentspeed;
		else currentspeed=-currentspeed;
	    speedcounter2=speedcounter1;
	    
	    
	    //光编错误计数
	    if(currentspeed==0) Counter_Error++;
	    else Counter_Error=0;
	    
	    SpeedControl();
	}
  	PIT.CH[1].TFLG.B.TIF = 1;	//write 1 to clear PIT1 清除标志位
}
#endif
//*****************************************************************************************************************
//************************************************速度控制************************************************    	  *
//*****************************************************************************************************************
void SpeedControl()
{
	//1*******************************起始线停车速度控制及光编线接触不牢控制***********************
//	if(StartLine){
//    	stop_delay++;
//
//    		if(stop_delay==43){
//		    	if(stop_flag==2) set_speed_pwm(0);
//		    	else if(data_encoder.is_forward) set_speed_pwm(-300);
//		    	else stop_flag++;
//		    	stop_delay--;
//		      	return;
//		    }
//	}
//   	if(Counter_Error>50) {set_speed_pwm(0);return;}
//   	
//   	StartTime2s++;
	//2*****正常速度控制...速度分配还要结合最远行和offset


   //最低速
	if(Slope==1)				{targetspeed=180;
									Speed_kp=6.5;Speed_ki=0.1;Speed_kd=0.2;}
	else if(Slope==2)			{targetspeed=140;
									Speed_kp=6;Speed_ki=0.1;Speed_kd=0.2;}
									
	else if(RoadEnd<15)			{targetspeed=175;
									Speed_kp=5.5;Speed_ki=0.1;Speed_kd=0.2;}
	else if(RoadEnd<30)			{targetspeed=155-target_offset*target_offset/40;
									Speed_kp=5.5;Speed_ki=0.2;Speed_kd=0.2;}
	else						{targetspeed=130;
									Speed_kp=5.5;Speed_ki=0.2;Speed_kd=0.2;}


//	if(StartTime2s<290)	{if(currentspeed>targetspeed) SumError=0;}
//	else {StartTime2s--;}
	
	
	
    Error=(signed int)(targetspeed)-(signed int)(currentspeed);
    
    SumError+=Error;
    if(SumError>3000) SumError=3000;
    if(SumError<-3000) SumError=-3000;
    

   	Motor_PWM=Speed_kp*Error+Speed_ki*SumError+Speed_kd*(Error-PreError);
   	
    if(Motor_PWM>Motor_PWM_MAX)  Motor_PWM=Motor_PWM_MAX;
	else if(Motor_PWM<Motor_PWM_MIN)  Motor_PWM=Motor_PWM_MIN;
    set_speed_pwm(Motor_PWM);
	
	PreError=Error;
}
