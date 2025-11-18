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

int      count_chars_from(char **args)
{
	int   count;

	count = 0;
	while (*args)
	{
		count = ft_strlen(*args);
		if (*(args + 1))
			count += 1;
		++args;
	}
	return (count);
}

int   join_to_write(char **args, int len, int option_n, char **joined)
{
	char *iterator;
	*joined = ft_calloc(len, sizeof(char));
	if (!(*joined))
		return (0);
	iterator = *joined;
	while (args)
	{
	}
	return (1);
}
	
//Join args to write it at once
int	execute_echo(t_cmd *cmd/*, int pipefd[2]??*/)
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
	write_len += count_chars_from(args);
	if (!join_to_write(args, write_len, option_n, &joined_to_write))
		return (0);//malloc error happened
	write(/*output_fd*/, joined_to_write, write_len);
}
