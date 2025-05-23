/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:07:12 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/23 15:07:34 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_token	*help_rtwm(t_token *nt, t_match_list *match)
{
	nt = (t_token *)ft_malloc(sizeof(t_token));
	nt->value = hb_strdup(match->name);
	nt->type = TOKEN_WORD;
	nt->mask = (char *)ft_malloc(hb_strlen(match->name) + 1);
	nt->mask = set_mask_expa(nt);
	nt->flag = 200;
	nt->next = NULL;
	return (nt);
}
