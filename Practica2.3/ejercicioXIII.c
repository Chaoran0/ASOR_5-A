#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile bool stop;

void sighandler (int signo){
    if(signo == SIGUSR1) stop = true;
}

int main(int argc, char *argv[]) {
  int secs = atoi(argv[1]);
  if (argc != 2) {
    printf("ERROR: Introduce los segundos!\n");
    exit(1);
  }

  struct sigaction act;
  //Sigint
  sigaction(SIGUSR1, NULL, &act); //Get handler
  act.sa_handler = &sighandler;
  sigaction(SIGUSR1, &act, NULL); //Set sa_handler

  int i = 0;
	while (i < secs && stop == 0) {
    i++;
    sleep(1);
  }

  if (stop == 0) {
    printf("Se va a borrar");
    unlink(argv[0]);
  } else {
    printf("Has tenido suerte!");
  }
    
  return 0;
}
