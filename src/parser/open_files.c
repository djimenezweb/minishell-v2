/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:20:47 by danielji          #+#    #+#             */
/*   Updated: 2025/12/03 09:40:33 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_hdoc(t_lextoken *lst, t_cmd *last_node)
{
	last_node->is_heredoc = 1;
	last_node->delimiters = append(last_node->delimiters, lst->value);
}

/* Open file and assign fd to nodes of type `TOK_INFILE`,`TOK_OUTFILE_CREATE`
or `TOK_OUTFILE_APPEND` */
void	assign_fd(t_lextoken *lst, t_cmd *node)
{
	int	file;

	if (is_infile(lst))
	{
		file = open_infile(lst->value);
		if (node->input < 0 || node->output < 0)
			return ;
		else if (node->input != STDIN_FILENO)
			safe_close(node->input);
		node->input = file;
	}
	if (is_outfile(lst))
	{
		if (node->output < 0 || node->input < 0)
			return ;
		else if (node->output != STDOUT_FILENO)
			safe_close(node->output);
		file = open_outfile(lst->value, lst->word_type);
		node->output = file;
	}
}

/* Open file in read-only and return its `fd`.
On error print a warning and return the `fd`.*/
int	open_infile(char *path)
{
	int	fd;
	int	err;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		err = errno;
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", path, strerror(err));
	}
	return (fd);
}

/* Open file for writing and return its `fd`.
On error print a warning and return the `fd`.*/
int	open_outfile(char *path, enum e_lex_type type)
{
	int	fd;
	int	err;
	int	flag;

	flag = O_WRONLY | O_CREAT | O_TRUNC;
	if (type == TOK_OUTFILE_APPEND)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(path, flag, 0644);
	if (fd < 0)
	{
		err = errno;
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", path, strerror(err));
	}
	return (fd);
}
