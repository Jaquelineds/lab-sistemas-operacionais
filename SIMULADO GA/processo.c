#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(char *url){
   pid_t 
   load_firefox(url);
   return 0;
	//exercicio 5
}

void load_firefox(char *url){
   char argString[500];
   sprintf(argString, "%s", "firefox --new-window");
   strcat(argString, " ");
   strcat(argString, url);
   system(argString);
}
