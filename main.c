/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:25 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/11 12:18:00 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

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
void	sighand(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		//write (1, "\n", 1);
		rl_replace_line("\n", 0);
		rl_redisplay();
		return ;
	}
	if (sig == SIGQUIT)
	{
		(void)sig;
	}
}

int	signals(int mode)
{
	if (mode == NORMAL)
	{
		signal(SIGINT, sighand);
		signal(SIGQUIT, sighand);
		return (1);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return (1);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, sighand);
		signal(SIGQUIT, SIG_DFL);
		return (1);
	}
	return (0);
}
// New test main for parsing/tokenizing and printing command linked list
int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("Enter command to parse (or 'exit'): ");
		if (!line)
			break;
		if (!*line)
			continue;
		if (!strcmp(line, "exit"))
			break;
		add_history(line);
		parsing2(line);
	}
	ft_free();
	return (0);
}
//*/
