NAME = philo

SOURCE = free.c main.c philo_utils.c philo_utils_2.c
OBJS = ${SOURCE:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

%.o: %.c
	@echo "\033[34m"
	$(CC) -c $(CFLAGS) $?

all : $(NAME)

$(NAME): $(OBJS)
	@echo "\033[34m"
	@$(CC) $(CFLAGS) ${OBJS} -o ${NAME}
	@echo "\033[33m ____  _   _  ____  __    _____"
	@echo "(  _ \( )_( )(_  _)(  )  (  _  )"
	@echo " )___/ ) _ (  _)(_  )(__  )(_)("
	@echo "(__)  (_) (_)(____)(____)(_____)\033[0m"

clean:
	@echo "\033[31m"
	rm -rf $(OBJS)

fclean: clean
	@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"
	rm -rf $(NAME)

re: fclean all
