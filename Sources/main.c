//#include "MPC5604B.h"

#include "includes.h"


void main(void)
{
	//int flag = 1;
	
	init_all_and_POST();
	//read_rad_xyz = 1;
	//reset_rev_data();
	//g_f_enable_mag_steer_control = 1;
//	g_f_enable_speed_control=1;
	//delay_ms(6000);//等待蓝牙配对
	//write_camera_data_to_TF();
	//set_speed_target(10);
	//SetupCCD();	
	L1=1;
	L2=1;
	L3=1;
	L4=1;
	//L5=1;
	//L6=1;
	D1=0;
	D2=0;
	D3=0;
	D0=0;
	
	EMIOS_0.CH[3].CCR.B.FEN=1;//开场中断

	/*等待开始*/
#if 0	
	while(!g_start_all&&(WIFI_ADDRESS_CAR_4 == g_device_NO||WIFI_ADDRESS_CAR_3 == g_device_NO))
	{
		if (REMOTE_FRAME_STATE_OK == g_remote_frame_state)
		{
			g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
			
			execute_remote_cmd(remote_frame_data+5);
		}
		delay_ms(10);
	}
 	
	if(WIFI_ADDRESS_CAR_3 == g_device_NO)
		set_speed_target(10);
	else if(WIFI_ADDRESS_CAR_4 == g_device_NO)
	{
		delay_ms(1000);
		set_speed_target(10);
	}
	else 	set_speed_target(0);
#endif	
	/* Loop forever */
		
	for (;;)
	{

#if 0
		/* 执行远程命令 */
		if (REMOTE_FRAME_STATE_OK == g_remote_frame_state)
		{
			g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
			
			execute_remote_cmd(remote_frame_data+5);
		}


		//serial_port_1_TX(0xAC);
		//delay_ms(10);
	

		/* 整车动作控制 */
		control_car_action();

		/* 报告在线 */
		report_online();
#endif
#if 1
//		D3=~D3;
		if(fieldover)
		{
			
			Display_Video();
			//Send_CCD_Video();
//			D4=~D4;

			//write_camera_data_to_TF();
			fieldover=0;
			//FindBlackLine();
			
			//SteerControl();
//		    if(Slope==0)
			//serial_port_1_TX(RoadType);
//			else if(Slope==1)
//				LINFlex_TX(0x31);
//			else if(Slope==2)
//				LINFlex_TX(0x32);
			EMIOS_0.CH[3].CSR.B.FLAG = 1;
			EMIOS_0.CH[3].CCR.B.FEN=1;
		}
#endif
		
	}

}
















