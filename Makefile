NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
SRC_PATH	= src
OBJ_PATH	= build
SRC			=	main.c cleanup.c\
				builtins/cd.c builtins/echo.c builtins/env.c\
				builtins/exit.c builtins/export.c\
				builtins/pwd.c builtins/unset.c\
				environment/environment-list-utils.c\
				environment/environment.c\
				environment/environment-envp.c\
				environment/environment-list-free.c\
				environment/environment-last-exit-st.c\
				execution/execution.c\
				execution/execution-utils.c\
				execution/execution-utils2.c\
				execution/execution-wait.c\
				execution/paths.c execution/execution-child.c\
				execution/heredoc.c\
				execution/call_to_builtins.c\
				expander/expander.c expander/escape_chars.c\
				expander/find_expansion_and_get_data.c\
				expander/resize_expansions.c\
				expander/update_quote_flag.c\
				expander/variable_name.c\
				lexer/lexer.c lexer/lexer-list-utils.c\
				lexer/lexer-word-utils.c\
				lexer/lexer-word-types.c lexer/remove_quotes.c\
				parser/parser.c parser/parser-list-utils.c\
				parser/set_words_per_cmd.c parser/add_to_cmd.c\
				parser/parser_utils.c parser/open_files.c \
				parser/parser-list-free-utils.c\
				syntax/pipes_and_quotes_validation.c\
				syntax/is_valid_token.c\
				syntax/is_valid_token_utils.c\
				syntax/syntax_validation.c\
				signals/signals.c signals/signals-handlers.c
SRCS		= $(addprefix $(SRC_PATH)/, $(SRC))
OBJS		= $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))
INCLUDE		= -I./include -I./libft
LDFLAGS		= libft/libft.a -lreadline -lhistory

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -sC libft libft.a
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	@rm -rf $(OBJ_PATH)
	@$(MAKE) -sC libft clean

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -sC libft fclean

re : fclean all

run : all
	./$(NAME)

valgrind : all
	valgrind --suppressions=readline.supp\
			 --leak-check=full\
			 --show-leak-kinds=all\
			 --track-fds=yes\
			 ./$(NAME)

.PHONY : all clean fclean re run valgrind
