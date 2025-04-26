/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:58:47 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/26 02:07:45 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../libhb/libhb.h"
#include "../ft_malloc/ft_malloc.h"
#include "stddef.h"

int		count_args(t_token *lst);
char	**tokens_to_args(t_token *lst, int n);
int		is_redir(t_token_type t);
int		fill_redir(t_cmd *cmd, t_token *tok);
t_cmd	*new_cmd(void);

static void	process_args(t_cmd *curr, t_token **tok)
{
	int	ac;

	ac = count_args(*tok);
	if (ac)
	{
		curr->args = tokens_to_args(*tok, ac);
		while (ac--)
			*tok = (*tok)->next;
	}
}

static void	process_redir(t_cmd *curr, t_token **tok)
{
	while (*tok && is_redir((*tok)->type))
	{
		fill_redir(curr, *tok);
		*tok = (*tok)->next;
		if (*tok)
			*tok = (*tok)->next;
	}
}

static void	process_pipe(t_cmd **curr, t_token **tok)
{
	if (*tok && (*tok)->type == TOKEN_PIPE)
	{
		(*curr)->next = new_cmd();
		*curr = (*curr)->next;
		*tok = (*tok)->next;
	}
}

static void	process_tokens(t_cmd *curr, t_token **tok)
{
	process_args(curr, tok);
	process_redir(curr, tok);
	process_pipe(&curr, tok);
}

t_cmd	*tokenizer(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_token	*tok;

	if (!tokens)
		return (NULL);
	head = new_cmd();
	curr = head;
	tok = tokens;
	while (tok)
	{
		process_tokens(curr, &tok);
	}
	return (head);
}
