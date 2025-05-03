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

int	prompt(t_ms *ms)
{
	t_cmd	*cmd;

	while (1)
	{
		if (!ms->e)
			ms->cmd = readline("\033[0;36mмιηιѕнєℓℓ \033[0;32m❱ \033[0m");
		else
			ms->cmd = readline("\033[0;36mмιηιѕнєℓℓ \033[0;31m❱ \033[0m");
		if (!ms->cmd)
		{
			hb_printerr("exit\n");
			break ;
		}
		if (!*ms->cmd)
			continue ;
		add_history(ms->cmd);
		cmd = parsing(ms->cmd);
		if (!cmd)
		{
			ms->e = 2;
			continue ;
		}
		ms->e = pip(ms, cmd);
	}
	return (ms->e);
}

int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	(void)av;
	ms.e = 0;
	ms.env = envtolist(env);
	ms.p2env = env;
	if (ac > 1)
		return (hb_printerr("usage: <./minishell>\n"), 1);
	prompt(&ms);
	ft_exit(ms.e);
}
