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
#include <stdio.h>

int	run(char *cmd, char **args, char **env)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if(pid == 0)
	{
		if (execve(cmd, args, env) == -1)
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
	}else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		printf("%s\n", strerror(errno));
	return (0);
}

int	builtins(char *cmd, t_ms *ms)
{
	if (hb_strcmp(cmd, "cd") == 0)
		cd(ms->args);
	else if (hb_strcmp(cmd, "exit") == 0)
		ft_exit(ms->e);
	else if (hb_strcmp(cmd, "echo") == 0)
		echo(ms->args, ms);
	else if (hb_strcmp(cmd, "env") == 0)
		envi(ms->env);
	else if (hb_strcmp(cmd, "pwd") == 0)
		pwd();
	else if (hb_strcmp(cmd, "export") == 0)
		ft_exit(0);
	else if (hb_strcmp(cmd, "unset") == 0)
		ft_exit(0);
	else
		return (1);
	return (0);
}

int	execute(t_ms *ms)
{
	ms->args = hb_split(ms->cmd, ' ');
	varexp(ms);
	if (!builtins(ms->args[0], ms))
		return (0);
	ms->cmd = getpath(ms->args[0], ms->env);
	if (!ms->cmd)
		return (1);
	ms->e = run(ms->cmd, ms->args, ms->env);
	return (ms->e);
}
