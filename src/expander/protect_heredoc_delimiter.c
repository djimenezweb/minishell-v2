/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_heredoc_delimiter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:08:42 by enrgil-p          #+#    #+#             */
/*   Updated: 2025/11/11 20:47:02 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_dollar_to_sub(char **line,
		t_expansion_data forced_quote_flag)
{
	char	*heredoc;

	heredoc = *line + 2;
	while (heredoc && ft_isspace(*heredoc))
		heredoc++;
	while (heredoc)
	{
		if (*heredoc == SINGLE_QUOTE || *heredoc == DOUBLE_QUOTE)
		{
			update_quote_flag(&forced_quote_flag, *heredoc);
			++heredoc;
		}
		else if (*heredoc == DOLLAR)
			*heredoc = SUB_CHAR;
		else if ((ft_isspace(*heredoc)
				&& forced_quote_flag.env_quoted == 0))
			break ;
		else
			++heredoc;
	}
}

//If status is PROTECT, checks next word and change $ to char SUB, 26;
//If status is RESTORE, do the same but returns char to $ value
void	protect_heredoc_delimiter(char **str, t_protect_chars_status status,
		t_expansion_data quote_status)
{
	char	*ptr;

	ptr = *str;
	while (status == PROTECT && ptr)
	{
		ptr = ft_strnstr(ptr, "<<", ft_strlen(ptr));
		if (ptr)
		{
			change_dollar_to_sub(&ptr, quote_status);
			ptr += 2;
		}
	}
	while (status == RESTORE && ptr)
	{
		ptr = ft_strchr(ptr, SUB_CHAR);
		if (ptr)
			*ptr = '$';
	}
}
