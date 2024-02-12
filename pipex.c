/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: hichokri <marvin@42.fr>                    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/02/11 16:12:30 by hichokri          #+#    #+#             */
/*   Updated: 2024/02/11 16:12:35 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex pipex;

	if (argc == 5)
	{
		pipex.infile = open(argv[1], O_RDONLY);
		if (pipex.infile == -1)
			perror("opening file error hahah");
		pipex.outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex.outfile == -1)
			perror("opening file error");
		if (pipe(pipex.fd) < 0)
			perror("pipe error");
		pipex.path = find_path(envp);
		pipex.cmd_path = ft_split(pipex.path, ':');
		pipex.pid1 = fork();
		if (pipex.pid1 == -1)
			perror("fork error");
		else if (pipex.pid1 == 0)
			child_process1(&pipex, argv[2]);
		pipex.pid2 = fork();
		if (pipex.pid2  == -1)
			perror("fork error");
		else if (pipex.pid2 == 0)
			child_process2(&pipex, argv[3]);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		waitpid(pipex.pid1, NULL, 0);
		waitpid(pipex.pid2, NULL, 0);
		// free(pipex.path);
		// free(pipex.cmd_args);
	}
	else
		perror("number of arguments incorrect");
	return (0);
}
