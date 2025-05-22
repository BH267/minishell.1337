/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:10:09 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/21 12:12:57 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	pars_exec(t_cmd *cmd, t_ms *ms)
{
	ms->args = cmd->args;
	if (ms->args)
		ms->cmd = cmd->args[0];
	ms->rdctl = cmd->redirect_list;
	return (0);
}

int	runcmd(t_ms *ms, t_cmd *cmd)
{
	ms->e = runheredoc(cmd , ms->env);
	if (ms->e)
		return (ms->e);
	if (pars_exec(cmd, ms))
		return (setes(ms->e));
	if (!cmd->next)
		return (setes(singlecmd(ms)));
	ms->e = pipeline(ms, cmd);
	return (ms->e);
}
