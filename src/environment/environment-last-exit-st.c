/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment-last-exit-st.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:52:50 by danielji          #+#    #+#             */
/*   Updated: 2025/11/20 10:52:58 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_last_exit_status(t_env_var *list, int status)
{
	t_env_var	*node;

	node = find_env_var(list, "?");
	free(node->value);
	node->value = ft_itoa(status);
	if (!node->value)
		return (-1);
	return (0);
}
