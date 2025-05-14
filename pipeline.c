/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:49:39 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/08 19:09:56 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	lastcmd(t_cmd *cmd, t_ms *ms, int fd)
{
	int	pid;
	int	status;

	status = 0;
	pars_exec(cmd, ms);
	pid = fork();
	if (pid == 0)
	{
		signals(CHILD);
		if (fd != -1)
		{
			dup2(fd, 0);
			close(fd);
		}
		execute(ms);
		if (ms->e)
			ft_exit(ms->e);
	}
	else
	{
		signals(NORMAL);
		if (fd != -1)
			close(fd);
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}

void	child(t_ms *ms, int *fd, int pfd)
{
	signals(CHILD);
	if (pfd != -1)
	{
		dup2(pfd, 0);
		close(pfd);
	}
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (builtins(ms->args[0], ms) != 99)
		ft_exit(ms->e);
	ms->e = execute(ms);
	ft_exit (ms->e);
}

int	parent(t_cmd **cmd, int	*fd, int *pfd, int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	signals(NORMAL);
	if (*pfd != -1)
		close(*pfd);
	close(fd[1]);
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	*pfd = fd[0];
	*cmd = (*cmd)->next;
	return (WEXITSTATUS(status));
}

int	pipeline(t_ms *ms, t_cmd *cmd)
{
	int	fd[2];
	int	pfd;
	int	pid;

	pfd = -1;
	while (cmd->next)
	{
		pars_exec(cmd, ms);
		if (pipe(fd) == -1)
			return (hb_printerr("%s\n", strerror(errno)), errno);
		pid = fork();
		if (pid == 0)
		{
			child(ms, fd, pfd);
			if (ms->e)
				ft_exit(ms->e);
		}
		else
		{
			ms->e = parent(&cmd, fd, &pfd, pid);
			if (ms->e)
				return (ms->e);
		}
	}
	ms->e = lastcmd(cmd, ms, pfd);
	return (ms->e);
}
