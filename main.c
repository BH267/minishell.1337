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

#include "header/mini.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

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

void	execute_cmd(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("minishell");
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork failed");
}

void	free_args(char **args)
{
    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

int	main(void)
{
	char	*cmd;
	char	**args;

	while (1)
	{
		cmd = readline("minishel> ");
		if (!cmd)
		{
			ft_printf("exit\n");
			break;
		}
		if (*cmd)
			add_history(cmd);
		args = split_cmd(cmd);
		if (args[0])
			execute_cmd(args);

		free(cmd);
		free_args(args);
	}
	rl_clear_history();
	return (0);
}

