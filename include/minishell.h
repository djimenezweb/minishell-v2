/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/10/21 11:32:00 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libft and our headers
# include "libft.h"
# include "macros.h"
# include "environment.h"
# include "expander.h"
# include "lexer.h"
# include "syntax.h"

// malloc, free
# include <stdlib.h>

// readline, printf
# include <stdio.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

//#include <string.h>
//#include <ctype.h>

typedef struct s_shell
{
	char		*line;
	t_lextoken	*lex_list;
	t_env_var	*env_list;
}			t_shell;

// DEBUG HELPERS
void	print_lex_list(t_lextoken *list);
void	print_array_of_strings(char **arr);

#endif
