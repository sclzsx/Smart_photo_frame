#ifndef _MUSIC_H
#define _MUSIC_H

extern float A[7],C[7],B[7];
extern int r,i;
			
extern void music_1(void);
extern void music_2(void);
//extern void delay_ms(long nms);
extern void TIM2_PWM_Init(int arr,int psc);
extern void  low1(void) ;
extern void  low2(void) ;
extern void  low3(void) ;
extern void  low4(void) ;
extern void  low5(void) ;
extern void  low6(void) ;
extern void  low7(void) ;
extern void  mid1(void) ;
extern void  mid2(void) ;
extern void  mid3(void) ;
extern void  mid4(void) ;
extern void  mid5(void) ;
extern void  mid6(void) ;
extern void  mid7(void) ;
extern void  hig1(void) ;
extern void  hig2(void) ;
extern void  hig3(void) ;
extern void  hig4(void) ;
extern void  hig5(void) ;
extern void  hig6(void) ;
extern void  hig7(void) ;

#endif

