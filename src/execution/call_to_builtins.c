/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_to_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:23:43 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/29 19:16:12 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//! Run in PARENT process (is_forkable == 0):	cd, unset, export, exit
//! Run in CHILD process (is_forkable == 1):	pwd, echo, env

/* Include `t_shell` for exit and `env_list`?*/
int	call_to_builtins(t_cmd *cmd, char **envp, t_env_var *env_list)
{
	if (cmd->cmd[0][0] != 'e')
	{
		if (cmd->cmd[0][0] == 'c')
			return (execute_cd(cmd->cmd, cmd->cmd[1], env_list, envp));
		else if (cmd->cmd[0][0] == 'p')
			return (ft_pwd());
		else if (cmd->cmd[0][0] == 'u')
			return (ft_unset(cmd));//Needs env_list
	}
	else
	{
		if (cmd->cmd[0][1] == 'c')
			return(execute_echo(cmd));
		else if (cmd->cmd[0][1] == 'n')
			return (ft_env(cmd->cmd, envp, 0));
		else if (cmd->cmd[0][2] == 'p')
			return (ft_export(cmd->cmd, env_list, envp));//needs env_list
		else if (cmd->cmd[0][2] == 'i')
			return (ft_exit(cmd));
	}
	return (1);
}
