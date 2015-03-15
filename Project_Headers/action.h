#ifndef __ACTION_H__
#define __ACTION_H__


#define ACTION_PUNCTURED_BALLON	/* 刺气球 */
#define ACTION_PUNCTURED_BALLON_STEP_NO (0x00)	/* 不执行 */
#define ACTION_PUNCTURED_BALLON_STEP_1 (0x01)	/* 转弯 */
#define ACTION_PUNCTURED_BALLON_STEP_2 (0x02)	/* 前进 */
#define ACTION_PUNCTURED_BALLON_STEP_3 (0x03)	/* 停留 */
#define ACTION_PUNCTURED_BALLON_STEP_4 (0x04)	/* 后退 */
#define ACTION_PUNCTURED_BALLON_STEP_5 (0x05)	/* 反向转弯 */
#define ACTION_PUNCTURED_BALLON_STEP_6 (0x06)	/* 回到线上 */
#define ACTION_PUNCTURED_BALLON_STEP_OK (0x07)	/* 完成 */

#define ACTION_PUNCTURED_BALLON_STEP_CAR3_TURN1 (0x08)	/* 车3第1次转弯 */
#define ACTION_PUNCTURED_BALLON_STEP_CAR4_TURN1 (0x09)	/* 车4第1次转弯 */
#define ACTION_PUNCTURED_BALLON_STEP_CAR3_TURN2 (0x0a)	/* 车3第2次转弯 */
#define ACTION_PUNCTURED_BALLON_STEP_CAR4_TURN2 (0x0b)	/* 车4第2次转弯 */


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
void speed_up_bridge1();
void puncture_ballon();
void puncture_ballon_2();
void turn_left_1();
void turn_left_2();
void speed_up_bridge2();
void speed_down_bridge2();
void push_box2();
void avoid_box();
void fly_bridge();
void push_box1();

extern void WiFi_control_car_1_action(WORD cmd);
extern void WiFi_control_car_2_action(WORD cmd);
extern void WiFi_control_car_3_action(WORD cmd);
extern void WiFi_control_car_4_action(WORD cmd);
extern void RFID_control_car_1_action(DWORD site);
extern void RFID_control_car_2_action(DWORD site);
extern void RFID_control_car_3_action(DWORD site);
extern void RFID_control_car_4_action(DWORD site);


#endif
