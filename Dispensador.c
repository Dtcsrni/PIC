//Contador con sensor via infrarrojo, con pantalla LCD para PIC 16f887
//Por Erick Renato Vega Cerón
//Ingeniería en Sistemas Computacionales
//Centro Universitario Hidalguense

// Conexiones del módulo LCD
sbit LCD_RS at RC0_bit;    //Mapear puerto RC0 a RS
sbit LCD_EN at RC1_bit;    //Mapear puerto RC1 a EN

sbit LCD_D4 at RB7_bit;   //Mapear D4 a RB7
sbit LCD_D5 at RB6_bit;    //Mapear D5 a RB6
sbit LCD_D6 at RB5_bit;   //Mapear D6 a RB5
sbit LCD_D7 at RB4_bit;  //Mapear D7 a RB4
//Definir direccion de escritura para bits
sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;

sbit LCD_D4_Direction at TRISB7_bit;
sbit LCD_D5_Direction at TRISB6_bit;
sbit LCD_D6_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB4_bit;

// Final de las conexiones del módulo LCD
//Variables de apoyo
//Unidades de servicio por opcion
   int cantidad1 = 1;
   int cantidad2 = 5;
   int cantidad3 = 10;
   int cantidad4 = 20;
//Precio por opcion de servicio
   int precio1 = 1;
   int precio2 = 3;
   int precio3 = 6;
   int precio4 = 12;
   int saldoExistente = 0;

   int activado1=0;         //Bandera de activado
   int activado2=0;
   int desactivado1=0;         //Bandera de desactivado
   int desactivado2=0;
   int saldo=0;      //variables de contador
   int contador2=0;
   int botonActivo=0;
   int opcionElegida = 0;
   int valorAnalogico = 0;

   //Constantes de texto
   char txt[16];
   char nombreUnidadProducto[17] = "Lt";
   char mensajeCantidadProducto[17] = "Cantidad:";
   char tipoNegocio[17] = "|Purificadora|"  ;
   char nombreNegocio[17] = "||CUH||";
   char mensajeOpcion[17] = ">Elija opcion" ;
   char mensajeEfectivo[17] = "Ingrese efectivo"  ;
   char mensajeSaldo[17] = ">Saldo: $";
   char mensajeCosto[17] =  ">Costo: $" ;
   char msjOpcion[17] = "Opcion elegida:";
   //Declaracion de funcion
   void mostrarMensaje(int opcion, int saldo, int boton);
   void despacharServicio(int cantidad);
   void revisarSensorDinero();
   void revisarBotones();
   
   char txt1[16] = "";   //Texto P1
   char txt3[16] = "";   //Texto P2
   char txt2[16] = "";
