NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
SRC_PATH	= src/
SRC			=	main.c debug_helpers.c\
				environment/environment-list-utils.c environment/environment.c\
				expander/expander.c expander/find_expansion_and_get_data.c expander/resize_expansions.c expander/update_quote_flag.c expander/variable_name.c\
				lexer/lexer.c lexer/lexer-list-utils.c lexer/lexer-word-utils.c\
				syntax/quote_validation.c syntax/syntax_validation.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
OBJS		= $(SRCS:.c=.o)
INCLUDE		= -I./include -I./libft

# Libft
LIBFT_PATH	= libft
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)/$(LIBFT_NAME)
LIBFT_COMP	= $(LIBFT) -I./$(LIBFT_PATH)/

all : $(LIBFT) $(NAME)
	@echo "===          Done           ==="

$(LIBFT) :
	@echo "===      Making Libft       ==="
	@$(MAKE) -sC $(LIBFT_PATH)

$(NAME) : $(OBJS)
	@echo "===        Compiling        ==="
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_COMP) -o $(NAME) -lreadline

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean :
	@echo "===    Removing .o files    ==="
	@rm -f $(OBJS)
	@echo "=== Removing Libft .o files ==="
	@$(MAKE) clean -sC $(LIBFT_PATH)

fclean : clean
	@echo "===   Removing executable   ==="
	@rm -f $(NAME)
	@echo "===     Removing Libft      ==="
	@rm -f $(LIBFT)

re : fclean all
	@echo "===       Rebuilding        ==="

run : all
	@$(MAKE) clean
	./$(NAME)

debug : CFLAGS += -g -fsanitize=address
debug : fclean $(LIBFT) $(NAME)

.PHONY : all clean fclean re run debug
