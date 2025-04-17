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
			strerror(errno);
			return (1);
		}
	}else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		strerror(errno);
	return (0);
}

int	builtins(char *cmd, char **args, char *cmdl)
{
	if (hb_strcmp(cmd, "cd") == 0)
		cd(args);
	else if (hb_strcmp(cmd, "exit") == 0)
		ft_exit(0, cmdl);
	else if (hb_strcmp(cmd, "echo") == 0)
		ft_exit(0, cmdl);
	else if (hb_strcmp(cmd, "env") == 0)
		ft_exit(0, cmdl);
	else if (hb_strcmp(cmd, "pwd") == 0)
		ft_exit(0, cmdl);
	else if (hb_strcmp(cmd, "export") == 0)
		ft_exit(0, cmdl);
	else if (hb_strcmp(cmd, "unset") == 0)
		ft_exit(0, cmdl);
	else
		return (1);
	return (0);
}

int	execute(char *cmd, char **env)
{
	char	**args;
	
	args = hb_split(cmd, ' ');
	if (!builtins(args[0], args, cmd))
		return (0);
	cmd = getpath(args[0], env);
	if (!cmd)
	{
		strerror(errno);
		return (1);
	}
	return (run(cmd, args, env));
}
