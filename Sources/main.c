//#include "MPC5604B.h"

#include "includes.h"


void main(void)
{
	int flag = 1;
	
	init_all_and_POST();
	//read_rad_xyz = 1;
	//reset_rev_data();
	//g_f_enable_mag_steer_control = 1;
	g_f_enable_speed_control=1;
	//set_speed_target(0);
	//delay_ms(1000);//等待蓝牙配对
	//write_camera_data_to_TF();
	//test_file_system();
	//SetupCCD();
	//EMIOS_0.CH[3].CCR.B.FEN=1;//开场中断
	
	/*等待开始*/
	
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
	
	/* Loop forever */
		
	for (;;)
	{

		/* 执行远程命令 */
		if (REMOTE_FRAME_STATE_OK == g_remote_frame_state)
		{
			g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
			
			execute_remote_cmd(remote_frame_data+5);
		}


//		//serial_port_1_TX(0xAC);
//		//delay_ms(10);
//	
//
		/* 整车动作控制 */
		control_car_action();

		/* 报告在线 */
		report_online();
#if 0
		if(fieldover)
		{
			fieldover=0;
			//Display_Video();
			Send_CCD_Video();
			//D3=~D3;
			//write_camera_data_to_TF();
			
			EMIOS_0.CH[3].CSR.B.FLAG = 1;
			EMIOS_0.CH[3].CCR.B.FEN=1;
		}
#endif
		
	}

}
















