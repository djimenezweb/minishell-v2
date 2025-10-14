/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:23:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/14 20:06:44 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_expansion_data
{
	int		dollar_position;
	int		resize_len;
	int		var_name_len;
	int		expanded_len;
	char	*expanded;
}	t_expansion_data;

void	check_token_words(t_lextoken **token_list);
int	find_expansion_and_get_data(const char *str,
		t_expansion_data *exp_data);
char		*get_variable_name(char *str);
char	*resize_expansions(char *old_str, t_expansion_data *ed);

#endif
