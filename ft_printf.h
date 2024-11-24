/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:03:34 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/24 15:19:11 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef int			t_bool;
# define TRUE 1
# define FALSE 0

# define FLAG_MINUS 1 << 0
# define FLAG_PLUS 1 << 1
# define FLAG_SPACE 1 << 2
# define FLAG_ZERO 1 << 3
# define FLAG_HASH 1 << 4

typedef struct s_opts
{
	unsigned int	width;
	int				flags;
	char			specifier;
}					t_opts;

typedef struct s_scanner
{
	const char		*s;
	size_t			len;
	size_t			cursor;
}					t_scanner;

//------- printf
int					ft_printf(const char *format, ...);

//-------- io helpers
int					ft_putchar(char c);

//-------- strings helper
size_t				ft_strlen(const char *s);
char				*ft_strdup(char *src);
//--------- number helpers
int					max(int n1, int n2);
char				*itoa(int num);
//---------- scanner
t_scanner			*create_scanner(const char *s);
t_bool				match(t_scanner *scn, char c);
char				advance(t_scanner *scn);
char				peek(t_scanner *scn);
t_bool				is_at_end(t_scanner *scn);

//--------- DEBUG
void				debug_flags(t_opts *op);
#endif