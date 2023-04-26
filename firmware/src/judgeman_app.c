/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    judgeman_app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "judgeman_app.h"
#include "string.h"
//#include "rs232_app.h"
#include "configuration.h"
//#include "peripheral/sercom/usart/plib_sercom5_usart.h"
#include "system/console/sys_console.h"
#include "com_lib.h"
#include "uart_command.h"
#include "Judgeman.h"
#include "eeprom.h"
#include "stdlib.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the JUDGEMAN_APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

JUDGEMAN_APP_DATA judgeman_appData;
extern EEPROMData_POC EEData_POC;
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void JUDGEMAN_APP_Initialize ( void )

  Remarks:
    See prototype in judgeman_app.h.
 */

void JUDGEMAN_APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    judgeman_appData.state = JUDGEMAN_APP_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void JUDGEMAN_APP_Tasks ( void )

  Remarks:
    See prototype in judgeman_app.h.
 */

void JUDGEMAN_APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( judgeman_appData.state )
    {
        /* Application's initial state. */
        case JUDGEMAN_APP_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                judgeman_appData.state = JUDGEMAN_APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case JUDGEMAN_APP_STATE_SERVICE_TASKS:
        {
            //Als_read = ALS_Read(ALS_1_CTRL_ADDR);
            //threadJudgeman();
#if 0            
                //ADC0_Enable();
                //ADC0_ConversionStart();
                //CBVC
                if(ADC0_ConversionStatusGet())
                {
                    uint16_t v_adc_p=ADC0_ConversionResultGet();
                    //SYS_CONSOLE_PRINT("v_adc_p = %x\r\n", v_adc_p);
                   if(v_adc_p > 0xFF0)
                    {
                        flag_CBVC = true;
                        FEEDBACK_UART_PC(POC_FEEDBACKCBVC);
                        flag_CBVC = false;
                     }
                }
                //if(v_adc_p < 5)
                //{
  
                //}
#endif                
#if 0           
            //OCCD
            if(!GPIO_PA06_Get())
            {
             flag_OCCD = true;   
             FEEDBACK_UART_PC(POC_FEEDBACKOCCD);
            }
#endif                
#if 0                
            //OCDS    
            if(GPIO_PA07_Get())
            {
             flag_OCDS = true;   
             FEEDBACK_UART_PC(POC_FEEDBACKOCDS);
            }
#endif                
#if 0                
            //OCDD    
            if(!GPIO_PC10_Get())
            {
             flag_OCDD = true;   
             FEEDBACK_UART_PC(POC_FEEDBACKOCDD);
            }
#endif            
#if 1          
            if(flag_JudgeEEPROM == true){
                flag_JudgeEEPROM = false;
            EEPROM_Write_Data_POC(EEPROM_USERDATA_ADDR1,&EEData_POC);
            }
             if(flagReadEEPROM == true){
             EEPROM_Read_Data_POC(EEPROM_USERDATA_ADDR1,&EEData_POC);
             flagReadEEPROM = false;
             }
#endif 
#if 1          
            if(flag_ALSRead == true){
                flag_ALSRead = false;
             Als_read = ALS_Read(ALS_1_CTRL_ADDR);
             if(Als_read < Als_judge){
              FEEDBACK_UART_PC(POC_FEEDBACKNG);
             }
            }
#endif                 
            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
