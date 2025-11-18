/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:52:03 by danielji          #+#    #+#             */
/*   Updated: 2025/11/18 09:52:12 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_heredoc(int *is_quoted, char *delim, int here_pipe[2])
{
	*is_quoted = 0;
	if (ft_strchr(delim, DOUBLE_QUOTE))
	{
		*is_quoted = 1;
		remove_quotes(delim);
	}
	if (here_pipe[READ_END] != -1)
		safe_close(here_pipe[READ_END]);
	if (here_pipe[WRITE_END] != -1)
		safe_close(here_pipe[WRITE_END]);
	if ((pipe(here_pipe) < 0))
		return (perror("heredoc pipe"), -1);
	return (0);
}

int	heredoc(t_cmd *cmd)
{
	int		i;
	int		here_pipe[2];
	int		is_quoted;
	char	*line;

	i = 0;
	here_pipe[READ_END] = -1;
	here_pipe[WRITE_END] = -1;
	while (cmd->delimiters[i])
	{
		if (init_heredoc(&is_quoted, cmd->delimiters[i], here_pipe) < 0)
			return (-1);
		line = NULL;
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			else if (ft_strncmp(cmd->delimiters[i], line, ft_strlen(line) + 1) == 0)
			{
				free(line);
				break ;
			}
			if (!is_quoted)
				expander(line, NULL);
			ft_putendl_fd(line, here_pipe[WRITE_END]);
			free(line);
		}
		i++;
	}
	safe_close(here_pipe[WRITE_END]);
	cmd->input = here_pipe[READ_END];
	return (0);
}
