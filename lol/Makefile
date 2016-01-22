##
## Makefile for Makefile in /home/chuck/rendu/Libraries
##
## Made by Charles Durst
## Login   <charles.durst@epitech.net>
##
## Started on  Wed Nov  4 16:31:15 2015 Charles Durst
## Last update Fri Jan 22 19:11:30 2016 Charles Durst
##

NAME	= no_comment

RM	= rm -f

CC	= gcc

LDFLAGS	= -Wall -I .

SRCS	=	main.c \
		parsing.c \
		delete.c \
		utils.c

OBJS	= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all: fclean $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
