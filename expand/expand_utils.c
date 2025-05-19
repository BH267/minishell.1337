/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:08:12 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/19 11:47:25 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	count_args_using_mask(t_token *token)
{
	int	i;
	int	count_args;
	int	max;
	int	in_word;

	i = 0;
	count_args = 0;
	in_word = 0;
	max = hb_strlen(token->value);
	while (i < max)
	{
		if (token->mask[i] == MASK_EXPANSION && !is_space(token->value[i]))
		{
			if (!in_word)
			{
				count_args++;
				in_word = 1;
			}
		}
		else if (token->mask[i] == MASK_EXPANSION && is_space(token->value[i]))
			in_word = 0;
		else if (!in_word)
		{
			count_args++;
			in_word = 1;
		}
		i++;
	}
	return (count_args);
}

char *submem(char *str, int start , int len)
{
	char	*sub;
	int		i;

	sub = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

t_data_splited	*split_args(t_token *token)
{
	t_data_splited	*data;
	int		i;
	int		j;
	int		count_args;
	int		start;
	int		max;
	int		in_word;

	count_args = count_args_using_mask(token);
	data = (t_data_splited *)ft_malloc(sizeof(t_data_splited));
	if (!data)
		return (NULL);
	data->args = (char **)ft_malloc(sizeof(char *) * (count_args + 1));
	data->mask_args = (char **)ft_malloc(sizeof(char *) * (count_args + 1));
	if (!data->args || !data->mask_args)
		return (NULL);
	i = 0;
	j = 0;
	in_word = 0;
	max = hb_strlen(token->value);
	while (i < max)
	{
		if ((token->mask[i] == MASK_EXPANSION && !is_space(token->value[i]))
			|| (token->mask[i] != MASK_EXPANSION && !in_word))
		{
			if (!in_word)
			{
				start = i;
				in_word = 1;
			}
		}
		else if (token->mask[i] == MASK_EXPANSION && is_space(token->value[i]))
		{
			if (in_word)
			{
				data->mask_args[j] = submem(token->mask, start, i - start);
				data->args[j++] = hb_substr(token->value, start, i - start);
				in_word = 0;
			}
		}
		i++;
	}
	if (in_word)
	{
		data->mask_args[j] = submem(token->mask, start, i - start);
		data->args[j++] = hb_substr(token->value, start, i - start);
	}
	data->args[j] = NULL;
	data->mask_args[j] = NULL;
	return (data);
}

// t_token	*new_token(char *value, t_token **tok )
// {
// 	t_token	*new;

// 	new = (t_token *)ft_malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	new->value = value;
// 	new->type = (*tok)->type;
// 	new->mask = (*tok)->mask;
// 	new->next = NULL;
// 	return (new);
// }

// void extract_tokens(t_token **tok, char **args)
// {
// 	t_token	*curent;
// 	t_token *next;
// 	int		i;
// 	int		max;

// 	i = 0;
// 	curent = *tok;
// 	next = (*tok)->next;
// 	max = count_args_using_mask(*tok);
// 	while (i < max)
// 	{

// 	}
// 	(*tok)->next = next;
// }

// void	field_spliting_with_mask(t_token **tok)
// {
// 	t_token	*curent;
// 	char	**args;
// 	int		max;
// 	int		i;

// 	i = 0;
// 	curent = *tok;
// 	while (curent)
// 	{
// 		args = split_args(*tok);
// 		if (args[1] != NULL )
// 			extract_tokens(tok , args);
// 		curent = curent->next;
// 	}
// }
