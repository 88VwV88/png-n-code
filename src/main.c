#include <stdio.h>

int main() {
  FILE *pFile = fopen("image.png", "wb+");

  fprintf(pFile, "%s",
          (char[]){0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A});

  char buffer[8];
  fgets(buffer, 8, pFile);

  printf("file contents are: %s\n", buffer);
  
  return fclose(pFile);
}
