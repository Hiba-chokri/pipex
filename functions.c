/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hichokri <marvin@42.fr>                    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/02/11 16:12:16 by hichokri          #+#    #+#             */
/*   Updated: 2024/02/11 16:12:20 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	path_cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(tmp, path_cmd);
		i++;
	}
	return (path);
}

void	child_process1(t_pipex *pipex, char *cmd1)
{
	int		i;
	char	**cmd;

	i = 0;
	pipex->cmd_args = ft_split(cmd1, ' ');
	cmd = cmd_path(pipex->cmd_path, pipex->cmd_args[0]);
    // to check if the commad exists so
    // execve will not execute a non existing command
	while (cmd[i])
	{
		if (access(cmd[i], F_OK | X_OK) == 0)
		{
			dup2(pipex->infile, 0);
			dup2(pipex->fd[1], 1);
			close(pipex->fd[0]);
			close(pipex->fd[1]);
			close(pipex->infile);
			close(pipex->outfile);
			if (execve(cmd[i], pipex->cmd_args, NULL) == -1)
				perror("execve error");
		}
		//free(cmd);// we free and we try a new path
		i++;
		// cmd = cmd_path(pipex->cmd_path[i], pipex->cmd_args[0]);
	}
	perror("command not found");
}

void	child_process2(t_pipex *pipex, char *cmd2)
{
	int		i;
	char	**cmd;

	i = 0;

	pipex->cmd_args = ft_split(cmd2, ' ');
	cmd = cmd_path(pipex->cmd_path, pipex->cmd_args[0]);
	while (cmd[i])
	{
		
		if (access(cmd[i], F_OK | X_OK) == 0)
		{
			// if (dup2(pipex->fd[0], 0) < 0)
			// 	perror("dup2 error");
			// if (dup2(pipex->outfile, 1) < 0)
			// 	perror("dup2 error");

			dup2(pipex->fd[0], 0);
			dup2(pipex->outfile, 1);
			close(pipex->fd[0]);
			close(pipex->fd[1]);
			close(pipex->infile);
			close(pipex->outfile);

			execve(cmd[i], pipex->cmd_args, NULL);
			perror("execve error");
		}
		//free(cmd);
		i++;
		// cmd = cmd_path(pipex->cmd_path[i], pipex->cmd_args[0]);
	}
	perror("command not found");
}
