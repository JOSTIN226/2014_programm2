#ifndef __VEDIO_H__
#define __VEDIO_H__
#define byte unsigned char
#define word unsigned int


#define ROW  (69)
#define ROWS  (70)	     
#define COLUMN (82)
#define COLUMNS (83)



extern void FieldInputCapture(void);
extern void RowInputCapture(void);
void Video_Image(void);
extern void Display_Video(void);
extern void TF_Image(void);

//*************************************************************************
//*			**********************鍥惧儚鍙戦�鍑芥暟*************************   *
//*************************************************************************
void Send_CCD_Video(void); 
void SetupCCD(void);

void SetupBKL(void);
void Send_CCD_Blackline(void);


//*************************************************************************
//*			**********************閲囨牱鍙橀噺*****************************   *
//*************************************************************************
extern byte fieldover;                //涓�満閲囨牱缁撴潫鏍囧織绗�
extern volatile byte g_pix[ROWS][COLUMNS]; 
extern volatile byte pic[ROWS][COLUMNS];
extern byte	pix[ROWS][COLUMNS];

#endif
