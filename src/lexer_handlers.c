/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:04:55 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/25 17:16:47 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/token.h"
#include "../libhb/libhb.h"
#include "../ft_malloc/ft_malloc.h"

int	handle_quoted(const char *input, int i, t_token **lst)
{
	char	*val;
	int		ret;

	ret = extract_quoted(input, i, &val);
	if (ret == -1)
		return (-1);
	add_token(lst, val, TOKEN_WORD);
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
	int		ret;

	ret = extract_word(input, i, &val);
	add_token(lst, val, TOKEN_WORD);
	return (ret);
}
