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
#if 1            
            //if(EEData_POC.uchour == 0x00004E20){          //20000 hrs warning
            if(EEData_POC.uchour >= 0x0000000B){          //11 hrs warning    
             if(Cont_TIMEAL < 3){
                Cont_TIMEAL++;
                FEEDBACK_UART_PC(POC_FEEDBACKTIMEWR);
                //FEEDBACK_UART_PC(POC_FEEDBACKOCCD);
            // }else{
                //flag_OCCD = false;
                //Cont_TIMEAL = 0;
            
            }                
                //FEEDBACK_UART_PC(POC_FEEDBACKTIMEWR);
            }
#endif            
            if(flag_Startup == true){
#if 1            
                //ADC0_Enable();
                //ADC0_ConversionStart();
                //CBVC
                if(ADC0_ConversionStatusGet())
                {
                    uint16_t v_adc_p=ADC0_ConversionResultGet();
                    //SYS_CONSOLE_PRINT("v_adc_p = %x\r\n", v_adc_p);
                   if(v_adc_p > 0xF00)
                    {
                        flag_CBVC = true;
                        if(Cont_CBVC < 3){
                           Cont_CBVC++;                        
                           FEEDBACK_UART_PC(POC_FEEDBACKGPIONG);
                           //FEEDBACK_UART_PC(POC_FEEDBACKCBVC);
                        //flag_CBVC = false;
                        }
                        }else{
                           flag_CBVC = false;
                           Cont_CBVC = 0;
                          
                   }
                }
                //if(v_adc_p < 5)
                //{
  
                //}
#endif                
#if 1           
            //OCCD
            if(!GPIO_PA06_Get())
            {
             flag_OCCD = true;
             if(Cont_OCCD < 3){
                Cont_OCCD++;
                FEEDBACK_UART_PC(POC_FEEDBACKGPIONG);
                //FEEDBACK_UART_PC(POC_FEEDBACKOCCD);
             }
             }else{
                flag_OCCD = false;
                Cont_OCCD = 0;
            
            }
#endif                
#if 1                
            //OCDS    
            if(GPIO_PA07_Get())
            {
             flag_OCDS = true;
             if(Cont_OCDS < 3){
                Cont_OCDS++;
                FEEDBACK_UART_PC(POC_FEEDBACKGPIONG);
                //FEEDBACK_UART_PC(POC_FEEDBACKOCDS);
             }  
              }else{
                flag_OCDS = false;
                Cont_OCDS = 0;
            }
            
#endif                
#if 1                
            //OCDD    
            if(!GPIO_PC10_Get())
            {
             flag_OCDD = true;
             if(Cont_OCDD < 3){
                Cont_OCDD++;
                FEEDBACK_UART_PC(POC_FEEDBACKGPIONG);
                //FEEDBACK_UART_PC(POC_FEEDBACKOCDD);
             }
            }else{
                flag_OCDD = false;
                Cont_OCDD = 0;
            }
#endif  
            }
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
#if 0          
            if(flag_ALSRead == true){
                flag_ALSRead = false;
             Als_read = ALS_Read(ALS_1_CTRL_ADDR);
             if(Als_read < Als_judge){
              FEEDBACK_UART_PC(POC_FEEDBACKNG);
             }
            }
#endif
#if 1               
           if(EEData_POC.uchour == 0x00000001)
           {
             if(EEData_POC.mark != 0x01){
             EEData_POC.mark = 0x01;
             Als_read = ALS_Read(ALS_1_CTRL_ADDR);
             EEData_POC.Als_100 = Als_read;
             EEPROM_Write_Data_POC(EEPROM_USERDATA_ADDR1,&EEData_POC);
             }
           }
                
            //if((EEData_POC.mark == 0x01) & (flag_CheckMark == true) & ((EEData_POC.uchour % 0x18) == 0x00)){
            if((EEData_POC.mark == 0x01) & (flag_CheckMark == true)){    
                flag_CheckMark = false;
                Als_read = ALS_Read(ALS_1_CTRL_ADDR);
                if(Als_read <= (EEData_POC.Als_100/2))
                {
                 //FEEDBACK_UART_PC(POC_FEEDBACKDALSNG);
                 FEEDBACK_UART_PC(POC_FEEDBACKDALSAL);
                }
            }
            if(flag_pre_Als == true){    
                pre_Als_read = ALS_Read(ALS_1_CTRL_ADDR);
                for (uint32_t i = 0; i < 20000; i++);//1ns*20000=2ms
                Als_read = ALS_Read(ALS_1_CTRL_ADDR);
                if((pre_Als_read - Als_read) > (pre_Als_read/4)){
                    //if(Cont_ALS25NG < 3 ){
                        //Cont_ALS25NG++;
                        FEEDBACK_UART_PC(POC_FEEDBACKDALSNG);
                    //}else{
                        //Cont_ALS25NG = 0;
                    //}
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
