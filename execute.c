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

int	run(char *cmd, char **args, char **env, t_ms *ms)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if(pid == 0)
	{
		if (execve(cmd, args, env) == -1)
		{
			printf("%s\n", strerror(errno));
			ms->e = 1;
			return (1);
		}
	}else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (printf("mohaal %s\n", strerror(errno)), 1);
	return (0);
}

int	builtins(char *cmd, t_ms *ms)
{
	if (hb_strcmp(cmd, "cd") == 0)
		ms->e = cd(ms->args);
	else if (hb_strcmp(cmd, "echo") == 0)
		ms->e = echo(ms->args, ms);
	else if (hb_strcmp(cmd, "env") == 0)
		ms->e = envi(ms->env);
	else if (hb_strcmp(cmd, "pwd") == 0)
		ms->e = pwd();
	else if (hb_strcmp(cmd, "export") == 0)
		ft_exit(0);
	else if (hb_strcmp(cmd, "unset") == 0)
		ft_exit(0);
	else if (hb_strcmp(cmd, "exit") == 0)
	{
		printf("exit\n");
		ft_exit(ms->e);
	}
	else
		return (1);
	return (0);
}

int	execute(t_ms *ms)
{
	ms->args = hb_split(ms->cmd, ' ');
	if (!ms->args )
		return (1);
	varexp(ms);
	if (!builtins(ms->args[0], ms))
		return (0);
	ms->cmd = getpath(ms->args[0], ms->env);
	if (!ms->cmd)
	{
		ms->e = 1;
		return (1);
	}
	ms->e = run(ms->cmd, ms->args, ms->env, ms);
	return (ms->e);
}
