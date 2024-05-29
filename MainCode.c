/*
 * File:   MainCode.c
 * Author: Pham Trung Hieu
 * ID    : 20119001
 * Created on 12 May 2024, 11:13 AM
 */

#include <xc.h>
#include "DefinePins.h"
#define F_CPU 1000000
#include<util/delay.h>




// 7-SEGMENT NUMBERS CODES
unsigned char SegCode[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x80, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};


// Khai báo bien cho LED 
void LedDisplay (unsigned long long led)
{
    LED0 = (unsigned char)(led & 0xFF);
    LED1 = (unsigned char)((led >> 8) & 0xFF);
    LED2 = (unsigned char)((led >> 16) & 0xFF);
    LED3 = (unsigned char)((led >> 24) & 0xFF);
    LED4 = (unsigned char)((led >> 32) & 0xFF);
    LED5 = (unsigned char)((led >> 40) & 0xFF);
    LED6 = (unsigned char)((led >> 48) & 0xFF);
    LED7 = (unsigned char)((led >> 56) & 0xFF);
}
unsigned long long led ;

// Sang dan
void Increment(){
int i;
led = 0;
    for (i=0;i<64;i++)
    {
        led =(led<<1)|1;
        LedDisplay(led);
        _delay_ms(100);
    } 
}

// Sang duoi
void Chasing(){
int i;
led = 0;
    for (i=0;i<64;i++)
    {
    (led = (unsigned long long)1<<i);
    LedDisplay(led);
    _delay_ms(100);
    } 
}

// Sang don
void PushBack(){
unsigned char i,j;
unsigned long long run = 1;//0000 0000 0000 0001
unsigned long long led = 0x0000;
unsigned long long save_state = 0x0000;
    for (i=0;i<64;i++)
    {
        for (j=0;j<64-i;j++)
        {
            led = (run<<j)|save_state;
            LedDisplay(led);
            _delay_ms(100);
        }
        save_state = led;
        LedDisplay(led);
        _delay_ms(100);
    } 
}

// Sang xen ke
void Alternate(){
int i;
led = 0x5555555555555555;
    for (i=0;i<64;i++)
    {
        (led = (led<<1));
        LedDisplay(led);
        _delay_ms(100);
        (led = (led>>1));
        LedDisplay(led);
        _delay_ms(100);
    } 
}


// 7 Seg Timer initialize
void timer0_init() {
    // Set up timer with prescaler = 1024
    TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);

    // Initialize counter
    TCNT0 = 0;
}

// 7 Seg Timer Display
void Timer()
{
    unsigned char seconds = 0;
    unsigned char minutes = 0;
    unsigned char timer_counter = 0;
    
    // Initialize timer
    timer0_init();
    
    while(1)
    {
        // Display the time
        LED7D1 = SegCode[minutes / 10];
        LED7D2 = SegCode[minutes % 10];
        LED7D3 = SegCode[seconds / 10];
        LED7D4 = SegCode[seconds % 10];

        // Wait for overflow
        while ((TIFR & (1 << TOV0)) == 0);

        // Clear overflow flag
        TIFR |= (1 << TOV0);
    
        // T?ng bi?n ??m
        timer_counter++;

        // C?p nh?t th?i gian m?i 0.25 giây
        if (timer_counter == 4) {
            timer_counter = 0;

            // T?ng giá tr? seconds và minutes n?u c?n
            if (seconds < 59) {
                seconds++;
            } else {
                seconds = 0;
                if (minutes < 59) {
                    minutes++;
                } else {
                    minutes = 0;
                }
            }
        }
    }
}


// Relays control
void Relay(){
    //Relays
    Relays.relay.RL0 = 1; Relay_Activate;
    Relays.relay.RL1 = 1; Relay_Activate;
}


// Motors control
void Motor(){
    //Motors
    Motors.DC1 = FORWARD;
    Motors.DC2 = BACKWARD ;
    Motors_Activate;
}


//LCD 
void LCDInit()
{
LCD_INS =0x38 ;LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
_delay_us(200) ;
LCD_INS =0x0c ; LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
_delay_us(200) ;
LCD_INS =0x06 ; LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
_delay_us(200) ;
LCD_INS =0x01 ;LCDE_H ;_delay_us(1); LCDE_L; _delay_us(1);
_delay_ms(20) ;
}

void PrintL (const char *str,unsigned char line, unsigned char col) {

    unsigned char add ;
    switch (line){
        case 0: add = 0x80; break;
        case 1: add = 0xC0; break;
        case 2: add = 0x94; break;
        case 3: add = 0xD4; break;
    }
    
    LCD_INS =add + col ;
    LCDE_H ;_delay_us(1); LCDE_L; _delay_us(50); // move to the position
    while(*(str)!='\0' ) {
        LCD_DATA = *str++ ;
        LCDE_H ;_delay_us(1); LCDE_L;
        _delay_us(10);
    }
}


//Display LCD with LINKED LIST options
void MenuDisplay(Menu *menu, unsigned char select)
{
    PrintL(menu->Title,0,0);
    PrintL(menu->List1,1,0);
    PrintL(menu->List2,2,0);
    PrintL(menu->List3,3,0);
    
    PrintL(">", select, 0);
}



// Main functions
int main(void) {
    MCUCR = 0x80 ;// Assume setup SRE (external memory enable)
    Menu *menu;
    unsigned char select = 1;
    XMCRA = 0;
    DDRG =0x0f;
    //LCD PRINTING  
    menu = &MainMenu;
    LCDInit();
    MenuDisplay(menu, select);
    
while(1){
//    PushBack(); // Sang dan
//    Increment(); // Sang don
//    Chasing(); // Sang duoi
//    Alternate(); // Sang xen ke
      
//    Timer();
    
//    Relay();
    
//    Motor();    

    
        ReadKey;
        if (!Buttons.DOWN) {
            while(!Buttons.DOWN) ReadKey;
            select = (select==3) ?1:select+1;
            MenuDisplay(menu, select);
        }

        if (!Buttons.UP) {
            while(!Buttons.UP) ReadKey;
            select = (select==1) ?3:select-1;
            MenuDisplay(menu, select);
        }
        
        if (!Buttons.RIGHT)
        {
            while(!Buttons.RIGHT) ReadKey;
            switch (select)
            {
                case 1:menu=(menu->MenuList1==NULL)?menu:menu->MenuList1;break;
                case 2:menu=(menu->MenuList2==NULL)?menu:menu->MenuList2;break;
                case 3:menu=(menu->MenuList3==NULL)?menu:menu->MenuList3;break;
            }
            MenuDisplay(menu,select) ;
        }
        
        if (!Buttons.LEFT)
        {
        while(!Buttons.LEFT) ReadKey;
        menu=(menu->pre==NULL)?menu:menu->pre;
        MenuDisplay(menu,select) ;
        }
    
        // Delay for a short period to allow display refresh
        _delay_ms(100);

} 

return 0;
}