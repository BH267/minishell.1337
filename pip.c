/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:07:11 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/26 12:22:33 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"


int	child(t_cmd *cmd, t_ms *ms, int *fd, int oldfd)
{
	dup2(fd[1], 1);
	close (fd[0]);
	close(fd[1]);
	dup2(oldfd, 0);
	close(oldfd);
	return (pars_exec(cmd, ms));
}

void	parent(int *oldfd, int *fd)
{
	if (*oldfd >= 0)
		close(*oldfd);
	*oldfd = fd[0];
	close(fd[1]);
}

int	pip(t_ms *ms, t_cmd *cmd)
{
	t_cmd	*tmp;
	int	fd[2];
	int	pid;
	int	oldfd;

	tmp = cmd;
	oldfd = 0;
	if (!tmp->next)
		return (pars_exec(cmd, ms));
	while (tmp->next)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child(cmd, ms, fd, oldfd);
		if (pid > 0)
		{
			wait(NULL);
			parent(&oldfd, fd);
		}
		tmp = tmp->next;
		if (!tmp->next)
		{
			dup2(fd[0], 0);
			close (fd[0]);
			pars_exec(tmp, ms);
			close (fd[1]);
		}
	}
	return (ms->e);
}
