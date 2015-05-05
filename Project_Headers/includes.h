#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#ifndef _TYPEDEF_BYTE_
#define _TYPEDEF_BYTE_
typedef unsigned char BYTE;
#endif

#ifndef _TYPEDEF_SBYTE_
#define _TYPEDEF_SBYTE_
typedef signed char SBYTE;
#endif

#ifndef _TYPEDEF_WORD_
#define _TYPEDEF_WORD_
typedef unsigned short WORD;
#endif

#ifndef _TYPEDEF_SWORD_
#define _TYPEDEF_SWORD_
typedef signed short SWORD;
#endif

#ifndef _TYPEDEF_DWORD_
#define _TYPEDEF_DWORD_
//typedef unsigned int DWORD;
typedef unsigned long int DWORD;
#endif

#if 0
#ifndef _TYPEDEF_byte_
#define _TYPEDEF_byte_
typedef unsigned char byte;
#endif

#ifndef _TYPEDEF_word_
#define _TYPEDEF_word_
typedef unsigned short word;
#endif
#endif

#include "MPC5604B.h"
#include "ff.h"	/* 定义了FATFS，后面要用 */
#include "init.h"
#include "control.h"
#include "supersonic.h"
#include "sdcard.h"
#include "time.h"
#include "lcd.h"
#include "WiFi.h"
#include "UART.h"
#include "L3G4200D.h"
#include "RFIDCard.h"
#include "mag.h"
#include "drifting.h"
#include "action.h"
#include "IntcInterrupts.h"
#include "video.h"
#include "camcontrol.h"
#include "analyse.h"



///****************LED&LIGHT****************///
#define D0 SIU.GPDO[40].B.PDO
#define D1 SIU.GPDO[45].B.PDO
#define D2 SIU.GPDO[44].B.PDO
#define D3 SIU.GPDO[71].B.PDO
#define D5 SIU.GPDO[12].B.PDO


#define LeftL SIU.GPDO[26].B.PDO
#define RightL SIU.GPDO[27].B.PDO
#define RunL SIU.GPDO[30].B.PDO
#define StopL SIU.GPDO[31].B.PDO

/***************DIP*****************/
#define switch1 SIU.GPDI[56].R
#define switch2 SIU.GPDI[54].R
#define switch3 SIU.GPDI[52].R
#define switch4 SIU.GPDI[50].R


#endif
