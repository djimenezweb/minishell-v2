/* THESE FUNCTIONS ARE FOR DEBUG PURPOSES ONLY */
/*  NOT TO BE SUBMITTED TO THE FINAL PROJECT   */

#include "minishell.h"

void	print_lex_list(t_lextoken *list)
{
	t_lextoken	*curr;

	curr = list;
	while (curr)
	{
		if (curr->type == TOK_WORD)
			ft_printf("WORD(%s)\n", curr->value);
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
}

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
