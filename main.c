/*
** main.c
**
** This program will automaticaly create a copy of the files past as parameter
** and will delete every comments in them
**
** Made by Chuck Durst <charles.durst@epitech.eu>
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "include.h"

llist		get_params(char **args, int cnt)
{
  int		i = 1;
  int		j = 0;
  int		dir_c = 0;
  llist		l_args;

  if ((l_args = malloc(sizeof(llist))) == NULL)
    exit(EXIT_FAILURE);
  while (i < cnt)
    {
      if (args[i][0] == '-')
	{
	  j = 1;
	  while (args[i][j] != '\0')
	    {
	      switch (args[i][j])
		{
		case 'h':
		  display_usage();
		  break;
		case 'd':
		  if (l_args->pr_D == 1)
		    print_error("Error: Cannot use params 's' and 'S' together\n");
		  l_args->pr_d = 1;
		  break;
		case 'D':
		  if (l_args->pr_d == 1)
		    print_error("Error: Cannot use params 's' and 'S' together\n");
		  l_args->pr_D = 1;
		  break;
		case 's':
		  l_args->pr_s = 1;
		  break;
		case 'n':
		  if (l_args->pr_N == 1)
		    print_error("Error: Cannot use params 'n' and 'N' together\n");
		  l_args->pr_n = 1;
		  break;
		case 'N':
		  if (l_args->pr_n == 1)
		    print_error("Error: Cannot use params 'n' and 'N' together\n");
		  l_args->pr_N = 1;
		  break;
		default:
		  printf("Error: '%c' is not a valid argument\n", args[i][j]);
		  exit(EXIT_FAILURE);
		  break;
		}
	      j++;
	    }
	}
      else
	{
	  if (l_args->pr_D == 1 || l_args->pr_d == 1)
	    {
	      if (dir_c == 0)
		{
		  if ((l_args->directory = malloc(sizeof(args[i]))) == NULL)
		    exit(EXIT_FAILURE);
		  if (l_args->pr_d == 1 && check_directory(args[i], 0) != 1)
		    print_error("Error: Directory not found\n");
		  else if (l_args->pr_D == 1 && check_directory(args[i], 1) != 1)
		    l_args->directory = args[i];
		  else
		    l_args->directory = args[i];
		  dir_c = 1;
		}
	    }
	}
      i++;
    }
  if (l_args->pr_D != 1 && l_args->pr_d != 1)
    {
      if ((l_args->directory = malloc(11)) == NULL)
	exit(EXIT_FAILURE);
      l_args->directory = "no_comments";
      check_directory("no_comments", 1);
    }
  if (l_args->pr_d == 1 && dir_c == 0)
    display_usage();
  return (l_args);
}

int		main(int ac, char **av)
{
  int		i = 0;
  int		j = 0;
  int		*counter;
  int		count_file = 0;
  int		sub_dir = 0;
  llist		l_args = NULL;

  if ((counter = malloc(4)) == NULL)
    exit(0);
  while (i < 4)
    counter[i++] = 0;
  i = 1;
  if (ac < 2)
    display_usage();
  l_args = get_params(av, ac);
  printf("pr_h: %d\n", l_args->pr_h);
  printf("pr_d: %d\n", l_args->pr_d);
  printf("pr_D: %d\n", l_args->pr_D);
  printf("pr_s: %d\n", l_args->pr_s);
  printf("pr_n: %d\n", l_args->pr_n);
  printf("pr_N: %d\n", l_args->pr_N);
  printf("pr_directory: %s\n", l_args->directory);
  while (i < ac)
    {
      if (av[i][0] != '-' && nmatch(l_args->directory, av[i]) != 1)
	{
	  counter = parsing_file(av[i], counter, l_args);
	}
      i++;
    }
  printf(ANSI_COLOR_BLUE"---------------------DONE--------------------\n"
	 ANSI_COLOR_RESET);
  printf(" %d files ", counter[3]);
  printf(ANSI_COLOR_GREEN" %d success "ANSI_COLOR_RESET, counter[0]);
  printf(ANSI_COLOR_RED" %d errors "ANSI_COLOR_RESET, counter[1]);
  printf(ANSI_COLOR_BLUE" %d comments deleted\n"ANSI_COLOR_RESET, counter[2]);
}
