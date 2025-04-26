/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:44:04 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/26 02:00:51 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ms.h"
#include "header/lexer_token.h"
#include <stdio.h>

// Helper to print tokens (for debug)
static void print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("[type=%d, value='%s']\n", tok->type, tok->value);
		tok = tok->next;
	}
}

// Helper to print parsed command structure (for debug)
static void print_cmds(t_cmd *cmd)
{
	int i;
	while (cmd)
	{
		printf("Command:\n");
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("  arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		if (cmd->infile)
			printf("  infile: %s\n", cmd->infile);
		if (cmd->outfile)
			printf("  outfile: %s (append=%d)\n", cmd->outfile, cmd->append);
		cmd = cmd->next;
	}
}

void	parsing(char *cmdl)
{
	t_token *tokens;
	t_cmd *cmds;

	tokens = lexer(cmdl);
	printf("Tokens:\n");
	print_tokens(tokens);
	cmds = tokenizer(tokens);
	printf("\nParsed commands:\n");
	print_cmds(cmds);
}
