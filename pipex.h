#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct s_pipex
{
    int infile;
    int outfile;
    int fd[2];
    char *path;
    char **cmd_path;
    char **cmd_args;
    pid_t pid1;
    pid_t pid2;
} t_pipex;

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);//should work with get next line strjoin
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char *find_path(char **envp);
char *cmd_path(char *path, char *cmd);
void child_process1(t_pipex *pipex, char *cmd1);
void child_process2(t_pipex *pipex, char *cmd2);

#endif
