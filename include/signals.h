/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:08:09 by danielji          #+#    #+#             */
/*   Updated: 2025/11/25 11:55:45 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	init_signals(void);
void	handle_sigint(int sig);
void	restore_signals(void);
void	ignore_sigint(void);
void	prompt_newline(void);

#endif
