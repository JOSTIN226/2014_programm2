﻿#define __CONTROL_C_
#include "includes.h"


int g_f_pit = 0;
int g_f_enable_mag_steer_control = 0;	/* 启用电磁循迹标志位 */
int g_f_enable_speed_control = 0;	/* 启用速度控制标志位 */
int g_f_enable_rad_control_1 = 0;		/* 启用陀螺仪角度控制漂移标志位*/
int g_f_enable_rad_control_2 = 0;		/* 启用陀螺仪角度控制转向标志位 */
int g_f_enable_speed_control_2 = 0;		/* 启用陀螺仪角度控制上下坡标志位 */
int angle1 = 0; 		 /* 启用陀螺仪角度控制转向标志位   转向角度值 */
int g_f_enable_single_bridge_control = 0;		/*单边桥标志位*/
int g_f_enable_fly_bridge = 0;		/* 飞桥标志位 */
int g_f_enable_steer_bridge = 0;		/* 钢丝桥标志位 */
int speed = 0;
int read_rad_xyz = 0;/* 启用读陀螺仪xyz三轴数据 */
int find_mag_back_box = 0; 	/*找回磁线  推箱子*/
int update_steer_helm_basement_to_steer_helm(void);
int find_mag_back_box_2=0;
int find_mag_back_car1=0;
int g_f_big_U=0;
int g_f_big_U_2=0;


/*-----------------------------------------------------------------------*/
/* 舵机初始化 	                                                                      */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* PIT中断处理函数                                                                 */
/*-----------------------------------------------------------------------*/
void PitISR(void)
{
	g_f_pit = 1;
	
	g_time_basis_PIT++;	/* 计时 */
#if 1	
	/* start:encoder */
	data_encoder.is_forward = SIU.GPDI[46].B.PDI;//PC14
	data_encoder.cnt_old = data_encoder.cnt_new;
	data_encoder.cnt_new = (WORD)EMIOS_0.CH[15].CCNTR.R;//PC15
	if (data_encoder.cnt_new >= data_encoder.cnt_old)
	{
		data_encoder.speed_now = data_encoder.cnt_new - data_encoder.cnt_old;
	}
	else
	{
		data_encoder.speed_now = 0xffff - (data_encoder.cnt_old - data_encoder.cnt_new);
	}
	/* end:encoder */
#endif
	
	
	/* 开始执行速度控制算法 */
	if (g_f_enable_speed_control)
	{
		//SpeedControl();//不同路段PID,尚未调,不可用
		contorl_speed_encoder_pid();
//		LCD_PrintoutInt(32, 0, data_encoder.speed_now);
//		LCD_PrintoutInt(32, 2, data_encoder.cnt_old);
//		LCD_PrintoutInt(32, 4, data_encoder.cnt_new);
//		LCD_PrintoutInt(64, 4, g_time_basis_PIT++);
//		LCD_PrintoutInt(32, 6, data_encoder.is_forward);
	}
#if 0
	/* 电磁循迹 */
	if (g_f_enable_mag_steer_control)
	{
		mag_read();
		control_steer_helm();
	}
	
	/*找回磁线  推箱子*/
	if(find_mag_back_box )
	{
		mag_read();
		if(mag_left>500 && mag_right<100) 
		{
			g_f_enable_mag_steer_control=1;
			find_mag_back_box=0;
			g_f_enable_rad_control_2=0;
		}
	}
	/*找回磁线  漂移车*/
	if(find_mag_back_car1 )
	{
		mag_read();
		if(mag_right>500 && mag_left<100) 
		{
			g_f_enable_mag_steer_control=1;
			find_mag_back_car1=0;
			g_f_enable_rad_control_2=0;
		}
	}

	/* 读陀螺仪三轴数据 */
	if(read_rad_xyz)
	{
		if (!read_rev_data())	/* 不是每次都能读出来的 */
		{
#if 0
			LCD_PrintoutInt(64, 0, rad.x);
			LCD_PrintoutInt(64, 2, rad.y);
			LCD_PrintoutInt(64, 4, rad.z);
#endif
		}
	}
	
	/* 陀螺仪角度控制漂移*/
	if (g_f_enable_rad_control_1 != 0)
	{
		if (!control_steer_helm_2(g_f_enable_rad_control_1))
		{
			g_f_enable_mag_steer_control=1; 
			set_steer_helm((WORD)(data_steer_helm.center));	
			if(g_f_enable_rad_control_1==1)
			{
				set_speed_target(20);
			}
			if(g_f_enable_rad_control_1==2||g_f_enable_rad_control_1==3)
			{
				set_speed_target(0);
			}
			g_f_enable_rad_control_1 =0; 
		}
	}
	
	/* 陀螺仪角度控制转向 */
	if(g_f_enable_rad_control_2)
	{
		if (!control_steer_helm_3(angle1))
		{
			g_f_enable_rad_control_2 =0;  
			set_steer_helm((WORD)(data_steer_helm.center));	
			if(find_mag_back_box_2==1)
			{
				find_mag_back_box=0;
				find_mag_back_box_2=1;
				g_f_enable_mag_steer_control=1;
				set_speed_target(20);
			}
		}
	}
	
	
	/* 陀螺仪控制上下坡 */
	if(g_f_enable_speed_control_2)
	{
		control_speed_target_1(speed);
	}
#endif	
#if 0
	/* 发送位置 */
	{
		BYTE data[7];
		
		generate_remote_net_frame_to_send_site(WIFI_NET_CMD_CAR_REPORT_CURRENT_SITE, RFID_site_data.site, data);
		generate_remote_frame(WIFI_CMD_NET, data, sizeof(data));
	}
#endif

	PIT.CH[1].TFLG.B.TIF = 1;	// MPC56xxB/P/S: Clear PIT 1 flag by writing 1
}


