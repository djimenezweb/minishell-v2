/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:47:23 by danielji          #+#    #+#             */
/*   Updated: 2025/11/22 10:58:22 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RESET		"\001\033[0m\002"
#define BLACK		"\001\033[0;30m\002"
#define BGREEN		"\001\033[1;32m\002"
#define CYAN		"\001\033[0;36m\002"
#define BG_CYAN		"\001\033[46m\002"
#define BG_MAGENTA	"\001\033[45m\002"
#define BG_YELLOW	"\001\033[43m\002"
#define BYELLOW		"\001\033[1;33m\002"
#define BG_WHITE	"\001\033[47m\002"

/* #define RED "\001\033[0;31m\002"
#define GREEN "\001\033[0;32m\002"
#define YELLOW "\001\033[0;33m\002"
#define BLUE "\001\033[0;34m\002"
#define MAGENTA "\001\033[0;35m\002"
#define WHITE "\001\033[0;37m\002"

#define BBLACK "\001\033[1;30m\002"
#define BRED "\001\033[1;31m\002"
#define BBLUE "\001\033[1;34m\002"
#define BMAGENTA "\001\033[1;35m\002"
#define BCYAN "\001\033[1;36m\002"
#define BWHITE "\001\033[1;37m\002"

#define BG_RED "\001\033[41m\002"
#define BG_GREEN "\001\033[42m\002"
#define BG_BLUE "\001\033[44m\002" */

void	print_tok_word(t_lex_type wtype, char *value)
{
	if (wtype >= 0)
	{
		if (wtype == TOK_COMMAND)
			printf(BGREEN"%s "RESET, value);
		if (wtype == TOK_ARGUMENT)
			printf(CYAN"%s "RESET, value);
		if (wtype == TOK_INFILE)
			printf(BG_CYAN"%s"RESET" ", value);
		if (wtype == TOK_OUTFILE_APPEND || wtype == TOK_OUTFILE_CREATE)
			printf(BG_MAGENTA"%s"RESET" ", value);
		if (wtype == TOK_DELIMITER)
			printf(BG_YELLOW"%s"RESET" ", value);
	}
}

void	print_lex_list(t_lextoken *list)
{
	t_lextoken	*curr;

	curr = list;
	while (curr)
	{
		if (curr->type == TOK_WORD)
			print_tok_word(curr->word_type, curr->value);
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

/* For debug purposes only */
void	print_array_of_strings(char **arr)
{
	int	i;

	i = 0;
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
		printf("Command:    %s, %s\n", list->cmd[0], list->cmd[1]);
		printf("Path:       %s\n", list->path);
		printf("Forkable?:  %i\n", list->is_forkable);
		printf("Input:      %i\n", list->input);
		printf("Output:     %i\n", list->output);
		printf("Heredoc?:   %i\n", list->is_heredoc);
		if (list->delimiters)
		{
			printf("Delimiters: %s\n", list->delimiters[0]);
			printf("            %s\n", list->delimiters[1]);
		}
		printf("pid:        %i\n", list->pid);
		printf("next:       %p\n", list->next);
		printf("prev:       %p\n", list->prev);
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
