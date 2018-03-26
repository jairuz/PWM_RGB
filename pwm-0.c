#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

unsigned glbTicks;

#define PWM_PERIOD_IN_CYLCLES 3000  // 1 ms x 3M = 3000
#define RED_DUTY_CYCLE 1000          // 10% duty cycle
#define GRN_DUTY_CYCLE 0          // 50% duty cycle
#define BLU_DUTY_CYCLE 1000         // 50% duty cycle

Timer_A_PWMConfig pwmConfig_red = {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,    // 3 MHz
        PWM_PERIOD_IN_CYLCLES,
        TIMER_A_CAPTURECOMPARE_REGISTER_3, // This is not programmer's choice. The RED LED is wired to this channel
        TIMER_A_OUTPUTMODE_RESET_SET,
        RED_DUTY_CYCLE
};

Timer_A_PWMConfig pwmConfig_grn = {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,    // 3 MHz
        PWM_PERIOD_IN_CYLCLES,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        GRN_DUTY_CYCLE
};

Timer_A_PWMConfig pwmConfig_blu = {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,    // 3 MHz
        PWM_PERIOD_IN_CYLCLES,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        BLU_DUTY_CYCLE
};

void initPWM()
{
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

  Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_red);
  Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_grn);
  Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig_blu);

  while (1) ;

}
