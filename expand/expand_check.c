/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:07 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/21 23:52:26 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

int	have_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_space(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

int	have_space_from_expand(char *str, char *mask)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_space(str[i]) && (mask[i] & MASK_EXPANSION))
			return (-1);
		i++;
	}
	return (1);
}

int	check_ambiguous(t_token **tok, char *var)
{
	if (have_space_from_expand((*tok)->value, (*tok)->mask) == -1)
	{
		(*tok)->value = hb_strdup(var);
		(*tok)->flag = 404;
		return (-1);
	}
	return (1);
}

char	*get_value_with_mask(char mask, t_env *env, char *var)
{
	char	*value;

	(void)mask;
	if (hb_strcmp(var, "?") == 0)
		value = hb_itoa(*(estate()));
	else
		value = getfromenv(env, var);
	return (value);
}
