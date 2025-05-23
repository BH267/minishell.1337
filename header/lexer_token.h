/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:11:42 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/21 12:43:14 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOKEN_H
# define LEXER_TOKEN_H

# include "../libhb/libhb.h"
# include <stdlib.h>

enum					e_mask_flags
{
	MASK_ORIGIN = 0,
	MASK_EXPANSION = 1,
	MASK_S_QUOTES = 2,
	MASK_QUOTES = 4
};

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
	int					flag;
	char				*mask;
}						t_token;

typedef struct s_redirect
{
	char				*value;
	char				*ambiguous;
	t_token_type		type;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char				**args;
	t_redirect			*redirect_list;
	struct s_cmd		*next;
}						t_cmd;

typedef struct e_list
{
	char				*var;
	char				*value;
	int					exp;
	struct e_list		*next;
}						t_env;

// Lexer
int						is_space(char c);
int						is_operator(char c);
int						skip_spaces(const char *s, int i);
int						get_op_len(const char *s);
t_token_type			get_operator_type(const char *s);
int						handle_operator(const char *input, int i,
							t_token **lst);
int						handle_word(const char *input, int i, t_token **lst);
int						extract_word(const char *input, int i, char **val);
void					add_token(t_token **lst, char *value, t_token_type type,
							char *mask);
t_token					*lexer(const char *input);
int						check_balanced_quotes(const char *input);
int						check_grammar(t_token *tok);

// Tokenizer/Parser
int						is_redir(t_token_type t);
void					add_redirect(t_redirect **lst, char *value,
							t_token_type type, char *ambiguous);
void					free_redirects(t_redirect *lst);
t_cmd					*new_cmd(void);
void					free_cmds(t_cmd *lst);

// here-doc
int						heredoc(t_redirect *rdct, t_env *env);
// mask

void	edit_mask(char *val, char *mask);
int	extract_word_with_mask(const char *input, int i, char **out_val, char **out_mask);
void	help_editmask(char *val, char *mask, int *flag, int reset);

#endif
