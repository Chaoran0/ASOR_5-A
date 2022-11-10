#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <locale.h>

int  main(int argc, char *argv[]){
	//size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
  //char *setlocale(int category, const char *locale);
  setlocale(LC_ALL, "es_ES");
  time_t t = time(NULL);
  struct tm *local = localtime(&t);
  char outstr[200], outstrDay[200], outstrDay1[200], outstrMonth[200], outstrYear[200];
  
  strftime(outstrDay, sizeof(outstrDay), "%A", local);//weekday name
  strftime(outstrDay1, sizeof(outstrDay1), "%e", local);//month day
  strftime(outstr, sizeof(outstr), "%R", local);//The time in 24-hour notation (%H:%M)
  strftime(outstrMonth, sizeof(outstrMonth), "%B", local);//month name
  strftime(outstrYear, sizeof(outstrYear), "%Y", local);//year

	printf("%s, %d de %s de %d,%s\n",outstrDay, outstrDay1, outstrMonth, outstrYear, outstr);
  
	return 0;
}
