/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:46:19 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/27 20:44:34 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option_n(char *arg_one)
{
	if (*arg_one != '-')
		return (0);
	++arg_one;
	while (*arg_one != '\0')
	{
		if (*arg_one != 'n')
			return (0);
		++arg_one;
	}
	return (1);
}

static int	count_chars_from(char **args)
{
	int	count;

	count = 0;
	while (*args)
	{
		count += ft_strlen(*args);
		if (*(args + 1))
			count += 1;
		++args;
	}
	return (count);
}

static void	copy_args_to_join(char **args, char **joined, int option_n)
{
	char	*iterator_joined;
	char	*iterator_arg;

	iterator_joined = *joined;
	while (*args)
	{
		iterator_arg = *args;
		while (*iterator_arg != '\0')
		{
			*iterator_joined = *iterator_arg;
			++iterator_joined;
			++(iterator_arg);
		}
		if (*(args + 1) != NULL)
		{
			*iterator_joined = ' ';
			++iterator_joined;
		}
		++args;
	}
	if (!option_n)
		*iterator_joined = '\n';
}

static int	join_to_write(char **args, int len, int option_n, char **joined)
{
	*joined = ft_calloc(len, sizeof(char));
	if (!*joined)
		return (0);
	copy_args_to_join(args, joined, option_n);
	return (1);
}

//Join args to write it at once
int	execute_echo(t_cmd *cmd)
{
	int		join_len;
	int		option_n;
	char	*joined_to_write;
	char	**args;

	join_len = 2;
	option_n = 0;
	joined_to_write = NULL;
	args = cmd->cmd + 1;
	if (*args && is_option_n(*args))
	{
		option_n = 1;
		++args;
		join_len -= 1;
	}
	join_len += count_chars_from(args);
	if (!join_to_write(args, join_len, option_n, &joined_to_write))
	{
		perror("echo failed in malloc");
		return (12);
	}
	write(STDOUT_FILENO, joined_to_write, join_len - 1);
	free(joined_to_write);
	return (0);
}
