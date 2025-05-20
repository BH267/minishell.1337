/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_mask.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 00:00:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/20 13:15:29 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

char	*c_new_mask(char *value, char type)
{
	int		i;
	char	*new_mask;

	type = (type & ~MASK_EXPANSION) | MASK_EXPANSION;
	i = 0;
	new_mask = (char *)malloc(hb_strlen(value) + 1);
	if (!new_mask)
		return (NULL);
	while (value[i])
	{
		new_mask[i] = type;
		i++;
	}
	new_mask[i] = '\0';
	return (new_mask);
}

void	update_mask(t_token **tok, char *new_mask, int pos, int len, int lent_mask)
{
	int		i;
	int		j;
	char	*updated_mask;
	int		remaining_len;
	int		k;

	if (!tok || !(*tok) || !new_mask)
		return ;
	updated_mask = (char *)malloc(hb_strlen((*tok)->value) - len + lent_mask + 1);
	if (!updated_mask)
		return ;
	i = 0;
	while (i < pos - 1)
	{
		updated_mask[i] = (*tok)->mask[i];
		i++;
	}
	j = 0;
	while (j < lent_mask)
		updated_mask[i++] = new_mask[j++];
	j = pos + len;
	remaining_len = hb_strlen((*tok)->value) - j;
	k = 0;
	while (k < remaining_len)
		updated_mask[i++] = (*tok)->mask[j + k++];
	updated_mask[i] = '\0';
	(*tok)->mask = updated_mask;
}

void	replace_variable(t_token **tok, char *var_name, char *expanded_value, int pos)
{
	char	*new_str;
	char	*old_value;
	int		var_len;

	if (!tok || !(*tok) || !var_name)
		return ;
	old_value = (*tok)->value;
	var_len = hb_strlen(var_name) + 1;
	if (!expanded_value)
		expanded_value = "";
	new_str = (char *)malloc(
			hb_strlen(old_value) - var_len + hb_strlen(expanded_value) + 1);
	if (!new_str)
		return ;
	hb_strlcpy(new_str, old_value, pos + 1);
	hb_strlcat(new_str, expanded_value,
		pos + hb_strlen(expanded_value) + 1);
	hb_strlcat(new_str, old_value + pos + var_len,
		hb_strlen(old_value) - var_len + hb_strlen(expanded_value) + 1);
	(*tok)->value = new_str;
}
