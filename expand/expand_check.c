/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:07 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/21 12:54:38 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

/**
 * Checks if a string contains spaces
 * Returns -1 if the string has spaces, 1 otherwise
 */
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

/**
 * Checks if a string has spaces that were added during expansion
 * Returns -1 if the string has spaces from expansion, 1 otherwise
 */
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

/**
 * Checks if a token is ambiguous after expansion
 * Returns -1 if ambiguous, 1 otherwise
 */
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

/**
 * Gets the value of a variable based on mask
 * Returns the expanded value or NULL if not found
 */
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
