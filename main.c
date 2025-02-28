/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:05:14 by habenydi          #+#    #+#             */
/*   Updated: 2025/02/28 18:17:08 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	main(int ac)
{
	char	*cmd;

	if (ac > 1)
		ft_printf("\033[38;2;255;255;0	usage : just < ./minishell >\n\033[0m");
	while (1)
	{
		cmd = readline("minishel> ");
		ft_printf("%s", cmd);
	}
}
