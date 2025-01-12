/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:30:54 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/12 02:58:28 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	err_bin(char *path, char *cmd)
{
	free(path);
	perror(cmd);
}

void	cmd_not_found(char *cmd)
{
	char	*err;

	err = ft_strjoin(cmd, ": Command not found\n");
	ft_putstr_fd(err, 2);
	free(err);
}

void	find_bin(t_pipe pipex, char **cmd_n_args)
{
	int		i;
	char	*path;

	i = 0;
	while (pipex.path[i])
	{
		path = ft_strjoin(pipex.path[i], cmd_n_args[0]);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				if (execve(path, cmd_n_args, pipex.envp) < 0)
					break ;
			}
			else
				break ;
		}
		free(path);
		path = NULL;
		++i;
	}
	if (path)
		return (err_bin(path, cmd_n_args[0]));
	cmd_not_found(cmd_n_args[0]);
}

void	access_bin(int index, t_pipe pipex)
{
	int			i;
	t_cmd_args	*cmd_arg;

	i = 0;
	cmd_arg = pipex.all_args;
	while (i != index && cmd_arg)
	{
		if (!cmd_arg->next)
			break ;
		cmd_arg = cmd_arg->next;
		++i;
	}
	find_bin(pipex, cmd_arg->args);
}
