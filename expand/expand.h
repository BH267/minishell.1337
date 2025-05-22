/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:38 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/22 13:10:42 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../header/lexer_token.h"
# include "../binsutils.h"

typedef struct data_splited
{
	char	**args;
	char	**mask_args;
}	t_data_splited;

typedef struct expand_data
{
	int		start;
	int		end;
}			t_expand_data;

/* expand.c */
void				expansion_loop(t_token *tokens, t_env *env);
void				treat_red(t_token *tok, t_env *env);

/* expand_mask.c */
char				*c_new_mask(char *value, char type);
void				update_mask(t_token **tok, char *new_mask, int pos,
						int len, int lent_mask);
void				replace_variable(t_token **tok, char *var_name,
						char *expanded_value, int pos);

/* expand_utils.c */
int					count_args_using_mask(t_token *token);
char				*submem(char *str, int start, int len);
t_data_splited		*split_args(t_token *token);

/* expand_check.c */
int					have_space(char *str);
int					have_space_from_expand(char *str, char *mask);
int					check_ambiguous(t_token **tok, char *var);
char				*get_value_with_mask(char mask, t_env *env, char *var);

/* expand herdoc */
char	*expand_herdoce(char *str , t_env *env);




/* expand loop utils */
void	treat_red(t_token *tok, t_env *env);
void	handle_redirection(t_token **tok, t_env *env);
void	handle_word_token(t_token *tok, t_env *env);
void	handle_redirection(t_token **tok, t_env *env);
char	*find_variable_name(char *str, int pos);
int		need_expansion(char *str, char *mask);
void	handle_expansion(t_token *tok, char *var_name, t_env *env, int pos);
#endif
