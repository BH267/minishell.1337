/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_mask.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 00:00:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 22:22:25 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

int	copy_new_mask(char *dst, char *src, int pos, int len)
{
	int	j;
	int	i;

	j = 0;
	i = pos;
	while (j < len)
	{
		dst[i++] = src[j++];
	}
	return (i);
}

void	copy_suffix(t_suffix_copy *sc)
{
	int	k;

	k = 0;
	while (k < sc->len)
	{
		sc->dst[sc->dst_pos++] = sc->src[sc->src_pos + k++];
	}
	sc->dst[sc->dst_pos] = '\0';
}

void	update_mask(t_token **tok, char *new_mask, int pos,
		t_expand_data len_data)
{
	char			*updated_mask;
	int				i;
	int				remaining_len;
	t_suffix_copy	sc;

	if (!tok || !(*tok) || !new_mask)
		return ;
	updated_mask = (char *)ft_malloc(hb_strlen((*tok)->value) - len_data.start
			+ len_data.end + 1);
	if (!updated_mask)
		return ;
	copy_prefix_mask(updated_mask, (*tok)->mask, pos - 1);
	i = copy_new_mask(updated_mask, new_mask, pos - 1, len_data.end);
	remaining_len = hb_strlen((*tok)->value) - (pos + len_data.start);
	sc.dst = updated_mask;
	sc.dst_pos = i;
	sc.src = (*tok)->mask;
	sc.src_pos = pos + len_data.start;
	sc.len = remaining_len;
	copy_suffix(&sc);
	(*tok)->mask = updated_mask;
}

void	replace_variable(t_token **tok, char *var_name, char *expanded_value,
		int pos)
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
	new_str = (char *)ft_malloc(hb_strlen(old_value) - var_len
			+ hb_strlen(expanded_value) + 1);
	if (!new_str)
		return ;
	hb_strlcpy(new_str, old_value, pos + 1);
	hb_strlcat(new_str, expanded_value, pos + hb_strlen(expanded_value) + 1);
	hb_strlcat(new_str, old_value + pos + var_len, hb_strlen(old_value)
		- var_len + hb_strlen(expanded_value) + 1);
	(*tok)->value = new_str;
}
