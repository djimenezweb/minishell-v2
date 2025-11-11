/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:34:13 by danielji          #+#    #+#             */
/*   Updated: 2025/11/10 12:15:46 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	ft_envlist_size(t_env_var *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int	ft_cmdlist_size(t_cmd *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	**get_envp(t_env_var *env_lst)
{
	int		i;
	int		size;
	char	*temp;
	char	**arr;

	i = 0;
	size = ft_envlist_size(env_lst);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	while (env_lst && i < size)
	{
		temp = ft_strjoin(env_lst->name, "=");
		if (env_lst->value)
			arr[i] = ft_strjoin(temp, env_lst->value);
		else
			arr[i] = ft_strjoin(temp, "");
		free(temp);
		env_lst = env_lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

/* Child process:
- Redirect input & output
- Close unused fd
- Execute command */
void	child_process(t_cmd *cmd, int temp_fd, int pipefd[2], char **envp)
{
	redirect_in(temp_fd, cmd->input, is_first(cmd));
	redirect_out(pipefd, cmd->output, is_last(cmd));
	if (temp_fd != -1)
		close(temp_fd);
	if (!is_last(cmd))
		close(pipefd[READ_END]);
	execve(cmd->path, cmd->cmd, envp);
	// TODO Mensaje error
	exit(EXIT_FAILURE);
}

/* Parent process:
- Close previous read end 
- Save current read end for next command
- Close current write end */
void	parent_process(t_cmd *cmd, int *temp_fd, int pipefd[2])
{
	if (*temp_fd != -1)
		close(*temp_fd);
	if (!is_last(cmd))
	{
		*temp_fd = pipefd[READ_END];
		close(pipefd[WRITE_END]);
	}
	else
		*temp_fd = -1;
}

/* For each command in the command list:
- Create pipe except on last command
- Fork process
- Return `-1` on error */
int	execute_cmd_list(t_cmd *cmd, char **envp)
{
	int	pipefd[2];
	int	temp_fd;

	temp_fd = -1;
	while (cmd)
	{
		if (!is_last(cmd) && (pipe(pipefd) < 0))
			return (-1);
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			return (-1);
		}			
		if (cmd->pid == 0)
			child_process(cmd, temp_fd, pipefd, envp);
		parent_process(cmd, &temp_fd, pipefd);
		cmd = cmd->next;
	}
	return (0);
}

int	wait_children(t_cmd *cmd)
{
	int	status;

	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	return (WEXITSTATUS(status));
}

void	execution(t_shell *data)
{
	t_cmd	*cmd;
	char	**paths;
	char	**envp;
	int		status;

	cmd = data->cmd_list;
	paths = get_path_dirs(data->env_list);
	envp = get_envp(data->env_list);
	while (cmd)
	{
		cmd->path = get_exec_path(cmd->cmd[0], paths);
		cmd = cmd->next;
	}
	execute_cmd_list(data->cmd_list, envp);
	status = wait_children(data->cmd_list);
	free_strings_array(paths);
	free_strings_array(envp);
	ft_cmdlist_clear(&(data->cmd_list));
}
