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
#include <unistd.h>

int	child(t_cmd *cmd, t_ms *ms, int *fd, int oldfd)
{
	close(fd[0]);
	dup2(fd[1], 1);
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
	while (tmp->next)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child(tmp, ms, fd, oldfd);
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
			parent(&oldfd, fd);
		}
		else
			hb_printerr("fork fails, try again\n");
		tmp = tmp->next;
	}
	return (ms->e);
}
