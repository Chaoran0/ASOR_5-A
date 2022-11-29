#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char *argv[]) {

  sigset_t set;

  //export SLEEP_SECS=100 ó usar int setenv(const char *name, const char *value, int overwrite); para poner la variable de entorno
  setenv("SLEEP_SECS", "5", 1); //Nombre: SLEEP_SECS  Valor: 5  Sobreescribir: Sí

  sigemptyset(&set);//inicializa un conjunto como vacío, excluyendo todas las señales
  sigaddset(&set, SIGINT);//añade una señal a un conjunto
  sigaddset(&set, SIGTSTP);

  //Protegemos la región de código contra la recepción de las señales
  sigprocmask(SIG_BLOCK, &set, NULL);//Añade el conjunto set al conjunto de señales actualmente bloqueadas (“OR”)

  //Obtenemos la variable de entorno
  char *sleep_secs = getenv("SLEEP_SECS");
  int secs = atoi(sleep_secs);
  printf("Se va a dormir el proceso durante %d segundo(s)\n", secs);
  //Dormimos el proceso
  sleep(secs);

  //Comprobamos las señales pendientes
  sigset_t pending;
  sigpending(&pending);

  if (sigismember(&pending, SIGINT) == 1) { //comprueba si una señal pertenece a un conjunto
    printf("Se ha recibido la señal SIGINT\n");
    //Eliminamos la señal del conjunto anterior
    sigdelset(&set, SIGINT);
  } else {
      printf("No se ha recibido la señal SIGINT\n");
  }
  if (sigismember(&pending, SIGTSTP) == 1) {
    printf("Se ha recibido la señal SIGTSTP\n");

    //Eliminamos la señal del conjunto anterior
    sigdelset(&set, SIGTSTP);
  } else {
    printf("No se ha recibido la señal SIGTSTP\n");
  }

  sigprocmask(SIG_UNBLOCK, &set, NULL);

  return 0;
}
