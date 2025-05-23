/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:49:39 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/18 12:15:10 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

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

static void	parent(t_cmd **cmd, int	*fd, int *pfd)
{
	*cmd = (*cmd)->next;
	signal(SIGINT, SIG_IGN);
	signals(NORMAL);
	if (*pfd != -1)
		close(*pfd);
	close(fd[1]);
	*pfd = fd[0];
}

int	wastloop(t_ms *ms, t_cmd *cmd, int pfd)
{
	int	fd[2];
	int	pid;

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
		else if (pid > 0)
			parent(&cmd, fd, &pfd);
		else
			return (hb_printerr("%s\n", strerror(errno)), errno);
	}
	ms->e = lastcmd(cmd, ms, pfd);
	return (ms->e);
}

int	pipeline(t_ms *ms, t_cmd *cmd)
{
	int	pfd;
	int	status;

	pfd = -1;
	setes(wastloop(ms, cmd, pfd));
	while (wait(&status) > 0)
		if (WEXITSTATUS(status) != 0)
			ms->e = WEXITSTATUS(status);
	return (ms->e);
}
