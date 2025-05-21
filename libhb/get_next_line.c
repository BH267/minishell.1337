/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:23:32 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/11 08:42:53 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_readline(int fd, char *string, char *buff)
{
	ssize_t	cont;
	char	*fnl;

	cont = 0;
	fnl = NULL;
	while (!fnl)
	{
		cont = read(fd, buff, BUFFER_SIZE);
		if (!cont)
			break ;
		if (cont < 0)
			return (NULL);
		buff[cont] = '\0';
		fnl = ft_strchr(buff, '\n');
		string = ft_strjoin(string, buff);
	}
	return (string);
}

static void	ft_getline(char **string, char **line)
{
	size_t	i;

	if (!**string)
	{
		*string = NULL;
		*line = NULL;
		return ;
	}
	i = 0;
	while ((*string)[i] && (*string)[i] != '\n')
		i++;
	if (!(*string)[i])
	{
		*line = ft_strdup(*string);
		*string = NULL;
		return ;
	}
	*line = ft_substr(*string, i + 1);
	*string = ft_strdup(&(*string)[i + 1]);
}

int	get_next_line(char **str)
{
	char		*buff;
	static char	*string;
	char		*line;

	buff = NULL;
	if (BUFFER_SIZE <= 0)
		return (1);
	if (!ft_strchr(string, '\n'))
	{
		buff = ft_malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (1);
		if (write(0, "> ", 2) == -1)
			return (1);
		string = ft_readline(0, string, buff);
		if (!string)
			return (1);
	}
	ft_getline(&string, &line);
	*str = line;
	return (0);
}
