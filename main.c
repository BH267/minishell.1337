/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:25 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/27 17:45:40 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	parsing(char *cmdl);

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("Enter command to parse (or 'exit'): ");
		if (!line)
			break;
		if (!*line)
		{
			free(line);
			continue;
		}
		if (!strcmp(line, "exit"))
		{
			free(line);
			break;
		}
		add_history(line);
		parsing(line);
		free(line);
	}
	return (0);
}
