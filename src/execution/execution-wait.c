/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution-wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:13:32 by danielji          #+#    #+#             */
/*   Updated: 2025/12/01 11:24:45 by danielji         ###   ########.fr       */
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
	if (g_heredoc_signal == SIGINT)
		return (0);
	while (cmd)
	{
		if (cmd->is_forkable || !is_single_cmd(cmd))
		{
			if (waitpid(cmd->pid, &wstatus, 0) < 0)
				perror("minishell: waitpid");
			cmd->status = get_status(wstatus, &signal);
		}
		last_status = cmd->status;
		cmd = cmd->next;
	}
	if (signal == SIGINT || signal == SIGQUIT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
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
