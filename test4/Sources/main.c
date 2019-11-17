/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K1xx
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"

  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/


#define LEDR 16U
#define SW2 3U
#define SW3 5U
#define LEDG 15U

  void PORTD_ISR(void) {
	  //Only run ISR if a single pin has triggered interrupt

	  switch (PINS_DRV_ReadPins(PTD) & (1<<SW2 | 1<<SW3)) {
	  case 1<<SW2 | 1<<SW3:
			  //Do nothing if both pressed
			  PINS_DRV_ClearPortIntFlagCmd(PORTD);
			  break;
	  case 1<<SW2:
			  PINS_DRV_TogglePins(PTD, 1<<LEDR);
			  PINS_DRV_ClearPinIntFlagCmd(PORTD, SW2);
			  break;
	  case 1<<SW3:
			  PINS_DRV_TogglePins(PTD, 1<<LEDG);
			  PINS_DRV_ClearPinIntFlagCmd(PORTD, SW3);
			  break;
	  }


  }

int main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

    CLOCK_SYS_Init(g_clockManConfigsArr,CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr,CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U,CLOCK_MANAGER_POLICY_AGREEMENT);

    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
    PINS_DRV_SetPinsDirection(PTD, 1<<LEDR | 1<<LEDG );

    INT_SYS_InstallHandler(PORT_IRQn, PORTD_ISR, (isr_t*)0);
    INT_SYS_EnableIRQ(PORT_IRQn);


    for (;;) {

    	/*
    	if (PINS_DRV_ReadPins(PTD) & (1<<SW2)) {
    		PINS_DRV_SetPins(PTD, 1<<LEDR);
    	} else {
    		PINS_DRV_ClearPins(PTD, 1<<LEDR);
    	}

    	if (PINS_DRV_ReadPins(PTD) & (1<<SW3)) {
    		PINS_DRV_SetPins(PTD, 1<<LEDG);
    	} else {
    		PINS_DRV_ClearPins(PTD, 1<<LEDG);
    	}
		*/

    }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the NXP S32K series of microcontrollers.
**
** ###################################################################
*/
