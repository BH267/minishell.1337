/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lastcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:14:31 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/22 15:18:00 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

static void	parent(int *fd, int *status, int pid)
{
	if (*fd != -1)
		close(*fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	signals(NORMAL);
}

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
		parent(&fd, &status, pid);
	}
	return (WEXITSTATUS(status));
}
