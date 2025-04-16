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
	char *cmd;

	(void)av;
	if (ac > 1)
	{
		printf("usage: <./minishell>\n");
		return (1);
	}
	while (1)
	{
	//	cmd = readline("𝚖𝚒𝚗𝚒𝚜𝚑𝚎𝚕𝚕>");
		cmd = readline("мιηιѕнєℓℓ>");
		if (!cmd)
		{
			printf("exit\n");
			break ;
		}
		add_history(cmd);
		execute(cmd, env);
	}
	ft_exit(0);
}
