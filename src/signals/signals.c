/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:07:15 by danielji          #+#    #+#             */
/*   Updated: 2025/11/25 13:54:01 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* - Call `handle_sigint` if `SIGINT` (Ctrl+C)
- Ignore `SIGQUIT` (Ctrl+\) */
void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/* If `SIGINT` write new line and redisplay */
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		prompt_newline();
		rl_redisplay();
	}
}

/* Ignore `SIGINT` (Ctrl+C) */
void	ignore_sigint(void)
{
	signal(SIGINT, SIG_IGN);
}

/* Restore `SIGINT` and `SIGQUIT` to defaults */
void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/* - Write new line character to `STDOUT`
- Tell the update functions that we have moved onto a new (empty) line
- Replace the contents of `rl_line_buffer` with an empty string */
void	prompt_newline(void)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

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
