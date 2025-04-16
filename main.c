/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:05:14 by habenydi          #+#    #+#             */
/*   Updated: 2025/03/01 02:11:28 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	**split_cmd(char *cmd)
{
	int		i = 0;
	char	**args = malloc(100 * sizeof(char *));
	char	*token = strtok(cmd, " ");

	while (token)
	{
		args[i++] = strdup(token);
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}

char	**get_path(char **env)
{
	char	**paths;

	paths = hb_split(hb_mtrrchr(env, "PATH"), ':');
	return (paths);
}

void	execute_cmd(char **args, char **env)
{
	pid_t	pid;
	int		status;
	char	**cmd;
	int	i;
	char *tmp;

	if (hb_strncmp(args[0], "cd", 2) == 0)
	{
		cd(args[0]);
	}
	cmd = get_path(env);
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		while (cmd[i])
		{
			tmp = cmd[i];
			cmd[i] = hb_strjoin(cmd[i], "/");
			free(tmp);
			tmp = cmd[i];
			cmd[i] = hb_strjoin(cmd[i], args[0]);
			free(tmp);
			if(execve(cmd[i], args, env) != -1)
				exit(0);
			i++;
		}
		strerror(errno);
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork failed");
	hb_mtrfree(cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	char	**args;

	if (ac != 1)
		printf("usage : <./minishell>\n");
	(void)av;
	while (1)
	{
		cmd = readline("minishell> ");
		if (!cmd)
		{
			printf("exit\n");
			break;
		}
		if (*cmd)
			add_history(cmd);
		//lexer(cmd);
		args = split_cmd(cmd);

		if (args[0])
			execute_cmd(args, env);
		free(cmd);
		hb_mtrfree(args);
	}
	rl_clear_history();
	return (0);
}
