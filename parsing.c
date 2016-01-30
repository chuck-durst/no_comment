/*
** parsing.c
**
** Read the files
**
** Made by Chuck Durst <charles.durst@epitech.euq>
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include "include.h"

int             *parsing_file(char *file_name, int *counter, llist l_args)
{
  FILE          *fp;
  FILE          *np;
  char          *line = NULL;
  size_t        len = 0;
  ssize_t       read;
  int           i = 1;
  int		comment_count = 0;
  DIR           *d;
  char		*directory = make_directory(l_args->directory, file_name);
  int		sub_dir = l_args->pr_s;
  char		*org_dir = l_args->directory;
  struct dirent *dir;

  if (nmatch(file_name, "*/..") == 1 || nmatch(file_name, "*/.") == 1 ||
      nmatch(file_name, ".") == 1 || nmatch(file_name, "..") == 1 ||
      nmatch(file_name, "no_comment") == 1)
    return (counter);
  counter[3] = counter[3] + 1;
  if  (is_directory(file_name) == 1 && nmatch(file_name, org_dir) == 0)
    {
      d = opendir(file_name);
      if (d && sub_dir == 1)
	{
	  printf(ANSI_COLOR_BLUE"!---> Reading directory '%s':\n"ANSI_COLOR_RESET,
		 file_name);
	  while ((dir = readdir(d)) != NULL)
	    {
	      check_directory(directory, 1);
	      counter = parsing_file(make_directory(file_name, dir->d_name),
				     counter, l_args);
	    }
	  printf(ANSI_COLOR_BLUE"End of directory '%s' <---!\n"ANSI_COLOR_RESET,
		 file_name);
	  return (counter);
	  closedir(d);
	}
      return (counter);
    }
  printf("\n> Reading file: '%s'\n", file_name);
  printf("Destination: '%s'\n", directory);
  if ((fp = fopen(file_name, "r")) == NULL)
    {
      printf(ANSI_COLOR_RED"! Error while reading file '%s'\n" ANSI_COLOR_RESET
	     , (file_name ? file_name : " "));
      counter[1] = counter[1] + 1;
      return (counter);
    }
  if ((np = fopen(directory, "w+")) == NULL)
    {
      printf(ANSI_COLOR_RED"! Error while creating file '%s'\n"ANSI_COLOR_RESET
	     , (file_name ? file_name : " "));
      counter[1] = counter[1] + 1;
      return (counter);
    }
  counter[0] = counter[0] + 1;
  while ((read = getline(&line, &len, fp)) != -1)
    comment_count = write_file(np, line, comment_count);
  printf("Total of comments deleted: %d\n", comment_count);
  printf(ANSI_COLOR_GREEN "--> Done for %s\n\n"ANSI_COLOR_RESET, file_name);
  counter[2] = counter[2] + comment_count;
  return (counter);
  fclose(fp);
  fclose (np);
}
