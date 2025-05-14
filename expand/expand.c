/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:07 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/14 05:43:40 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"


typedef struct expand_data
{
	int start;
	int end;
} t_expand_data;

static void handle_quote_state(const char *value, char *mask, int *i, char *quote)
{
	if (!*quote && (value[*i] == '\'' || value[*i] == '"'))
    {
	    *quote = value[*i];
		if (*quote == '\'') {
			mask[*i] = MASK_S_QUOTES;
        } else
            mask[*i] = MASK_QUOTES;
        (*i)++;
    } else if (*quote && value[*i] == *quote) {
        if (*quote == '\'') {
            mask[*i] = MASK_S_QUOTES;
        } else {
            mask[*i] = MASK_QUOTES;
        }
        *quote = 0;
        (*i)++;
    } else if (*quote) {
        if (*quote == '\'') {
            mask[*i] = MASK_S_QUOTES;
        } else {
            mask[*i] = MASK_QUOTES;
        }
        (*i)++;
    }
}

static void handle_expansion(const char *value, char *mask, int i, char quote)
{
    if (value[i] == '$' && quote != '\'') {
        mask[i] |= MASK_EXPANSION;
        int j = i + 1;
        while (value[j] && (hb_isalnum(value[j]) || value[j] == '_')) {
            mask[j] |= MASK_EXPANSION;
            j++;
        }
    }
}

static void flood_quotes(char *value, char *mask, int len)
{
    int i = 0;
    int start, end;
    char current_mask;
    while (i < len)
    {
        if ((mask[i] & MASK_QUOTES) == 0 && (mask[i] & MASK_S_QUOTES) == 0)
        {
            i++;
            continue;
        }
        start = i;
        current_mask = mask[i] & (MASK_QUOTES | MASK_S_QUOTES);
        while (i < len && (mask[i] & current_mask))
            i++;

        end = i - 1;
        i = start;
        while (i > 0 && !is_space(value[i-1]) && value[i-1] != '"' && value[i-1] != '\'')
        {
            i--;
            mask[i] |= current_mask;
        }
        i = end + 1;
        while (i < len && !is_space(value[i]) && value[i] != '"' && value[i] != '\'')
        {
            mask[i] |= current_mask;
            i++;
        }
    }
}

char *update_mask(char *value)
{
    int i = 0;
    char quote = 0;
    int len = hb_strlen(value);
    char *mask = (char *)malloc(len + 1);

    while (i <= len) {
        handle_quote_state(value, mask, &i, &quote);

        if (i >= len) break;
        if (quote == '\'')
            mask[i] = MASK_S_QUOTES;
        else if (quote == '"')
            mask[i] = MASK_QUOTES;
        else
            mask[i] = MASK_ORIGIN;

        handle_expansion(value, mask, i, quote);
        i++;
    }

    i = 0;
    while (i < len) {
        if (value[i] == ' ' && mask[i] != MASK_EXPANSION) {
            mask[i] = MASK_ORIGIN;
        }
        i++;
    }
    flood_quotes(value, mask, len);

    mask[len] = '\0';
    return mask;
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

void expand_variable(char **value, char **mask, t_env *env)
{
    t_expand_data data;
    char *var;
    char *new_mask;
    data = get_index(*value);
    if (data.start == -1 || data.end == -1)
		return;
    while (data.start != -1)
	{
        var = hb_substr(*value, data.start + 1, data.end - data.start);
        if (((*mask)[data.start] & MASK_EXPANSION) != 0)
            start_expand_variable(value, var, env, (*mask)[data.start]);
        new_mask = update_mask(*value);
        free(*mask);
        *mask = new_mask;

        data = get_index(*value);
        if (data.start == -1 || data.end == -1) break;
    }
}



int is_expansion_needed(t_token *tok)
{
	int i;
	int lent;

	i = 0;
	lent = hb_strlen(tok->value);
	while (i <= lent)
	{
		if ((tok->mask[i] & MASK_EXPANSION) != 0 && (tok->mask[i] & MASK_S_QUOTES ) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void expansion_loop(t_token *tokens , t_env *env)
{
	t_token *tok;

	tok = tokens;
	while(tok)
	{
		if (tok->type == TOKEN_WORD && is_expansion_needed(tok))
		{
			expand_variable(&tok->value, &tok->mask, env);
			tok->flag = 42;
		}
		else
			tok->flag = -42;
		tok = tok->next;
	}
}

