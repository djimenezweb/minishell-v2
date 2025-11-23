/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:44:41 by danielji          #+#    #+#             */
/*   Updated: 2025/11/23 00:25:40 by enrgil-p         ###   ########.fr       */
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

int		call_to_builtins(t_cmd *cmd, t_env_var *env_list);
int		heredoc(t_cmd *cmd);
void	execution(t_shell *data);
int		execute_cmd_list(t_cmd *cmd, char **envp, t_shell *data);
void	parent_process(t_cmd *cmd, int *temp_fd, int pipefd[2]);
void	child_process(t_cmd *cmd, int temp_fd, int pipefd[2], char **envp);
int		wait_children(t_cmd *cmd);
char	**get_path_dirs(t_env_var *env_list);
char	*get_exec_path(char *cmd, char **paths);
int		is_builtin(char *cmd);
int		is_forkable(char *cmd);
void	safe_dup2(int oldfd, int newfd);
void	safe_close(int fd);
void	close_child_fds(int temp_fd, int pipefd[2], int last);
void	redirect_in(int temp_fd, int input, int first);
void	redirect_out(int pipefd[2], int output, int last);
void	close_pipe(int pipefd[2]);
int		is_last(t_cmd *cmd);
int		is_first(t_cmd *cmd);
void	command_not_found(char *cmd);
void	permission_denied(char *cmd);

#endif
