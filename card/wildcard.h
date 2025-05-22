/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:58:19 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 00:18:46 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../ms.h"
# include "../header/lexer_token.h"
# include "../libhb/libhb.h"
# include <dirent.h>
# include <sys/stat.h>

typedef struct s_match_list
{
	char					*name;
	struct s_match_list		*next;
}	t_match_list;

/* Core wildcard functions */
void		card(t_token *tokens);

/* Pattern matching functions */
int			contains_wildcards(const char *str);
int			match_pattern(const char *pattern, const char *string);
t_match_list	*get_matches(const char *pattern);

/* Match list utilities */
t_match_list	*new_match(char *name);
void		add_match(t_match_list **list, t_match_list *new);
char		**convert_matches_to_array(t_match_list *matches);

/* Token manipulation */
void		replace_token_with_matches(t_token **token, t_match_list *matches);

#endif

