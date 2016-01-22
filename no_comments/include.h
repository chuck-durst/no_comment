

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


#ifndef COLORS_GLOBALS
#define COLORS_GLOBALS
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif 




int	write_file(FILE*, char*, int);
int	*parsing_file(char*, char*, int*);
void	display_usage();
char	*make_directory(char*, char*);
int	check_directory(char*, int);
