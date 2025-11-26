/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:07:15 by danielji          #+#    #+#             */
/*   Updated: 2025/11/26 17:08:18 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* - Call `handle_sigint` if `SIGINT` (Ctrl+C)
- Ignore `SIGQUIT` (Ctrl+\) */
void	parent_signals(void)
{
	signal(SIGINT, handle_parent_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/* Ignore `SIGINT` (Ctrl+C) */
void	parent_ignore_sigint(void)
{
	signal(SIGINT, SIG_IGN);
}

/* Restore `SIGINT` and `SIGQUIT` to defaults */
void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	heredoc_signals(void)
{
	signal(SIGINT, handle_hdoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
