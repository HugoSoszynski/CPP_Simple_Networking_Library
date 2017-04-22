##
## Makefile for ncurses in /home/soszyn_h/Documents/Projects/MyNcursesPP
## 
## Made by Hugo SOSZYNSKI
## Login   <hugo.soszynski@epitech.eu>
## 
## Started on  Wed Apr  5 09:57:14 2017 Hugo SOSZYNSKI
## Last update Sat Apr 22 11:34:50 2017 Hugo SOSZYNSKI
##

INCLUDE		=	-I./includes

RM		=	rm -rf

CPPFLAGS	+=	$(INCLUDE)

CPPFLAGS	+=	-MD -MP

CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		+=	-shared

CC		=	g++

DEBUG		?=	0

ifeq	($(DEBUG), 1)
	CC		=	g++
	CPPFLAGS	+=	-g -ggdb3
endif

NAME		=	libmysocket.so

SRCS		=	$(shell cat ./sources.mk)

OBJS		=	$(SRCS:.cpp=.o)

DEPS		=	$(SRCS:.cpp=.d)


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

%.o:		%.cpp
		$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
		$(RM) $(OBJS) $(DEPS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean
		@$(MAKE) all

.PHONY:	 all clean fclean re

-include	$(DEPS)
