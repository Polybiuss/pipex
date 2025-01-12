/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pipe_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 03:08:13 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/12 03:09:49 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_cmd_args	*create_args(char *arg)
{
	t_cmd_args	*args;

	args = malloc(sizeof(t_cmd_args));
	if (!args)
		return (NULL);
	args->args = ft_split(arg, ' ');
	args->next = NULL;
	return (args);
}

void	add_last(t_cmd_args **args, t_cmd_args *add)
{
	t_cmd_args	*tmp;

	if (!(*args))
	{
		*args = add;
		return ;
	}
	tmp = *args;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = add;
}

t_cmd_args	*lst_args(char **argv)
{
	t_cmd_args	*args;
	int			i;

	i = 2;
	args = NULL;
	while (argv[i])
	{
		if (argv[i + 1])
			add_last(&args, create_args(argv[i]));
		++i;
	}
	return (args);
}

t_pipe	create_pipex(int argc, char *argv[], char **envp)
{
	t_pipe	pipex;

	pipex.envp = envp;
	pipex.path = path_bin(envp);
	pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	pipex.all_args = lst_args(argv);
	pipex.pipe_nb = argc - 3;
	return (pipex);
}
