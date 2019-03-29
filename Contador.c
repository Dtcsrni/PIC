//Contador con sensor via infrarrojo, con pantalla LCD para PIC 16f887
//Por Erick Renato Vega Cerón
//Ingeniería en Sistemas Computacionales
//Centro Universitario Hidalguense

// Conexiones del módulo LCD
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;

sbit LCD_D4 at RB7_bit;
sbit LCD_D5 at RB6_bit;
sbit LCD_D6 at RB5_bit;
sbit LCD_D7 at RB4_bit;

sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;

sbit LCD_D4_Direction at TRISB7_bit;
sbit LCD_D5_Direction at TRISB6_bit;
sbit LCD_D6_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB4_bit;

// Final de las conexiones del módulo LCD
//Variables de apoyo
   int activado1=0;         //Bandera de activado
   int activado2=0;
   int desactivado1=0;         //Bandera de activado
   int desactivado2=0;
   int contador1=0;
   int contador2=0;
   int Lactiv=0;
   char txt[8];
   char txt1[8]="P1";
   char txt3[8]="P2";
   char txt2[8];
void main() {

       ANSEL = 0b00000000; // Digital
       ANSELH = 0;
       TRISE = 0b00000011; // PORTE.0 y PORTE.1 son configurados como entradas. Los demás como salidas
       PORTE = 0;
       TRISD = 0b00000000; // PORTE.0 y PORTE.1 son configurados como entradas. Los demás como salidas
       PORTD = 0;
        Lcd_Init();
        Delay_ms(500);
        Lcd_Out(1,1,"   ||CUH||");
        Lcd_Out(2,1,"||ERICK VEGA||");
        Delay_ms(2000);
               // Cursor off
         Lcd_Cmd(_LCD_CLEAR);
         Lcd_Cmd(_LCD_CURSOR_OFF);

             PORTD.RD2=1;
      while(1){
      Lcd_Cmd(_LCD_CLEAR);
      if(Lactiv==0){
      PORTD.RD2=1;
      Lactiv=1;
      }
      else{
      if(Lactiv==1){
      PORTD.RD2=0;
        Lactiv=0;
      }
        }
            if(PORTE.RE0 ==0){
               activado1=1;
            }
            else{
               desactivado1=0;
               activado1=0;
            }

            if(PORTE.RE1 ==0){
               activado2=1;
            }
            else{
               desactivado2=0;
               activado2=0;
            }

      if(activado1==1&&desactivado1==0){
                 contador1=contador1+1;
                 desactivado1=1;
               }
               else{
      if(activado2==1&&desactivado2==0){
                 contador2=contador2+1;
                 desactivado2=1;
               }      }
               WordToStr(contador1, txt);
               WordToStr(contador2, txt2);
      Lcd_Out(1,1,txt1);
      Delay_us(1000);
      Lcd_Out(1,8,txt);
      Delay_us(1000);
      Lcd_Out(2,1,txt3);
      Delay_us(1000);
      Lcd_Out(2,8,txt2);
      Delay_ms(500);

      }


}
