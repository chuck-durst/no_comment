

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "include.h"

int             *parsing_file(char *file_name, char *directory, int *counter)
{
  FILE          *fp;
  FILE          *np;
  char          *line = NULL;
  size_t        len = 0;
  ssize_t       read;
  int           i = 1;
  int		comment_count = 0;

  printf("\n> Reading file: %s\n", file_name);
  printf("Destination: %s\n", directory);
  if ((fp = fopen(file_name, "r")) == NULL)
    {
      printf(ANSI_COLOR_RED "! Error while reading file %s\n" ANSI_COLOR_RESET
	     , (file_name ? file_name : " "));
      counter[1] = counter[1] + 1;
      return (counter);
    }
  if ((np = fopen(directory, "w+")) == NULL)
    {
      printf(ANSI_COLOR_RED "! Error while creating file %s\n" ANSI_COLOR_RESET
	     , (file_name ? file_name : " "));
      counter[1] = counter[1] + 1;
      return (counter);
    }
  counter[0] = counter[0] + 1;
  while ((read = getline(&line, &len, fp)) != -1)
    comment_count = write_file(np, line, comment_count);
  printf("Total comments deleted: %d\n", comment_count);
  printf(ANSI_COLOR_GREEN "--> Done for %s\n\n"ANSI_COLOR_RESET, file_name);
  counter[2] = counter[2] + comment_count;
  return (counter);
  fclose(fp);
  fclose (np);
}
