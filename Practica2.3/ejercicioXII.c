#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int INTcount = 0;
volatile int TSTPcount = 0;

void sighandler (int signo){
    if(signo == SIGINT) INTcount++;
    if(signo == SIGTSTP) TSTPcount++;
}

int main(int argc, char *argv[]) {

  //int sigaction(int signal, const struct sigaction *act, struct sigaction *oldact); manejador
  /*
  sa_handler specifies the action to be associated with signum and is be one of the following:
       * SIG_DFL for the default action.
       * SIG_IGN to ignore this signal.
       * A pointer to a signal handling function.  This function receives the signal number as its only argument.
       */

  struct sigaction act;
  if(sigaction(SIGINT, NULL, &act) != -1){
        act.sa_handler = sighandler;
        printf("Señal SIGINT recibido. Numero total recibido: %d\n", INTcount);
  }
  sigaction(SIGINT, &act, NULL);

  if(sigaction(SIGTSTP, NULL, &act) != -1){
        act.sa_handler = sighandler;
        printf("Señal SIGINT recibido. Numero total recibido: %d\n", TSTPcount);
  }
  sigaction(SIGTSTP, &act, NULL);

  sigset_t set;
  sigemptyset(&set);
  while(INTcount + TSTPcount < 10){
    //int sigsuspend(const sigset_t *set);
    sigsuspend(&set);
  }
    printf("Señal SIGINT . Numero total recibido: %d\n", INTcount);
    printf("Señal SIGISTP. Numero total recibido: %d\n", TSTPcount);

    
  return 0;
}
