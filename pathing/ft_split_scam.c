/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_scam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:10:38 by jbergos           #+#    #+#             */
/*   Updated: 2025/01/12 03:01:15 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static size_t	ft_count_words(char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			++i;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			++i;
	}
	return (count);
}

static void	free_table(char **pptr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(pptr[i]);
		++i;
	}
	free(pptr);
}

char	*add_slash(char *str)
{
	char	*s;

	s = ft_strjoin(str, "/");
	free(str);
	return (s);
}

char	**ft_split_scam(char *s, char c)
{
	char	**pptr;
	size_t	i;
	size_t	j;
	size_t	end;

	pptr = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!pptr)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_count_words(s, c))
	{
		while (s[i] && s[i] == c)
			++i;
		end = 0;
		while (s[i + end] != '\0' && s[i + end] != c)
			++end;
		pptr[j++] = add_slash(ft_substr(s + i, 0, end));
		if (!pptr[j - 1])
			return (free_table(pptr, j - 1), NULL);
		i += end;
	}
	pptr[j] = NULL;
	return (pptr);
}
