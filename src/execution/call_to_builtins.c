/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_to_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:23:43 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/18 20:32:30 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Something*/	call_to_builtins(t_cmd *cmd/*, t_shell for exit and env_list?*/)
{
	if (cmd->cmd[0][0] != 'e')
	{
		if (cmd->cmd[0][0] == 'c')
			//execute cd
		else if (cmd->cmd[0][0] == 'p')
			//execute pwd
		else if (cmd->cmd[0][0] == 'u')
			//execute unset
	}
	else
	{
		if (cmd->cmd[0][1] == 'c')
			//execute echo 
/*return some status of function?*/execute_echo(cmd);
		else if (cmd->cmd[0][1] == 'n')
			//execute env
		else if (cmd->cmd[0][2] == 'p')
			//execute export
		else if (cmd->cmd[0][2] == 'i')
			//execute exit
	}
}