/*-----------------------------------------------------------------------*/
/* 设置速度PWM      电机接口函数                                                             */
/*-----------------------------------------------------------------------*/
void set_speed_pwm(int16_t speed_pwm)	//speed_pwm正为向前，负为向后
{
	if (speed_pwm>0)	//forward
	{
		if (speed_pwm>SPEED_PWM_MAX)
		{
			speed_pwm = SPEED_PWM_MAX;
		}
		EMIOS_0.CH[17].CBDR.R = speed_pwm;//PE1
		EMIOS_0.CH[18].CBDR.R = 1;//PE2
		
	}
	else if (speed_pwm<0)	//backward
	{
		speed_pwm = 0-speed_pwm;
		if (speed_pwm>SPEED_PWM_MAX)
		{
			speed_pwm = SPEED_PWM_MAX;
		}

		EMIOS_0.CH[17].CBDR.R = 1;
		EMIOS_0.CH[18].CBDR.R = speed_pwm;	
	}
	else
	{
		EMIOS_0.CH[17].CBDR.R = 1;
		EMIOS_0.CH[18].CBDR.R = 1;	
	}
}


/*-----------------------------------------------------------------------*/
/* BangBang速度控制                                                             */
/*-----------------------------------------------------------------------*/
void contorl_speed_encoder_bb(void)
{
	int32_t tmp_speed_now;
	
	
	if (data_encoder.is_forward)
	{
		tmp_speed_now = data_encoder.speed_now;
	}
	else
	{
		tmp_speed_now = 0 - data_encoder.speed_now;
	}
	
	if (tmp_speed_now > data_speed_settings.speed_target)
	{
		set_speed_pwm(0 - SPEED_PWM_MAX);
	}
	else if (tmp_speed_now < data_speed_settings.speed_target)
	{
		set_speed_pwm(SPEED_PWM_MAX);
	}
}


