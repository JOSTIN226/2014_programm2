#include "includes.h"
//*************************************************************************
//*		 *************************采样变量*****************************   *
//*************************************************************************
//采样图像标号
word crow = 0;           //行数计数器
byte prow = 0;  	  	    //摄像头采样当前行
byte pcolumn = 0;        //摄像头当前列
byte RowSAIC_DelayTime=90;   //图像延时时间82//43
//采样结束标志
byte fieldover = 0;                //一场采样结束标志符 
int kkk=0;
int kkk2=0;
//采样二维数组    
volatile byte g_pix[ROWS][COLUMNS]; 
volatile byte pic[ROWS][COLUMNS]; 
byte pix[ROWS][COLUMNS];

word selectRows[ROWS]=
{
//最小行:17
//最大行:255
//图像采样从近往远
//23 ,39 ,52 ,65 ,76 ,89 ,96 ,105,113,121,
//128,134,140,146,151,156,161,165,169,173,
//177,180,183,186,189,192,195,198,200,202,
//204,206,208,210,212,214,216,218,220,222,
//224,225,226,227,228,229,230,231,232,233,
//234,235,236,237,238,239,240,241,242,243,
//244,245,246,247,248,249,250,251,252,253,

//		17,20,25,30,35,40,45,50,55,60,
//		131,136,141,146,148,150,154,159,162,
//		166,170,173,176,179,182,185,188,191,
//		193,196,198,200,203,205,207,209,211,
//		213,214,216,218,220,221,223,224,226,
//		227,229,230,232,233,234,235,237,238,
//		239,240,241,242,243,244,245,246,247,
//		248,249,250,251,252,255//70 数字大为远端
		
//		61 ,67 ,73 ,79 ,85 ,90 ,96 ,101,106,111,
//		115,120,124,128,133,136,140,144,148,151,
//		155,158,161,164,167,170,173,176,179,181,
//		184,187,189,191,194,196,198,201,203,205,
//		207,209,211,213,215,217,218,220,222,224,
//		225,227,228,230,232,233,235,236,237,239,
//		240,242,243,244,245,247,248,249,250,252
		
		20,21,22,23,24,25,26,27,28,30,
		31,32,33,35,36,37,39,40,41,43,
		44,46,47,49,50,52,54,56,57,59,
		61,63,65,67,69,71,73,75,78,80,
		82,85,88,90,93,96,99,102,105,108,
		111,115,118,122,126,130,134,138,142,147,
		152,157,162,167,173,179,185,191,198,205
	
		



};

//*************************************************************************
//*   **************************中断函数****************************      *
//*************************************************************************
void FieldInputCapture(void) 
{	
    EMIOS_0.CH[3].CSR.B.FLAG = 1;
	EMIOS_0.CH[3].CCR.B.FEN=0;  //关闭场中断 
	prow=0;crow=0;
	EMIOS_0.CH[7].CSR.B.FLAG = 1;//清行中断
	EMIOS_0.CH[7].CCR.B.FEN=1;	//开启行中断
}


void RowInputCapture(void) 
{	
	EMIOS_0.CH[7].CSR.B.FLAG = 1;
	EMIOS_0.CH[7].CCR.B.FEN=0;
	++crow;
	//采样开始
	//行消影 因为摄像头输出信号的前几行是不能用的，所以扔掉前ROWS_MIN行
	if(crow>selectRows[prow])
  	{
	    for(pcolumn=0;pcolumn<RowSAIC_DelayTime;++pcolumn) {}
	    /************************
	    	延时消隐区
	    ***********************************/ 
	   
	   	g_pix[prow][0]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][1]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][2]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][3]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][4]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][5]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][6]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][7]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][8]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][9]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	
	   	g_pix[prow][10]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][11]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][12]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");																																															
	   	g_pix[prow][13]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][14]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][15]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][16]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][17]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][18]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][19]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	
	   	g_pix[prow][20]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][21]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][22]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][23]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][24]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][25]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][26]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][27]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][28]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][29]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	
	   	g_pix[prow][30]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][31]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][32]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][33]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][34]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][35]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][36]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][37]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][38]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][39]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	
	   	g_pix[prow][40]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][41]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][42]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	    g_pix[prow][43]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][44]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][45]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][46]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][47]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][48]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][49]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	
	   	g_pix[prow][50]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][51]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][52]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][53]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][54]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][55]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][56]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][57]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][58]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][59]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	
	   	g_pix[prow][60]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][61]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][62]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][63]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][64]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][65]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][66]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][67]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][68]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][69]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	
	   	g_pix[prow][70]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][71]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][72]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][73]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][74]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][75]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][76]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][77]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][78]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][79]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	
	   	g_pix[prow][80]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][81]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
	   	g_pix[prow][82]=SIU.GPDI[42].R; asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");	
	    ++prow;
		if(prow==ROWS)
		{
			EMIOS_0.CH[7].CCR.B.FEN=0; 	//关闭行中断
			fieldover=1; 
		}
	}
	EMIOS_0.CH[7].CSR.B.FLAG = 1;//清行中断
	EMIOS_0.CH[7].CCR.B.FEN=1;	//开启行中断
}

