/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:40:49 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/23 16:57:59 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand/expand.h"
#include "ms.h"

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
	close(fd);
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

int	oktob(int fd, char *dl, t_env *env)
{
	char	*line;
	int		vdl;

	vdl = valid(dl);
	line = NULL;
	while (1)
	{
		if (get_next_line(&line) == 99)
			return (1);
		if (!line)
		{
			hb_printerr("\nwarning: here-document delimited by end-of-file");
			hb_printerr("(wanted `%s')\n", dl);
			return (0);
		}
		if (hb_strcmp(line, hb_strjoin(dl, "\n")) == 0)
			break ;
		if (vdl)
			line = expand_herdoce(line, env);
		write(fd, line, hb_strlen(line));
	}
	return (0);
}

int	runheredoc(t_cmd *cmd, t_env *env)
{
	int	e;

	while (cmd)
	{
		e = heredoc(cmd->redirect_list, env);
		cmd = cmd->next;
	}
	return (e);
}

int	heredoc(t_redirect *rdct, t_env *env)
{
	int		fd;
	char	*filename;

	signals(HEREDOC);
	b2o(1);
	while (rdct)
	{
		if (rdct->type == TOKEN_HEREDOC)
		{
			filename = random_name();
			fd = open(filename, O_WRONLY | O_CREAT, 0644);
			if (fd == -1)
				return (hb_printerr("%s\n", strerror(errno)), setes(errno));
			if (oktob(fd, rdct->value, env))
				return (b2o(0), *(estate()));
			rdct->value = filename;
		}
		rdct = rdct->next;
	}
	b2o(0);
	signals(NORMAL);
	return (0);
}
