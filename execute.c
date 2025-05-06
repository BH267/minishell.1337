/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:04:28 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/06 12:09:23 by deepseeko        ###   ########.fr       */
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

int	builtins(char *cmd, t_ms *ms)
{
	redirect(ms);
	if (hb_strcmp(cmd, "cd") == 0)
		ms->e = cd(ms->args, ms);
	else if (hb_strcmp(cmd, "echo") == 0)
		ms->e = echo(ms->args);
	else if (hb_strcmp(cmd, "env") == 0)
		ms->e = envi(ms->env);
	else if (hb_strcmp(cmd, "pwd") == 0)
		ms->e = pwd(ms->env);
	else if (hb_strcmp(cmd, "export") == 0)
		ms->e = ft_export(ms->args, &(ms->env));
	else if (hb_strcmp(cmd, "unset") == 0)
		ms->e = unset(&(ms->env), ms->args);
	else if (hb_strcmp(cmd, "exit") == 0)
		ms->e = bexit(ms->args, ms->e);
	else
	{
		b2o(1, 0, 0);
		return (99);
	}
	b2o(1, 0, 0);
	return (ms->e);
}

int	pars_exec(t_cmd *cmd, t_ms *ms, int bins)
{
	ms->args = cmd->args;
	if (!ms->args)
		return (1);
	ms->cmd = cmd->args[0];
	ms->rdctl = cmd->redirect_list;
	varexp(ms);
	if (bins)
		return (builtins(ms->cmd, ms));
	return (execute(ms));
}

int	execute(t_ms *ms)
{
	//varexp(ms);
	if (builtins(ms->args[0], ms) != 99)
		return (ms->e);
	ms->cmd = getpath(ms->cmd, ms->p2env);
	if (!ms->cmd)
	{
		ms->e = 127;
		return (127);
	}
	ms->e = run(ms);
	return (ms->e);
}
