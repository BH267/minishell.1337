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

int	builtins(char *cmd, char **args, char **env)
{
	if (hb_strcmp(cmd, "cd") == 0)
		cd(args);
	else if (hb_strcmp(cmd, "exit") == 0)
		ft_exit(0);
	else if (hb_strcmp(cmd, "echo") == 0)
		echo(args);
	else if (hb_strcmp(cmd, "env") == 0)
		envi(env);
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

int	execute(char *cmd, char **env)
{
	char	**args;
	int	e;

	args = hb_split(cmd, ' ');
	if (!builtins(args[0], args, env))
		return (0);
	cmd = getpath(args[0], env);
	if (!cmd)
		return (1);
	e = run(cmd, args, env);
	return (e);
}
