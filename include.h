/*
** include.h
**
** Read the files
**
** Made by Chuck Durst <charles.durst@epitech.eu>
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

//Define some colors for the printf function
#ifndef COLORS_GLOBALS
#define COLORS_GLOBALS
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif /*COLORS_GLOBALS*/


//functions

int	write_file(FILE*, char*, int);
int	*parsing_file(char*, char*, int*, int, char*);
void	display_usage();
char	*make_directory(char*, char*);
int	check_directory(char*, int);
int	is_directory(char *);
int	nmatch(char*, char*);
