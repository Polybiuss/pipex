/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:48:15 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/12 04:35:34 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_arg_without_space(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			++count;
		i++;
	}
	return (count);
}

int	check_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!count_arg_without_space(argv[i]))
			return (0);
		++i;
	}
	return (1);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipe	pipex;

	if (argc == 5)
	{
		if (!check_arg(argv))
		{
			ft_putstr_fd("pipex: File or command empty\n", 2);
			return (0);
		}
		pipex = create_pipex(argc, argv, envp);
		exec_pipe(pipex);
		free_s_pipex(pipex);
	}
	return (0);
}
