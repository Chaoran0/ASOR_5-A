#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int stop = 0;

void sighandler (int signo){
    if(signo == SIGUSR1) stop = 1;
}

int main(int argc, char *argv[]) {
  int secs = atoi(argv[1]);
  if (argc != 2) {
    printf("ERROR: incorrect arguments\n");
    exit(1);
  }

  struct sigaction act;
  //Sigint
  sigaction(SIGUSR1, NULL, &act); //Get handler
  act.sa_handler = sighandler;
  sigaction(SIGUSR1, &act, NULL); //Set sa_handler

  printf("Se va a borrar el fichero %s después de %d segundos. Envía SIGUSR1 para detener.\n", argv[0], secs);

  int i = 0;
  alarm(secs+1);
	while (i < secs && stop == 0) {
    i++;
    sleep(1);
    
  }
  

  if (stop == 0) {
    printf("Borrado\n");
    unlink(argv[0]);
  } else {
    printf("Impedido\n");
  }
    
  return 0;
}
