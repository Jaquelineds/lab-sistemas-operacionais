#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  printf("Memória livre: \n");
  system("free -g | awk '{print $4}'");
  printf("Memória usada: \n");
  system("free -g | awk '{print $3}'");
  return 0;
}
