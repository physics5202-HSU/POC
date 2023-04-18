/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "OLED12864.h"
#include "adc.h"

extern EEPROMData EEDataDefault;
extern EEPROMData EEData;
extern EEPROMData_POC EEDataDefault_POC;
extern EEPROMData_POC EEData_POC;
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
 */
static void rtcEventHandler (RTC_TIMER32_INT_MASK intCause, uintptr_t context)
{
	if (intCause & RTC_MODE0_INTENSET_PER7_Msk)
	{   
		timeElapsedOneSec();
	}
}
void TC3_Callback_InterruptHandler(TC_TIMER_STATUS status, uintptr_t context)
{
    //GPIO_PB01_Toggle();
    Second_poc = Second_poc+1;
    //SYS_CONSOLE_PRINT("Minute = %d\r\n", EEData_POC.ucminute);
    //SYS_CONSOLE_PRINT("Second = %d\r\n", Second_poc);   
    if(Second_poc == 0x3c)
    {
        Second_poc = 0; 
       EEData_POC.ucminute = EEData_POC.ucminute + 1;
       //SYS_CONSOLE_PRINT("Minute = %d\r\n", EEData_POC.ucminute);
       if(EEData_POC.ucminute == 0x3c)
       {
           EEData_POC.ucminute = 0;
           EEData_POC.uchour = EEData_POC.uchour + 1;
       }
       
    }   
}
#if 0
void TC3_Overflow(TC_COMPARE_STATUS status, uintptr_t context)
{
     uint8_t *TXCMD_POC = calloc(2, sizeof(uint8_t *));
    if( status & TC_INTFLAG_OVF_Msk )
    {
    Second_poc = Second_poc+1;
    printf("%d\n",Second_poc);
       TXCMD_POC[0] = Second_poc;
       SERCOM5_USART_Write(TXCMD_POC, 1);    
    }
    if(Second_poc == 0x3c)
    {
        Second_poc = 0; 
       EEData_POC.ucminute = EEData_POC.ucminute + 1;
       TXCMD_POC[1] = EEData_POC.ucminute;
       SERCOM5_USART_Write(TXCMD_POC, 2);
       if(EEData_POC.ucminute == 0x3c)
       {
           EEData_POC.ucminute = 0;
           EEData_POC.uchour = EEData_POC.uchour + 1;
       }
       
    }
    free(TXCMD_POC);
}
#endif
// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    TCC0_PWMStart();
	RTC_Timer32CallbackRegister(rtcEventHandler, 0);
	RTC_Timer32Start();
    EEData_POC = EEDataDefault_POC;
    Second_poc = 0;
    //TC3_CompareCallbackRegister( TC3_Overflow, (uintptr_t )NULL );
    //TC3_CompareStart();
    /* Register callback function for TC0 period interrupt */
    TC3_TimerCallbackRegister(TC3_Callback_InterruptHandler, (uintptr_t)NULL);  
    /* Start the timer channel 0*/
    TC3_TimerStart();    
    Als_Crlon = 0;
    Als_Demo01 = 0;
    Als_Demo02 = 0;
    Als_max = 0xffff;
    Als_min = 0;
    Als_read = 0;
    Als_count = 0;
    EEData.drbo_NUM = 1;
    //drbo_NUM = EEData.drbo_NUM_EE;
    value_stepL = 0;
    //flagALS = threadALS();
    flagALS = false;
    flagALS_TAR = false;
    flagGPIO = false;
    flagADC = false;
    flagHMI = false;
    flagReadEEPROM = true;
    EEData = EEDataDefault;

    //drbo_NUM = EEData.drbo_NUM_EE;
    //ADC0_CallbackRegister(ADC_EventHandler, (uintptr_t)NULL);
    //ADC0_Enable();
    //ADC0_ConversionStart();
    //EEPROM_Read_Data(EEPROM_USERDATA_ADDR1,&EEData);
    //EEPROM_Read_Data(EEPROM_USERDATA_ADDR1,&EEData);
    //for (uint32_t i = 0; i < 100000; i++);//1ns*20000=2ms
    //SYS_CONSOLE_PRINT("------\r\n");
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        //threadJudgeman();
        //TC3_Overflow();
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

