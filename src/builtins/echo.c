/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:46:19 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/18 21:26:42 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option_n(char *arg_one)
{
	if (*arg_one != '-')
		return (0);
	++arg_one;
	while (arg_one)
	{
		if (*arg_one != 'n')
			return (0);
		++arg_one;
	}
	return (1);
}

/*Some*/	execute_echo(t_cmd *cmd/*, int pipefd[2]??*/)
{
	int	write_len;
	int	option_n;
	char	*joined_to_write;
	char	**args;

	write_len = 2;
	option_n = 0;
	join_to_write = NULL;
	args = cmd->cmd[1];
	if (args && is_option_n(args))
	{
		option_n = 1;
		++args;
		write_len -= 1;
		/*Concatenate all the options, with 32 space. If not -n, 
		 * add a \n. at the end*/
	}
	//count_args()
	//if count is 1, add or not '\n', and write it
	//if count >= 2, join arg + ' ' + arg, until it is the last
	//Or maybe create a function that copies inside joined_to_write
	//	arg by arg, add ' ' if current arg is != count_args,
	//	and add later \n if it is needed
	write_len += ft_strlen(joined_to_write);
}
