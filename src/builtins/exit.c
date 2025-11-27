/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:02:09 by danielji          #+#    #+#             */
/*   Updated: 2025/11/27 17:53:36 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Todos los builtins devuelven 0 si han tenido éxito o un número distinto de
0 en caso de error.
Devuelven 2 para indicar uso incorrecto, opciones inválidas o que faltan
argumentos. */

static int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
		{
			ft_dprintf(STDERR_FILENO, "minishell: exit: %s: ");
			ft_dprintf(STDERR_FILENO, "numeric argument required\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	get_exit_status(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (!cmd->cmd[1] || !cmd->cmd[1][0])
		status = cmd->shell->last_status;
	else
		status = ft_atoi(cmd->cmd[1]);
	return (status);
}

int	ft_exit(t_cmd *cmd)
{
	unsigned char	status;

	if (arr_size(cmd->cmd) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (2);
	}
	if (cmd->cmd[1] && is_valid_number(cmd->cmd[1]) == 0)
		return (2);
	status = (unsigned char)get_exit_status(cmd);
	free_shell(cmd->shell, status);
	return (0);
}
