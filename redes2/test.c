#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// Recibir la funcion en memoria global para los hilos
void *thread_func(void *args);
//recibir desde parametros de consola el numero de hilos a crear
int main(int argc, char const *argv[])
{
    //paso 0: Recepcion del numero de hilos a crear
    if (argc == 2)
    {
        int num_hilos;
        //Definir el numero de hilos
        num_hilos = atoi(argv[1]);
        //Definir los hilos que se crearan
        pthread_t *hilos[num_hilos];
        void *retvals[num_hilos];
        printf("num de hilos: %d\n", num_hilos);
        int count;
        for (count = 0; count < num_hilos; count++)
        {
            //Creacion de los hilos
            if (pthread_create(&hilos[count], NULL, thread_func, "..."))
            {
                printf("Error al crear hilos\n");
                break;
            }
        }
        // int pthread_join(pthread_t thread, void **retval);
        for (size_t i = 0; i < count; i++)
        {

            if (pthread_join(hilos[i], &retvals[i]) != 0)
            {
                fprintf(stderr, "error: Cannot join thread # %d\n", i);
            }
        }

        return 0;
    }
    else
    {
        printf("Introducir el numero de hilos\n");
        return -1;
    }
}

void *thread_func(void *args)
{
    const char *str = (const char *)args;

    printf("Threading %s\n", str);
    usleep(1000);
}
