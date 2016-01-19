/*
** no_comment.c
**
** This program will automaticaly create a copy of the files past as parameter
** and will delete every comments in them
**
** Made by Chuck Durst <chuckdurst67@gmail.com>
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int		COMMENT_COUNT = 0;
int		FILE_COUNT = 0;
int		ERR_COUNT = 0;

void		display_usage()
{
  printf("Usage: ./no_comment [FILES_NAME]\n");
  printf("\nOptions:\n");
  printf("-h : get help\n");
  printf("-d [DIRECTORY] : set the directory for output files\n");
  printf("-D [DIRECTORY] : set the directory for output files and build it if not exist\n");
  printf("\nnote: if no directory is specified, a new one called 'no_comment' will be created\n");
  printf("You can use multiple files using the structure '*.' but don't use the '*' caractere alone!\n");
  exit(EXIT_FAILURE);
}

char		*make_directory(char *directory, char *file_name)
{
  char		*res;
  int		i = 0;
  int		j = 0;

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

int		check_directory(char *directory, int build)
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

int		write_file(FILE *fp, char *line)
{
  int		i = 0;
  static int	control;

  if (control == 1)
    {
      while (line[i] != '*' || line[i + 1] != '/')
	{
	  if (line[i] == '\0')
	    return (0);
	  i++;
	}
      control = 0;
      i = i + 2;
    }
  else if (control == 2)
    {
      while (line[i] != '-' || line[i + 1] != '-'  || line[i + 2] != '>')
	{
	  if (line[i] == '\0')
	    return (0);
	  i++;
	}
      control = 0;
      i = i + 3;
    }
  while (line[i] != '\0')
    {
      if (line[i] == '/')
	{
	  if (line[i + 1] == '/')
	    {
	      COMMENT_COUNT++;
	      fputc('\n', fp);
	      return (0);
	    }
	  else if (line[i + 1] == '*')
	    {
	      COMMENT_COUNT++;
	      i = i + 2;
	      while (line[i] != '*' || line[i + 1] != '/')
		{
		  if (line[i] == '\0')
		    {
		      control = 1;
		      return (0);
		    }
		  else
		    i++;
		}
	      i = i + 2;
	    }
	}
      else if (line[i] == '<')
	{
	  if (line[i + 1] == '!' && line[i + 2] == '-' && line[i + 3] == '-')
	    {
	      COMMENT_COUNT++;
	      i = i + 4;
	      while (line[i] != '-' || line[i + 1] != '-' || line[i + 2] != '>')
		{
		  if (line[i] == '\0')
		    {
		      control = 2;
		      return (0);
		    }
		  else
		    i++;
		}
	      i = i + 3;
	    }
	}
      fputc(line[i], fp);
      i++;
      }
  return (0);
}

int		parsing_file(char *file_name, char *directory)
{
  FILE		*fp;
  FILE		*np;
  char		*line = NULL;
  size_t	len = 0;
  ssize_t	read;
  int		i = 1;

  printf("Reading file: %s\n", file_name);
  printf("Destination: %s\n", directory);
  COMMENT_COUNT = 0;
  if ((fp = fopen(file_name, "r")) == NULL)
    {
      printf(ANSI_COLOR_RED "Error while reading file %s\n" ANSI_COLOR_RESET
	     , (file_name ? file_name : " "));
      ERR_COUNT++;
      return (0);
    }
  if ((np = fopen(directory, "w+")) == NULL)
    {
      printf(ANSI_COLOR_RED "Error while creating file %s\n" ANSI_COLOR_RESET
	     , (file_name ? file_name : " "));
      ERR_COUNT++;
      return (0);
    }
  FILE_COUNT++;
  while ((read = getline(&line, &len, fp)) != -1)
    {
      write_file(np, line);
    }
  printf(ANSI_COLOR_GREEN "--> Done for %s\n", file_name);
  printf("Total comments deleted: %d\n\n" ANSI_COLOR_RESET, COMMENT_COUNT);
  fclose(fp);
  fclose (np);
}

int		main(int ac, char **av)
{
  int		i = 1;
  int		j = 0;
  char		*directory = NULL;

  if (ac < 2)
    display_usage();
  while (i < ac)
    {
      if (av[i][0] == '-')
	{
	  if (av[i][1] == 'd')
	    {
	      i++;
	      if (check_directory(av[i], 0) == 1)
		directory = av[i];
	      i++;
	    }
	  else if (av[i][1] == 'D')
	    {
	      i++;
	      if (check_directory(av[i], 1) == 1)
		directory = av[i];
	      i++;
	    }
	  else if (av[i][1] == 'h')
	    display_usage();
	}
      else
	{
	  if(directory == NULL)
	    check_directory("no_comment", 1);
	  parsing_file(av[i],
		       (directory != NULL ?
			make_directory(directory, av[i]) :
			make_directory("./no_comment", av[i])));
	}
      i++;
    }
  printf(ANSI_COLOR_BLUE "\n---------------------DONE--------------------\n");
  printf("Total files: %d\n", FILE_COUNT);
  printf("Total errors: %d\n"ANSI_COLOR_RESET, ERR_COUNT);
}
