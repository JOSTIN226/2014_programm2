/*
 * stepmotor.h
 *
 *  Created on: Jul 6, 2015
 *      Author: JOSTIN
 */

#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_


#define SMotor_A SIU.GPDO[16].B.PDO	//PB0
#define SMotor_B SIU.GPDO[17].B.PDO	//PB1
#define SMotor_C SIU.GPDO[72].B.PDO	//PE8
#define SMotor_D SIU.GPDO[73].B.PDO	//PE9


void init_motorpit(void);
void MotorPit(void);
void init_Stepmotor(void);
void Motor_stop(void);
void Motor_A(void);
void Motor_B(void);
void Motor_C(void);
void Motor_D(void);





#endif /* STEPMOTOR_H_ */
