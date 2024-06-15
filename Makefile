NAME = push_swap
OBJDIR = objets
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
LIBFT = Libft
LIBFT_A = $(LIBFT)/libft.a
FLAGS = -fsanitize=address -fdiagnostics-color=always -g3 -Wall -Wextra -Werror
LIBS = -L$(LIBFT) -lft

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
	@$(MAKE) -C $(LIBFT) --no-print-directory

$(NAME): $(LIBFT_A) $(OBJ)
	@echo "$(GREEN)Building $(NAME)...$(RESET)"
	@$(CC) $(FLAGS) -I$(LIBFT) $(OBJ) -o $@ $(LIBS)
	@echo "$(BLUE)$(NAME) built successfully!$(RESET)"

$(OBJDIR)/%.o: %.c $(LIBFT_A)
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(FLAGS) -I$(LIBFT) -c $< -o $@

clean:
	@echo "$(MAGENTA)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT) clean --no-print-directory

fclean: clean
	@echo "$(RED)Cleaning all files...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re