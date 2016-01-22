/*
** utils.c
**
** Some utils functions
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
#include "include.h"

//Display the usage command line guide

void            display_usage()
{
  printf("Usage: ./no_comment [FILES_NAME]\n");
  printf("\nOptions:\n");
  printf("-h : get help\n");
  printf("-d [DIRECTORY] : set the directory for output files\n");
  printf("-s : open sub directory\n");
  printf("-D [DIRECTORY] : set the directory for output files and build it if not exist\n");
  printf("\nnote: if no directory is specified, a new one called 'no_comments' will be created\n");
  exit(EXIT_FAILURE);
}

//Build a new directory

char            *make_directory(char *directory, char *file_name)
{
  char          *res;
  int           i = 0;
  int           j = 0;

  if ((res = malloc(sizeof(directory) + sizeof(file_name) + 5)) == NULL)
    exit(0);
  while (directory[i] != '\0')
    res[i] = directory[i++];
  if (res[i] != '/' && file_name[0] != '/')
    res[i++] = '/';
  while (file_name[j] != '\0')
    res[i++] = file_name[j++];
  res[i + 1] = '\0';
  return (res);
}

//Check if the directory exist and quit if it's not the case

int             check_directory(char *directory, int build)
{
  struct stat s;
  int err = stat(directory, &s);

  if(-1 == err)
    {
      if(build == 0)
	{
	  printf(ANSI_COLOR_RED "ERROR: %s does not exist\n" ANSI_COLOR_RESET,
		 directory);
	  exit(0);
	}
      else
	{
	  mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	  return (1);
	}
    }
  else
    {
      if(S_ISDIR(s.st_mode))
	return (1);
      else
	{
	  printf(ANSI_COLOR_RED "ERROR: %s is not a directory\n" ANSI_COLOR_RESET
		 , directory);
	  exit(0);
	}
    }
  return (0);
}

int             is_directory(char *directory)
{
  struct stat s;
  int err = stat(directory, &s);

  if(-1 == err && ENOENT == errno)
    return (0);
  else
    {
      if(S_ISDIR(s.st_mode))
	return (1);
      else
	return (0);
    }
  return (0);
}

int     nmatch(char *s1, char *s2)
{
  if (*s1 != '\0' && *s2 == '*')
    return (nmatch(s1 + 1, s2) +  nmatch(s1, s2 + 1));
  else if (*s1 == '\0' && *s2 == '*')
    return (nmatch(s1, s2 + 1));
  else if (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
    return (nmatch(s1 + 1, s2 + 1));
  else if (*s1 == '\0' && *s2 == '\0')
    return (1);
  return (0);
}
