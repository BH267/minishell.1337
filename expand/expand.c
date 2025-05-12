/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:07 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/12 12:01:22 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"


typedef struct expand_data
{
	int start;
	int end;
} t_expand_data;

char *add_quotes(char *str)
{
	char *res;
	int i;

	i = hb_strlen(str);
	res = ft_malloc(sizeof(char) * (i + 3));
	if (!res)
		return (NULL);
	res[0] = '"';
	i = 0;
	while(str[i])
	{
		res[i + 1] = str[i];
		i++;
	}
	res[i + 1] = '"';
	return (res);
}

char *get_value_with_mask(char mask, t_env env  , char *var)
{
	char *value_var;

	value_var = getfromenv(env, var);
	if (mask & 4)
		value_var = add_quotes(value_var);
	return (value_var);
}

void replace_variable(char *value, char *var, char *expanded_value)
{
	char *new_value;
	int i;
	int j;
	new_value = ft_malloc(hb_strlen(value) + hb_strlen(expanded_value) - hb_strlen(var) + 1);
	if (!new_value)
		return ;
	i = 0;
	while (value[i] && value[i] != '$')
	{
		new_value[i] = value[i];
		i++;
	}
	j = i;
	while (expanded_value && *expanded_value)
	{
		new_value[i] = *expanded_value;
		i++;
		expanded_value++;
	}
	while (hb_isallnum(value[i]) || value[i] == '_')
		j++;
	while (value[j])
		new_value[i++] = value[j++];
	new_value[i] = '\0';
	value = new_value;
}

void start_expand_variable(char *value, char *var, t_env *env, char mask)
{
	char *expanded_value;

	expanded_value = get_value_with_mask(mask, *env, var);
	if (expanded_value)
	{
		if (mask & 4)
			replace_variable(value, var, expanded_value);
	}
}

t_expand_data get_index(const char *value)
{
	t_expand_data data;
	int i = 0;
	data.start = -1;
	data.end = -1;
	while (value && value[i])
	{
		if (value[i] == '$')
		{
			data.start = i;
			i++;
			if (value[i] == '\0')
				break;
			while (value[i] && (hb_isalnum(value[i]) || value[i] == '_'))
				i++;
			data.end = i - 1;
			return data;
		}
		i++;
	}
	return data;
}

void expand_variable(char *value , char *mask , t_env *env)
{
	t_expand_data data;
	int lent;
	char *var;
	data = get_index(value);
	if (data.start == -1 || data.end == -1)
		return ;
	while(data.start != -1)
	{
		var = hb_substr(value, data.start + 1, data.end - data.start);
		start_expand_variable(value, var, env, mask[data.start]);
		*mask = update_mask(value);
		data = get_index(value);
		if (data.start == -1 || data.end == -1)
			break;
	}

}

static void handle_quote_state(const char *value, char *mask, int *i, char *quote)
{
	if (!*quote && (value[*i] == '\'' || value[*i] == '"'))
	{
		*quote = value[*i];
		if (*quote == '\'')
			mask[*i] = MASK_S_QUOTES;
		else if (*quote == '"')
			mask[*i] = MASK_QUOTES;
		else
			mask[*i] = MASK_ORIGIN;
		(*i)++;
	}
	else if (*quote && value[*i] == *quote)
	{
		if (*quote == '\'')
			mask[*i] = MASK_S_QUOTES;
		else if (*quote == '"')
			mask[*i] = MASK_QUOTES;
		else
			mask[*i] = MASK_ORIGIN;
		*quote = 0;
		(*i)++;
	}
}

static void handle_expansion(const char *value, char *mask, int i, char quote)
{
	if (value[i] == '$' && quote != '\'')
	{
		mask[i] |= MASK_EXPANSION;
		int j = i + 1;
		while (value[j] && (hb_isalnum(value[j]) || value[j] == '_'))
		{
			mask[j] |= MASK_EXPANSION;
			j++;
		}
	}
}

char *update_mask(const char *value)
{
	int i = 0;
	char quote = 0;
	int len = hb_strlen(value);
	char *mask = (char *)ft_malloc(len + 1);
	while (i < len)
	{
		handle_quote_state(value, mask, &i, &quote);
		if (i >= len)
			break;
		if (quote == '\'')
			mask[i] = MASK_S_QUOTES;
		else if (quote == '"')
			mask[i] = MASK_QUOTES;
		else
			mask[i] = MASK_ORIGIN;
		handle_expansion(value, mask, i, quote);
		i++;
	}
	mask[len] = '\0';
	return mask;
}

int is_expansion_needed(t_token *tok)
{
	int i;

	i = 0;
	if (tok->mask)
	{
		while (tok->mask[i])
		{
			if (tok->mask[i] & 1)
				return (1);
			i++;
		}
	}
	return (0);
}

void expansion_loop(t_token *tokens , t_env *env)
{
	int i;
	t_token *tok;
	int j;

	i = 0;
	tok = tokens;
	while(tok)
	{
		if (tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_REDIR_IN)
		{

			tok = tok->next;
			continue;
		}
		if (tok->flag == TOKEN_WORD && is_expansion_needed(tok))
			expand_variable(tok->value , tok->mask, env);
		i++;
		tok = tok->next;
	}
}

