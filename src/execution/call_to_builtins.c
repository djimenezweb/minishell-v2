/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_to_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:23:43 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/23 02:08:00 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//! Run in parent process: cd, pwd, unset, export, exit
//! Run in child process: pwd, echo, env

/* Include `t_shell` for exit and `env_list`?*/
int	call_to_builtins(t_cmd *cmd, char **envp, t_env_var *env_list)
{
	if (cmd->cmd[0][0] != 'e')
	{
		if (cmd->cmd[0][0] == 'c')
			return(execute_cd(cmd->cmd, cmd->cmd[1], env_list));
		else if (cmd->cmd[0][0] == 'p')
			return (ft_pwd(envp));
		else if (cmd->cmd[0][0] == 'u')
			return (ft_unset());//Needs env_list
	}
	else
	{
		if (cmd->cmd[0][1] == 'c')
			return(execute_echo(cmd));
		else if (cmd->cmd[0][1] == 'n')
			return (ft_env());
		else if (cmd->cmd[0][2] == 'p')
			return (ft_export());//needs env_list
		else if (cmd->cmd[0][2] == 'i')
			return(ft_exit());
	}
	return (1);
}
