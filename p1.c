#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "sem.h"

#define SHMSZ     27

/*****************************************************************
 * Ejecutar:
 * gcc p1.c -o p1
 * gcc p2.c -o p2
 * gcc p3.c -o p3
 * 
 * RUN: ./p1
 * RUN: ./p2 & ./p3
 * 
 * Repositorio 
 * REPO: https://github.com/yerson001/BusyWaitSemaphore
 * 
 *****************************************************************
 */


char IntChar(int numero){
    return numero + '0';
}

main()
{   
    srand(time(NULL));
    char c,n;
    int shmid,num,cont=0;
    //key_t key;
    char *shm, *s;

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

    //asgigna segmento
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    s = shm;

    //for (c = 'a'; c <= 'z'; c++)
    //    *s++ = c;
    //*s = 's';
    num = rand() % (10);
    n = IntChar(num);
    *s++ = n;
    *s = NULL;

    while (*shm != '*'){
        //printf("Valor Actual en el Shared Memory: %i Cont : %i\n",num,cont++);
        printf("%i ",cont++);
        printf(" * Value SHM [ ");
        for(s = shm; *s!=NULL; s++)
        {
            putchar(*s);
        }

        printf(" ] * \n");
        sleep(3);
    }
        
    exit(0);
}
