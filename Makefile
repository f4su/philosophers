NAME	= philo
CC		= gcc
FLAGS	= -Wall -Wextra -Werror
GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m
RM		= rm -f

FUNC	= srcs/main srcs/utils srcs/threads srcs/philo \

SRC		= $(addsuffix .c, $(FUNC))
OBJ		= $(addsuffix .o, $(FUNC))

.c.o	: $(FILES) $(NAME)
	@$(CC) $(FLAGS) -c -o $@ $^

$(NAME)	: $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "$(GREEN)make done$(RESET)"

all		: $(NAME)

clean	: 
	@$(RM) $(OBJ)
	@echo "$(RED)clean done$(RESET)"

fclean	: clean
	@$(RM) $(NAME)
	@echo "$(RED)fclean done$(RESET)"

re		: fclean all

.PHONY	: all clean fclean re
