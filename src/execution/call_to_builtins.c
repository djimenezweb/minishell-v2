/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_to_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:23:43 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/12/01 10:54:49 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Run builtin function and return its exit status*/
int	call_to_builtins(t_cmd *cmd, char **envp, t_env_var *env_list)
{
	if (cmd->cmd[0][0] != 'e')
	{
		if (cmd->cmd[0][0] == 'c')
			return (execute_cd(cmd->cmd, cmd->cmd[1], env_list,
					envp));
		else if (cmd->cmd[0][0] == 'p')
			return (ft_pwd());
		else if (cmd->cmd[0][0] == 'u')
			return (ft_unset(cmd));
	}
	else
	{
		if (cmd->cmd[0][1] == 'c')
			return (execute_echo(cmd));
		else if (cmd->cmd[0][1] == 'n')
			return (ft_env(cmd->cmd, envp, 0));
		else if (cmd->cmd[0][2] == 'p')
			return (ft_export(cmd->cmd, env_list, envp));
		else if (cmd->cmd[0][2] == 'i')
			return (ft_exit(cmd));
	}
	return (1);
}
