
//PRÁCTCA n°1 
//Integrantes:
//Gutiérrez Gonzaléz Gustavo
//Ríos Guzmán Omar Eduardo
#include <stdio.h>                                                              //Librería principal para lenguaje c
#include <stdlib.h>                                                             //Librería para el manejo de  arreglos de caracteres 
#include "config.h"                                                             //Librería de las configuraciones del pic16f887
#define _XTAL_FREQ  4000000                                                     //Frecuencia del oscilador interno
#include "lcd.h"                                                                //Libería para el uso de un LCD
#include <xc.h>                                                                 //Librería para el manejo de los registros y puertos del pic16f887
char contrasena[]={"1234"};                                                     //Arreglo con la contraseña establecida
char datos[3];                                                                  //Arreglo donde se va almacenar los caracteres que ingrese el usuario
int i=1;                                                                        //variable para ver la posición del arreglo y del LCD
int verificar(char usuario[],char contrasena[]);                                //Función para comparar la contraseña establecida con la que ingreso el usuario
char teclas(void);                                                              //Función para detectar cual tecla fue presionada 
void main(void)                                                                 //Función principal del programa
  {
        ANSELH  = 0;                                                            //Lineas digitales RB
        ANSEL   = 0;                                                            //Lineas digitales RA
        OPTION_REGbits.nRBPU = 0;                                               //Activar resistencia de pull-up internas
        char aux;                                                               //varible para asignar el valor de la letra que fue precionada en el teclado
        ADCON1  = 0x07;                                                         //Lineas digitales
        Lcd_Init();                                                             //Iniciamos el LCD
        Lcd_Command(LCD_CLEAR);                                                 //Limpiamos pantalla
        Lcd_Command(LCD_CURSOR_OFF);                                            //Apaga el cursor
        __delay_ms(100);                                                        //Pausa en el programa
        Lcd_ConstText(1, 1, "PASS VISIBLE");                                //Se muestra en la parte de arriba del LCD la frase
        Lcd_ConstText(2, 1, "1.-Si/0.-No");                                           //Muestra las opciones que tiene el usuario para ver o no los valores que ingrese el usuario
        TRISAbits.TRISA0 = 0x00;                                                //TRISA0 lo asignamos como salida
        TRISAbits.TRISA1 = 0x00;                                                //TRISA1 lo asignamos como salida 
        PORTAbits.RA0    = 0x00;                                                //RA0 lo ponemos en 0
        PORTAbits.RA1    = 0x00;                                                //RA1 lo ponemos en 0
        int mostrar_aux  = 0;                                                   //Variable para indicar que se eligió una de las opciones 
        int mostrar      = 0;                                                   //Variable para saber cual de las dos opciones se elegió
        int proced       = 0;                                                   //Variable para omitir aguardar la respuesta de la visualización en el arreglo                                                              
        bucle:                                                                  //Inicio del bucle infinito
            aux=teclas();                                                       //Mandamos a llamar la función para ver que tecla se presiono
            if(aux!=' ')                                                        //Si es diferente el caracter a espacio que es el valor por default se realiza lo siguiente
              {
                    if((aux == '1')&&(mostrar == 0))                            //Si la tecla presionada es 1 y la variable para identificar el 0 los valores que ingrese se mostraran
                       {
                            mostrar_aux = 1;                                    //Se le asigna 1 a la variable que ya fue elegida una de las dos opciones
                            mostrar     = 1;                                    //Se le asigna 1 a la varible que indica que si se muestren los valores en el LCD
                            Lcd_WriteChar(2, 6,aux);                            //Se muestra en el display el valor que presiono el usuario
                            __delay_ms(100);                                    //Pausa en el programa
                            Lcd_Command(LCD_CLEAR);                             //Se limpia el display
                             __delay_ms(100);                                   //Pausa en el programa
                            Lcd_ConstText(1, 1, "PASSWD:");                   //Se muestra la frase Password para que el usuario pueda ingresar la contraseña
                       }
                    if((aux == '0')&&(mostrar == 0))                            //Si la tecla presionada es 0 y la variable para identificar es 0 los valores que ingrese se mostrara '*'                          
                      {
                            mostrar_aux =1;                                     //Se le asigna 1 a la variable que ya fue elegida una de las dos opciones
                            mostrar     =2;                                     //Se le asigna 2 a la variable que indica que se mostra '*' en cada caracter que ingrese
                            Lcd_WriteChar(2, 6,aux);                            //Se muestra en el display el valor que presiono el usuario
                            __delay_ms(100);                                    //Pausa en el programa
                            Lcd_Command(LCD_CLEAR);                             //Se limpia el display
                             __delay_ms(100);                                   //Pausa en el programa
                            Lcd_ConstText(1, 1, "PASSWD:");                   //Se muestra la frase Password para que el usuario pueda ingresar la contraseña
                       }
                    if(mostrar_aux == 1)                                        //Si la variable mostrar_aux es 1 se procede a realizar lo siguiente
                      {
                            if(proced != 0)                                     //Si la variable proced es diferente de 0 se realiza lo siguiente
                              {
                                    if(mostrar == 1)                            //Si mostrar es igual 1 se realiza lo siguiente
                                      {
                                         Lcd_WriteChar(2, i,aux);               //Se muestra en el display el caracter de la tecla que ingreso 
                                      }
                                    if(mostrar == 2)                            //Si mostrar es igual 2 se realiza lo siguiente 
                                      {
                                         Lcd_WriteChar(2, i,'*');               //Se muestra en el display un '*' por cada caracter de la tecla que presione el usuario
                                      }
                                     datos[i-1] = aux;                          //Se aguarda en el arreglo el caracter que eligió el usuario en el teclado
                                     i++;                                       //se le aumenta 1 a la variable 1
                                     if(i == 5)                                 //Si i se incremento a 5 indica que ya se lleno el arreglo con los caracteres necesarios para comparar con la contraseña
                                       {
                                            if(verificar(datos,contrasena) == 1)//Se comparan los arreglos  de la contraseña ya establecida con la que ingreso el usuario, si manda 1 los dos arreglos son iguales
                                               {
                                                    __delay_ms(100);            //Pausa en el programa
                                                    Lcd_Command(LCD_CLEAR);     //Se limpia el LCD
                                                    PORTAbits.RA0 = 1;          //Prendemos el LED verde donde mandamos 1 a RA0
                                                    __delay_ms(100);            //pausa en el programa
                                                    Lcd_ConstText(1, 1, "CORRECTO!");   //Se muestra en el display la frase de 'Bienvenido' 
                                                }
                                            else                                //Si regresa 0 la función verificar, los arreglos no son iguales 
                                                {
                                                    PORTAbits.RA1 = 1;          //Prendemos el LED rojo donde mandamos 1 a RA1
                                                    Lcd_Command(LCD_CLEAR);     //Se limpia el display
                                                    __delay_ms(80);             //Pausa en el programa
                                                    Lcd_ConstText(1, 1, "[ERROR]");   //Se muestra en el display la frase de 'ERROR' indicando que esta mal la contraseña
                                                    Lcd_ConstText(2, 1, "INCORRECT PASSWD"); // Mostrar descripcion del error
                                                    __delay_ms(200);           //Pausa en el programa
                                                    Lcd_Command(LCD_CLEAR);     //Se limpia el display
                                                    PORTAbits.RA1 = 0;          //Apagamos el LED rojo donde mandamos 1 a RA1
                                                    __delay_ms(100);            //Pausa en el programa
                                                    Lcd_ConstText(1, 1, "PASS VISIBLE");   //Se muestra en la parte de arriba del LCD la frase
                                                    Lcd_ConstText(2, 1, "1.-Si/0.-No");              //Muestra las opciones que tiene el usuario para ver o no los valores que ingrese el usuario
                                                    mostrar_aux   = 0;          //Mandamos 0 a la variable mostrar_aux
                                                    mostrar       = 0;          //Mandamos 0 a la variable mostrar                   
                                                    proced        = 0;          //Mandamos 0 a la variable proced
                                                    i             = 1;          //Mandamos 1 a i para volver a llenar el arreglo y el display de las teclas que ingrese el usuario
                                                 }
                                        }
                              }
                            else                                                //Si proced aun no se le asigna 1  
                              {
                                 proced = 1;                                    //Se le asigna 1 a proced para poder realizar el aguardado de los caracteres en el arreglo
                              }
                      }
                    else                                                        //Si el usuario no eligió una de las dos opciones 
                      {
                        __delay_ms(100);                                        //Pausa en el programa
                        Lcd_Command(LCD_CLEAR);                                 //Limpiamos el LCD
        Lcd_ConstText(1, 1, "PASS VISIBLE");                                //Se muestra en la parte de arriba del LCD la frase
        Lcd_ConstText(2, 1, "1.-Si/0.-No");                                           //Muestra las opciones que tiene el usuario para ver o no los valores que ingrese el usuario
                      }
               }
            while((PORTBbits.RB4==0)||(PORTBbits.RB5==0)||(PORTBbits.RB6==0)||(PORTBbits.RB7==0))   //Para evitar el efecto de rebote
              {
               __delay_ms(30);                                                                      //Pausa en el programa
              }
            while((PORTBbits.RB4==0)||(PORTBbits.RB5==0)||(PORTBbits.RB6==0)||(PORTBbits.RB7==0))   //Para evitar el efecto de rebote
              {
               __delay_ms(30);                                                                      //Pausa en el programa
              }
        goto bucle;                                                             //fin de las funciones que va hacer el bucle
}
int verificar(char u[],char c[])                                                //Función para comparar los arreglos 
  { 
    int j, bandera = 1;                                                         //Variable para el ciclo for, variable para identificar si son iguales los dos arreglos
    for(j = 0;j < 4;j++)
     {
        if(u[j] != c[j])                                                        //Si un caracter es diferente al arreglo de la contraseña establecida
          {
             j       = 4;                                                       //Se asigna 4 a j para terminar el ciclo for
             bandera = 0;                                                       //A la variable bandera le asignamos 0
          }
     }
    return bandera;                                                             //Regresamos la variable banbera 
}

