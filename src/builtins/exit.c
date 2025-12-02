/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:02:09 by danielji          #+#    #+#             */
/*   Updated: 2025/12/02 16:46:45 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Count number of strings in an array of strings */
static int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/* Print error if argument is not a valid number */
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (ft_isdigit(str[i]) != 1)
		{
			ft_dprintf(STDERR_FILENO, "minishell: exit: %s: "
				"numeric argument required\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

/* Get status from `exit` arguments or from `last_status` */
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

/* Free allocated memory and exit program */
int	ft_exit(t_cmd *cmd)
{
	unsigned char	status;

	if (arr_size(cmd->cmd) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (cmd->cmd[1] && is_valid_number(cmd->cmd[1]) == 0)
		return (2);
	status = (unsigned char)get_exit_status(cmd);
	free_shell(cmd->shell, status);
	return (0);
}
