/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:25:28 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/12 08:09:30 by deepseeko        ###   ########.fr       */
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
		signals(NORMAL);
		if (!*ms->cmd)// || signals(NORMAL))
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
	signals(NORMAL);
	if (ac > 1)
		return (hb_printerr("usage: <./minishell>\n"), 1);
	prompt(&ms);
	ft_exit(ms.e);
}
