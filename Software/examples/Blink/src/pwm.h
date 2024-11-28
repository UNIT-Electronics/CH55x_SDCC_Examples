// The original code is licensed under the Creative Commons Attribution-ShareAlike 3.0
// Unported License (CC BY-SA 3.0). For more details, visit:
// http://creativecommons.org/licenses/by-sa/3.0/
//
// Modifications and additional code in this file are licensed under the GNU General
// Public License v3.0 (GPL-3.0). For more information, see:
// https://www.gnu.org/licenses/gpl-3.0.en.html
//
// 2022 by
#pragma once
#include "ch554.h"

#if PWM_INTERRUPT
extern void  PWMInterruptEnable()                                            //PWM interrupt enable
#endif

#define SetPWMClk(CK_SE) PWM_CK_SE = CK_SE                                  //Frequency division, default clock Fsys 

#define SetPWM1Dat(dat)  PWM_DATA1 = dat                                   //Set PWM output duty cycle
#define SetPWM2Dat(dat)  PWM_DATA2 = dat

#define PWM1PinAlter( )  PIN_FUNC |= bPWM1_PIN_X                          // PWM mapping pin P30
#define PWM2PinAlter( )  PIN_FUNC |= bPWM2_PIN_X                          // PWM mapping pin P31

#define ForceClearPWMFIFO( ) PWM_CTRL |= bPWM_CLR_ALL                      //强制清除PWM FIFO和COUNT
#define CancelClearPWMFIFO( ) PWM_CTRL &= ~bPWM_CLR_ALL                    //取消清除PWM FIFO和COUNT

#define PWM1OutEnable()  PWM_CTRL |= bPWM1_OUT_EN                           //允许PWM1输出                           
#define PWM2OutEnable()  PWM_CTRL |= bPWM2_OUT_EN                           //允许PWM2输出  
#define DsiablePWM1Out() PWM_CTRL &= ~bPWM1_OUT_EN                          //关闭PWM1输出                           
#define DisablePWM2Out() PWM_CTRL &= ~bPWM2_OUT_EN                          //关闭PWM2输出  

#define PWM1OutPolarHighAct() PWM_CTRL &= ~bPWM1_POLAR                       //PWM1输出默认低，高有效                           
#define PWM2OutPolarHighAct() PWM_CTRL &= ~bPWM2_POLAR                       //PWM2输出默认低，高有效  
#define PWM1OutPolarLowAct()  PWM_CTRL |= bPWM1_POLAR                       //PWM1输出默认高，低有效                         
#define PWM2OutPolarLowAct()  PWM_CTRL |= bPWM2_POLAR                        //PWM2输出默认高，低有效   

//PWM中断使能
#define PWMInterruptEnable()  IE_PWMX = 1                                                                                                                                                       }
#define PWMInterruptDisable() IE_PWMX = 0
