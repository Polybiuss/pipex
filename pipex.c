/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:48:15 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/09 20:31:02 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_args(char **args)
{
	int i;

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
	int i;

	i = 0;
	while (pipex.path[i])
	{
		free(pipex.path[i]);
		++i;
	}
	free_lst(pipex.all_args);
	free(pipex.path);
}

t_cmd_args	*create_args(char *arg)
{
	t_cmd_args *args;

	args = malloc(sizeof(t_cmd_args));
	if (!args)
		return (NULL);
	args->args = ft_split(arg, ' ');
	args->next = NULL;
	return (args);
}

void	add_last(t_cmd_args **args, t_cmd_args *add)
{
	t_cmd_args *tmp;

	if(!(*args))
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
	t_cmd_args *args;
	int i;

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

void	show_args(char **args)
{
	int i;

	i = 0;

	while (args[i])
	{
		ft_printf("args : %s\n", args[i]);
		++i;
	}
}

void	show_lst_args(t_cmd_args *args)
{
	t_cmd_args *tmp;
	if (!args)
		return ;
	tmp = args;
	while (tmp)
	{
		show_args(tmp->args);
		tmp = tmp->next;
	}
}

int main(int argc, char *argv[], char **envp)
{
	(void)argv;
	t_pipe pipex;
	if (argc == 5)
	{
		pipex.envp = envp;
		pipex.path = path_bin(envp);
		pipex.infile = argv[1];
		pipex.outfile = argv[4];
		pipex.all_args = lst_args(argv);
		exec_pipe(pipex);
		// show_lst_args(pipex.all_args);
		free_s_pipex(pipex);
	}
	return (0);
}