/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals-handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:38:33 by danielji          #+#    #+#             */
/*   Updated: 2025/11/27 18:52:31 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If `SIGINT` write new line and redisplay.
- `rl_on_new_line`: Regenerate the prompt on a newline
- `rl_replace_line`: Clear the previous text 
- `rl_redisplay`: Reflect the current contents of `rl_line_buffer` */
void	handle_parent_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* If `SIGINT` during heredoc, set `g_heredoc_signal`
to `2` and write a new line */
void	handle_hdoc_sigint(int sig)
{
	char	c;

	(void)sig;
	g_heredoc_signal = 2;
	c = '\n';
	ioctl(STDIN_FILENO, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
}
