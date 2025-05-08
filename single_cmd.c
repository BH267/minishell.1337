/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:14:47 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/08 14:16:29 by habenydi         ###   ########.fr       */
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
		ms->e = execute(ms);
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
