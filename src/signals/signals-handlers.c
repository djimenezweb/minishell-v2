/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals-handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:38:33 by danielji          #+#    #+#             */
/*   Updated: 2025/11/26 17:16:08 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If `SIGINT` write new line and redisplay */
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

void	handle_hdoc_sigint(int sig)
{
	(void)sig;
	char c;

	g_heredoc_signal = 2;
	c = '\n';
	ioctl(STDIN_FILENO, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
}

/* - Write new line character to `STDOUT`
- Tell the update functions that we have moved onto a new (empty) line
- Replace the contents of `rl_line_buffer` with an empty string */
/* void	prompt_newline(void)
{
	write(STDOUT_FILENO, "\n", 1); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
} */

/*
`rl_on_new_line`:
	Tell the update functions that we have moved onto a new (empty) line.

`rl_replace_line(text, clear_undo)`:
	Replace the contents of `rl_line_buffer` with `text`. If `clear_undo` is
	non-zero, this clears the undo list associated with the current line. 

`rl_redisplay`:
	Change what’s displayed on the screen to reflect the current contents
	of `rl_line_buffer`.
*/