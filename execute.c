/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:04:28 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/16 17:11:37 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	run(t_ms *ms)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		redirect(ms);
		if (execve(ms->cmd, ms->args, ms->p2env) == -1)
		{
			if (!closedir(opendir(ms->cmd)))
			{
				hb_printerr("%s : Is a directory\n", ms->cmd);
				exit(126);
			}
			else
			{
				hb_printerr("%s\n", strerror(errno));
				exit(errno);
			}
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (hb_printerr("%s\n", strerror(errno)), errno);
	return (WEXITSTATUS(status));
}

int	builtins(char *cmd, t_ms *ms)
{
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
		return (2);
	return (ms->e);
}

int	pars_exec(t_cmd *cmd, t_ms *ms)
{
	ms->cmd = cmd->args[0];
	ms->args = cmd->args;
	if (!ms->args)
		return (1);
	ms->rdctl = cmd->redirect_list;
	return (execute(ms, ms->p2env));
}

int	execute(t_ms *ms, char **env)
{
	varexp(ms);
	if (builtins(ms->args[0], ms) != 2)
		return (ms->e);
	ms->cmd = getpath(ms->args[0], env);
	if (!ms->cmd)
	{
		ms->e = 127;
		return (127);
	}
	ms->e = run(ms);
	return (ms->e);
}
