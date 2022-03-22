#include "include/main.h"

int main(void) {
  FILE *fp = fopen("data/words.txt", "rt");
  if (fp == NULL) {
    printf("\t[ERROR] File does not exist\n");
    return EXIT_FAILURE;
  }

  size_t count_line = 0u;
  while (!feof(fp)) {
    fscanf(fp, "%*[^\n]%*c");
    count_line++;
  }

  int number_commands = 0;
  printf("Input number of comands (0 > n <= %d): ", MAX_NUM_COM);
  while (scanf("%d", &number_commands) != 1 || number_commands <= 0 || number_commands > MAX_NUM_COM) {
    fscanf(stdin, "%*[^\n]%*c");
    printf("\t[ERROR] Do not correct data\n");
  }

  size_t *scope = (size_t *)calloc(number_commands, sizeof(size_t));
  char **name_com = (char **)malloc(number_commands * sizeof(char *));

  for (size_t i = 0; i < (size_t)number_commands; ++i) {
    name_com[i] = (char *)malloc(20 * sizeof(char));
    printf("Name of %lu team: ", i + 1);
    scanf("%20s", name_com[i]);
  }

  char menu_option = '\0';
  while (menu_option != 27) {
    for (int i = 0; i < number_commands; ++i) {
    }
    for (int i = 0; i < number_commands; ++i) {
      printf("%2d:%20s %3lu\n", i + 1, name_com[i], scope[i]);
    }
    menu_option = getchar();
    fscanf(stdin, "%*[^\n]%*c");
  }

  fclose(fp);
  return EXIT_SUCCESS;
}