char teclas(void )                                                              //Función para detectar la tecla presionada por el usuario
  {
    TRISB = 0xF0;                                                               //Se asignan las salidas y entradas 
    PORTB = 255;                                                                //Se le asignan  1 al puerto B
    PORTBbits.RB0 = 0;                                                          //Le mandamos 0 a RB0
    if(PORTBbits.RB4 == 0)                                                      //Si RBO Y RB4 son 0 
     {
        return '1';                                                             //Se regresa el caracter de '1'
     }
    if(PORTBbits.RB5 == 0)                                                      //Si RB0 y RB5 son 0
     {
        return '2';                                                             //Se regresa el caracter de '2'
     }
    if(PORTBbits.RB6 == 0)                                                      //Si RB0 y RB6 son 0
     {
        return '3';                                                             //Se regresa el caracter de '3'
     }
    if(PORTBbits.RB7 == 0)                                                      //Si RBO y RB7 son 0
     {
        return 'A';                                                             //Se regresa el caracter de 'A'
     }
    PORTBbits.RB0 = 1;                                                          //Le mandamos 1 a RB0
    
    PORTBbits.RB1 = 0;                                                          //Le asignamos 0 a RB1
    if(PORTBbits.RB4 == 0)                                                      //Si RB1 y RB4 son 0
     {
        return '4';                                                             //Se regresa el caracter de '4'
     }
    if(PORTBbits.RB5 == 0)                                                      //Si RB1 y RB5 son 0
     {
        return '5';                                                             //Se regresa el caracter de '5'
     }
    if(PORTBbits.RB6 == 0)                                                      //Si RB1 y RB6 son 0
     {
        return '6';                                                             //Se regresa el caracter de '6'
     }
    if(PORTBbits.RB7 == 0)                                                      //Si RB1 y RB7 son 0
     {
        return 'B';                                                             //Se regresa el caracter de 'B'
     }
    PORTBbits.RB1 = 1;                                                          //Le mandamos 1 a RB1
    
    PORTBbits.RB2 = 0;                                                          //Le asignamos 0 a RB2
    if(PORTBbits.RB4 == 0)                                                      //Si RB2 y RB4 son 0
     {
        return '7';                                                             //Se regresa el caracter de '7'
     }
    if(PORTBbits.RB5 == 0)                                                      //Si RB2 y RB5 son 0
     {
        return '8';                                                             //Se regresa el caracter de '8'
     }
    if(PORTBbits.RB6 == 0)                                                      //Si RB2 y RB6 son 0
     {
        return '9';                                                             //Se regresa el caracter de '9'
     }
    if(PORTBbits.RB7 == 0)                                                      //Si RB2 y RB7 son 0
     {
        return 'C';                                                             //Se regresa el caracter de 'C'
     }
    PORTBbits.RB2 = 1;                                                          //Le mandamos 1 a RB2
    
    PORTBbits.RB3 = 0;                                                          //Le asignamos 0 a RB3
    if(PORTBbits.RB4 == 0)                                                      //Si RB3 y RB4 son 0
     {
        return '*';                                                             //Se regresa el caracter de '*'
     } 
    if(PORTBbits.RB5 == 0)                                                      //Si RB3 y RB5 son 0
     {
        return '0';                                                             //Se regresa el caracter de '0'
     }
    if(PORTBbits.RB6 == 0)                                                      //Si RB3 y RB6 son 0
     {
        return '#';                                                             //Se regresa el caracter de '#'
     }
    if(PORTBbits.RB7 == 0)                                                      //Si RB3 y RB7 son 0
     {
        return 'D';                                                             //Se regresa el caracter de 'D'                                                        
     }
    PORTBbits.RB3 = 1;                                                          //Le asignamos 1 a RB3
    
    return ' ';                                                                 //Si ninguna condición cumple se regresa el valor default ' '
  }