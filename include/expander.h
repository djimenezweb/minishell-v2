/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:23:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/13 19:52:41 by enrgil-p         ###   ########.fr       */
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
	int		third_start;
	int		expanded_len;
	char	*expanded;
}	t_expansion_data;

int	find_expansion_and_get_data(const char *str,
		t_expansion_data *exp_data);
char	*resize_expansions(char *old_str, t_expansion_data *ed);

#endif
