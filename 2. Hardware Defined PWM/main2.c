//Luciano Miles Miletta
//Embedded Systems
//LAB 4 PART 2

#include <msp430.h>

void TimerA0Setup(); // Initialize Timer0
void TimerA1Setup(); // Initialize Timer1
void TimerA3Setup(); //Initiallize Timer 3
void LEDSetup();



void main()
{

    WDTCTL = WDTPW | WDTHOLD;                   // stop watchdog timer

    TimerA3Setup();
    LEDSetup();

    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM0_bits | GIE);         // Enter LPM0 w/ interrupt
    __no_operation();                           // For debugger
}

void TimerA0Setup()                             // Setup Timer 0
{
    TB0CCR0 = 1000-1;                         // PWM Period
    TB0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB0CCR1 = 800;                            // CCR1 PWM duty cycle
    TB0CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}





void TimerA1Setup()                             // Setup Timer 1
{
    TB1CCR0 = 1000-1;                         // PWM Period
    TB1CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB1CCR1 = 800;                            // CCR1 PWM duty cycle
    TB1CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}





void TimerA3Setup()                             // Setup Timer 3
{
    TB3CCR0 = 1000-1;                         // PWM Period
    TB3CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB3CCR1 = 800;                            // CCR1 PWM duty cycle
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}




void LEDSetup()
{


    //P6DIR |= BIT0;                     // P6.0 output
    P6SEL0 |= BIT0;
    P6SEL1 &= ~BIT0;                    // P6.0 options select (RED)


    //P6DIR |= BIT1;                     // P6.1 output
    P6SEL0 |= BIT1;
    P6SEL1 &= ~BIT1;                    // P6.1 options select (Green)


    //P6DIR |= BIT2;                     // P6.2 output
    P6SEL0 |= BIT2;
    P6SEL1 &= ~BIT2;                    // P6.2 options select (Blue)

}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{

if (TB0CCR1 >= 800)
{
    TB0CCR1 += 100;

}

}




//#pragma vector = TIMER1_B0_VECTOR
//__interrupt void Timer1_B0_ISR(void)







//#pragma vector = TIMER3_B0_VECTOR
//__interrupt void Timer3_B0_ISR(void)

