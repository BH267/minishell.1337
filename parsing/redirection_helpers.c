/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:20:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/22 11:16:13 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"

int	fill_redir(t_cmd *cmd, t_token *tok)
{
	if (tok->next->flag == 404)
		add_redirect(&cmd->redirect_list, tok->next->value, tok->type,
			tok->next->value);
	else
		add_redirect(&cmd->redirect_list, tok->next->value, tok->type, NULL);
	return (1);
}

int	is_redir(t_token_type t)
{
	return (t == TOKEN_REDIR_IN || t == TOKEN_REDIR_OUT || t == TOKEN_APPEND
		|| t == TOKEN_HEREDOC);
}
