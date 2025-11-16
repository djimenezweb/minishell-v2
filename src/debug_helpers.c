/* THESE FUNCTIONS ARE FOR DEBUG PURPOSES ONLY */
/*  NOT TO BE SUBMITTED TO THE FINAL PROJECT   */

#include "minishell.h"

# define RESET "\001\033[0m\002"
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define WHITE "\001\033[0;37m\002"

# define BBLACK "\001\033[1;30m\002"
# define BRED "\001\033[1;31m\002"
# define BGREEN "\001\033[1;32m\002"
# define BYELLOW "\001\033[1;33m\002"
# define BBLUE "\001\033[1;34m\002"
# define BMAGENTA "\001\033[1;35m\002"
# define BCYAN "\001\033[1;36m\002"
# define BWHITE "\001\033[1;37m\002"

# define BG_RED "\001\033[41m\002"
# define BG_GREEN "\001\033[42m\002"
# define BG_YELLOW "\001\033[43m\002"
# define BG_BLUE "\001\033[44m\002"
# define BG_MAGENTA "\001\033[45m\002"
# define BG_CYAN "\001\033[46m\002"
# define BG_WHITE "\001\033[47m\002"


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
