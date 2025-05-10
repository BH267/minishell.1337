/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:25:28 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/26 14:30:25 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		//write (1, "\n", 1);
		rl_replace_line("\n", 0);
		rl_redisplay();
		return ;
	}
}

int	promptline(t_ms *ms)
{
	if (!ms->e)
		ms->cmd = readline("\033[0;36mмιηιѕнєℓℓ \033[0;32m❱ \033[0m");
	else
		ms->cmd = readline("\033[0;36mмιηιѕнєℓℓ \033[0;31m❱ \033[0m");
	if (!ms->cmd)
	{
		hb_printerr("exit\n");
		return (1);
	}
	return (0);
}

int	prompt(t_ms *ms)
{
	t_cmd	*cmd;

	while (1)
	{
		if (promptline(ms))
			break ;
		if (!*ms->cmd)
			continue ;
		add_history(ms->cmd);
		cmd = parsing(ms->cmd);
		if (!cmd)
		{
			ms->e = 2;
			continue ;
		}
		ms->e = runcmd(ms, cmd);
	}
	return (ms->e);
}

int	shlvl(char **env)
{
	char	*value;

	value = getenvalue(env, "SHLVL");
	if (!value)
		return (1);
	setvalue(env, "SHLVL", hb_itoa(hb_atoi(value)+ 1));
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	(void)av;
	ms.e = 0;
	shlvl(env);
	ms.env = envtolist(env);
	ms.p2env = env;
	signal(SIGINT, signals);
	if (ac > 1)
		return (hb_printerr("usage: <./minishell>\n"), 1);
	prompt(&ms);
	ft_exit(ms.e);
}
