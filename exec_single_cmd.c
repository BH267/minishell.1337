/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:39:11 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/03 11:39:25 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	singlecmd(t_ms *ms, t_cmd *cmd)
{
	int	pid;
	int	status;

	if (pars_exec(cmd, ms, 1) != 99)
		return (ms->e);
	pid = fork();
	status = 0;
	if (pid == -1)
		return (hb_printerr("fork fails, try again\n"), 1);
	if (pid == 0)
	{
		ms->e = pars_exec(cmd, ms, 0);
		ft_exit(ms->e);
	}
	else if (pid > 0)
	{
		signal(SIGINT, signals);
		waitpid(pid, &status, 0);
	}
	else
		return (hb_printerr("%s\n", strerror(errno)), errno);
	return (WEXITSTATUS(status));
}
