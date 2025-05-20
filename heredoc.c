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
	int		fd;

	rand = ft_malloc(10);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, rand, 10) == -1)
		return (NULL);
	return (hb_strjoin("/tmp/.", rand));
}

void	oktob(int fd, char *dl)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (hb_strcmp(line, dl) == 0 || !line)
			break ;
		write(fd, line, hb_strlen(line));
		write(fd, "\n", 1);
	}
	if (!line || !*line)
		hb_printerr("warning: here-document delimited by end-of-file (wanted `%s')\n",
			dl);
}

int	runheredoc(t_cmd *cmd)
{
	int	e;

	while (cmd)
	{
		e = heredoc(cmd->redirect_list);
		cmd = cmd->next;
	}
	return (e);
}

int	heredoc(t_redirect *rdct)
{
	int		fd;
	char	*filename;

	signals(HEREDOC);
	while (rdct)
	{
		if (rdct->type == TOKEN_HEREDOC)
		{
			filename = random_name();
			fd = open(filename, O_WRONLY | O_CREAT, 0644);
			if (fd == -1)
				return (hb_printerr("%s\n", strerror(errno)), setes(errno));
			oktob(fd, rdct->value);
			rdct->value = filename;
		}
		rdct = rdct->next;
	}
	signals(NORMAL);
	open("/dev/tty", O_RDONLY);
	return (0);
}
