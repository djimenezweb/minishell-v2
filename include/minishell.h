/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:18:26 by danielji          #+#    #+#             */
/*   Updated: 2025/11/10 13:04:18 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libft and our headers
# include "libft.h"
# include "macros.h"
# include "environment.h"
# include "lexer.h"
# include "expander.h"
# include "syntax.h"
# include "parser.h"
# include "execution.h"

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
	//Should include here exit status, updated after every execution
	t_cmd		*cmd_list;
}			t_shell;

void	free_shell(t_shell *data);
// DEBUG HELPERS
void	print_lex_list(t_lextoken *list);
void	print_array_of_strings(char **arr);

#endif
