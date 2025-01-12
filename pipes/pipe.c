/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:49:52 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/12 00:44:30 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exec_pipe(t_pipe pipex)
{
	int	fd[2];
	int	pid[2];
	int	i;

	pipe(fd);
	i = 0;
	while (i < pipex.pipe_nb)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child_process(pipex, i, fd);
		++i;
	}
	close(fd[0]);
	close(fd[1]);
	i = 0;
	while (i < pipex.pipe_nb)
	{
		waitpid(pid[i], NULL, 0);
		++i;
	}
}
