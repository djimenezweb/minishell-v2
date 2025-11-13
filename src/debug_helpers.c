/* THESE FUNCTIONS ARE FOR DEBUG PURPOSES ONLY */
/*  NOT TO BE SUBMITTED TO THE FINAL PROJECT   */

#include "minishell.h"

# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define BBLACK "\033[1;30m"
# define BRED "\033[1;31m"
# define BGREEN "\033[1;32m"
# define BYELLOW "\033[1;33m"
# define BBLUE "\033[1;34m"
# define BMAGENTA "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BWHITE "\033[1;37m"

# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"


void	print_lex_list(t_lextoken *list)
{
	t_lextoken	*curr;

	curr = list;
	while (curr)
	{
		if (curr->type == TOK_WORD)
		{
			if (curr->word_type >= 0)
			{
				if (curr->word_type == TOK_COMMAND)
					printf(BGREEN"%s "RESET, curr->value);
				if (curr->word_type == TOK_ARGUMENT)
					printf(CYAN"%s "RESET, curr->value);
				if (curr->word_type == TOK_INFILE)
					printf(BG_CYAN"%s"RESET" ", curr->value);
				if (curr->word_type == TOK_OUTFILE_APPEND || curr->word_type == TOK_OUTFILE_CREATE)
					printf(BG_MAGENTA"%s"RESET" ", curr->value);
				if (curr->word_type == TOK_DELIMITER)
					printf(BG_YELLOW"%s"RESET" ", curr->value);
			}
		}
		else if (curr->type == TOK_PIPE)
			printf(BYELLOW"| "RESET);
		else if (curr->type == TOK_REDIR_IN)
			printf(BG_CYAN"<"RESET);
		else if (curr->type == TOK_REDIR_OUT)
			printf(BG_MAGENTA">"RESET);
		else if (curr->type == TOK_APPEND)
			printf(BG_MAGENTA">>"RESET);
		else if (curr->type == TOK_HEREDOC)
			printf(BG_YELLOW"<<"RESET);
		else if (curr->type == TOK_EOF)
			printf(BG_WHITE"EOF"RESET);
		curr = curr->next;
	}
	printf("\n");
}

/* void	print_lex_list(t_lextoken *list)
{
	t_lextoken	*curr;

	curr = list;
	while (curr)
	{
		if (curr->type == TOK_WORD)
		{
			ft_printf("WORD(%s)", curr->value);
			if (curr->word_type >= 0)
			{
				if (curr->word_type == TOK_COMMAND)
					ft_printf(" COMMAND");
				if (curr->word_type == TOK_ARGUMENT)
					ft_printf(" ARGUMENT");
				if (curr->word_type == TOK_INFILE)
					ft_printf(" INFILE");
				if (curr->word_type == TOK_OUTFILE)
					ft_printf(" OUTFILE");
				if (curr->word_type == TOK_DELIMITER)
					ft_printf(" DELIMITER");
			}
			ft_printf("\n");
		}
		else if (curr->type == TOK_PIPE)
			ft_printf("PIPE\n");
		else if (curr->type == TOK_REDIR_IN)
			ft_printf("REDIR_IN\n");
		else if (curr->type == TOK_REDIR_OUT)
			ft_printf("REDIR_OUT\n");
		else if (curr->type == TOK_APPEND)
			ft_printf("APPEND\n");
		else if (curr->type == TOK_HEREDOC)
			ft_printf("HEREDOC\n");
		else if (curr->type == TOK_EOF)
			ft_printf("EOF\n");
		curr = curr->next;
	}
} */

void	print_array_of_strings(char **arr)
{
	int i = 0;
	while (1)
	{
		if (arr[i] == NULL)
		{
			printf("%d) >NULL<\n", i);
			break ;
		}
		printf("%d) >%s<\n", i, arr[i]);
		i++;
	}
}

/* For debug purposes only */
void	print_cmd_list(t_cmd *list)
{
	printf("-- START COMMAND LIST --\n");
	while (list)
	{
		printf("Command: %s\n", list->cmd[0]);
		printf("Path:    %s\n", list->path);
		printf("Input:   %i\n", list->input);
		printf("Output:  %i\n", list->output);
		list = list->next;
	}
	printf("-- END COMMAND LIST --\n");
}

/* For debug purposes only */
void	print_env_list(t_env_var *list)
{
	printf("-- START ENV VAR LIST --\n");
	while (list)
	{
		printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
	printf("-- END ENV VAR LIST --\n");
}
