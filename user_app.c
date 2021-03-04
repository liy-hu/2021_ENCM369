/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/


/*--------------------------------------------------------------------
void TimeXus(INPUT_PARAMETER_)
Sets Timer0 to count u16Microseconds_
Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535
Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
*/
void TimeXus(u16 microsecondsoffset)
{
 /* OPTIONAL: range check and handle edge cases */
 /* Disable the timer during config */
    T0CON0 = T0CON0 & 0x7F; // turns timer off
    u16 timervalue = 0xFFFF-microsecondsoffset; //value for which the timer starts counting
    
 /* Preload TMR0H and TMR0L based on u16TimeXus */
    TMR0L = (u8)(timervalue & 0x00FF); 
    TMR0H = (u8)((timervalue >> 8) & 0x00FF);
 
 /* Clear TMR0IF and enable Timer 0 */
   
    PIR3 = PIR3 & 0X7F; // clears the TMR0IF flag 
    T0CON0 = T0CON0 | 0x80; // starts timer
    
    
    

} /* end TimeXus () */

void UserAppInitialize(void)
{
  /* Timer control register Initialization */
    
    T0CON0 = 0x90; //Sets the required settings for timer0
    T0CON1 = 0x54; //Sets the required settings for timer0
    LATA = 0X80; //Sets LATA 
    

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
   /*Bit counter*/ 
   //u32 TempLATA; 
    
    //for (u8 counter =0x00; counter < 64; counter++ )
    //{
       //This is for the delay of 250 ms
      // u32 u32Counter = 400000;
       //while(u32Counter>0)
        //{
            //u32Counter= u32Counter-1; 
        //}
        
        //TempLATA = ((LATA | 0x80) +0x01);
       //LATA = TempLATA; 
        
     
        
   // }
    
        
   static u16 u16counter = 0; // acts as a counter to delay timer
   u16counter= u16counter+1;
   
   /*Blink RED LED RA0*/ 
   //if(u16counter >= 500) //causes the operation of toggle to delay
   //{
      // u16counter = 0;
       //LATA= (LATA & 0X01)^0X01;
   //}
   
  
  /*Interesting pattern design */
  
   static int index = 0;
   u8 au8Pattern[] ={0x01,0x02, 0x04, 0x08, 0x10, 0x20}; //array of bit patterns
  
   if (u16counter >= 200) //delays operation of implementing next pattern 
   {
    
      u16counter =0;
      LATA = 0x80; //resets LATA to be ready for next pattern
      LATA = LATA | au8Pattern[index]; //access the bit pattern in array and implements it
 
      index = index +1; 
    }
  
   if(index == 6) //repeats the array of the bit patterns by resetting index
   {
      index=0;
   }
   
  
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
