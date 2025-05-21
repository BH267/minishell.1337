/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:40:49 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/21 12:17:15 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
#include "expand/expand.h"

char	*random_name(void)
{
	char	*rand;
	int		fd;

	rand = ft_malloc(11);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, rand, 10) == -1)
		return (NULL);
	rand[10] = '\0';
	return (hb_strjoin("/tmp/.", rand));
}

int	valid(char *dl)
{
	int	i;

	i = 0;
	while (dl[i])
	{
		if (dl[i] == '\'' || dl[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

void	oktob(int fd, char *dl , t_env *env)
{
	char	*line;
	int	vdl;

	vdl = valid(dl);
	while (1)
	{
		line = readline("> ");
		if (hb_strcmp(line, dl) == 0 || !line)
			break ;
		if (vdl)
			line = expand_herdoce(line , env);
		write(fd, line, hb_strlen(line));
		write(fd, "\n", 1);
	}
	if (!line || !*line)
		hb_printerr("warning: here-document delimited by end-of-file (wanted `%s')\n", dl);
}

int	runheredoc(t_cmd *cmd , t_env *env)
{
	int	e;

	while (cmd)
	{
		e = heredoc(cmd->redirect_list , env);
		cmd = cmd->next;
	}
	return (e);
}

int	heredoc(t_redirect *rdct , t_env *env)
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
			oktob(fd, rdct->value , env);
			rdct->value = filename;
		}
		rdct = rdct->next;
	}
	signals(NORMAL);
	open("/dev/tty", O_RDONLY);
	return (0);
}
