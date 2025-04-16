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

int	execute(char *cmd, char **env)
{
	char	**args;
	
	args = hb_split(cmd, ' ');
	cmd = getpath(args[0], env);
	if (!cmd)
	{
		strerror(errno);
		return (1);
	}
	return (run(cmd, args, env));
}
