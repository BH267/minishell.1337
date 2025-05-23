/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:08:12 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/23 21:55:03 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_data_splited	*init_split_data(t_token *token)
{
	t_data_splited	*data;
	int				count_args;

	count_args = count_args_using_mask(token);
	data = (t_data_splited *)ft_malloc(sizeof(t_data_splited));
	if (!data)
		return (NULL);
	data->args = (char **)ft_malloc(sizeof(char *) * (count_args + 1));
	data->mask_args = (char **)ft_malloc(sizeof(char *) * (count_args + 1));
	if (!data->args || !data->mask_args)
		return (NULL);
	return (data);
}

static void	process_token(t_data_splited *data, t_token *token, int *j)
{
	int				i;
	int				max;
	int				in_word;
	t_word_params	wp;

	i = 0;
	in_word = 0;
	max = hb_strlen(token->value);
	init_word_params(&wp, data, token, j);
	while (i < max)
	{
		process_token_word(&wp, &in_word, i);
		i++;
	}
	handle_last_word(&wp, in_word, i);
}

t_data_splited	*split_args(t_token *token)
{
	t_data_splited	*data;
	int				j;

	data = init_split_data(token);
	if (!data)
		return (NULL);
	j = 0;
	process_token(data, token, &j);
	data->args[j] = NULL;
	data->mask_args[j] = NULL;
	return (data);
}
