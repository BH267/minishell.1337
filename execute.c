/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:04:28 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/20 00:39:28 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	run(t_ms *ms)
{
	redirect(ms);
	if (execve(ms->cmd, ms->args, ms->p2env) == -1)
	{
		if (!closedir(opendir(ms->cmd)))
		{
			hb_printerr("%s : Is a directory\n", ms->cmd);
			return (126);
		}
		else
		{
			hb_printerr("%s\n", strerror(errno));
			return (errno);
		}
	}
	return (0);
}

int	execute(t_ms *ms)
{
	ms->cmd = getpath(ms->cmd, ms->env);
	if (!ms->cmd)
	{
		ms->e = 127;
		return (127);
	}
	ms->e = run(ms);
	return (ms->e);
}
