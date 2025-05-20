/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:07 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/20 13:15:29 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

static char	*find_variable_name(char *str, int pos)
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

static int	need_expansion(char *str, char *mask)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (hb_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?')
			&& !(mask[i] & MASK_S_QUOTES))
			return (i);
		i++;
	}
	return (-1);
}

static void	handle_expansion(t_token *tok, char *var_name, t_env *env, int pos)
{
	char	*expanded_value;
	char	*new_mask;

	if (!var_name || !tok || !tok->value)
		return ;
	expanded_value = get_value_with_mask(tok->mask[pos], env, var_name);
	if (!expanded_value)
	{
		expanded_value = hb_strdup("");
	}
	new_mask = c_new_mask(expanded_value, tok->mask[pos - 1]);
	update_mask(&tok, new_mask, pos, hb_strlen(var_name),
		hb_strlen(expanded_value));
	replace_variable(&tok, var_name, expanded_value, pos - 1);
	tok->flag = 42;
}

void	treat_red(t_token *tok, t_env *env)
{
	char	*var;
	int		i;

	i = 0;
	if (!tok->next || tok->next->value[0] == '\0')
	{
		tok->flag = 404;
		return ;
	}
	i = need_expansion(tok->next->value, tok->next->mask);
	while (i != -1)
	{
		var = find_variable_name(tok->next->value, i);
		handle_expansion(tok->next, var, env, i + 1);
		if (check_ambiguous(&tok->next, var) == -1)
			return ;
		i = need_expansion(tok->next->value, tok->next->mask);
	}
}

void	expansion_loop(t_token *tokens, t_env *env)
{
	t_token	*tok;
	char	*var_name;
	int		i;

	tok = tokens;
	while (tok)
	{
		if (tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_REDIR_IN
			|| tok->type == TOKEN_APPEND)
		{
			treat_red(tok, env);
			if (tok->next)
				tok = tok->next;
		}
		else if (tok != NULL && tok->type == TOKEN_WORD && tok->value)
		{
			i = need_expansion(tok->value, tok->mask);
			while (i != -1)
			{
				var_name = find_variable_name(tok->value, i);
				handle_expansion(tok, var_name, env, i + 1);
				i = need_expansion(tok->value, tok->mask);
			}
		}
		else
			tok->flag = -42;
		tok = tok->next;
	}
}
