/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:04:55 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/14 09:19:17 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"

static int	handle_word_get_flag(char c)
{
	if (c == '\'')
		return (MASK_S_QUOTES);
	else if (c == '"')
		return (MASK_QUOTES);
	return (MASK_ORIGIN);
}

int	handle_quoted(const char *input, int i, char **out_val)
{
	char	*val;
	int		ret;

	ret = extract_quoted(input, i, &val);
	if (ret == -1)
		return (-1);
	*out_val = val;
	return (ret);
}

int	handle_operator(const char *input, int i, t_token **lst)
{
	int		oplen;
	char	*val;

	oplen = get_op_len(&input[i]);
	val = hb_substr(input, i, oplen);
	add_token(lst, val, get_operator_type(&input[i]), NULL);
	return (i + oplen);
}

static char *join_and_free(char *s1, char *s2)
{
	if (!s1)
		s1 = hb_strdup("");
	if (!s2)
		s2 = hb_strdup("");
	char *res ;
	res = hb_strjoin(s1, s2);
	return res;
}

static char *make_mask(int len, char flag)
{
    char *mask;
    int i;

    mask = (char *)ft_malloc(len + 1);
    if (!mask) return NULL;

    i = 0;
    while (i < len)
    {
        mask[i] = flag;
        i++;
    }

    mask[len] = '\0';  // Ensure the mask is properly null-terminated
    return mask;
}

static void fill_mask_for_expansion(const char *val, char *mask, int start, int flag)
{
    int i = start;

    if (val[i] == '$')
    {
        mask[i] |= MASK_EXPANSION | flag;  // Mark the $ character
        i++;
        // Mark all characters that are part of the variable name
        while (val[i] && (hb_isalnum(val[i]) || val[i] == '_'))
        {
            mask[i] |= MASK_EXPANSION | flag;
            i++;
        }
    }
}

static int handle_quoted_mask(const char *input, int i, char **out_val, char **out_mask)
{
    char *val;
    int ret;
    char *mask;
    int flag;
    int len;
    int j;

    flag = handle_word_get_flag(input[i]);
    ret = extract_quoted(input, i, &val);
    if (ret == -1)
        return -1;
    len = hb_strlen(val);
    mask = make_mask(len, flag);
    j = 0;
    while (j < len)
    {
        if (val[j] == '$' && flag != MASK_S_QUOTES)
            fill_mask_for_expansion(val, mask, j, flag);
        j++;
    }
    *out_val = val;
    *out_mask = mask;
    return ret;
}

static int handle_unquoted_mask(const char *input, int i, char **out_val, char **out_mask)
{
	int j;
	char *val;
	char *mask;
	int len;
	int k;

	j = i;
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]) && input[i] != '\'' && input[i] != '"')
		i++;
	val = hb_substr(input, j, i - j);
	len = hb_strlen(val);
	mask = make_mask(len, MASK_ORIGIN);
	k = 0;
	while (k < len)
	{
		if (val[k] == '$')
			fill_mask_for_expansion(val, mask, k, 0);
		k++;
	}
	*out_val = val;
	*out_mask = mask;
	return i;
}

int handle_word(const char *input, int i, t_token **lst)
{
    char *val;
    char *mask;
    char *tmp_val;
    char *tmp_mask;
    int ret;
    int j;

    val = hb_strdup("");
    mask = hb_strdup("");
    while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            ret = handle_quoted_mask(input, i, &tmp_val, &tmp_mask);
            if (ret == -1)
                return -1;
            val = join_and_free(val, tmp_val);
            mask = join_and_free(mask, tmp_mask);
            i = ret;
        }
        else
        {
            ret = handle_unquoted_mask(input, i, &tmp_val, &tmp_mask);
            val = join_and_free(val, tmp_val);
            mask = join_and_free(mask, tmp_mask);
            i = ret;
        }
    }

    // Scan the entire token for $ characters and mark them as expansions
    j = 0;
    while (val[j])
    {
        if (val[j] == '$')
        {
            fill_mask_for_expansion(val, mask, j, 0);
        }
        j++;
    }

    add_token(lst, val, TOKEN_WORD, mask);
    return i;
}
