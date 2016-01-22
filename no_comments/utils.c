

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "include.h"



void            display_usage()
{
  printf("Usage: ./no_comment [FILES_NAME]\n");
  printf("\nOptions:\n");
  printf("-h : get help\n");
  printf("-d [DIRECTORY] : set the directory for output files\n");
  printf("-D [DIRECTORY] : set the directory for output files and build it if not exist\n");
  printf("\nnote: if no directory is specified, a new one called 'no_comments' will be created\n");
  printf("You can use multiple files using the structure '*.' but don't use the '*' caractere alone!\\
n");
  exit(EXIT_FAILURE);
}



char            *make_directory(char *directory, char *file_name)
{
  char          *res;
  int           i = 0;
  int           j = 0;

  if ((res = malloc(sizeof(directory) + sizeof(file_name) + 1)) == NULL)
    exit(0);
  while (directory[i] != '\0')
    res[i] = directory[i++];
  if (res[i] != '/' && file_name[0] != '/')
    res[i++] = '/';
  while (file_name[j] != '\0')
    res[i++] = file_name[j++];
  return (res);
}



int             check_directory(char *directory, int build)
{
  struct stat s;
  int err = stat(directory, &s);

  if(-1 == err)
    {
      if(ENOENT == errno && build == 0)
	{
	  printf(ANSI_COLOR_RED "ERROR: %s does not exist\n" ANSI_COLOR_RESET
		 , directory);
	  exit(0);
	}
      else
	{
	  mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
    }
  else
    {
      if(S_ISDIR(s.st_mode))
	{
	  return (1);
	}
      else
	{
	  printf(ANSI_COLOR_RED "ERROR: %s is not a directory\n" ANSI_COLOR_RESET
		 , directory);
	  exit(0);
	}
    }
  return (0);
}
