/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:25 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/16 15:03:13 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	(void)av;
	ms.e = 0;
	ms.env = env;
	if (ac > 1)
	{
		printf("usage: <./minishell>\n");
		return (1);
	}
	while (1)
	{
	//	cmd = readline("𝚖𝚒𝚗𝚒𝚜𝚑𝚎𝚕𝚕>");
			//ms.cmd = readline("\033[38;2;0;255;0mмιηιѕнєℓℓ> \033[0m");
			//ms.cmd = readline("\033[38;2;255;0;0mмιηιѕнєℓℓ> \033[0m");
		if (!ms.e)
			ms.cmd = readline("\033[0;36mмιηιѕнєℓℓ\033[0;32m❱ \033[0m");
		else
			ms.cmd = readline("\033[0;36mмιηιѕнєℓℓ\033[0;31m❱ \033[0m");
		if (!ms.cmd)
		{
			printf("exit\n");
			break ;
		}
		if (!*ms.cmd)
			continue ;
		add_history(ms.cmd);
		ms.e = execute(&ms);
	}
	ft_exit(ms.e);
}
