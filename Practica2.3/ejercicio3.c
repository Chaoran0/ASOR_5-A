#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>



int main (int argc, char *argv[]){
    //int nice(int inc);
    
    if (argc != 2){
        printf("Argument failed\n");
        exit(1);
    }
    //int atoi(const char *nptr);
    int pid = atoi (argv[1]);
    struct sched_param sp;
    sp.sched_priority = 12; 
    int ret = sched_setscheduler(pid, SCHED_FIFO, &sp);//a politica SCHED_FIFO y prioridad 12
    if(ret == -1){
        printf ("ERROR \n");
        exit(1);
    }
    int sched = sched_getscheduler(pid);
    switch(sched){
        case SCHED_OTHER:
            printf("SCHEDULER OTHER\n");
        break;
        case SCHED_FIFO:
            printf("SCHEDULER FIFO\n");
        break;
        case SCHED_RR:
            printf("SCHEDULER RR\n");
        break;
        default:
            printf("ERROR\n");
    }


    struct sched_param p;//no se puede pasar un puntero sin inicializar(*p), pero si reservas en pila si se puede
    int param = sched_getparam(pid, &p);
    if(param == -1)
        printf("ERROR\n");
    else
        printf("Prioridad %d\n", p.sched_priority);
    
    int max = sched_get_priority_max(sched);
    int min = sched_get_priority_min(sched);
    printf("Prioridad máxima: %d\nPrioridad mínima: %d\n", max, min);
    

    return 0;
}
