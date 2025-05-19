/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:48:29 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/19 13:48:35 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	singlecmd(t_ms *ms)
{
	int	pid;
	int	status;

	if (builtins(ms->cmd, ms) != 99)
		return (ms->e);
	pid = fork();
	status = 0;
	if (pid == -1)
		return (hb_printerr("fork fails, try again\n"), 1);
	if (pid == 0)
	{
		signals(CHILD);
		ms->e = execute(ms);
		ft_exit(ms->e);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signals(NORMAL);
	}
	else
		return (hb_printerr("%s\n", strerror(errno)), errno);
	return (WEXITSTATUS(status));
}
