/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:46:07 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/01 20:23:07 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	lastcmd(t_cmd *cmd, t_ms *ms, int fd)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (fd != -1)
		{
			dup2(fd, 0);
			close(fd);
		}
		ms->e = pars_exec(cmd, ms, 0);
		if (ms->e)
			ft_exit(ms->e);
	}
	else
	{
		if (fd != -1)
			close(fd);
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}

int	child(t_cmd *cmd, t_ms *ms, int *fd, int pfd)
{
	if (pfd != -1)
	{
		dup2(pfd, 0);
		close(pfd);
	}
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	ms->e = pars_exec(cmd, ms, 0);
	return (ms->e);
}

int	parent(t_cmd **cmd, int	*fd, int *pfd, int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (*pfd != -1)
		close(*pfd);
	close(fd[1]);
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	*pfd = fd[0];
	*cmd = (*cmd)->next;
	return (WEXITSTATUS(status));
}

int	pipecmds(t_cmd *cmd, t_ms *ms, int *fd, int pfd)
{
	t_cmd	*tmp;
	int		pid;

	tmp = cmd;
	while (tmp->next)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			ms->e = child(tmp, ms, fd, pfd);
			if (ms->e)
				ft_exit(ms->e);
		}
		else
		{
			ms->e = parent(&tmp, fd, &pfd, pid);
			if (ms->e)
				return (ms->e);
		}
	}
	ms->e = lastcmd(tmp, ms, pfd);
	return (ms->e);
}

int	pip(t_ms *ms, t_cmd *cmd)
{
	int	fd[2];
	int	pfd;

	pfd = -1;
	if (pipe(fd) == -1)
		return (hb_printerr("pipe fails, try again\n"), 1);
	if (!cmd->next)
		return (singlecmd(ms, cmd));
	else
		ms->e = pipecmds(cmd, ms, fd, pfd);
	return (ms->e);
}
