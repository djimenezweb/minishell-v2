NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -lreadline
SRC_PATH	= src/
SRC			= main.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
OBJS		= $(SRCS:.c=.o)
INCLUDE		= -I./include -I./libft

# Libft
LIBFT_PATH	= libft
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)/$(LIBFT_NAME)
LIBFT_COMP	= $(LIBFT) -I./$(LIBFT_PATH)/

all : $(LIBFT) $(NAME)

$(LIBFT) :
	@echo "=== Making Libft ==="
	@$(MAKE) -sC $(LIBFT_PATH)

$(NAME) : $(OBJS)
	@echo "=== Compiling ==="
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_COMP) -o $(NAME)

%.o : %.c
	@echo "=== Creating object files ==="
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean :
	@echo "=== Removing .o files ==="
	@rm -f $(OBJS)
	@echo "=== Removing Libft .o files ==="
	@$(MAKE) clean -sC $(LIBFT_PATH)

fclean : clean
	@echo "=== Removing minishell executable ==="
	@rm -f $(NAME)
	@echo "=== Removing Libft ==="
	@rm -f $(LIBFT)

re : fclean all
	@echo "=== Rebuilding ==="

run : all
	@$(MAKE) clean
	./$(NAME) M

.PHONY : all clean fclean re run