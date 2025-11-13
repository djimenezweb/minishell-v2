/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:38:39 by danielji          #+#    #+#             */
/*   Updated: 2025/10/21 11:29:31 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "lexer.h"

int		quote_validation(char *str);
int		is_valid_heredoc(t_lextoken *node);
int		is_valid_redin(t_lextoken *node);
int		is_valid_append(t_lextoken *node);
int		is_valid_redout(t_lextoken *node);
int		is_valid_pipe(t_lextoken *node);
void	print_syntax_error(char *str);
int		syntax_validation(t_lextoken *node);

#endif
