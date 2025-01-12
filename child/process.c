/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:51:04 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/12 00:53:30 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	first_child_fd(int fd, int *pipe, t_pipe pipex, int index)
{
	if (dup2(pipe[1], STDOUT_FILENO) < 0)
	{
		perror("pipe");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror(pipex.infile);
		return ;
	}
	close(pipe[0]);
	close(pipe[1]);
	close(fd);
	access_bin(index, pipex);
}

void	last_child_fd(int fd, int *pipe, t_pipe pipex, int index)
{
	if (dup2(pipe[0], STDIN_FILENO) < 0)
	{
		perror("pipe");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror(pipex.outfile);
		return ;
	}
	close(pipe[0]);
	close(pipe[1]);
	close(fd);
	access_bin(index, pipex);
}

void	first_child_cmd(t_pipe pipex, int *pipe, int index)
{
	int	fd;

	if (access(pipex.infile, F_OK | R_OK) < 0)
		perror(pipex.infile);
	else
	{
		fd = open(pipex.infile, O_RDONLY);
		if (fd < 0)
			perror(pipex.infile);
		else
			first_child_fd(fd, pipe, pipex, index);
	}
}

void	last_child_cmd(t_pipe pipex, int *pipe, int index)
{
	int	fd;

	if (access(pipex.outfile, F_OK) < 0)
	{
		fd = open (pipex.outfile, O_CREAT | O_WRONLY, 0777);
		if (fd < 0)
			perror(pipex.outfile);
		else
			last_child_fd(fd, pipe, pipex, index);
	}
	else if (access(pipex.outfile, W_OK) < 0)
		perror(pipex.outfile);
	else
	{
		fd = open(pipex.outfile, O_WRONLY | O_TRUNC);
		if (fd < 0)
			perror(pipex.outfile);
		else
			last_child_fd(fd, pipe, pipex, index);
	}
}

void	child_process(t_pipe pipex, int i, int *fd)
{
	if (i == 0)
		first_child_cmd(pipex, fd, i);
	else
		last_child_cmd(pipex, fd, i);
	close(fd[0]);
	close(fd[1]);
	free_s_pipex(pipex);
	exit(1);
}