/*----------------------------------------------------------------------*/
/*视频信号输出                                            	 */
/*----------------------------------------------------------------------*/
void Video_Image(void)
{
	int y,x,i,col;
#if 1
	volatile int j=0;
	for(j=0;j<ROWS;j++)
	{
		col=CenterLine[j];
		g_pix[j][col]=0;
	}
#endif
	for(y=0;y<ROWS/8;y++)
		for(x=0;x<COLUMNS;x++)
		{
			pix[y][x]=0;
			for(i=7;i>=0;i--)
				pix[y][x]=pix[y][x]*2+g_pix[y*8+i][x];
		}	

}
void TF_Image(void)
{
	int i,j;
	for(i=0;i<ROWS;i++)
		for(j=0;j<COLUMNS;j++)
		{
			if(g_pix[i][j]==0)
				pic[i][j]=0x00;
			else
				pic[i][j]=0xFF;
		}
}
void Display_Video(void)
{
	
	BYTE x,y;

	Video_Image();
	for(y=0;y<ROWS/8;y++)
	{
		LCD_Set_Pos(10,y);				
    	for(x=0;x<COLUMNS;x++)
	    {      
	    	LCD_WrDat(pix[y][x]);		
	    }
	}
}

//*************************************************************************																							                        
//*   ********************无线发送图像******************************      *	
//*************************************************************************
void Send_CCD_Video(void) 
{
  unsigned char i,j;
  serial_port_1_TX(0x55);
  serial_port_1_TX(0xAA);
  serial_port_1_TX(0xFF);
  for(i = 0;i < ROWS;i ++)
  {   
	for(j = 0;j < COLUMNS;j ++)
	{
	   if(g_pix[i][j]==1)
		   serial_port_1_TX(0xFF);
	   else
		   serial_port_1_TX(0x00);
	}
  }
  serial_port_1_TX(0xFF);
  serial_port_1_TX(0xAA);
  serial_port_1_TX(0x55);
}

void SetupCCD(void)
{   
	serial_port_1_TX(0xAA);        
	serial_port_1_TX(0xBB);        
	serial_port_1_TX(0xFF);        
	serial_port_1_TX(ROWS);        
	serial_port_1_TX(COLUMNS);         
	serial_port_1_TX(0xFF);        
	serial_port_1_TX(0xBB);        
	serial_port_1_TX(0xAA);        
}

void SetupBKL(void)
{
    unsigned char para1[10] = {"L"};//设置显示在上位机上的变量名
    unsigned char para2[10] = {"R"};  
    unsigned char para3[10] = {"target_a"};
    byte i;
       
    serial_port_1_TX(0xCC);        
    serial_port_1_TX(0xDD);        
    serial_port_1_TX(0xFF);         
                                             
    serial_port_1_TX(ROWS);        
    serial_port_1_TX(COLUMNS);        
    serial_port_1_TX(3);         // number of parameters
    
    serial_port_1_TX(0);         // display position  0和1分别表示在左边窗口或者右边窗口显示
    serial_port_1_TX(0);         // display position
    serial_port_1_TX(1);
    
    for(i=0;i<10;++i)
    	serial_port_1_TX(para1[i]);
    for(i=0;i<10;++i)
    	serial_port_1_TX(para2[i]);
   	for(i=0;i<10;++i)
   		serial_port_1_TX(para3[i]);
    	        
   	serial_port_1_TX(9);         // parameter color
   	serial_port_1_TX(5);
   	serial_port_1_TX(9);         // parameter color
    
   	serial_port_1_TX(0xFF);        
   	serial_port_1_TX(0xDD);        
   	serial_port_1_TX(0xCC);  
}

void Send_CCD_Blackline(void)
{
	byte i=0;
	serial_port_1_TX(0x55);
	serial_port_1_TX(0xBB);
	serial_port_1_TX(0xFF);
    for(;i<ROWS;++i)
    	serial_port_1_TX(BlackLine[0][i]);
    serial_port_1_TX(0x00);
    serial_port_1_TX(0x00);
    serial_port_1_TX(0x00);
    serial_port_1_TX(LineType[0]);//
    serial_port_1_TX(0x00);
    serial_port_1_TX(0x00);
    serial_port_1_TX(0x00);
    serial_port_1_TX(LineType[1]);//
    serial_port_1_TX(0x00);
    serial_port_1_TX(0x00);
    serial_port_1_TX(0x00);
    serial_port_1_TX(target_offset);//
    serial_port_1_TX(0xFF);        
    serial_port_1_TX(0xBB);        
    serial_port_1_TX(0x55);              
}


