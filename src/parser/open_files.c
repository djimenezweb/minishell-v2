/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:20:47 by danielji          #+#    #+#             */
/*   Updated: 2025/11/05 18:20:47 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

/* Return file descriptor of input or output file
TODO: Check if path is file or directory, etc.?? */
int	open_file(char *path, enum e_lex_type type)
{
	if (type == TOK_INFILE)
		return (open_infile(path));
	else if (type == TOK_OUTFILE_CREATE || type == TOK_OUTFILE_APPEND)
		return (open_outfile(path, type));
	return (-1);
}

/* Open file in read-only and return its `fd`.
On error print a warning and return the `fd`. */
int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror(PERROR);
	return (fd);
}

/* Open file for writing and return its `fd`.
On error print a warning and return the `fd`. */
int	open_outfile(char *path, enum e_lex_type type)
{
	int	fd;
	int	flag;

	flag = O_WRONLY | O_CREAT | O_TRUNC;
	if (type == TOK_OUTFILE_APPEND)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(path, flag, 0644);
	if (fd < 0)
		perror(PERROR);
	return (fd);
}
