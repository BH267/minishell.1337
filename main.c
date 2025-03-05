/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:05:14 by habenydi          #+#    #+#             */
/*   Updated: 2025/03/05 07:46:46 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/mini.h"


void	init_command(void)
{
	char	*line;
	char	**command;
	int		i;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		command = ft_split(line, ' ');
		i = 0;
		while (command[i])
		{
			ft_printf("command[%d] = %s\n", i, command[i]);
			i++;
		}
	}
}

void te(e_code x)
{
	if (x == CMD)
		printf("CMD\n");
	else
		printf("ikhjab\n");

}

int main(int ac, char**av, char**envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	// init_command();
	te(AND);
}
/*



allo alloc (char*) "ls      -a" > out
["ls      -a"]
[>]
[out]
NULL
*/
