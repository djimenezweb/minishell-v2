/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:23:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/10/22 20:05:48 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"


typedef struct s_shell t_shell;//ENRIQUE 22/10: We shoudl create a structs.h
typedef struct s_expansion_data
{
	//WATCH PUT, COMMENTS ABOVE
	int		dollar_position;
	int		resize_len;
	int		var_name_len;
	int		expanded_len;
	int		chars_after_var_name;
	int		malloc_fail;
	char	*var_name;
	char	*expanded;
}	t_expansion_data;

void	expander(t_shell *data);
int		find_expansion(char *str, t_expansion_data *exp_data);
char	*get_variable_name(char *str);
char	*resize_expansions(char *old_str, t_expansion_data *ed);
int		update_quote_flag(int quote_flag, int char_found);

#endif