void main() {
/////Configuracion de PINES
       ANSEL = 0x0000000; // Configure AN2 pin as analog
       TRISA  = 0xFF;
       ANSELH = 0;
       TRISE = 0b00000111; // PORTE.0, PORTE.1 y PORTE.2 son configurados como entradas. Los demas como salidas
       PORTE = 0;                     //Se limpia el puerto
       TRISB = 0b00000001; // PORTE.0, PORTE.1 y PORTE.2 son configurados como entradas. Los demas como salidas
       PORTB = 0;
       TRISD = 0b01000001; // PORTD.7 como entrada y el resto de PORTD como salidas
       PORTD = 0;                     //Se limpia el puerto

        Lcd_Init();                  //Se inicializa el módulo lcd
        Delay_ms(100);                  //Espera de estabilizacion de LCD
               // Cursor off
         Lcd_Cmd(_LCD_CURSOR_OFF);     //Ocultar cursor
                        mostrarMensaje(0, 0, 0); //Mostrar el mensaje de inicio
                        delay_ms(2500);     //Esperar 2.5 segundos
                        while(1){    //Ciclo iterativo permanente
                            PORTD.RD2=1;
                           //Detectar ingreso de dinero
                           revisarSensorDinero();
                           if(saldoExistente==1){
                              if(saldo == opcionElegida){
                                    despacharServicio(opcionElegida);
                              }
                           }
                           //Revisar botones en caso de que alguno sea presionado
                           revisarBotones();
                           //Conmutar el estado del led
                           delay_MS(500);
                           PORTD.RD2=0;     //Prender LED en RD2
                        }
     }
     void revisarSensorDinero(){
                    if(Button(&PORTB, 0, 1, 1)){
                    saldo++;
                    Lcd_Cmd(_LCD_CLEAR);
                    botonActivo = 0;
                    Lcd_Out(1,1, mensajeSaldo);
                    Lcd_Out(2,4, "$");
                    IntToStr(saldo, txt);
                    Lcd_Out(2,5, txt);
                    saldoExistente = 1;
                   }
     }
     
     void revisarBotones(){
                             //Se revisa el estado de cada boton y se coloca su valor correspondiente en la variable de boton
                           if(Button(&PORTE, 0, 1, 1))
                           {
                                    opcionElegida = 1 ;
                           }
                           else   if(Button(&PORTE, 1, 1, 1))
                           {
                                    opcionElegida=2;
                           }
                           else   if(Button(&PORTE, 2, 1, 1))
                           {
                                    opcionElegida=3;
                           }
                           else   if(Button(&PORTD, 7, 1, 1))
                           {
                                    opcionElegida=4;
                           }
                           if(botonActivo>0)
                           {
                                    mostrarMensaje(3, -1, opcionElegida); //mostrar mensaje

                           }
     }

     void despacharServicio(int opcionElegida){
     int i = 0;
     int cantidad = 0;
           if(opcionElegida==1){
           cantidad = 1;
           }
           if(opcionElegida==2){
           cantidad = 5;
           }
           if(opcionElegida==3){
           cantidad = 10;
           }
           if(opcionElegida==4){
           cantidad = 15;
           }
           for(i=0;i<cantidad;i++){  //Bucle para servir cantidad de producto
                 Lcd_Cmd(_LCD_CLEAR);
                 PORTD.RD2=1;   //Encender LED de Estado
                 Lcd_Out(1,1, "Solicitado:");      //Mostrar cantidad de producto solicitado
                 IntToStr(cantidad, txt);
                 Lcd_Out(1,12, txt);

                 Lcd_Out(2,1, "Servido:");         //Mostrar Producto Servido
                 IntToStr(i, txt1);
                 Lcd_Out(2,8, txt1);
                 delay_ms(1000);
                 PORTD.RD2=0;    //Apagar LED de Estado
           }
           saldoExistente=0;
           mostrarMensaje(0, 0, 0);
     }
void mostrarMensaje(int modo, int saldo, int boton) {
     switch(modo)
     {
      case 1:           //Si el sistema esta en modo reposo
       Lcd_Cmd(_LCD_CLEAR);//Limpiar pantalla previo a mensaje
       Lcd_Out(1,1, mensajeOpcion); //Mostrar mensajes de opcion o de dinero
       Lcd_Out(2,1, mensajeOpcion);
      break;
      case 2:          //En caso de que el usuario ingrese primero el dinero
       Lcd_Cmd(_LCD_CLEAR);//Limpiar pantalla
       Lcd_Out(1,1, mensajeSaldo); //Mostrar saldo actual de cliente
       IntToStr(saldo, txt);
       Lcd_Out(1,10, txt);
      break;
      case 3:    //En caso de que el usuario ingrese primero la opcion  de producto
       Lcd_Cmd(_LCD_CLEAR);//Limpiar pantalla
       Lcd_Out(1,1, mensajeCosto); //Mostrar coste actual de la opcion elegida
      switch(boton)   //Mostrar dependiendo de la opcion elegida
      {
          case 1:
               IntToStr(precio1, txt1);
               Lcd_Out(2,1, txt1);
               break;
          case 2:
               IntToStr(precio2, txt1);
               Lcd_Out(2,1, txt1);
               break;
          case 3:
               IntToStr(precio3, txt1);
               Lcd_Out(2,1, txt1);
               break;
          case 4:
               IntToStr(precio4, txt1);
               Lcd_Out(2,1, txt1);
               break;
         }
      break;
      case 0:     //Si el sistema acaba de terminar un servicio
      Lcd_Cmd(_LCD_CLEAR);//Limpiar pantalla previo a mensaje
       Lcd_Out(1,1, tipoNegocio);
       Lcd_Out(2,1, nombreNegocio);
      break;
     }
}
