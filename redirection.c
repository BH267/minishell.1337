/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:18:37 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/08 18:30:09 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	redin(t_redirect *rdct)
{
	int	fd;

	fd = open(rdct->value, O_RDONLY);
	if (fd == -1)
		return (hb_printerr("%s\n", strerror(errno)), errno);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	redout(t_redirect *rdct)
{
	int	fd;

	fd = open(rdct->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (hb_printerr("%s\n", strerror(errno)), errno);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	append(t_redirect *rdct)
{
	int	fd;

	fd = open(rdct->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (hb_printerr("%s\n", strerror(errno)), errno);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	hrdoc(t_redirect *rdct)
{
	int	fd;

	fd = open(rdct->value, O_RDONLY);
	if (fd == -1)
		return (hb_printerr("%s\n", strerror(errno)), errno);
	dup2(fd, 0);
	close(fd);
	return (0);
}

void	b2o(int doit)
{
	static int	std_out;
	static int	std_in;

	if (doit)
	{
		std_out = dup(1);
		std_in = dup(0);
	}
	else
	{
		dup2(std_out, 1);
		dup2(std_in, 0);
		close(std_out);
		close(std_in);
	}
}

int	redirect(t_ms *ms)
{
	t_redirect	*rdct;

	b2o(1);
	rdct = ms->rdctl;
	while (rdct)
	{
		if (rdct->type == TOKEN_REDIR_IN)
			if (redin(rdct))
				return (1);
		if (rdct->type == TOKEN_REDIR_OUT)
			if (redout(rdct))
				return (1);
		if (rdct->type == TOKEN_APPEND)
			if (append(rdct))
				return (1);
		if (rdct->type == TOKEN_HEREDOC)
			if (hrdoc(rdct))
				return (1);
		rdct = rdct->next;
	}
	return (0);
}
