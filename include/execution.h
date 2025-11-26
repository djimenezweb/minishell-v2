/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:44:41 by danielji          #+#    #+#             */
/*   Updated: 2025/11/26 17:56:53 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

int		call_to_builtins(t_cmd *cmd, char **envp, t_env_var *env_list);
int		heredoc(t_cmd *cmd);
void	execution(t_shell *data);
void	preprocess_cmdlist(t_shell *data, char **paths);
int		execute_cmd_list(t_cmd *cmd, char **envp, t_shell *data);
pid_t	fork_cmd(t_cmd *cmd, int *temp_fd, int pipefd[2], char **envp);
void	parent_process(t_cmd *cmd, int *temp_fd, int pipefd[2]);
void	child_process(t_cmd *cmd, int temp_fd, int pipefd[2], char **envp);
int		get_status(int wstatus, int *signal);
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
void	init_pipe(int pipefd[2]);
int		is_last(t_cmd *cmd);
int		is_first(t_cmd *cmd);
int		is_executable(char *path, char *cmd);
void	print_error_exit(char *cmd, char *msg, int exit_status);

#endif
