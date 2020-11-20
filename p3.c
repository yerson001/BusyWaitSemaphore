#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<stdlib.h> 
#include<unistd.h>
#include "sem.h"

#define SHMSZ     27

main()
{
    char *args[]={"./p1",NULL};
    int shmid,num;
    //key_t key;
    char *shm, *s,*ss;

    int sem_id;
    int shm_id;
    int rc;
    key_t key;
    key = ftok(".",'A');

    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }

    initsem(key,1);

    //key = 5678;

    if ((shmid = shmget(key, SHMSZ, 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }


 // usamos nuestro semaforo para esta zona critica donde se accede a
 // la SHM la memoria conpartida ya que ambos procsos pueden acceder al mismo tiempo
 // el primero que ingresa bloquea el segmento 

    //while (*shm != '*'){
        // siempre intenta leer lo que hay en el segmeto compartido  
//**************************************************************
        sem_p(); //indicamos que el resurso no esta disponible
//*************************************************************
        printf("proceso 3\n");
        for(s = shm; *s!=NULL; s++)
        {
            ss = s; putchar(*s);printf(" -> Value Into SHM\n");
        }

    
        num = *ss-'0';
        if(num%2==1)
        {
            printf("\n +++++++++[> The number is ODD <]+++++++++ %i\n",num);
            printf("KILL proces P1\n");
            *shm = '*';
            execvp(args[0],args); 
        }
//****************************************************************
        sem_v();  // liberamos el resurso
//****************************************************************
// }
 //****************************************************************
    sem_destroy(); // eliminamos el semaforo 
//******************************************************************
    exit(0);
}