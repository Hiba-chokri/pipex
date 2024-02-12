/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hichokri <marvin@42.fr>                    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/02/11 16:12:46 by hichokri          #+#    #+#             */
/*   Updated: 2024/02/11 16:12:52 by hichokri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		fd[2];
	char	*path;
	char	**cmd_path;
	char	**cmd_args;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

char	**ft_split(char *s, char c);
char	*ft_strstr(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*find_path(char **env);
char	**cmd_path(char **path, char *cmd);
void	child_process1(t_pipex *pipex, char *cmd1);
void	child_process2(t_pipex *pipex, char *cmd2);

#endif
