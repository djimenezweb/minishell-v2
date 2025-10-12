/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:23:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/12 20:33:00 by enrgil-p         ###   ########.fr       */
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
	char	*expanded;
}	t_expansion_data;

int	find_expansion_and_get_data(const char *str,
		t_expansion_data *exp_data);

#endif
