#pragma once
#ifndef PWM_H
#define PWM_H

#if PWM_INTERRUPT
extern void PWMInterruptEnable(); // PWM interrupt enable
extern void PWMInterruptDisable(); // PWM interrupt disable
#endif

#define SetPWMClk(CK_SE) (PWM_CK_SE = CK_SE) // Frequency division, default clock Fsys

#define SetPWM1Dat(dat) (PWM_DATA1 = dat) // Set PWM output duty cycle
#define SetPWM2Dat(dat) (PWM_DATA2 = dat)

#define PWM1PinAlter() {PIN_FUNC |= bPWM1_PIN_X;} // PWM mapping pin P30
#define PWM2PinAlter() {PIN_FUNC |= bPWM2_PIN_X;} // PWM mapping pin P31

#define ForceClearPWMFIFO() {PWM_CTRL |= bPWM_CLR_ALL;} // Force clear PWM FIFO and COUNT
#define CancelClearPWMFIFO() {PWM_CTRL &= ~bPWM_CLR_ALL;} // Cancel clear PWM FIFO and COUNT

#define PWM1OutEnable() (PWM_CTRL |= bPWM1_OUT_EN) // Enable PWM1 output
#define PWM2OutEnable() (PWM_CTRL |= bPWM2_OUT_EN) // Enable PWM2 output
#define DisablePWM1Out() (PWM_CTRL &= ~bPWM1_OUT_EN) // Disable PWM1 output
#define DisablePWM2Out() (PWM_CTRL &= ~bPWM2_OUT_EN) // Disable PWM2 output

#define PWM1OutPolarHighAct() (PWM_CTRL &= ~bPWM1_POLAR) // PWM1 output default low, active high
#define PWM2OutPolarHighAct() (PWM_CTRL &= ~bPWM2_POLAR) // PWM2 output default low, active high
#define PWM1OutPolarLowAct() (PWM_CTRL |= bPWM1_POLAR) // PWM1 output default high, active low
#define PWM2OutPolarLowAct() (PWM_CTRL |= bPWM2_POLAR) // PWM2 output default high, active low

#endif // PWM_H
