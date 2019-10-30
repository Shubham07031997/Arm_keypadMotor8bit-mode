#include <lpc21xx.h>
 
#define LCD (0xff<<8)
#define RS (1<<16)
#define RW (1<<17)
#define EN (1<<18)
 
#define r1 (1<<16)
#define r2 (1<<17)
#define r3 (1<<18)
#define r4 (1<<19)
#define c1 (1<<20)
#define c2 (1<<21)
#define c3 (1<<22)
#define c4 (1<<23)
 
void delay(unsigned int time);           // variable delay function
 
void lcd_ini(void);
void lcd_print(char *str);
void lcd_cmd(unsigned char command);
void lcd_dat(unsigned int data);
 
unsigned char keypad (void);
void keypad_delay(unsigned int z);
 int a;
int main (void)
   {
        PINSEL0 = 0x00000000;
        IODIR0 = 0Xffffffff;
        PINSEL1 = 0x00000000;
        IODIR1=0x00f00000;
        PINSEL2=0x00000000;
        lcd_ini();
        lcd_print("Press any key");
        lcd_cmd(0xc0);
 
        while(1)
          {	   	a=keypad();
                
				
				lcd_dat(a);
				if(a=='4')
				{
				    	IOSET0=0xA0000000;	 //led
						delay(200);
						IOCLR0=0xA0000000;
						delay(50);}
						if(a=='8')
						{
						    	IOSET0=0x00000001;	//motor
						delay(100);
						IOCLR0=0x00000001;
						delay(50);}
						if(a=='2')
						{ 	IOSET0=0x00000000;			 //all of
						delay(100);}
						if(a=='6')
						{
						  	IOSET0=0x50000000;	  //relay
						delay(200);
						IOCLR0=0x50000010;
						delay(50);}
          } 
        return 0;
   }

 
void keypad_delay(unsigned int z)
   {
        unsigned int t1,t2;
        for(t1=0;t1<z;t1++)                 
                for(t2=0;t2<1275;t2++);
   }
 
 
 
unsigned char keypad (void)
   {
        unsigned char key;
        IOCLR1|=(c1|c2|c3|c4|r1|r2|r3|r4);
        while(1)
           {
                IOCLR1|=c1;
                IOSET1|=(c2|c3|c4);                     // first column = 0
                
                if((IOPIN1&r1)==0)
                   {
                        key='7';
                        keypad_delay(50);
                        return key;
                   }
                else if((IOPIN1&r2)==0)
                  {
                        key='4';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r3)==0)
                  {
                        key='1';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r4)==0)
                  {			 lcd_cmd(0x01);
                        keypad_delay(50);
                        
                  }
                
                IOCLR1|=c2;
                IOSET1|=(c1|c3|c4);                     //second column = 0
                
                if((IOPIN1&r1)==0)
                  {
                        key='8';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r2)==0)
                  {
                        key='5';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r3)==0)
                  {
                        key='2';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r4)==0)
                  {
                        key='0';
                        keypad_delay(50);
                        return key;
                  }
                
                IOCLR1|=c3;
                IOSET1|=(c1|c2|c4);                     //third column = 0
 
                if((IOPIN1&r1)==0)
                  {
                        key='9';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r2)==0)
                  {
                        key='6';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r3)==0)
                  {
                        key='3';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r4)==0)
                  {
                        key='=';
                        keypad_delay(50);
                        return key;
                  }
                
                IOCLR1|=c4;
                IOSET1|=(c1|c2|c3);                     //forth column = 0
 
                if((IOPIN1&r1)==0)
                  {
                        lcd_cmd(0x01);
                        keypad_delay(50);
                        
                  }
                else if((IOPIN1&r2)==0)
                  {
                        key='0';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r3)==0)
                  {
                        key='=';
                        keypad_delay(50);
                        return key;
                  }
                else if((IOPIN1&r4)==0)
                  {
                        key='+';
                        keypad_delay(50);
                        return key;
                  }
          }
   }
 
void lcd_cmd(unsigned char command)
  {
        IO0CLR|=(RS|RW|EN|LCD);
        IO0SET|=(command<<8);
        IO0CLR|=RS;
        IO0CLR|=RW;
        IO0SET|=EN;
        delay(2);
        IO0CLR|=EN;
        delay(3);
  }
  
void lcd_dat(unsigned int data)        
  {
        IO0CLR|=(RS|RW|EN|LCD);
        IO0SET|=(data<<8);
        IO0SET|=RS;
        IO0CLR|=RW;
        IO0SET|=EN;
        delay(2);
        IO0CLR|=EN;
        delay(3);
  }
 
void lcd_print(char *str)
  {
        while(*str!='\0')
          {
                lcd_dat(*str);
                str++;
          }
  }
 
void lcd_ini(void)
  {
        delay(5);
        lcd_cmd(0X38);
        lcd_cmd(0X0f);
        lcd_cmd(0X06);
        lcd_cmd(0X01);
        delay(5);
        lcd_cmd(0X80);
  }
 
void delay(unsigned int time)           // variable delay function 
  {
        unsigned int t1,t2;
        for(t1=0;t1<time;t1++)       
                for(t2=0;t2<1275;t2++);
  }
