/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:17:48 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/01 16:20:18 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	singlecmd(t_ms *ms, t_cmd *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
		return (hb_printerr("fork fails, try again\n"),1);
	if (pid == 0)
	{
		ms->e = pars_exec(cmd, ms);
		ft_exit(ms->e);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (hb_printerr("%s\n", strerror(errno)), errno);
	return (WEXITSTATUS(status));
}

int	isfirst(t_cmd *cmd, t_ms *ms, int *fd)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
		return (hb_printerr("fork fails, try again\n"),1);
	if (!pid)
	{
		dup2(fd[1], 1);
		close (fd[1]);
	//	close (fd[0]);
		ms->e = pars_exec(cmd, ms);
		ft_exit(ms->e);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (hb_printerr("%s\n", strerror(errno)), errno);
	return (WEXITSTATUS(status));
}

int	lastcmd(t_cmd *cmd, t_ms *ms, int *fd)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
		return (hb_printerr("fork fails, try again\n"),1);
	if (!pid)
	{
		dup2(fd[0], 0);
	//	close (fd[1]);
		close (fd[0]);
		ms->e = pars_exec(cmd, ms);
		ft_exit(ms->e);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (hb_printerr("%s\n", strerror(errno)), errno);
	return (WEXITSTATUS(status));
}

int	pipedcmds(t_cmd *cmd, t_ms *ms, int *pfd, int *fd)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
		return (hb_printerr("fork fails, try again\n"),1);
	if (!pid)
	{
		dup2(pfd[0], 0);
		dup2(fd[1], 1);
	//	close (fd[0]);
		close (fd[1]);
	//	close (pfd[0]);
		close (pfd[1]);
		ms->e = pars_exec(cmd, ms);
		ft_exit(ms->e);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (hb_printerr("%s\n", strerror(errno)), errno);
	close (fd[0]);
	close (fd[1]);
	return (WEXITSTATUS(status));
}

int	pipeline(t_cmd *cmd, t_ms *ms)
{
	static int	isfst;
	int		fd[2];
	int		pfd[2];

	if (pipe(fd) == -1 || pipe(pfd) == -1)
		return (hb_printerr("pipe fails, try again\n"),1);
	if (!isfst)
		return (isfirst(cmd, ms, fd));
	isfst = 1;
	if (!cmd->next)
		ms->e = lastcmd(cmd, ms, pfd);
	else
	{
		ms->e = pipedcmds(cmd, ms, pfd, fd);
		pfd[0] = fd[1];
		fd[0] = pfd[1];
	}
	close(fd[0]);
	close(fd[1]);
	return (ms->e);
}

int	pip(t_ms *ms, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (!tmp->next)
		return (singlecmd(ms, cmd));
	while (tmp->next)
	{
		pipeline(tmp, ms);
		tmp = tmp->next;
	}
	return (ms->e);
}
