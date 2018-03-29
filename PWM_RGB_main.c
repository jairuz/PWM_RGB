#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// This application mixes a RGB color using PWM on the booster board
// All three colors are driven by a 1KHz PWM
// Changing the duty cycle of these PWM signals creates different colors.

// goal: to generate a 1KHz PWM, 1ms = N *  (1/3M), or N = 3M/1K = 3000
#define PWM_PERIOD_IN_CYLCLES 3000

// Number of ON cycles for each of the colors
#define RED_DUTY_CYCLE 30           // 1% duty cycle
#define GRN_DUTY_CYCLE 750          // 25% duty cycle
#define BLU_DUTY_CYCLE 1500         // 50% duty cycle

// The below set of choices are not programmer's.
// We need to study the Booster board and Launchpad board diagrams for this info.

// The RED LED is wired to TA0.3.
#define RED_TIMER    TIMER_A0_BASE
#define RED_CHANNEL  TIMER_A_CAPTURECOMPARE_REGISTER_3

// The GREEN LED is wired to TA0.1.
#define GRN_TIMER    TIMER_A0_BASE
#define GRN_CHANNEL  TIMER_A_CAPTURECOMPARE_REGISTER_1

// The BLUE LED is wired to TA2.1.
#define BLU_TIMER    TIMER_A2_BASE
#define BLU_CHANNEL  TIMER_A_CAPTURECOMPARE_REGISTER_1

Timer_A_PWMConfig pwmConfig_red = {
        TIMER_A_CLOCKSOURCE_SMCLK,         // system clock is the source clock
        TIMER_A_CLOCKSOURCE_DIVIDER_1,     // divider = 1 = > counter f = 3 MHz
        PWM_PERIOD_IN_CYLCLES,
        RED_CHANNEL,
        TIMER_A_OUTPUTMODE_RESET_SET,      // OC options , the ON part is first
        RED_DUTY_CYCLE
};

Timer_A_PWMConfig pwmConfig_grn = {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        PWM_PERIOD_IN_CYLCLES,
        GRN_CHANNEL,
        TIMER_A_OUTPUTMODE_RESET_SET,
        GRN_DUTY_CYCLE
};

Timer_A_PWMConfig pwmConfig_blu = {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        PWM_PERIOD_IN_CYLCLES,
        BLU_CHANNEL,
        TIMER_A_OUTPUTMODE_RESET_SET,
        BLU_DUTY_CYCLE
};

void initPWM()
{
    // For each of the LEDs, we first configure them as a GPIO and turn them off
    // Then, we configure them to work as output channel of a timer

    // RED LED
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P2,
            GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);

    // GREEN LED
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN4);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN4);
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P2,
            GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);

    // BLUE LED
    GPIO_setAsOutputPin    (GPIO_PORT_P5,    GPIO_PIN6);
    GPIO_setOutputLowOnPin (GPIO_PORT_P5,    GPIO_PIN6);
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P5,
            GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);
}


int main(void) {

  // Stop WDT
  WDT_A_holdTimer();
  initPWM();

  // The below lines start the pwm
  // Since we start them one at a time, they will not by in synch
  // In order to synchronize them to an extent, we need to delay the start of the other two, but we don't need it here.
  Timer_A_generatePWM(RED_TIMER, &pwmConfig_red);
  Timer_A_generatePWM(GRN_TIMER, &pwmConfig_grn);   
  Timer_A_generatePWM(BLU_TIMER, &pwmConfig_blu);

  while (1) ;

}
