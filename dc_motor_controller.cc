#define F_CPU 32000000UL
#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>
 
// Function Declarations
void Config32MHzClock(void); // Skifter klokkehastighet
 
 
int main (void)
{
  board_init();
  Config32MHzClock();
	
	
    // setup PORTD GPIO output
	PORTD.DIRSET = PIN0_bm | PIN1_bm | PIN5_bm; // Setter utgang
	
	
	// setup timer for PORTD PWM output to motor
	TCD0.CTRLA = TC_CLKSEL_DIV1024_gc; // 32M/1024=32K or .03ms/tick
	TCD0.CTRLB = TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_WGMODE1_bm | TC0_WGMODE0_bm; // enable waveform gen single slope // Velger og utgang
	TCD0.PER = 32;    // 1ms = 1KHz waveform
    TCD0.CCA = 0;    // 16/32 = 50% duty cycle
	TCD0.CCB = 0;
 
	while (1)
	{
		
		
		PORTD.OUTTGL = PIN5_bm;
		TCD0.CCA = 30; 
		TCD0.CCB = 30; 
		_delay_ms(3000);
		TCD0.CCA = 20; 
		TCD0.CCB = 20;
		_delay_ms(3000);
		TCD0.CCA = 16;
		TCD0.CCB = 16;
		_delay_ms(3000);
	}
}
 
 
 
void Config32MHzClock(void)
{
	CCP = CCP_IOREG_gc; //Security Signature to modify clock
	// initialize clock source to be 32MHz internal oscillator (no PLL)
	OSC.CTRL = OSC_RC32MEN_bm; // enable internal 32MHz oscillator
	while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // wait for oscillator ready
	CCP = CCP_IOREG_gc; //Security Signature to modify clock
	CLK.CTRL = 0x01; //select sysclock 32MHz osc
};
