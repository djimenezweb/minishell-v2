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

int	quote_validation(char *str);
int	is_tok_last(t_lextoken *node);
int	is_tok_first(t_lextoken *node);
int	is_tok_consecutive(t_lextoken *node);
int	syntax_validation(t_lextoken *node);

#endif
