/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_lh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:23:43 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/23 15:25:01 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"

int	handle_operator(const char *input, int i, t_token **lst)
{
	int		oplen;
	char	*val;

	oplen = get_op_len(&input[i]);
	val = hb_substr(input, i, oplen);
	add_token(lst, val, get_operator_type(&input[i]), NULL);
	return (i + oplen);
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

void	help_help_em(int *idt, int *flag, char *mask)
{
	*idt = !*idt;
	if (*idt)
	{
		*mask = *flag;
		*flag |= MASK_QUOTES;
	}
	else
	{
		*flag &= ~MASK_QUOTES;
		*mask = *flag;
	}
}

void	help_help_em2(int *ist, int *flag, char *mask)
{
	*ist = !*ist;
	if (*ist)
	{
		*mask = *flag;
		*flag |= MASK_S_QUOTES;
	}
	else
	{
		*flag &= ~MASK_S_QUOTES;
		*mask = *flag;
	}
}

void	help_editmask(char val, char mask, int flag, int reset)
{
	static int	indquot;
	static int	insquot;

	if (!reset)
	{
		indquot = 0;
		insquot = 0;
	}
	if (val == '"' && !insquot)
		help_help_em(&indquot, &flag, &mask);
	else if (val == '\'' && !indquot)
		help_help_em2(&insquot, &flag, &mask);
	else
		mask |= flag;
}
