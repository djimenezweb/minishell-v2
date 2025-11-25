/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:07:15 by danielji          #+#    #+#             */
/*   Updated: 2025/11/25 12:00:21 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* In interactive mode:
- `Ctrl`+`C` (`SIGINT`) displays a new prompt on a new line.
- `Ctrl`+`\` (`SIGQUIT`) does nothing. */
void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_sigint(void)
{
	signal(SIGINT, SIG_IGN);
}

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
}

/* Handler function for `Ctrl`+`C` (`SIGINT`)
In interactive mode displays a new prompt on a new line.

`rl_on_new_line`:
	Tell the update functions that we have moved onto a new (empty) line.

`rl_replace_line(text, clear_undo)`:
	Replace the contents of `rl_line_buffer` with `text`. If `clear_undo` is
	non-zero, this clears the undo list associated with the current line. 

`rl_redisplay`:
	Change what’s displayed on the screen to reflect the current contents
	of `rl_line_buffer`.*/
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		prompt_newline();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
