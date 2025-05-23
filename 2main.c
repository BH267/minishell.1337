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

#include "libhb/libhb.h"
#include "ms.h"

int	promptline(t_ms *ms)
{
	if (!(*(estate())))
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

int	whites(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (hb_isprint(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

int	prompt(t_ms *ms)
{
	t_cmd	*cmd;

	while (1)
	{
		signals(NORMAL);
		if (promptline(ms))
			break ;
		if (!*ms->cmd || whites(ms->cmd))
			continue ;
		add_history(ms->cmd);
		cmd = parsing(ms->cmd, ms->env);
		if (!cmd)
		{
			ms->e = 2;
			continue ;
		}
		ms->e = setes(runcmd(ms, cmd));
	}
	return (setes(ms->e));
}

int	shlvl(char **env)
{
	char	*value;

	if (!env || !*env)
		return (0);
	value = getenvalue(env, "SHLVL");
	if (!value)
		return (1);
	setvalue(env, "SHLVL", hb_itoa(hb_atoi(value)+ 1));
	return (hb_atoi(value) + 1);
}

int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	(void)av;
	ms.e = 0;
	shlvl(env);
	ms.env = envtolist(env);
	ms.p2env = env;
	b2o(1);
	signals(NORMAL);
	if (ac > 1)
		return (hb_printerr("usage: <./minishell>\n"), 1);
	prompt(&ms);
	ft_exit(*(estate()));
}
