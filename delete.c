/*
** delete.c
**
** Delete the comments in the files
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

int             write_file(FILE *fp, char *line, int comment_count)
{
  int           i = 0;
  static int    control;

  if (control == 1)
    {
      while (line[i] != '*' || line[i + 1] != '/')
	{
	  if (line[i] == '\0')
	    return (comment_count);
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
	    return (comment_count);
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
	      comment_count++;
	      fputc('\n', fp);
	      return (comment_count);
	    }
	  else if (line[i + 1] == '*')
	    {
	      comment_count++;
	      i = i + 2;
	      while (line[i] != '*' || line[i + 1] != '/')
		{
		  if (line[i] == '\0')
		    {
		      control = 1;
		      return (comment_count);
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
	      comment_count++;
	      i = i + 4;
	      while (line[i] != '-' || line[i + 1] != '-' || line[i + 2] != '>')
		{
		  if (line[i] == '\0')
		    {
		      control = 2;
		      return (comment_count);
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
  return (comment_count);
}
