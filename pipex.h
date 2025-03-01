/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:48:41 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/12 03:13:00 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_cmd_args
{
	char				**args;
	struct s_cmd_args	*next;
}						t_cmd_args;

typedef struct s_pipe
{
	char		**path;
	char		**envp;
	char		*infile;
	char		*outfile;
	int			pipe_nb;
	t_cmd_args	*all_args;
}				t_pipe;

char	**path_bin(char **envp);
char	**ft_split_scam(char *s, char c);
void	exec_pipe(t_pipe pipex);
void	free_args(char **argv);
void	free_s_pipex(t_pipe pipex);
void	access_bin(int index, t_pipe pipex);
void	child_process(t_pipe pipex, int i, int *fd);
t_pipe	create_pipex(int argc, char *argv[], char **envp);

#endif