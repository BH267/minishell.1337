/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:07 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/16 13:06:08 by deepseeko        ###   ########.fr       */
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


int count_dolar(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(str[i])
    {
        if (str[i] == '$')
            count++;
        i++;
    }
    printf("count = %d\n", count);
    return (count);
}

static char *find_variable_name(char *str)
{
    int i = 0;
    int j = 0;
    char *var_name;

    if (!str || !str[0] || str[0] != '$')
        return NULL;
    i = 1;
    while (str[i] && (hb_isalnum(str[i]) || str[i] == '_'))
        i++;
    var_name = ft_malloc(sizeof(char) * i);
    if (!var_name)
        return NULL;
    i = 1;
    j = 0;
    while (str[i] && (hb_isalnum(str[i]) || str[i] == '_'))
        var_name[j++] = str[i++];
    var_name[j] = '\0';
    return var_name;
}

static void handle_expansion(t_token *tok, char *var_name, int pos, t_env *env)
{
    char *value;
    char *prefix;
    char *suffix;
    char *expanded;
    char *env_value;

    if (tok->mask && (tok->mask[pos] & MASK_S_QUOTES))
        return;

    env_value = getvalue(env, var_name);
    if (!env_value)
        env_value = "";

    prefix = NULL;
    if (pos > 0)
        prefix = hb_substr(tok->value, 0, pos);
    else
        prefix = hb_strdup("");

    suffix = hb_substr(tok->value, pos + hb_strlen(var_name) + 1,
                      hb_strlen(tok->value) - pos - hb_strlen(var_name) - 1);
    if (!suffix)
        suffix = hb_strdup("");

    expanded = hb_strjoin(prefix, env_value);
    value = hb_strjoin(expanded, suffix);

    free(prefix);
    free(suffix);
    free(expanded);

    free(tok->value);
    tok->value = value;
}

static int is_inside_quotes(char mask) {
    return (mask & MASK_QUOTES) || (mask & MASK_S_QUOTES);
}

static void flood_quotes(char *value, char *mask, int len)
{
    int i, j;
    int in_quotes;
    char quote_type;

    i = 0;
    while (i < len) {
        if ((value[i] == '"' || value[i] == '\'') &&
            ((mask[i] & MASK_QUOTES) || (mask[i] & MASK_S_QUOTES))) {

            if (value[i] == '"')
                quote_type = MASK_QUOTES;
            else
                quote_type = MASK_S_QUOTES;

            j = i + 1;
            while (j < len && !(value[j] == value[i] &&
                  ((mask[j] & MASK_QUOTES) || (mask[j] & MASK_S_QUOTES)))) {
                mask[j] |= quote_type;
                j++;
            }

            if (j < len) {
                i = j + 1;
            } else {
                i++;
            }
        } else {
            i++;
        }
    }

    i = 0;
    while (i < len) {
        if ((mask[i] & MASK_QUOTES) || (mask[i] & MASK_S_QUOTES)) {
            quote_type = mask[i] & (MASK_QUOTES | MASK_S_QUOTES);
            in_quotes = 1;

            j = i;
            while (j < len && in_quotes) {
                if (value[j] == ' ' && is_inside_quotes(mask[j])) {
                    mask[j] = quote_type;
                }
                j++;

                if (j < len && !(mask[j] & quote_type)) {
                    in_quotes = 0;
                }
            }
        }
        i++;
    }

    i = 0;
    while (i < len - 1) {
        if (is_inside_quotes(mask[i]) && is_inside_quotes(mask[i+1])) {
            if ((mask[i] & MASK_QUOTES) && (mask[i+1] & MASK_S_QUOTES)) {
                mask[i+1] |= MASK_QUOTES;
            } else if ((mask[i] & MASK_S_QUOTES) && (mask[i+1] & MASK_QUOTES)) {
                mask[i+1] |= MASK_S_QUOTES;
            }
        }
        i++;
    }
}

char *update_mask(char *value)
{
    int i = 0;
    char quote = 0;
    int len = hb_strlen(value);
    char *mask = (char *)malloc(len + 1);

    if (!mask)
        return NULL;

    i = 0;
    while (i < len)
    {
        mask[i] = 0;
        i++;
    }

    i = 0;
    while (i < len) {
        if (!quote && (value[i] == '\'' || value[i] == '"'))
        {
            quote = value[i];
            if (quote == '\'')
                mask[i] = MASK_S_QUOTES;
            else
                mask[i] = MASK_QUOTES;
            i++;
            continue;
        }
        else if (quote && value[i] == quote) {
            if (quote == '\'')
                mask[i] = MASK_S_QUOTES;
            else
                mask[i] = MASK_QUOTES;
            quote = 0;
            i++;
            continue;
        }

        if (quote) {
            if (quote == '\'')
                mask[i] = MASK_S_QUOTES;
            else
                mask[i] = MASK_QUOTES;
        } else {
            mask[i] = MASK_ORIGIN;

            if (value[i] == '$' && value[i+1] && (hb_isalnum(value[i+1]) || value[i+1] == '_' || value[i+1] == '?'))
                mask[i] = MASK_EXPANSION;
        }
        i++;
    }

    i = 0;
    while (i < len) {
        if (value[i] == ' ' && !(mask[i] & (MASK_QUOTES | MASK_S_QUOTES))) {
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
        if (!((*mask)[data.start] & MASK_S_QUOTES))
            start_expand_variable(value, var, env, (*mask)[data.start]);
        free(var);

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

void reset_mask_for_literal_content(t_token *tok)
{
    int i;
    int len;

    if (!tok || !tok->mask || !tok->value)
        return;

    len = hb_strlen(tok->value);
    i = 0;

    while (i < len)
    {
        if (tok->value[i] == '\'' && (tok->mask[i] & MASK_S_QUOTES))
        {
            i++;

            while (i < len && !(tok->value[i] == '\'' && (tok->mask[i] & MASK_S_QUOTES)))
            {
                tok->mask[i] = MASK_S_QUOTES;
                i++;
            }

            if (i < len && tok->value[i] == '\'' && (tok->mask[i] & MASK_S_QUOTES))
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }
}

void expansion_loop(t_token *tokens, t_env *env)
{
    t_token *tok;
    char *var_name;
    int i;
    int in_single_quotes;

    tok = tokens;
    while (tok)
    {
        if (tok->type == TOKEN_WORD && tok->value)
        {
            if (!tok->mask)
                tok->mask = update_mask(tok->value);

            reset_mask_for_literal_content(tok);

            i = 0;
            in_single_quotes = 0;

            while (tok->value[i])
            {
                if (tok->value[i] == '\'')
                {
                    in_single_quotes = !in_single_quotes;
                    i++;
                    continue;
                }

                if (!in_single_quotes && tok->value[i] == '$' &&
                    tok->value[i+1] && (hb_isalnum(tok->value[i+1]) || tok->value[i+1] == '_' || tok->value[i+1] == '?'))
                {
                    var_name = find_variable_name(tok->value + i);
                    if (var_name)
                    {
                        handle_expansion(tok, var_name, i, env);

                        free(tok->mask);
                        tok->mask = update_mask(tok->value);
                        reset_mask_for_literal_content(tok);

                        i = 0;
                        in_single_quotes = 0;
                        free(var_name);
                        continue;
                    }
                }
                i++;
            }
        }
        tok = tok->next;
    }
}

