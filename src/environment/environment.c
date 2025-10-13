/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:02 by danielji          #+#    #+#             */
/*   Updated: 2025/10/13 11:23:02 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

//#include "minishell.h"
//#include "../../include/minishell.h"
#include <stdio.h>
#include "libft.h"

#define DEFAULT_PATH "COCO=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

t_env_var	*ft_find_env_var(t_env_var *list, char *name)
{
	t_env_var *current;

	current = list;
	while (current)
	{
		if (ft_strnstr(current->name, name, ft_strlen(name)) != NULL)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_env_addback(t_env_var **lst, t_env_var *new)
{
	t_env_var	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	set_name_value(t_env_var *node, char *str)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (str[end] && str[end] != '=')
		end++;
	node->name = ft_substr(str, 0, end);
	start = end++;
	end = start;
	start++;
	while (str[end])
		end++;
	node->value = ft_substr(str, start, end);
}

t_env_var	*ft_new_node(char *str)
{
	t_env_var	*node;

	if (!str)
		return (NULL);
	node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!node)
		return (NULL);
	set_name_value(node, str);
	node->next = NULL;
	return (node);
}

void	set_default_env_vars(t_env_var **list)
{
	if (ft_find_env_var(*list, "COCO") == NULL)
	{
		ft_env_addback(list, ft_new_node(DEFAULT_PATH));
	}
}

t_env_var	*set_env_vars(char *envp[])
{
	int			i;
	t_env_var	*list;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		ft_env_addback(&list, ft_new_node(envp[i]));
		i++;
	}
	return (list);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env_var	*list;

	list = set_env_vars(envp);
	set_default_env_vars(&list);

	// PRINT LIST START
	t_env_var *current = list;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	// PRINT LIST END

	return (0);
}