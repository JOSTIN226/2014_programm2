//#include "MPC5604B.h"

#include "includes.h"


void main(void)
{
	//int flag = 1;
	
	init_all_and_POST();
	//g_f_enable_speed_control=1;
	//set_speed_pwm(400);
	//delay_ms(6000);//等待蓝牙配对
	//write_camera_data_to_TF();
	//set_speed_target(10);
	//SetupBKL();
	//SetupCCD();	


	EMIOS_0.CH[3].CCR.B.FEN=1;//开场中断

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
		
		if(fieldover)
		{
			
			
			
			//D3=~D3;
			//write_camera_data_to_TF();
			fieldover=0;
			//FindBlackLine();
			Display_Video();
			//Send_CCD_Video();
			//Send_CCD_Blackline();
			//SteerControl();
		    if(Slope==0)
			serial_port_1_TX(RoadType);
			else if(Slope==1)
				serial_port_1_TX(0x31);
			else if(Slope==2)
				serial_port_1_TX(0x32);
			EMIOS_0.CH[3].CSR.B.FLAG = 1;
			EMIOS_0.CH[3].CCR.B.FEN=1;
		}
#endif
		
	}

}
















