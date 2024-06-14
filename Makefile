NAME = push_swap
SRC = push_swap.c \
		instruction/instruction1.c \
		instruction/instruction2.c \
		instruction/instruction3.c \
		controller.c \
		checker.c \
		algo/algo1.c \
		algo/algoTurk.c \
		algo/algoTurk_Utils.c \
		tools.c
OBJ = $(SRC:.c=.o)
LIBFT = Libft
LIBFT_A = $(LIBFT)/libft.a
FLAGS = -fsanitize=address -fdiagnostics-color=always -g3 -Wall -Wextra -Werror 
LIBS = -L$(LIBFT) -lft

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT)

$(NAME): $(LIBFT_A) $(OBJ)
	@echo "$(GREEN)Building $(NAME)...$(RESET)"
	@$(CC) $(FLAGS) -I$(LIBFT) $(OBJ) -o $@ $(LIBS)
	@echo "$(BLUE)$(NAME) built successfully!$(RESET)"

%.o: %.c $(LIBFT_A)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(FLAGS) -I$(LIBFT) -c $< -o $@

clean:
	@echo "$(MAGENTA)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@echo "$(RED)Cleaning all files...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
