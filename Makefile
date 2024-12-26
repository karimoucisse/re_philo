NAME = philo
CC = cc
UTILS = utils/
UTILS_CFILES = $(UTILS)ft_atoi.c $(UTILS)ft_strchr.c $(UTILS)ft_strlen.c\
		$(UTILS)utils.c
CFILES = philo.c errors.c checker.c init.c $(UTILS_CFILES) routine.c
CFLAGS = -Wall -Werror -Wextra -pthread -g
OFILES = $(CFILES:.c=.o)
RM = rm -f

all: $(NAME)
$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OFILES)
fclean : clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
