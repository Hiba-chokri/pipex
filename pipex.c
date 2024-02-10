
#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
    t_pipex pipex;//to access the struct variables
    if (argc == 5)//we check that we have 5 arguments
    {
        pipex.inflie = open(argv[1], O_RDONLY);//we read from infile,handle file rights
        if (pipex.infile < 0)
            perror("opening file error");
        pipex.outfile = open(argv[5], O_TRUNC | o_CREAT | O_WRONLY, 0644);//we write to output file ,cReate it if doesnt existe, or truncate it if it does
        if (pipex.outfile < 0)
            perror("opening file error");
        pipe(pipex.fd);//Creation of pipe
        if (pipe(pipex.fd) < 0)
            perror("pipe error");
        pipex.path = find_path(envp);
        //pipex.cmd_path = ft_split(pipex.path, ':');
        pipex.pid1 = fork(); //creation of child process1
        if (pipex.pid1 < 0)
            perror("fork error");
        else if (pipex.pid1 == 0)
            child_process1(&pipex, argv[2]);
        pipex.pid2 = fork();
        if (pipex.pid2 < 0)
            perror("fork error");
        else if (pipex.pid2 == 0)
            child_process2(&pipex, argv[3]);
        close(pipex.fd[0]);
        close(pipex.fd[1]);
        waitpid(pipex.pid1, NULL, 0);
        waitpid(pipex.pid2, NULL, 0);
        free(pipex.path);
        free(pipex.cmd_args);
	    free(pipex.cmd);
        return(0);
}
