/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:02 by danielji          #+#    #+#             */
/*   Updated: 2025/10/13 11:23:02 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

# define DEFAULT_PATH \
"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

t_env_var	*ft_find_env_var(t_env_var *list, char *name);
void		set_name_value(t_env_var *node, char *str);
void		set_default_env_vars(t_env_var **list);
t_env_var	*set_env_vars(char *envp[]);
t_env_var	*ft_new_node(char *str);
void		ft_env_addback(t_env_var **lst, t_env_var *new);

#endif