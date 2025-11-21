/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_to_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:23:43 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/21 12:57:57 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Include `t_shell` for exit and `env_list`?*/
void	call_to_builtins(t_cmd *cmd)
{
	if (cmd->cmd[0][0] != 'e')
	{
		if (cmd->cmd[0][0] == 'c')
			return ;//execute cd
		else if (cmd->cmd[0][0] == 'p')
			return ;//execute pwd
		else if (cmd->cmd[0][0] == 'u')
			return ;//execute unset
	}
	else
	{
		if (cmd->cmd[0][1] == 'c')
			execute_echo(cmd);/*return some status of function?*/
		else if (cmd->cmd[0][1] == 'n')
			return ;//execute env
		else if (cmd->cmd[0][2] == 'p')
			return ;//execute export
		else if (cmd->cmd[0][2] == 'i')
			ft_exit();
	}
}
