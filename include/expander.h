/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:23:08 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/12 20:04:19 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef enum e_protect_chars_status
{
	PROTECT,
	RESTORE
}	t_protect_chars_status;

typedef struct s_expansion_data
{
	char	*iterator;
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
void	protect_heredoc_delimiter(char **str, t_protect_chars_status status,
			t_expansion_data quote_status);
void	quote_chars_in_expanded_vars(char **str, t_protect_chars_status status);
void	swap_char_value(char **str, int searched, int new_value);

#endif
