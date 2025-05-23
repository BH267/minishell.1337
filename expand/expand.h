/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:38 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/23 22:22:15 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../binsutils.h"
# include "../header/lexer_token.h"

typedef struct data_splited
{
	char			**args;
	char			**mask_args;
}					t_data_splited;

typedef struct expand_data
{
	int				start;
	int				end;
}					t_expand_data;

typedef struct s_word_params
{
	int				start;
	int				*in_word;
	int				i;
	int				*j;
	t_data_splited	*data;
	t_token			*token;
}					t_word_params;

typedef struct s_suffix_copy
{
	char			*dst;
	int				dst_pos;
	char			*src;
	int				src_pos;
	int				len;
}					t_suffix_copy;

/* expand.c */
void				expansion_loop(t_token *tokens, t_env *env);
void				treat_red(t_token *tok, t_env *env);

/* expand_mask.c */
char				*c_new_mask(char *value, char type);
void				update_mask(t_token **tok, char *new_mask, int pos,
						t_expand_data len_data);
void				replace_variable(t_token **tok, char *var_name,
						char *expanded_value, int pos);
void				copy_suffix(t_suffix_copy *sc);

/* expand_mask_utils.c */
void				copy_prefix_mask(char *dst, char *src, int prefix_len);
int					copy_new_mask(char *dst, char *src, int pos, int len);
void				copy_suffix(t_suffix_copy *sc);

/* expand_utils.c */
int					count_args_using_mask(t_token *token);
char				*submem(char *str, int start, int len);
t_data_splited		*split_args(t_token *token);

/* expand_process_utils.c */
void				init_word_params(t_word_params *wp, t_data_splited *data,
						t_token *token, int *j);
void				process_token_word(t_word_params *wp, int *in_word, int i);
void				handle_last_word(t_word_params *wp, int in_word, int i);

/* expand_check.c */
int					have_space(char *str);
int					have_space_from_expand(char *str, char *mask);
int					check_ambiguous(t_token **tok, char *var);
char				*get_value_with_mask(char mask, t_env *env, char *var);

/* expand herdoc */
char				*expand_herdoce(char *str, t_env *env);

/* expand loop utils */
void				treat_red(t_token *tok, t_env *env);
void				handle_redirection(t_token **tok, t_env *env);
void				handle_word_token(t_token *tok, t_env *env);
void				handle_redirection(t_token **tok, t_env *env);
char				*find_variable_name(char *str, int pos);
int					need_expansion(char *str, char *mask);
void				handle_expansion(t_token *tok, char *var_name, t_env *env,
						int pos);

/* split args utils */
int					count_args_using_mask(t_token *token);
char				*submem(char *str, int start, int len);

/* Function declarations for expand_handle_word.c */
int					is_word_start(t_token *token, int i, int in_word);
int					is_word_end(t_token *token, int i, int in_word);
void				handle_token_char(t_word_params *wp);
void				store_word(t_word_params *wp);

/* just bach n9ad norm dyal l5ra */
char				*c_new_mask(char *value, char type);
void				copy_prefix_mask(char *dst, char *src, int prefix_len);

#endif
