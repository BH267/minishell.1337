/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:11:58 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 00:19:20 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	contains_wildcards(const char *str)
{
	while (str && *str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}

int	match_pattern(const char *pattern, const char *string)
{
	if (*pattern == '\0')
		return (*string == '\0');
	if (*pattern == '*')
	{
		return (match_pattern(pattern + 1, string) ||
				(*string != '\0' && match_pattern(pattern, string + 1)));
	}
	if (*string != '\0' && *pattern == *string)
		return (match_pattern(pattern + 1, string + 1));

	return (0);
}

t_match_list	*new_match(char *name)
{
	t_match_list	*match;

	match = (t_match_list *)ft_malloc(sizeof(t_match_list));
	if (!match)
		return (NULL);

	match->name = name;
	match->next = NULL;
	return (match);
}

void	add_match(t_match_list **list, t_match_list *new)
{
	t_match_list	*current;

	if (!list || !new)
		return ;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}
