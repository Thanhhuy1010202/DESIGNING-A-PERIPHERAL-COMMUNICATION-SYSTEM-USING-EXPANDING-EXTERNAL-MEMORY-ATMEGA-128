/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */



/*----------------------------------------------------------------------------------*/
//code bellow


#define EXMEM_ADD 0x1100
// CS offset
#define CS0 0
#define CS1 1
#define CS2 2
#define CS3 3
#define CS4 4
#define CS5 5
#define CS6 6
#define CS7 7
#define CS8 8
#define CS9 9
#define CS10 10
#define CS11 11
#define CS12 12
#define CS13 13
#define CS14 14
#define CS15 15
#define CS16 16
#define CS17 17
#define CS18 18
#define CS19 19


//DEFINE USING H/L STATE FOR LCD
#define LCDE_H (PORTG |= (1<<3))
#define LCDE_L (PORTG &= ~(1<<3))


// LIBRARY FOR NULL CHARACTER IN LINKED LIST EXERCISE
#include<stddef.h> // for NULL popinter


//define external device

//FOR LEDS
#define LED0 *(unsigned char *) (EXMEM_ADD+CS0)
#define LED1 *(unsigned char *) (EXMEM_ADD+CS1)
#define LED2 *(unsigned char *) (EXMEM_ADD+CS2)
#define LED3 *(unsigned char *) (EXMEM_ADD+CS3)
#define LED4 *(unsigned char *) (EXMEM_ADD+CS4)
#define LED5 *(unsigned char *) (EXMEM_ADD+CS5)
#define LED6 *(unsigned char *) (EXMEM_ADD+CS6)
#define LED7 *(unsigned char *) (EXMEM_ADD+CS7)
//
//FOR 7-SEG
#define LED7D1 *(unsigned char *) (EXMEM_ADD+CS8)
#define LED7D2 *(unsigned char *) (EXMEM_ADD+CS9)
#define LED7D3 *(unsigned char *) (EXMEM_ADD+CS10)
#define LED7D4 *(unsigned char *) (EXMEM_ADD+CS16)

////FOR LCD
#define LCD_DATA *(unsigned char *) (EXMEM_ADD+CS11)
#define LCD_INS *(unsigned char *) (EXMEM_ADD+CS12)


//FOR RELAYS
#define Relay_Activate (*(volatile unsigned char *) (EXMEM_ADD+CS15) = *( unsigned char *)(&Relays))



//MACROS
#define Motors_Activate (*(volatile unsigned char *) (EXMEM_ADD+CS13) = *(unsigned char *)(&Motors))
#define ReadKey (*(unsigned char *)(&Buttons) = *(unsigned char *) (EXMEM_ADD+CS14) )
#define STOP 0
#define FORWARD 1
#define BACKWARD 2




//RELAYS
struct bits {
unsigned char RL0 : 1 ;
unsigned char RL1 : 1 ;
unsigned char RL2 : 1 ;
unsigned char RL3 : 1 ;
unsigned char RL4 : 1 ;
unsigned char RL5 : 1 ;
unsigned char RL6 : 1 ;
unsigned char RL7 : 1 ;
};
union RL {
unsigned char relayall ;
struct bits relay ;
};
union RL Relays;



//MOTOR
struct Motor {
    unsigned char DC1: 2;
    unsigned char DC2: 2;
    unsigned char DCfree: 4;
};

struct Motor Motors;



//BUTTONS
struct Button{
unsigned char LEFT : 1 ;
unsigned char RIGHT : 1 ;
unsigned char UP : 1 ;
unsigned char DOWN : 1 ;
unsigned char GO : 1 ;
unsigned char BTN1 : 1 ;
unsigned char BTN2 : 1 ;
unsigned char BTN3 : 1 ;
};
struct Button Buttons;


/*------------------------------LINKED LIST----------------------------*/
typedef struct linker {
struct linker *pre ;
char Title[20];
char List1[20];
struct linker *MenuList1;
char List2[20];
struct linker *MenuList2;
char List3[20];
struct linker *MenuList3;
} Menu ;

Menu
MainMenu,SensorMenu,TempMenu,HumidityMenu,SetupMenu,AcuatorMenu,
        MotorMenu,Motor1Menu,Motor2Menu,RelaysMenu,LedsMenu;


//MAIN MENU
Menu MainMenu;

Menu MainMenu = {
    NULL,
    "      Main Menu     " ,
    " Sensors       " , &SensorMenu,
    " Actuators     " , &AcuatorMenu,
    " Setup        " , &SetupMenu,
};


// ACTUATOR_MENU 
Menu AcuatorMenu = {
    &MainMenu,
    "      Actuator      " ,
    " DC Motors " ,&MotorMenu,
    " Relays    " ,&RelaysMenu,
    " LEDs      " ,&LedsMenu,
};


// LED_MENU 
Menu LedsMenu = {
    &AcuatorMenu,
    "        LEDS        " ,
    " ON                 " ,NULL,
    " OFF                " ,NULL,
    " NONE               " ,NULL,
};

//MORTOR MENU
Menu MotorMenu = {
    &AcuatorMenu,
    "      DC Motors     " ,
    " Motors 01          " ,&Motor1Menu,
    " Motors 02          " ,&Motor2Menu,
    " ALL                " ,NULL,
};

//MOTOR_SUB MENU 1
Menu Motor1Menu = {
    &MotorMenu,
    "      Motors 1      " ,
    " ON                 " ,NULL,
    " OFF                " ,NULL,
    " NONE               " ,NULL,
};

Menu Motor2Menu = {
    &MotorMenu,
    "      Motors 2      " ,
    " ON                 " ,NULL,
    " OFF                " ,NULL,
    " NONE               " ,NULL,
};

//RELAY MENU
Menu RelaysMenu = {
    &AcuatorMenu,
    "       Relays       " ,
    " ON                 " ,NULL,
    " OFF                " ,NULL,
    " NONE               " ,NULL,
};

//SENSOR MENU
Menu SensorMenu = {
&MainMenu,
    "       Sensors      " ,
    " Temperature        " ,&TempMenu,
    " Humidity           " ,&HumidityMenu,
    " Date&Time          " , NULL,
};

//TEMPERATURE MENU
Menu TempMenu = {
    &SensorMenu,
    "     Temperature    " ,
    " ON                 " ,NULL,
    " OFF                " ,NULL,
    " setup              " ,NULL,
};

//HUMIDITY MENU
Menu HumidityMenu = {
    &SensorMenu,
    "      Humidity       " ,
    " ON                 " ,NULL,
    " OFF                " ,NULL,
    " setup              " ,NULL,
};

//SETUP MENU
Menu SetupMenu = {
    &MainMenu,
    "       Set up       " ,
    " Motor speed        " ,NULL,
    " LED sequence speed " ,NULL,
    " None               " ,NULL,
};