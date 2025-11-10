/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:23:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/10 13:32:17 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

//ENRIQUE 22/10: We shoudl create a structs.h

typedef struct s_shell	t_shell;

typedef struct s_expansion_data
{
	//WATCH PUT, COMMENTS ABOVE
	int		dollar_position;
	int		resize_len;
	int		var_name_len;
	int		expanded_len;
	int		malloc_fail;
	int		env_quoted;
	char	*var_name;
	char	*expanded;
}	t_expansion_data;

typedef struct s_join
{
	char	*dst;
	char	*src;
	int		len;
}	t_join;

int		expander(char **str, t_env_var *list);
int		find_expansion(char *str, t_expansion_data *exp_data);
char	*get_variable_name(char *str);
char	*resize_expansions(char *old_str, t_expansion_data *ed);
void	update_quote_flag(t_expansion_data *expansion, int char_found);

#endif
