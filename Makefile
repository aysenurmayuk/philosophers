NAME = philo
SRCS = philo.c sim_handler.c sim_init.c sim_destroy.c sim_utils.c
OBJS = $(SRCS:.c=.o)  
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME) 

$(NAME): $(OBJS)  
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:  
	rm -rf $(OBJS)

fclean: clean  
	rm -rf $(NAME)

re: fclean all  

.PHONY: all clean fclean re  
