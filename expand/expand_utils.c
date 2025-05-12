/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:08:12 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/12 12:08:28 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char *add_quotes(char *str)
{
	int i;
	char *res;
	i = hb_strlen(str);
	res = ft_malloc(sizeof(char) * (i + 3));
	if (!res)
		return (NULL);
	res[0] = '"';
	i = 0;
	while(str[i])
	{
		res[i + 1] = str[i];
		i++;
	}
	res[i + 1] = '"';
	res[i + 2] = '\0';
	return (res);
}

char *get_value_with_mask(char mask, t_env env, char *var)
{
	char *value_var;

	value_var = getfromenv(env, var);
	if (mask & 4)
		value_var = add_quotes(value_var);
	return (value_var);
}

void replace_variable(char *value, char *var, char *expanded_value)
{
	char *new_value;
	int i;
	int j;
	new_value = ft_malloc(hb_strlen(value) + hb_strlen(expanded_value) - hb_strlen(var) + 1);
	if (!new_value)
		return ;
	i = 0;
	while (value[i] && value[i] != '$')
	{
		new_value[i] = value[i];
		i++;
	}
	j = i;
	while (expanded_value && *expanded_value)
	{
		new_value[i] = *expanded_value;
		i++;
		expanded_value++;
	}
	while (hb_isallnum(value[i]) || value[i] == '_')
		j++;
	while (value[j])
		new_value[i++] = value[j++];
	new_value[i] = '\0';
	value = new_value;
}

void start_expand_variable(char *value, char *var, t_env *env, char mask)
{
	char *expanded_value;

	expanded_value = get_value_with_mask(mask, *env, var);
	if (expanded_value)
	{
		if (mask & 4)
			replace_variable(value, var, expanded_value);
	}
}
