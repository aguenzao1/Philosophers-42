NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

SRCS =  srcs/main.c \
		srcs/init.c \
		srcs/philosophers.c \
		srcs/utils.c \
		srcs/utils_2.c

OBJS = $(SRCS:.c=.o)

HEADERS = includes/philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	clean