
/* 
 * File:   main.c
 * Integrantes: 
 * 
 * Rocio Trejo Reyes
 * Mauricio Yael Diaz Rosales
 * José Emiliano Pérez Garduño
 *
 * Created on October 26, 2020, 10:31 AM
 */

//#ifndef KEYPAD_4X4_H
#define KEYPAD_4X4_H

//Definicion de librerias para funcionamiento del programa
#include <xc.h>           // include processor files - each processor file is guarded.
#include <stdint.h>       // libreria que nos permitira trabajar con variables enteras
#include <stdlib.h>       // Libreria para tipo char
#include <stdio.h>        // Libreria para lenguaje C
#include "config.h"       // Header para poder usar el pic16f887
#include "lcd.h"          // Header para poder usar el LCD

//Definicion de variables para funcionamiento del programa
#define _XTAL_FREQ 8000000 // Frecuencia para el reloj interno
char pass[] = {"9876"};    // pass para el programa
char data[3];              // Input del user
unsigned char index = 0;             // Variable auxiliar para posicionar datos en el arreglo y en el LCD

//Definicion de funciones para el programa
int login(char input[], char pass[]); // Funcion para verificar el login correcto
char boton_pressed(void);             // Funcion para indicar la tecla presionada

//Funcion principal
void main(void)
{
    // Creacion de variables para la matriz
    ANSELH = 0;                          //  Registro RB del PIC
    ANSEL = 0;                           //  Registro RA del PIC
    OPTION_REGbits.nRBPU = 0;            //  PULLUP-RESISTORS
    char tecla;                          //  char del teclado
    ADCON1 = 0x07;                       //  Registro 1 ADCON
    Lcd_Init();                          //  Inicializacion LCD
    Lcd_Command(LCD_CLEAR);              //  Clear pantalla LCD
    Lcd_Command(LCD_CURSOR_OFF);         //  No usaremos cursor asi que lo apagamos
    __delay_ms(100);                     //  Pausa de 100 milisegundos para evitar conflictos con el LCD
    Lcd_ConstText(1, 1, "PASS VISIBLE"); //  Se muestra en la parte de arriba del LCD la opcion de mostrar el char introducido o no
    Lcd_ConstText(2, 1, "1.-Si/0.-No");  //  Elegir si mostar o no char
    TRISAbits.TRISA0 = 0x00;             //  Se asigna TRISA0 como output
    TRISAbits.TRISA1 = 0x00;             //  Se asigna TRISA1 como output
    PORTAbits.RA0 = 0x00;                //  Inicializar PORTA.RA0 con valor de 0x00
    PORTAbits.RA1 = 0x00;                //  Inicializar PORTA.RA1 con valor de 0x
    int mostrar_tecla = 0;               //  Flag para indicar si se mostrara el char o no
    int next_step = 0;                   //  Variable para omitir aguardar la respuesta de la visualizaciï¿½n en el arreglo
    int bucle = 1;
    //Bucle infinito para ejecutar correctamente el programa
    while (bucle == 1)
    {
        tecla = boton_pressed(); // Almacenamos el resultado de la tecla presionada en tecla
        if (tecla != ' ')        // Si la tecla presionada retorna vacio hubo un error o no se presiona nada por lo que no se hace nada
        {
            if (tecla == '1') // Si la tecla presionada es 1 y la variable para identificar el 0 los valores que ingrese se mostraran
            {
                mostrar_tecla = 1;              //  Se asigna 1 al flag de mostrar tecla, mostrara el char
                Lcd_WriteChar(2, 6, tecla);     //  Se muestra en el display el valor que presiono el usuario
                __delay_ms(100);                //  Pausa de 100 milis para evitar conflictos
                Lcd_Command(LCD_CLEAR);         //  Se limpia el display
                __delay_ms(100);                //  Pausa de 100 milis para evitar conflictos
                Lcd_ConstText(1, 1, "PASSWD:"); //  Se pide ingresar la pass
            }
            else if (tecla == '0') //Si la tecla presionada es 0 y la variable para identificar es 0 los valores que ingrese se mostrara '*'
            {
                mostrar_tecla = 0;              //  Se asigna 1 al flag de mostrar tecla, mostrara asterisco
                Lcd_WriteChar(2, 6, tecla);     //  Se muestra en el display el valor ingresado
                __delay_ms(100);                //  Pausa de 100 milis para evitar conflictos
                Lcd_Command(LCD_CLEAR);         //  Se limpia el display
                __delay_ms(100);                //  Pausa de 100 milis para evitar conflictos
                Lcd_ConstText(1, 1, "PASSWD:"); //  Se pide ingresar la pass
            }
            if (mostrar_tecla == 1) //  Si se presiono algo mostramos siguiente menu
            {
                if (next_step != 0) //  Si la variable next_step es diferente de 0 se accede al proximo menu
                {
                    if (mostrar_tecla == 1) //  Si la flag mostrar es 1 se muestra el char
                    {
                        Lcd_WriteChar(2, index, tecla); //  Se muestra en el display el char
                    }
                    if (mostrar_tecla == 0) //  Si la variable next_step es diferente de 0 se accede al proximo menu
                    {
                        Lcd_WriteChar(2, index, '*'); //    Se muestra en el display el *
                    }
                    data[index] = tecla; // Se guarda en data la tecla ingresada y se sigue al proximo index
                    index++;             // index aumenta
                    if (index == 4)      // Cuando index sea 4 se llego al limite de chars para el password
                    {
                        if (login(data, pass) == 1) //  Se verifica que el password ingresado sea el correcto
                        {
                            __delay_ms(100);                  //  Sleep de 100 milis para evitar conflictos
                            Lcd_Command(LCD_CLEAR);           //  Limpiar LCD para nuevo text
                            PORTAbits.RA0 = 1;                //  LED de indicacion prendido
                            __delay_ms(100);                  //  Sleep de 100 milis para evitar conflictos
                            Lcd_ConstText(1, 1, "CORRECTO!"); //  Password correcto, se accede al sistema
                        }
                        else // Passwd incorrecta
                        {
                            PORTAbits.RA1 = 1;                       // Se prende LED rojo para mostrar conflicto
                            Lcd_Command(LCD_CLEAR);                  // Limpiar LCD para nuevo text
                            __delay_ms(100);                         // Sleep de 100 milis para evitar conflictos
                            Lcd_ConstText(1, 1, "[ERROR]");          // Mostrar ERROR
                            Lcd_ConstText(2, 1, "INCORRECT PASSWD"); // Mostrar descripcion del error
                            __delay_ms(200);                         // Sleep de 100 milis para evitar conflictos
                            Lcd_Command(LCD_CLEAR);                  // Limpiar LCD para nuevo text
                            PORTAbits.RA1 = 0;                       // Se apaga el LED rojo
                            __delay_ms(100);                         // Sleep de 100 milis para evitar conflictos
                            Lcd_ConstText(1, 1, "PASS VISIBLE");     // Se muestra el primer menu
                            Lcd_ConstText(2, 1, "1.-Si/0.-No");      // Opciones para mostrar char o no
                            mostrar_tecla = 0;                       // Reiniciamos flags
                            next_step = 0;                           // Reiniciamos flags
                            index = 0;                                   // Reiniciamos index
                        }
                    }
                }
                else // Si todavia no se muestra el sig menu
                {
                    next_step = 1; // Se guardan los caracteres en el arreglo
                }
            }
            else //  Si no se presiona nada se sigue mostrando el primer menu
            {
                __delay_ms(100);                     //  Sleep programa por 100 milisegundos
                Lcd_Command(LCD_CLEAR);              //  Clear LCD
                Lcd_ConstText(1, 1, "PASS VISIBLE"); //  Se muestra en la parte de arriba del LCD la opcion de mostrar el char introducido o no
                Lcd_ConstText(2, 1, "1.-Si/0.-No");  //  Elegir si mostar o no char
            }
        }
        while ((PORTBbits.RB4 == 0) || (PORTBbits.RB5 == 0) || (PORTBbits.RB6 == 0) || (PORTBbits.RB7 == 0)) // Limpiar registros para evitar memory dump
        {
            __delay_ms(50); //  Pase de 50 milis para evitar conflictos
        }
        while ((PORTBbits.RB4 == 0) || (PORTBbits.RB5 == 0) || (PORTBbits.RB6 == 0) || (PORTBbits.RB7 == 0)) // Limpiar registros para evitar memory dump
        {
            __delay_ms(50); //  Pase de 50 milis para evitar conflictos
        }
    }
}
// Funcion para realizar la verificacion de password
int login(char input[], char pass[])
{
    for (int x = 0; x < 4; x++) // Ciclamos los 4 datos introducidos [0-3]
    {
        if (input[x] != pass[x]) // Si el char x de input es igual al char x de pass continua con el ciclo, sino se rompe y regresa -1
        {
            return -1;
        }
    }
    return 1; // Si nunca se rompio el ciclo el login fue exitoso
}

