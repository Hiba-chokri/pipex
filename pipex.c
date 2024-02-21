/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichokri <hichokri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:09:31 by hichokri          #+#    #+#             */
/*   Updated: 2024/02/21 16:42:06 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


static void	ft_open(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	if (argc == 5)
	{
		pipex->argv = argv;
		if (pipe(pipex->fd) < 0)
			perror("pipe error");
		pipex->path = find_path(envp);
		pipex->cmd_path = ft_split(pipex->path, ":");
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			perror("fork error");
		else if (pipex->pid1 == 0)
			child_process1(pipex, argv[2], envp);
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
			perror("fork error");
		else if (pipex->pid2 == 0)
			child_process2(pipex, argv[3], envp);
	}
	else
		perror("number of args incorrect");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		status;

	ft_open(&pipex, argc, argv, envp);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
	return (WEXITSTATUS(status));
}
