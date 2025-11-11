/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:44:41 by danielji          #+#    #+#             */
/*   Updated: 2025/11/10 12:10:41 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// wait
# include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

char	**get_path_dirs(t_env_var *env_list);
char	*get_exec_path(char *cmd, char **paths);
int		is_builtin(char *cmd);
void	close_pipe(int pipefd[2]);
int		is_last(t_cmd *cmd);
int		is_first(t_cmd *cmd);
void	redirect_in(int temp_fd, int input);
void	redirect_out(int pipefd[2], int output, int is_last);
void	child_process(t_cmd *cmd, int temp_fd, int pipefd[2], char **envp);
void	parent_process(t_cmd *cmd, int *temp_fd, int pipefd[2]);
int		execute_cmd_list(t_cmd *cmd, char **envp);
void	execution(t_shell *data);
int		wait_children(t_cmd *cmd);

#endif
