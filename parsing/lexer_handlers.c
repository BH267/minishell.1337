/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:04:55 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/08 13:49:35 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ft_malloc/ft_malloc.h"

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
	add_token(lst, val, get_operator_type(&input[i]));
	return (i + oplen);
}

int	handle_word(const char *input, int i, t_token **lst)
{
	char	*val;
	char	*tmp;
	int		ret;

	val = NULL;
	tmp = NULL;
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			ret = handle_quoted(input, i, &tmp);
			if (ret == -1)
				return (-1);
			if (!val)
				val = hb_strdup("");
			char *joined = hb_strjoin(val, tmp);
			val = joined;
			free(tmp);
			i = ret;
		}
		else
		{
			int j = i;
			while (input[i] && !is_space(input[i]) && !is_operator(input[i])
				&& input[i] != '\'' && input[i] != '"')
				i++;
			tmp = hb_substr(input, j, i - j);
			if (!val)
				val = hb_strdup("");
			char *joined = hb_strjoin(val, tmp);

			val = joined;
			free(tmp);
		}
	}
	add_token(lst, val, TOKEN_WORD);
	return (i);
}
