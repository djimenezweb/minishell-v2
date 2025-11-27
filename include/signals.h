/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:08:09 by danielji          #+#    #+#             */
/*   Updated: 2025/11/27 18:47:44 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	parent_signals(void);
void	parent_ignore_sigint(void);
void	child_signals(void);
void	heredoc_signals(void);
void	handle_parent_sigint(int sig);
void	handle_hdoc_sigint(int sig);

#endif
