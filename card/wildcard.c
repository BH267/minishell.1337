/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:40:25 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 00:19:06 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static void	process_token(t_token **tok)
{
	t_match_list	*matches;
	int				i;

	if (!tok || !*tok || (*tok)->type != TOKEN_WORD)
		return ;
	i = 0;
	while ((*tok)->value[i])
	{
		if ((*tok)->value[i] == '*' && ((*tok)->mask[i] == 0
				|| (*tok)->mask[i] == 1))
		{
			matches = get_matches((*tok)->value);
			if (matches)
			{
				replace_token_with_matches(tok, matches);
			}
			return ;
		}
		i++;
	}
}

t_match_list	*get_matches(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_match_list	*matches;
	t_match_list	*new;

	matches = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			entry = readdir(dir);
		if (match_pattern(pattern, entry->d_name))
		{
			new = new_match(hb_strdup(entry->d_name));
			if (new)
				add_match(&matches, new);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

void	replace_token_with_matches(t_token **tok, t_match_list *matches)
{
	t_match_list	*match;

	t_token (*current), (*next), (*new_token);
	if (!matches)
		return ;
	next = (*tok)->next;
	current = *tok;
	match = matches;
	current->value = hb_strdup(match->name);
	match = match->next;
	while (match)
	{
		new_token = (t_token *)ft_malloc(sizeof(t_token));
		new_token->value = hb_strdup(match->name);
		new_token->type = TOKEN_WORD;
		new_token->mask = (char *)ft_malloc(hb_strlen(match->name) + 1);
		hb_memset(new_token->mask, 0, hb_strlen(match->name) + 1);
		new_token->flag = -42;
		new_token->next = NULL;
		current->next = new_token;
		current = new_token;
		match = match->next;
	}
	current->next = next;
}

void	card(t_token *tokens)
{
	t_token	*tok;

	tok = tokens;
	while (tok)
	{
		process_token(&tok);
		tok = tok->next;
	}
}
