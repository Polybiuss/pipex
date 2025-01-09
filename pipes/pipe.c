/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:49:52 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/09 22:57:33 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	access_bin(int index, t_pipe pipex)
{
	int i;
	t_cmd_args *arg;
	char *path;

	i = 0;
	arg = pipex.all_args;
	while(i != index && arg)
	{
		arg = arg->next;
		++i;
	}
	i = 0;
	while (pipex.path[i])
	{
		path = ft_strjoin(pipex.path[i], arg->args[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			execve(path, arg->args, pipex.envp);
			perror(arg->args[0]);
			return ;
		}
		free(path);
		++i;
	}
	perror(arg->args[0]);
	return ;
}

void	child_process(t_pipe pipex, int i, int *pipe)
{
	int fd;
	if (i == 0)
	{
		if (access(pipex.infile, R_OK | F_OK) < 0)
		{
			perror(pipex.infile);
			// close(pipe[0]);
			// close(pipe[1]);
			// exit(1);
			// return ;
		}
		else
		{
			fd = open(pipex.infile, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			dup2(pipe[1], STDOUT_FILENO);
			close(pipe[0]);
			close(pipe[1]);
			close(fd);
			access_bin(i, pipex);
		}
	}
	else if (i == 1)
	{
		if (access(pipex.outfile, W_OK) < 0)
		{
			if (access(pipex.outfile, F_OK) < 0)
			{
				fd = open(pipex.outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
				dup2(fd, STDOUT_FILENO);
				dup2(pipe[0], STDIN_FILENO);
				close(pipe[1]);
				close(pipe[0]);
				close(fd);
				access_bin(i, pipex);
			}
			else
			{
				perror(pipex.outfile);
				// exit(1);
			}
		}
		else
		{
			fd = open(pipex.outfile, O_WRONLY);
			dup2(fd , STDOUT_FILENO);
			dup2(pipe[0], STDIN_FILENO);
			close(pipe[1]);
			close(pipe[0]);
			close(fd);
			access_bin(i, pipex);
		}
	}
	close(pipe[0]);
	close(pipe[1]);
	free_s_pipex(pipex);
	exit(1);
}

void	exec_pipe(t_pipe pipex)
{
	int fd[2];
	int pid[2];
	int	i;

	pipe(fd);
	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			child_process(pipex, i, fd);
			//infile
			//path
			//access bin
			//dup2("infile", STDIN_FILENO);
			// dup2(fd[1], STDOUT_FILENO);
			// close(fd[0]);
			// close(fd[1]);
			// execve();
		}
		++i;
	}
	close(fd[0]);
	close(fd[1]);
	// close infile oufile
	i = 0;
	int status;
	while (i < 2)
	{
		waitpid(pid[i], &status, 0);
		++i;
	}
}