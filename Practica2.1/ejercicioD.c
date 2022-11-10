#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>


int main(){
  //int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);
  //int settimeofday(const struct timeval *tv, const struct timezone *tz);
  /*
  struct timezone {
     int tz_minuteswest;      --minutes west of Greenwich
     int tz_dsttime;          --type of DST correction 
  };
  */
	timeval ini, fin, sol;

	gettimeofday(&ini, NULL);
	for(int i = 0; i < 1000000; i++){}
	gettimeofday(&fin, NULL);

	printf("Inicio: %d\n", ini.tv_usec);
	printf("Fin: %d\n", fin.tv_usec);
	sol.tv_usec = fin.tv_usec - ini.tv_usec;
	printf("Tarda: %d\n", sol.tv_usec);
  
  return 0;
}
