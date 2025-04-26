/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:11:42 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/26 02:17:54 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOKEN_H
# define LEXER_TOKEN_H

// Minimal token and command structures for lexer/tokenizer

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
} t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
} t_token;

typedef struct s_cmd
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
	struct s_cmd *next;
} t_cmd;

# include <stdlib.h>

// Lexer
int	is_space(char c);
int	is_operator(char c);
int	skip_spaces(const char *s, int i);
int	get_op_len(const char *s);
t_token_type get_operator_type(const char *s);
int	handle_quoted(const char *input, int i, t_token **lst);
int	handle_operator(const char *input, int i, t_token **lst);
int	handle_word(const char *input, int i, t_token **lst);
int	extract_quoted(const char *input, int i, char **val);
int	extract_word(const char *input, int i, char **val);
void	add_token(t_token **lst, char *value, t_token_type type);
t_token *lexer(const char *input);

// Tokenizer
int	count_args(t_token *lst);
char **tokens_to_args(t_token *lst, int n);
int	is_redir(t_token_type t);
int	fill_redir(t_cmd *cmd, t_token *tok);
t_cmd *new_cmd(void);
t_cmd *tokenizer(t_token *tokens);
t_cmd *parse_tokens(t_token *tokens);
void	free_tokens(t_token *lst);

#endif
