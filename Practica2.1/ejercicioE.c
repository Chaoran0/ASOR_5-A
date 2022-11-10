#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>


int main(){
  //struct tm *localtime(const time_t *timep);
	time_t timep;
	struct tm *local;
	
	t = time(NULL);
	local = localtime(&timep);
	
	printf("Año: %d\n", local->tm_year+1900);
  //tm_year: The number of years since 1900.
  
	return 0;
}
