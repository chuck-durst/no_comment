/*
1;2802;0c** include.h
**
** Read the files
**
** Made by Chuck Durst <charles.durst@epitech.eu>
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

//Structure used to store the program parameters
#ifndef _PARAMS_STRUCT
#define _PARAMS_STRUCT
typedef struct  p_list
{
  int	pr_h;
  int	pr_d;
  int	pr_D;
  int	pr_s;
  int	pr_n;
  int	pr_N;
  char	*directory;
  int	file_cnt;
} t_list;
typedef t_list *llist;
#endif

//Define some colors for the printf function
#ifndef COLORS_GLOBALS
#define COLORS_GLOBALS
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif /*COLORS_GLOBALS*/


//functions

llist	get_params(char**, int);
int	write_file(FILE*, char*, int);
int	*parsing_file(char*, int*, llist);
void	display_usage();
char	*make_directory(char*, char*);
int	check_directory(char*, int);
void	print_error(char*);
int	is_directory(char *);
int	nmatch(char*, char*);
