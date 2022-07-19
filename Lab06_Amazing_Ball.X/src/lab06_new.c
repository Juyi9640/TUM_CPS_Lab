// To solve two problems:
// 1. Set up a timer and serve as a source of time for the frequency domains
// 2. Implement PD controllers

#include "lab06.h"

#include <xc.h>
// do not change the order of the following 2 definitions
#define FCY 12800000UL
#include <libpic30.h>
#include <stdint.h>

#include <math.h>

#include "types.h"
#include "lcd.h"
#include "led.h"

/*
 * Parameter
 */
// Seperate timer1 into different frequency zone
volatile int counterHundredHz = 0;
volatile int counterFiftyHz = 0;
volatile int counterFiveHz = 0;

/*
 * Common Definitions
 */
#define TCKPS_1 0x00
#define TCKPS_8 0x01
#define TCKPS_64 0x02
#define TCKPS_256 0x03

/*
 * Global Variables
 */

/*
 * Timer Code
 */

// Raise an Interrupt every 10ms, equal to 100Hz
CLEARBIT(T1CONbits.TON);   // Disable Timer1
CLEARBIT(T1CONbits.TCS);   // Select internal instruction cycle clock
CLEARBIT(T1CONbits.TGATE); // Disable Gated Timer mode
TMR1 = 0x00;               // Clear timer register
T1CONbits.TCKPS = 0b10;    // Select 1:64 Prescaler
PR1 = 2000;                // Load the period value
IPC0bits.T1IP = 0x01;      // Set Timer1 Interrupt Priority Level
CLEARBIT(IFS0bits.T1IF);   // Clear Timer1 Interrupt Flag
SETBIT(IEC0bits.T1IE);     // Enable Timer1 interrupt
SETBIT(T1CONbits.TON);     // Start Timer

/*
 * Servo Code
 */

/*
 * Touch screen code
 */

/*
 * PD Controller
 */

/*
 * Butterworth Filter N=1, Cutoff 3 Hz, sampling @ 50 Hz
 */

/*
 * main loop
 */
void main_loop()
{
    // print assignment information
    lcd_printf("Lab06: Amazing Ball");
    lcd_locate(0, 1);
    lcd_printf("Group: GroupName");
    lcd_locate(0, 2);

    while (TRUE)
    {
    }
}

// ISR Timer1
void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T1Interrupt(void)
{
    // invoked every 10ms, equal to 100Hz

    CLEARBIT(IFS0bits.T1IF); // Clear Timer1 Interrupt Flag

    // 100Hz for Task1
    counterHundredHz++;
    if (counterHundredHz == 1)
    {
        counterHundredHz = 0;
        taskOneFunction();
    }

    // 50Hz for Task2
    counterFiftyHz++;
    if (counterFiftyHz == 2)
    {
        counterFiftyHz = 0;
        taskTwoFunction();
    }

    // 5Hz for Task3
    counterFiveHz++;
    if (counterFiveHz == 20)
    {
        counterFiveHz = 0;
        taskThreeFunction();
    }
}