/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:07 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/23 15:02:38 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

char	*find_variable_name(char *str, int pos)
{
	int		i;
	int		len;
	char	*var_name;

	i = pos + 1;
	len = 0;
	if (str[i] == '?')
		return (hb_strdup("?"));
	while (str[i] && (str[i] == '_' || hb_isalnum(str[i])))
	{
		len++;
		i++;
	}
	var_name = hb_substr(str, pos + 1, len);
	return (var_name);
}

int	need_expansion(char *str, char *mask)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (hb_isalnum(str[i + 1]) || str[i
					+ 1] == '_' || str[i + 1] == '?')
			&& !(mask[i] & MASK_S_QUOTES)
			&& !(mask[i] & MASK_EXPANSION))
			return (i);
		i++;
	}
	return (-1);
}

void	handle_expansion(t_token *tok, char *var_name, t_env *env, int pos)
{
	char	*expanded_value;
	char	*new_mask;
	int		*data;

	data = ft_malloc(sizeof(int) * 3);
	if (!var_name || !tok || !tok->value)
		return ;
	expanded_value = get_value_with_mask(tok->mask[pos], env, var_name);
	if (!expanded_value)
		expanded_value = hb_strdup("");
	new_mask = c_new_mask(expanded_value, tok->mask[pos - 1]);
	update_mask(&tok, new_mask, pos, hb_strlen(var_name),
		hb_strlen(expanded_value));
	replace_variable(&tok, var_name, expanded_value, pos - 1);
	tok->flag = 42;
}

void	expansion_loop(t_token *tokens, t_env *env)
{
	t_token	*tok;

	tok = tokens;
	while (tok)
	{
		if (tok->type == TOKEN_HEREDOC)
		{
			tok->flag = -42;
			tok = tok->next;
			if (tok)
				tok = tok->next;
			continue ;
		}
		if (tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_REDIR_IN
			|| tok->type == TOKEN_APPEND)
			handle_redirection(&tok, env);
		else if (tok->type == TOKEN_WORD && tok->value)
			handle_word_token(tok, env);
		else
			tok->flag = -42;
		tok = tok->next;
	}
}