/*-----------------------------------------------------------------------*/
/* 获得速度偏差                                                                      */
/* 有问题找叶川                                                                      */
/*-----------------------------------------------------------------------*/
static SWORD get_e0()
{
	SWORD tmp_speed_now;
	SWORD e0;
	if (data_encoder.is_forward)
	{
		tmp_speed_now =(SWORD) data_encoder.speed_now;
	}
	else
	{
		tmp_speed_now = 0 - (SWORD) data_encoder.speed_now;
	}
	e0=data_speed_settings.speed_target-tmp_speed_now;
	return e0;
	
}


/*-----------------------------------------------------------------------*/
/* PID速度控制                                                                       */
/* 有问题找叶川                                                                      */                                                          
/*-----------------------------------------------------------------------*/
void contorl_speed_encoder_pid(void)
{
	float d_speed_pwm;
	SWORD e0=get_e0();
	static SWORD e1=0;
	static SWORD e2=0;
	static SWORD speed_pwm=SPEED_PWM_MIN;
	d_speed_pwm=(float)(data_speed_pid.p*(e0-e1));       //P控制
	d_speed_pwm+=(float)(data_speed_pid.d*(e0+e2-2*e1));
	d_speed_pwm+=(float)(data_speed_pid.i*(e0));		
	if(d_speed_pwm>200)
	      d_speed_pwm=200;
	if(d_speed_pwm<-200)
	      d_speed_pwm=-200;   //限制pwm变化量
	speed_pwm+=d_speed_pwm;
	if(speed_pwm>SPEED_PWM_MAX)
			speed_pwm = SPEED_PWM_MAX;
	else if (speed_pwm<0-SPEED_PWM_MAX)
			speed_pwm =0- SPEED_PWM_MAX;    //防止溢出（造成负数）
	set_speed_pwm(speed_pwm);
	e2=e1;
	e1=e0;	
}


/*-----------------------------------------------------------------------*/
/* 设置目标速度                                                                      */
/*-----------------------------------------------------------------------*/
void set_speed_target(SWORD speed_target)
{
	data_speed_settings.speed_target = speed_target;
}


/*-----------------------------------------------------------------------*/
/* 设置速度PID控制P值                                                            */
/*-----------------------------------------------------------------------*/
void set_speed_KP(WORD kp)
{
	data_speed_pid.p = kp;
}


/*-----------------------------------------------------------------------*/
/* 设置速度PID控制I值                                                             */
/*-----------------------------------------------------------------------*/
void set_speed_KI(WORD ki)
{
	data_speed_pid.i = ki;
}


/*-----------------------------------------------------------------------*/
/* 设置速度PID控制D值                                                            */
/*-----------------------------------------------------------------------*/
void set_speed_KD(WORD kd)
{
	data_speed_pid.d = kd;
}

/*-----------------------------------------------------------------------*/
/* 陀螺仪控制转向   //叶川添加                                            */
/*-----------------------------------------------------------------------*/
void control_angle_steer_helm(int angle_target)
{
	reset_rev_data();
	read_rad_xyz = 1;
	g_f_enable_rad_control_2=1;
	angle1=angle_target;
	if(find_mag_back_box_2) start_time = g_time_basis_PIT;
}
/*-----------------------------------------------------------------------*/
/* 陀螺仪控制速度   //周斯航添加                                            */
/*-----------------------------------------------------------------------*/

void control_speed_motor(int speed_target)
{
	reset_rev_data();
	read_rad_xyz = 1;
	g_f_enable_speed_control_2 = 1;	
	speed = speed_target;
}



/*-----------------------------------------------------------------------*/
/* 设置方向舵机位置                                                                */
/* 统一舵机访问接口                                                                */
/* 负数左舵，正数右舵，零中值                                                 */
/*-----------------------------------------------------------------------*/
void set_steer_helm(SWORD helmData)
{
	if(helmData <= data_steer_helm.left_limit)
	{
		helmData = data_steer_helm.left_limit;
	}
	else if(helmData >= data_steer_helm.right_limit)
	{
		helmData = data_steer_helm.right_limit;
	}
	helm_data_record = helmData;
	helmData = (WORD)(helmData*data_steer_helm_basement.direction + data_steer_helm_basement.center);
	set_steer_helm_basement(helmData);
}

