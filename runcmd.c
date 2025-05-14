/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:10:09 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/08 14:48:46 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	pars_exec(t_cmd *cmd, t_ms *ms)
{
	ms->args = cmd->args;
	if (!ms->args)
		return (1);
	ms->cmd = cmd->args[0];
	ms->rdctl = cmd->redirect_list;
	return (0);
}


int	runcmd(t_ms *ms, t_cmd *cmd)
{
	if (pars_exec(cmd, ms))
		return (1);
	runheredoc(cmd);
	if (!cmd->next)
		return (singlecmd(ms));
	pipeline(ms, cmd);
	return (ms->e);
}
