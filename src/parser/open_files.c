/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:20:47 by danielji          #+#    #+#             */
/*   Updated: 2025/11/05 18:20:47 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"
#include "parser.h"

/* Return file descriptor of input or output file
TODO: Check if path is file or directory, etc. */
int	open_file(char *path, enum e_lex_type type)
{
	printf("LEX TYPE %d\n", type);
	if (type == TOK_INFILE)
		return open_infile(path);
	else if (type == TOK_OUTFILE_CREATE)
		return open_outfile(path, type);
	else if (type == TOK_OUTFILE_APPEND)
		return open_outfile(path, type);
	return (-1);
}

/* int	open_infile(char *path)
{
	(void)path;
	return (3);
}

int	open_outfile(char *path, enum e_lex_type type)
{
	(void)path;
	(void)type;
	return (4);
} */

/* Open file in read-only and return its `fd`.
On error print a warning and return the `fd`. */
int	open_infile(char *path)
{
	int	fd;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		if (!access(path, F_OK) && access(path, R_OK) < 0)
		{
			// TODO
			// printerror(EACCES, path);
		}
		else
		{
			// TODO
			// printerror(ENOENT, path);
		}
	}
	return (fd);
}

/* Open file for writing and return its `fd`. */
int	open_outfile(char *path, enum e_lex_type type)
{
	int	fd;
	int	flag;

	flag = O_WRONLY | O_CREAT | O_TRUNC, 0644;
	if (type == TOK_APPEND)
		flag = O_WRONLY | O_CREAT | O_APPEND, 0644;

	fd = open(path, flag);
	if (fd == -1)
	{
		if (!access(path, F_OK) && access(path, W_OK) < 0)
		{
			// TODO
			// printerror(EACCES, path);
		}
		else
		{
			// TODO
			// printerror(ENOENT, path);
		}
		// exit(1);
	}
	return (fd);
}
