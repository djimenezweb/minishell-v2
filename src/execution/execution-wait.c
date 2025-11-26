/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:13:32 by danielji          #+#    #+#             */
/*   Updated: 2025/11/26 13:05:10 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Wait for each child process and return the exit status of the last child */
int	wait_children(t_cmd *cmd)
{
	int	wstatus;
	int	signal;
	int	last_status;

	signal = 0;
	if (g_heredoc_signal == 2)
		return (0);
	while (cmd)
	{
		if (cmd->is_forkable)
		{
			if (waitpid(cmd->pid, &wstatus, 0) < 0)
				perror("waitpid");
			cmd->status = get_status(wstatus, &signal);
		}
		last_status = cmd->status;
		cmd = cmd->next;
	}
	if (signal == SIGINT)
		prompt_newline();
	return (last_status);
}

/* Return exit status of awaited child process */
int	get_status(int wstatus, int *signal)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
	{
		*signal = WTERMSIG(wstatus);
		return (128 + *signal);
	}
	return (1);
}
