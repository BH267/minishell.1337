/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:50:36 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 20:19:11 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

static int	need_expansion_true(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && ((hb_isalnum(str[i + 1])
					|| str[i + 1] == '_' || str[i + 1] == '?')
				|| hb_isdigit(str[i + 1])))
			return (i);
		i++;
	}
	return (-1);
}

static char	*find_variable_name_herdoc(char *str, int pos)
{
	int		i;
	int		len;
	char	*var_name;

	i = pos + 1;
	len = 0;
	if (str[i] == '?')
		return (hb_strdup("?"));
	if (hb_isdigit(str[i]))
		return (hb_substr(str, i, 1));
	while (str[i] && (str[i] == '_' || hb_isalnum(str[i])))
	{
		len++;
		i++;
	}
	var_name = hb_substr(str, pos + 1, len);
	return (var_name);
}

void	replace_variable_herdoc(char **str, char *var_name,
		char *expanded_value, int pos)
{
	char	*new_str;
	char	*old_value;
	int		var_len;

	if (!str || !*str || !var_name)
		return ;
	old_value = *str;
	var_len = hb_strlen(var_name) + 1;
	if (!expanded_value)
		expanded_value = "";
	new_str = (char *)ft_malloc(hb_strlen(old_value) - var_len
			+ hb_strlen(expanded_value) + 1);
	if (!new_str)
		return ;
	hb_strlcpy(new_str, old_value, pos + 1);
	hb_strlcat(new_str, expanded_value, pos + hb_strlen(expanded_value) + 1);
	hb_strlcat(new_str, old_value + pos + var_len, hb_strlen(old_value)
		- var_len + hb_strlen(expanded_value) + 1);
	*str = new_str;
}

char	*expand_herdoce(char *str, t_env *env)
{
	int		i;
	int		flag;
	char	*var_name;
	char	*expanded_value;

	i = 0;
	flag = need_expansion_true(str);
	while (flag != -1)
	{
		var_name = find_variable_name_herdoc(str, flag);
		expanded_value = get_value_with_mask(*str, env, var_name);
		if (!expanded_value)
			expanded_value = "";
		replace_variable_herdoc(&str, var_name, expanded_value, flag);
		flag = need_expansion_true(str);
	}
	return (str);
}
