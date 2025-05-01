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
	int	status;
	int	oldfd;

	tmp = cmd;
	oldfd = 0;
	status = 0;
	if (!tmp->next)
	{
		pid = fork();
		if (pid == 0)
			ft_exit(pars_exec(cmd, ms));
		else if (pid > 0)
			waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
		//return (ms->e);
	}
	while (tmp->next)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			ms->e = child(cmd, ms, fd, oldfd);
			if (ms->e)
				exit (ms->e);
		}
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
			parent(&oldfd, fd);
		}
		ms->e = WEXITSTATUS(status);
		tmp = tmp->next;
		if (!tmp->next)
		{
			dup2(fd[0], 0);
			close (fd[0]);
			ms->e = pars_exec(tmp, ms);
			close (fd[1]);
		}
		if (ms->e)
			break ;
	}
	close (fd[1]);
	close (fd[0]);
	return (ms->e);
}
