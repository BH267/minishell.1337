/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:40:49 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/07 13:44:11 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*random_name(void)
{
	char	*rand;
	int	fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, rand, 10) == -1)
		return (NULL);
	return (hb_strjoin("/tmp/", rand));
}

void	oktob(int fd, char *dl)
{
	char	*line;

	line = "\0";
	while (line)
	{
		line = get_next_line(fd);
		write(fd, line, hb_strlen(line));
		if (hb_strcmp(line, dl) == 0)
			break ;
	}
	if (!line)
		hb_printerr("warning: here-document delimited by end-of-file (wanted `%s')\n", dl);
}

int	heredoc(t_redirect *rdct)
{
	int	fd;
	char	*filename;

	while (rdct)
	{
		if (rdct->type == TOKEN_HEREDOC)
		{
			filename = random_name();
			fd = open(filename, O_WRONLY | O_CREAT, 0644);
			if (fd == -1)
				return (hb_printerr("open failed, try again\n"), 1);
			oktob(fd, rdct->value);
			rdct->value = filename;
		}
		rdct = rdct->next;
	}	
	return (0);
}
