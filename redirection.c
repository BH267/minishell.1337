/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:34:55 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/29 09:30:38 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	redin(t_redirect *rdct, int fd, int *tfd)
{
	fd = open(rdct->value, O_RDONLY);
	if (fd == -1)
		return (hb_printerr("open faild, try again\n"), 1);
	*tfd = dup(0);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	redout(t_redirect *rdct, int fd, int *tfd)
{
	fd = open(rdct->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (hb_printerr("open faild, try again\n"), 1);
	*tfd = dup(1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	append(t_redirect *rdct, int fd, int *tfd)
{
	fd = open(rdct->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (hb_printerr("open faild, try again\n"), 1);
	*tfd = dup(1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	b2o(int	pfdo, int pfdi, int doit)
{
	static int	fdo;
	static int	fdi;

	if (doit)
	{
		fdo = pfdo;
		fdi = pfdi;
	}
	else
	{
		dup2(fdo, 1);
		dup2(fdi, 0);
	}
	return (0);
}

int	redirect(t_ms *ms)
{
	t_redirect	*rdct;
	int			fd;
	int			tmpfdo;
	int			tmpfdi;

	rdct = ms->rdctl;
	tmpfdo = 1;
	tmpfdi = 0;
	fd = 0;
	while (rdct)
	{
		if (rdct->type == 2)
			if (redin(rdct, fd, &tmpfdi))
				return (1);
		if (rdct->type == 3)
			if (redout(rdct, fd, &tmpfdo))
				return (1);
		if (rdct->type == 4)
			if (append(rdct, fd, &tmpfdo))
				return (1);
		rdct = rdct->next;
	}
	b2o(tmpfdo, tmpfdi, 1);
	return (0);
}
