#ifndef __ACTION_H__
#define __ACTION_H__



/* 刺气球数据 */
#ifdef __ACTION_C_
struct
{
	DWORD time;
	int step;
} data_punctured_ballon = { 0x00000000, };
#else
extern struct
{
	DWORD time;
	int step;
} data_punctured_ballon;
#endif



extern void control_car_action(void);



extern void WiFi_control_car_1_action(WORD cmd);
extern void WiFi_control_car_2_action(WORD cmd);

extern void RFID_control_car_2_action(DWORD site);


#endif
