//Contador con sensor via infrarrojo, con pantalla LCD para PIC 16f887
//Por Erick Renato Vega Cerón
//Ingeniería en Sistemas Computacionales
//Centro Universitario Hidalguense

// Conexiones del módulo LCD
sbit LCD_RS at RD0_bit;
sbit LCD_EN at RD1_bit;

sbit LCD_D4 at RB7_bit;
sbit LCD_D5 at RB6_bit;
sbit LCD_D6 at RB5_bit;
sbit LCD_D7 at RB4_bit;

sbit LCD_RS_Direction at TRISB3_bit;
sbit LCD_EN_Direction at TRISB2_bit;

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
void main() {

       ANSEL = 0b00000000; // Digital
       ANSELH = 0;
       TRISE = 0b00000011; // PORTE.0 y PORTE.1 son configurados como entradas. Los demás como salidas
       PORTE = 0;
        Lcd_Init();
        Lcd_Cmd(_LCD_CLEAR);               // Clear display
        Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off

       
      while(1){
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
      if(activado2==1&&desactivado2==0){
                 contador2=contador2+1;
                 desactivado2=1;
               }
      Lcd_Out(1,6,contador1);
      Lcd_Out(2,6,contador2);
      
      }


}
