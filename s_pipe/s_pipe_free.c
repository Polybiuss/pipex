/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pipe_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 03:03:06 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/12 03:04:14 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		++i;
	}
	free(args);
}

void	free_lst(t_cmd_args *args)
{
	if (!(args))
		return ;
	free_lst(args->next);
	if (!args->args)
		free((args));
	else
	{
		free_args(args->args);
		free(args);
	}
}

void	free_s_pipex(t_pipe pipex)
{
	int	i;

	i = 0;
	while (pipex.path[i])
	{
		free(pipex.path[i]);
		++i;
	}
	free_lst(pipex.all_args);
	free(pipex.path);
}
