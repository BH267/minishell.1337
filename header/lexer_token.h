/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:11:42 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/27 17:51:59 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOKEN_H
# define LEXER_TOKEN_H

# include <stdlib.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	ERR
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	char				*value;
	t_token_type		type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			**args;
	t_redirect		*redirect_list;
	struct s_cmd	*next;
}	t_cmd;

// Lexer
int				is_space(char c);
int				is_operator(char c);
int				skip_spaces(const char *s, int i);
int				get_op_len(const char *s);
t_token_type	get_operator_type(const char *s);
int				handle_quoted(const char *input, int i, t_token **lst);
int				handle_operator(const char *input, int i, t_token **lst);
int				handle_word(const char *input, int i, t_token **lst);
int				extract_quoted(const char *input, int i, char **val);
int				extract_word(const char *input, int i, char **val);
void			add_token(t_token **lst, char *value, t_token_type type);
t_token			*lexer(const char *input);

// Tokenizer/Parser
int				count_args(t_token *lst);
char			**tokens_to_args(t_token *lst, int n);
int				is_redir(t_token_type t);
void			add_redirect(t_redirect **lst, char *value, t_token_type type);
void			free_redirects(t_redirect *lst);
t_cmd			*new_cmd(void);
t_cmd			*parse_tokens(t_token *tokens);
void			free_tokens(t_token *lst);
void			free_cmds(t_cmd *lst);

#endif