// Funcion para leer la tecla presionada
char boton_pressed(void)
{
    TRISB = 0XF0;      //  Valor inicial de input
    PORTB = 255;       // Valor inicial B
    PORTBbits.RB0 = 0; // Inicializar RB0 en 0 para introducir los valores de la matriz
    if (PORTBbits.RB4 == 0)
        return '1'; //  Boton 1 presionado
    if (PORTBbits.RB5 == 0)
        return '2'; //  Boton 2 presionado
    if (PORTBbits.RB6 == 0)
        return '3'; //  Boton 3 presionado
    if (PORTBbits.RB7 == 0)
        return 'A';    //  Boton A presionado
    PORTBbits.RB0 = 1; //Termina la primer columna, sigue con la proxima
    PORTBbits.RB1 = 0; //Inicializa la columna 2
    if (PORTBbits.RB4 == 0)
        return '4'; //  Boton 4 presionado
    if (PORTBbits.RB5 == 0)
        return '5'; //  Boton 5 presionado
    if (PORTBbits.RB6 == 0)
        return '6'; //  Boton 6 presionado
    if (PORTBbits.RB7 == 0)
        return 'B';    //  Boton B presionado
    PORTBbits.RB1 = 1; //Termina la segunda columna, sigue con la proxima
    PORTBbits.RB2 = 0; //Inicializa la columna 3
    if (PORTBbits.RB4 == 0)
        return '7'; //  Boton 7 presionado
    if (PORTBbits.RB5 == 0)
        return '8'; //  Boton 8 presionado
    if (PORTBbits.RB6 == 0)
        return '9'; //  Boton 9 presionado
    if (PORTBbits.RB7 == 0)
        return 'C';    //  Boton C presionado
    PORTBbits.RB2 = 1; //Termina la tercera columna, sigue con la proxima
    PORTBbits.RB3 = 0; //Inicializa la columna 4
    if (PORTBbits.RB4 == 0)
        return '*'; //  Boton 7 presionado
    if (PORTBbits.RB5 == 0)
        return '0'; //  Boton 8 presionado
    if (PORTBbits.RB6 == 0)
        return '#'; //  Boton 9 presionado
    if (PORTBbits.RB7 == 0)
        return 'D'; //  Boton C presionado
    PORTBbits.RB3 = 1;
    return ' '; //En caso de no presionar nada regresa espacio vacio
}