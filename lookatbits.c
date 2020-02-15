#include <stdio.h>
#include <inttypes.h>

void printbits(uint64_t s) {

  for (int i = 63; i>=0; i--)
   printf("%d",((1ULL << i) & s) ? 1 : 0 );

}

int main (int argc, char *argv[]){

  uint64_t s = 65;
  printbits(s);
  printf("\t%llx\t%lld\n", s, s);
return 0;

}

