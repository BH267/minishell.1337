/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:08:12 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/12 17:04:00 by deepseeko        ###   ########.fr       */
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

int count_quotes(char *str)
{
	int i;
	int count;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

char *dellet_all_quotes(char *str)
{
	int i;
	int j;
	char *res;
	i = 0;
	j = 0;
	res = ft_malloc(sizeof(char) * (hb_strlen(str) - count_quotes(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
char *get_value_with_mask(char mask, t_env *env, char *var)
{
	char *value_var;

	value_var = getfromenv(env, var);

	if (!value_var)
		value_var = hb_strdup("");
	value_var = dellet_all_quotes(value_var);
	if ((mask & 4) != 0)
		value_var = add_quotes(value_var);

	return (value_var);
}

void replace_variable(char **value, char *var, char *expanded_value)
{
	char *new_value;
	int i = 0;
	int j = 0;
	int k = 0;
	int value_len;
	int var_len;
	int expanded_len;
	if (!value || !*value)
		return;
	value_len = hb_strlen(*value);
	var_len = hb_strlen(var);
	if (expanded_value)
		expanded_len = hb_strlen(expanded_value);
	else
		expanded_len = 0;
	new_value = ft_malloc(value_len + expanded_len - var_len + 2);
	if (!new_value)
		return;
	while ((*value)[i] && (*value)[i] != '$')
		new_value[k++] = (*value)[i++];
	if ((*value)[i] == '$')
		i++;
	while ((*value)[i] && (hb_isalnum((*value)[i]) || (*value)[i] == '_'))
		i++;
	if (expanded_value)
		while (expanded_value[j])
			new_value[k++] = expanded_value[j++];
	while ((*value)[i])
		new_value[k++] = (*value)[i++];
	new_value[k] = '\0';
	free(*value);
	*value = new_value;
}

void start_expand_variable(char **value, char *var, t_env *env, char mask)
{
	char *expanded_value;

	expanded_value = get_value_with_mask(mask, env, var);
	if (!expanded_value)
		expanded_value = "";
	replace_variable(value, var, expanded_value);
}
