/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:04:55 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/22 11:04:06 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"

int	handle_operator(const char *input, int i, t_token **lst)
{
	int		oplen;
	char	*val;

	oplen = get_op_len(&input[i]);
	val = hb_substr(input, i, oplen);
	add_token(lst, val, get_operator_type(&input[i]), NULL);
	return (i + oplen);
}

static char	*create_zero_mask(int len)
{
	char	*mask;
	int		i;

	mask = (char *)ft_malloc(len + 1);
	if (!mask)
		return (NULL);
	i = 0;
	while (i < len)
	{
		mask[i] = MASK_ORIGIN;
		i++;
	}
	mask[i] = '\0';
	return (mask);
}

void	prnt_mask(int lent, char *mask)
{
	int	i;

	i = 0;
	while (i < lent)
	{
		printf("%d ", (unsigned int)mask[i]);
		i++;
	}
	printf("\n");
}

void	edit_mask(char *val, char *mask)
{
	int	i;
	int	in_double_quotes;
	int	in_single_quotes;
	int	len;
	int	flag;

	i = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	len = hb_strlen(val);
	flag = 0;
	while (i < len)
	{
		if (val[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			if (in_double_quotes)
			{
				mask[i] = flag;
				flag |= MASK_QUOTES;
			}
			else
			{
				flag &= ~MASK_QUOTES;
				mask[i] = flag;
			}
		}
		else if (val[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			if (in_single_quotes)
			{
				mask[i] = flag;
				flag |= MASK_S_QUOTES;
			}
			else
			{
				flag &= ~MASK_S_QUOTES;
				mask[i] = flag;
			}
		}
		else
			mask[i] |= flag;
		i++;
	}
}

int	extract_word_with_mask(const char *input, int i, char **out_val,
		char **out_mask)
{
	char	*val;

	i = extract_word(input, i, &val);
	*out_mask = create_zero_mask(hb_strlen(val));
	edit_mask(val, *out_mask);
	*out_val = val;
	return (i);
}

int	handle_word(const char *input, int i, t_token **lst)
{
	char	*val;
	char	*mask;
	int		ret;

	ret = extract_word_with_mask(input, i, &val, &mask);
	add_token(lst, val, TOKEN_WORD, mask);
	return (ret);
}
