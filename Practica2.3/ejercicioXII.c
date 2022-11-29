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
  act.sa_handler = sighandler;
  act.sa_flags = 0;
  if(sigaction(SIGINT, NULL, &act) == -1){
        perror("sigaction SIGINT failed\n");
        exit(-1);
  }
  //sigaction(SIGINT, &act, NULL);

  if(sigaction(SIGTSTP, NULL, &act) == -1){
        perror("sigaction SIGINT failed\n");
        exit(-1);
  }
  //sigaction(SIGTSTP, &act, NULL);

  while((INTcount + TSTPcount) < 10);

    printf("Señal SIGINT . Numero total recibido: %d\n", INTcount);
    printf("Señal SIGISTP. Numero total recibido: %d\n", TSTPcount);

    
  return 0;
}
