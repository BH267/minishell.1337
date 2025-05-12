/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:25 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/12 12:19:31 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"


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
int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env *lst_env;

	(void)ac;
	(void)av;
	lst_env = envtolist(env);
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
		parsing2(line, lst_env);
	}
	ft_free();
	return (0);
}
//*/
