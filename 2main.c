/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:25:28 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/20 00:38:41 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	promptline(t_ms *ms)
{
	if (!ms->e)
		ms->cmd = readline(BLUE"мιηιѕнєℓℓ "GREEN"❱ "DFLTCOL);
	else
		ms->cmd = readline(BLUE"мιηιѕнєℓℓ "RED"❱ "DFLTCOL);
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
		signals(NORMAL);
		*(estate()) = ms->e;
	 	ms->e = *(estate());
		if (promptline(ms))
			break ;
		if (!*ms->cmd)
			continue ;
		add_history(ms->cmd);
		cmd = parsing(ms->cmd, ms->env);
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
