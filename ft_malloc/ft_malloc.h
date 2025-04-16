/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:13:51 by ybouanan          #+#    #+#             */
/*   Updated: 2025/03/03 17:18:47 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>

typedef struct s_gc
{
	void		*p;
	struct s_gc	*next;
}				t_gc;

void			ft_free(void);
struct s_gc		**get_box(void);
void			add_to_box(void *addr);
void			*ft_malloc(size_t bytes);

#endif
