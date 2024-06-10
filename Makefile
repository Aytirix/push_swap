NAME = push_swap
SRC = push_swap.c \
		instruction/instruction1.c \
		instruction/instruction2.c \
		instruction/instruction3.c \
		controller.c \
		checker.c \
		algo/algo1.c \
		algo/algoTurk.c \
		tools.c
OBJ = $(SRC:.c=.o)
LIBFT = Libft
LIBFT_A = $(LIBFT)/libft.a
FLAGS = -fsanitize=address -fdiagnostics-color=always -g3 #-Wall -Wextra -Werror 
LIBS = -L$(LIBFT) -lft

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(FLAGS) -I$(LIBFT) $(OBJ) -o $@ $(LIBS)

%.o: %.c $(LIBFT_A)
	$(CC) $(FLAGS) -I$(LIBFT) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
