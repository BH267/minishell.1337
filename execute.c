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

int	run(char *cmd, char **args, char **env)
{
	pid_t	pid;
	int	status;

	status = 0;
	pid = fork();
	if(pid == 0)
	{
		if (execve(cmd, args, env) == -1)
		{
			printf("%s\n", strerror(errno));
			exit (1);
		}
	}else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (printf("%s\n", strerror(errno)), 1);
	return(WEXITSTATUS(status));
}

int	builtins(char *cmd, t_ms *ms)
{
	if (hb_strcmp(cmd, "cd") == 0)
		ms->e = cd(ms->args, ms);
	else if (hb_strcmp(cmd, "echo") == 0)
		ms->e = echo(ms->args, ms);
	else if (hb_strcmp(cmd, "env") == 0)
		ms->e = envi(ms->env);
	else if (hb_strcmp(cmd, "pwd") == 0)
		ms->e = pwd();
	else if (hb_strcmp(cmd, "export") == 0)
		ms->e = ft_export(ms->args, &(ms->env));
	else if (hb_strcmp(cmd, "unset") == 0)
		unset(&(ms->env), ms->args);
	else if (hb_strcmp(cmd, "exit") == 0)
	{
		printf("exit\n");
		ft_exit(ms->e);
	}
	else
		return (2);
	return (ms->e);
}

int	execute(t_ms *ms, char **env)
{
	ms->args = hb_split(ms->cmd, ' ');
	if (!ms->args )
		return (1);
	varexp(ms);
	if (builtins(ms->args[0], ms) != 2)
		return (ms->e);
	ms->cmd = getpath(ms->args[0], env);
	if (!ms->cmd)
	{
		ms->e = 1;
		return (1);
	}
	ms->e = run(ms->cmd, ms->args, env);
	return (ms->e);
}
