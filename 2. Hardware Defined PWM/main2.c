 //Created on: Feb 28, 2023
// Author: David Myers
#include <msp430.h>


void TimerA3Setup();
void LEDSetup();

int count;
int color;
color = 0;
count = 0;

void main()
{

//    WDTCTL = WDTPW | WDTHOLD;                   // stop watchdog timer
    WDTCTL = WDT_ADLY_1000;                       //
    TimerA3Setup();
    LEDSetup();

    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM0_bits | GIE);         // Enter LPM0 w/ interrupt
    __no_operation();                           // For debugger
}


void TimerA3Setup()                             // Setup Timer 0
{
    TB3CCTL0 |= CCIE;                       // Enable TB0 CCR0 Overflow IRQ
    TB3CCR0 = 0xFFFF;                         // PWM Period
    TB3CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB3CCR1 = 800;                            // CCR1 PWM duty cycle
    TB3CTL = TBSSEL__SMCLK | ID_3 | MC__UP | TBCLR; // SMCLK, up mode, clear TBR
}


void LEDSetup()
{
    P6DIR |= BIT0;                      ///MAKES RED
    P6SEL0 |= BIT0;
    P6SEL1 &= ~BIT0;                    // P6.0 options select
}

#pragma vector=TIMER3_B0_VECTOR
__interrupt void TIMER3_B0_ISR(void)
{
   count ++;
    if (count == 2)
       {
       if (color == 0)
       {
            color = 1;
            P6DIR |= BIT1;                     // P6.0 output           ////ADD Green
            P6SEL0 |= BIT1;
            P6SEL1 &= ~BIT0;                    // P6.0 options select

            count = 0;

            //ORANGE
       }
       else if (color == 1)
       {
           P6DIR &= ~ BIT0;                     // P6.0 output        ///STOPS RED
           P6SEL0 |= BIT0;
           P6SEL1 &= ~BIT0;                    // P6.0 options select

           //GREEN
            color = 2;
            count = 0;
        }
       else if (color == 2)
       {
           P6DIR |= BIT2;                     // P6.0 output               ///ADDS BlUE MAKING CYAN
           P6SEL0 |= BIT2;
           P6SEL1 &= ~BIT0;                    // P6.0 options select



           color = 3;
           count = 0;

       }
       else if (color == 3)
       {
           P6DIR &= ~ BIT1;                     // P6.0 output              ///STOPS GREEN
           P6SEL0 |= BIT0;
           P6SEL1 &= ~BIT0;                    // P6.0 options select
           //JUST BLUE

          color = 4;
          count = 0;
       }
       else if (color == 4)
       {
         P6DIR |= BIT0;         ///MAKES RED
         P6SEL0 |= BIT0;
         P6SEL1 &= ~BIT0;                    // P6.0 options select
         //LEFT with purple
         color = 5;
         count = 0;
       }
       else if (color ==5)
       {
        P6DIR &= ~BIT2;                     // P6.0 output               ///STOPS BlUE
        P6SEL0 |= BIT0;
        P6SEL1 &= ~BIT0;                    // P6.0 options select
                       //Get rid of blue
       //LEFT WITH RED
        color = 0;
        count = 0;
       }

        }

}