/*-----------------------------------------------------------------------*/
/* 设置方向舵机位置                                                                */
/* 对于白色信号线的舵机：                                                       */
/* 面对舵机轴，占空比增大，舵机逆时针旋转，对我们的车是左舵    */
/* 对于橙色信号线的舵机：                                                       */
/* 相反                                                                                  */
/* 直接方向舵机寄存器                                                             */
/* 有限幅                                                                               */
/* 舵机接口函数                                                                          */
/*-----------------------------------------------------------------------*/
void set_steer_helm_basement(WORD helmData)
{
	if(helmData <= 1500)
	{
		helmData = 1500;
	}
	else if(helmData >= 5000)
	{
		helmData = 5000;
	}
	EMIOS_0.CH[9].CBDR.R = helmData;
}


/*-----------------------------------------------------------------------*/
/* 设置方向舵机底层数据 中值                                                   */
/* 更改方向舵机寄存器                                                             */
/*-----------------------------------------------------------------------*/
void set_steer_helm_basement_center(WORD helmData)
{
	data_steer_helm_basement.center = helmData;
	set_steer_helm_basement(helmData);
}


/*-----------------------------------------------------------------------*/
/* 设置方向舵机底层数据 左极限                                                */
/* 更改方向舵机寄存器                                                             */
/*-----------------------------------------------------------------------*/
void set_steer_helm_basement_left_limit(WORD helmData)
{
	data_steer_helm_basement.left_limit = helmData;
	set_steer_helm_basement(helmData);
}


/*-----------------------------------------------------------------------*/
/* 设置方向舵机底层数据 右极限                                                */
/* 更改方向舵机寄存器                                                             */
/*-----------------------------------------------------------------------*/
void set_steer_helm_basement_right_limit(WORD helmData)
{
	data_steer_helm_basement.right_limit = helmData;
	set_steer_helm_basement(helmData);
}


/*-----------------------------------------------------------------------*/
/* 将方向舵机底层数据更新到方向舵机上层数据                            */
/* 校验数据是否合理                                                                */
/* 合理则修改 返回0                                                                */
/* 不合理拒绝修改 返回1                                                          */
/*-----------------------------------------------------------------------*/
int update_steer_helm_basement_to_steer_helm(void)
{
	if(data_steer_helm_basement.left_limit < data_steer_helm_basement.center && data_steer_helm_basement.center < data_steer_helm_basement.right_limit)
	{
		data_steer_helm_basement.direction = 1;
		data_steer_helm.left_limit = (SWORD)(data_steer_helm_basement.left_limit - data_steer_helm_basement.center);
		data_steer_helm.right_limit = (SWORD)(data_steer_helm_basement.right_limit - data_steer_helm_basement.center);
	}
	else if (data_steer_helm_basement.left_limit > data_steer_helm_basement.center && data_steer_helm_basement.center > data_steer_helm_basement.right_limit)
	{
		data_steer_helm_basement.direction = -1;
		data_steer_helm.left_limit = (SWORD)(data_steer_helm_basement.center - data_steer_helm_basement.left_limit);
		data_steer_helm.right_limit = (SWORD)(data_steer_helm_basement.center - data_steer_helm_basement.right_limit);
	}
	else
	{
		return 1;
	}
	return 0;
}


/*-----------------------------------------------------------------------*/
/* 获取两个周期计数的差值，常用故写成函数                               */
/*-----------------------------------------------------------------------*/
DWORD diff_time_basis_PIT(const DWORD new_time, const DWORD old_time)
{
	DWORD diff;
	
	if (new_time >= old_time)
	{
		diff = new_time - old_time;
	}
	else
	{
		diff = new_time + (0xFFFFFFFF- old_time);
	}
	
	return diff;
}
#if 0
int abs(int data)
{
	if (data<0)
		data=0-data;
	return data;
}
#endif
