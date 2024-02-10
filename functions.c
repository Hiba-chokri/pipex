char *find_path(char **envp)//to find the path in the environement variable
{
    int i;
    char *path;
    
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path = ft_strdup(envp[i] + 5);
            return (path);
        }
        i++;
    }
    return (NULL);
}

char *cmd_path(char *path, char *cmd)
{
    char *path_cmd;
    char *tmp;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (path[i])
    {
            tmp = ft_substr(path, j, i - j);
            path_cmd = ft_strjoin(tmp, "/");
            free(tmp);
            tmp = ft_strjoin(path_cmd, cmd);
            free(path_cmd);
            return (tmp);
        }
        i++;
    }
    if (path[i] == '\0')
            j = i + 1;
    return (NULL);
}

void child_process1(t_pipex *pipex, char *cmd1)
{
    int i;
    char *cmd;
    
    i = 0;
    cmd = cmd_path(pipex->cmd_path[i], cmd1);
    while (pipex->cmd_path[i])
    {
        if (access(cmd, F_OK) == 0)//to check if the commad exists so execve will not execute a non existing command    
        {
            dup2(pipex->infile, 0);
            dup2(pipex->fd[1], 1);
            close(pipex->fd[0]);
            close(pipex->fd[1]);
            close(pipex->infile);
            close(pipex->outfile);
            pipex.cmd_args = ft_split(argv[2], '');
            if  (execve(cmd, pipex.cmd_args[0], NULL) == -1)
                perror("execve error");
        }
        free(cmd);//we free and we try a new path
        i++;
        cmd = cmd_path(pipex->cmd_path[i], pipex->cmd_args[0]);
    }
    perror("command not found");
}

void child_process2(t_pipex *pipex, char *cmd2)
{
    int i;
    char *cmd;
    
    i = 0;
    cmd = cmd_path(pipex->cmd_path[i], cmd2);
    while (pipex->cmd_path[i])
    {
        if (access(cmd, F_OK) == 0)
        {
            if (dup2(pipex->fd[0], 0) < 0)
                perror("dup2 error");
            if (dup2(pipex->outfile, 1) < 0)
                perror("dup2 error");
            close(pipex->fd[0]);
            close(pipex->fd[1]);
            close(pipex->infile);
            close(pipex->outfile);
            pipex->cmd_args = ft_split(argv[3], '');
            execve(cmd, pipex->cmd_args[0], NULL);
            perror("execve error");
        }
        free(cmd);
        i++;
        cmd = cmd_path(pipex->cmd_path[i], pipex->cmd_args[0]);
    }
    perror("command not found");
}