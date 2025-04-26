/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:25 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/16 15:03:13 by habenydi         ###   ########.fr       */
/*   Updated by GitHub Copilot for parsing test main                         */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// Old main commented for test
/*
int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	(void)av;
	ms.e = 0;
	ms.env = envtolist(env);
	if (ac > 1)
		return (printf("usage: <./minishell>\n"), 1);
	while (1)
	{
		if (!ms.e)
			ms.cmd = readline("\033[0;36mмιηιѕнєℓℓ \033[0;32m❱ \033[0m");
		else
			ms.cmd = readline("\033[0;36mмιηιѕнєℓℓ \033[0;31m❱ \033[0m");
		if (!ms.cmd)
		{
			printf("exit\n");
			break ;
		}
		if (!*ms.cmd)
			continue ;
		add_history(ms.cmd);
		ms.e = execute(&ms, env);
	}
	ft_exit(ms.e);
}
*/

// New test main for parsing/tokenizing and printing command linked list
int	main(void)
{
	char *line;
	while (1)
	{
		line = readline("Enter command to parse (or 'exit'): ");
		if (!line)
			break;
		if (!*line)
		{
			free(line);
			continue;
		}
		if (!strcmp(line, "exit"))
		{
			free(line);
			break;
		}
		add_history(line);
		parsing(line);
		free(line);
	}
	return (0);
}
/**/
