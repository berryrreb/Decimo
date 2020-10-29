#!/usr/bin/python3
#Programa realizado por Victor Anaya Martinez y Emiliano Perez
import os
import sys
from shutil import copyfile

def main():
    print("Programa A Practica 1")
    copyFiles()

def copyFiles():
    flag_dir = validateIntInput("1.-Copiar imagenes desde directorio actual\n2.-Copiar imagenes desde otro directorio\n")
    if(flag_dir == 2):
        filelist= verifyNumImages(flag_dir)
    elif(flag_dir == 1):
        filelist= verifyNumImages(flag_dir)

def ruleImage(file):
    if(file.endswith('.png') or file.endswith('.jpg') or file.endswith('.jpeg')): 
        return True
    return False

def validateIntInput(message):
    while True:
        try:
            tryUserInput = int(input(message))
        except ValueError:
            print('El valor introducido no es un entero, intentar de nuevo.\n')
            continue
        else:
            return tryUserInput

def verifyFolder(message):
    while True:
        dir = input(message)
        if(os.path.isdir(dir)):
            return dir
        print('El directorio ingresado no existe, intentar de nuevo.\n')
            

def verifyNumImages(flag):
    while True:
        if(flag == 2):
            dir = verifyFolder("Escribir el directorio desde el que se copiaran las 10 imagenes\n")
            filelist = [file for file in os.listdir(dir) if ruleImage(file)]
            if(len(filelist) > 10):
                return filelist
            print('El directorio no tiene al menos 10 imagenes, intentar de nuevo.\n')
        elif(flag == 1):
            filelist = [file for file in os.listdir('.') if ruleImage(file)]
            if(len(filelist) > 10):
                return filelist
            print('El directorio no tiene al menos 10 imagenes.\n')
            sys.exit()




if __name__ == "__main__":
    main()