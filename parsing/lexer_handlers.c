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
	int (i), (in_double_quotes), (in_single_quotes), len, flag;
	i = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	len = hb_strlen(val);
	flag = 0;
	while (i < len)
	{
		help_editmask(val[i], mask[i], flag, i);
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
