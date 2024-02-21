/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:10:15 by hichokri          #+#    #+#             */
/*   Updated: 2024/02/21 18:06:14 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_str(char **tab, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	*find_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = "PATH";
	while (env[i])
	{
		if (ft_strstr(env[i], path))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	**cmd_path(char **path, char *cmd)
{
	char	*path_cmd;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (access(cmd, F_OK | X_OK) == 0)
	{
		path[0] = cmd;
		return (path);
	}
	path_cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(tmp, path_cmd);
		free(tmp);
		i++;
	}
	free(path_cmd);
	return (path);
}

void	child_process1(t_pipex *pipex, char *cmd1, char *env[])
{
	int		i;
	char	**cmd;

	i = 0;
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror("opening file error");
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		exit(pipex->status);
	}
	pipex->cmd_args = ft_split(cmd1, " \r\f\v\t\n");
	cmd = cmd_path(pipex->cmd_path, pipex->cmd_args[0]);
	while (cmd[i])
	{
		if (access(cmd[i], F_OK | X_OK) == 0)
		{
			dup2(pipex->infile, 0);
			dup2(pipex->fd[1], 1);
			close(pipex->fd[0]);
			close(pipex->fd[1]);
			close(pipex->infile);
			execve(cmd[i], pipex->cmd_args, env);
		}
		i++;
	}
	perror("command not found");
	exit(pipex->status);
}

void	child_process2(t_pipex *pipex, char *cmd2, char *env[])
{
	int		i;
	char	**cmd;

	i = 0;
	pipex->outfile = open(pipex->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror("opening file error");
		exit(1);
	}
	pipex->cmd_args = ft_split(cmd2, " \r\f\v\t\n");
	cmd = cmd_path(pipex->cmd_path, pipex->cmd_args[0]);
	while (cmd[i])
	{
		if (access(cmd[i], F_OK | X_OK) == 0)
		{
			dup2(pipex->fd[0], 0);
			dup2(pipex->outfile, 1);
			close(pipex->fd[0]);
			close(pipex->fd[1]);
			close(pipex->outfile);
			execve(cmd[i], pipex->cmd_args, env);
		}
		i++;
	}
	perror("command not found");
	exit(127);
}
