//#include "MPC5604B.h"

#include "includes.h"


void main(void)
{
	//int flag = 1;
	
	init_all_and_POST();
	//g_f_enable_speed_control=1;
	//delay_ms(6000);//等待蓝牙配对
	//write_camera_data_to_TF();
	//set_speed_target(10);
	//SetupBKL();
//	SetupCCD();	
	g_f_enable_speed_control=0;
	g_f_enable_supersonic=1;
//	EMIOS_0.CH[3].CCR.B.FEN=1;//开场中断
//	LCD_write_english_string(96,0,"T");

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

		/* 整车动作控制 */
		//control_car_action();

		/* 报告在线 */
		report_online();
#endif
#if 0
		if(fieldover)
		{
			
			//write_camera_data_to_TF();
			fieldover=0;
			FindBlackLine();
			Display_Video();
			//serial_port_1_TX(RoadType);
			if(target_offset<0)
				LCD_write_english_string(96,1,"-");
			else LCD_write_english_string(96,1,"+");
			LCD_Write_Num(105,1,ABS(target_offset),2);
			Send_CCD_Video();
			//Send_CCD_Blackline();
			SteerControl();
			D3=~D3;//7ms
			//write_camera_data_to_TF();
			EMIOS_0.CH[3].CSR.B.FLAG = 1;
			EMIOS_0.CH[3].CCR.B.FEN=1;
		}
#endif
		
	}

}


