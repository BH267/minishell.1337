/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:07 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/19 13:52:57 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

typedef struct expand_data
{
	int		start;
	int		end;
}			t_expand_data;

static char	*find_variable_name(char *str, int pos)
{
	int		i;
	int		len;
	char	*var_name;

	i = pos + 1;
	len = 0;
	while (str[i] && (str[i] == '_' || hb_isalnum(str[i])))
	{
		len++;
		i++;
	}
	var_name = hb_substr(str, pos + 1, len);
	return (var_name);
}

char	*get_value_with_mask(char mask, t_env *env, char *var)
{
	char	*value;

	(void)mask;
	value = getfromenv(env, var);
	return (value);
}

char *c_new_mask(char *value, char type)
{
    int i;
    char *new_mask;

    type = (type & ~MASK_EXPANSION) | MASK_EXPANSION;

    i = 0;
    new_mask = (char *)malloc(hb_strlen(value) + 1);
    if (!new_mask)
        return NULL;

    while(value[i])
    {
        new_mask[i] = type;
        i++;
    }
    new_mask[i] = '\0';

    return new_mask;
}


void update_mask(t_token **tok, char *new_mask, int pos, int len, int lent_mask)
{
    int     i;
    int     j;
    char    *updated_mask;
    int     remaining_len;

    if (!tok || !(*tok) || !new_mask)
        return;

    updated_mask = (char *)malloc(hb_strlen((*tok)->value) - len + lent_mask + 1);
    if (!updated_mask)
        return;

    i = 0;
    while (i < pos - 1)  // Stop before $
    {
        updated_mask[i] = (*tok)->mask[i];
        i++;
    }

    j = 0;
    while (j < lent_mask)
    {
        updated_mask[i] = new_mask[j];
        i++;
        j++;
    }

    j = pos + len;

    remaining_len = hb_strlen((*tok)->value) - j;
    int k = 0;
    while (k < remaining_len)
    {
        updated_mask[i] = (*tok)->mask[j + k];
        i++;
        k++;
    }

    updated_mask[i] = '\0';
    (*tok)->mask = updated_mask;
}


void replace_variable(t_token **tok, char *var_name, char *expanded_value, int pos)
{
    char *new_str;
    char *old_value;
    int var_len;

    if (!tok || !(*tok) || !var_name)
        return;

    old_value = (*tok)->value;

    var_len = hb_strlen(var_name) + 1;

    if (!expanded_value)
        expanded_value = "";

    new_str = (char *)malloc(
        hb_strlen(old_value) - var_len + hb_strlen(expanded_value) + 1);

    if (!new_str)
        return;

    hb_strlcpy(new_str, old_value, pos + 1);

    hb_strlcat(new_str, expanded_value,
        pos + hb_strlen(expanded_value) + 1);

    hb_strlcat(new_str, old_value + pos + var_len,
        hb_strlen(old_value) - var_len + hb_strlen(expanded_value) + 1);

    (*tok)->value = new_str;
}

static void handle_expansion(t_token *tok, char *var_name, t_env *env, int pos)
{
    char *expanded_value;
    char *new_mask;

    if (!var_name || !tok || !tok->value)
        return;

    expanded_value = get_value_with_mask(tok->mask[pos], env, var_name);

    if (!expanded_value)
	{
        expanded_value = hb_strdup("");
	}
	new_mask = c_new_mask(expanded_value, tok->mask[pos - 1]);
	update_mask(&tok, new_mask, pos, hb_strlen(var_name) , hb_strlen(expanded_value));
	replace_variable(&tok, var_name, expanded_value, pos - 1);
    tok->flag = 42;
}

static int need_expansion(char *str)
{
    int i = 0;

    if (!str)
		return -1;

    while (str[i])
    {
        if (str[i] == '$' && str[i+1] && (hb_isalnum(str[i + 1]) || str[i + 1] == '_'))
            return i;
        i++;
    }
    return -1;
}

int have_space(char *str)
{
	int i;
	i = 0;

	while(str[i])
	{
		if (is_space(str[i]))
			return (-1);
		i++;
	}
	return (1);
}
void treat_red(t_token *tok , t_env *env)
{
	// char *var;
	(void)env;
	if (!tok->next || tok->next->value[0] == '\0')
	{
		tok->flag = 404;
		return ;
	}
	// if (need_expansion(tok->next) && have_space(get_value_with_mask(NULL, env, tok->next->value))) // 5as nhandli ila da5el leya bezaf $ fi rediredct
	// {
	// 	tok->flag = 404;
	// 	return ;
	// }
	// need logique to handle redirection in case of expansion
}
void	expansion_loop(t_token *tokens, t_env *env)
{
	t_token	*tok;
	char	*var_name;
	int		i;

	tok = tokens;
	while (tok)
	{
		if (tokens->type == TOKEN_REDIR_OUT || tokens->type == TOKEN_REDIR_IN)
		{
			 //check null fi file name and $ expand not have space
			treat_red(tok , env);
			tok = tok->next->next;
		}
		if (tok->type == TOKEN_WORD && tok->value)
		{
			i = need_expansion(tok->value);
			while (i != -1)
			{
				var_name = find_variable_name(tok->value, i);
				handle_expansion(tok, var_name, env, i + 1);
				i = need_expansion(tok->value);
			}
		}
		else
			tok->flag = -42;
		tok = tok->next;
	}
}
