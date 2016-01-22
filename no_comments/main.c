

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "include.h"

int		main(int ac, char **av)
{
  int		i = 1;
  int		j = 0;
  int		*counter;
  int		count_file = 0;
  char		*directory = NULL;

  if ((counter = malloc(3)) == NULL)
    exit(0);
  counter[0] = 0;
  counter[1] = 0;
  counter[2] = 0;
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
	    }
	  else if (av[i][1] == 'D')
	    {
	      i++;
	      if (check_directory(av[i], 1) == 1)
		directory = av[i];
	    }
	  else if (av[i][1] == 'h')
	    display_usage();
	}
      else
	{
	  if(directory == NULL)
	    {
	      check_directory("no_comments", 1);
	      directory = "no_comments";
	    }
	  counter =  parsing_file(av[i],
			make_directory(directory, av[i]), counter);
	  count_file++;
	}
      i++;
    }
  printf(ANSI_COLOR_BLUE"---------------------DONE--------------------\n"
	 ANSI_COLOR_RESET);
  printf(" %d files ", count_file);
  printf(ANSI_COLOR_GREEN" %d success "ANSI_COLOR_RESET, counter[0]);
  printf(ANSI_COLOR_RED" %d errors "ANSI_COLOR_RESET, counter[1]);
  printf(ANSI_COLOR_BLUE" %d comments deleted\n"ANSI_COLOR_RESET, counter[2]);
}
