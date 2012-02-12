#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *fp;
  if ((fp = fopen("./test_dump.txt","r")) == NULL) {
    printf("Can't open file"); exit(-1);
  }

  char n[405000];
  fscanf(fp, "%s", &n);
  printf("%s\n", n);
  fclose(fp);
}
