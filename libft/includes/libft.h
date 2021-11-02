/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:37:48 by eniini            #+#    #+#             */
/*   Updated: 2021/11/02 15:17:42 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
**	stdlib included for an access to size_t data type, NULL constant
**	and memory allocation functions.
**	stdint & wchar for additional type definitions.
**	defs.h defines generalized linked list datatype and relevant macros for
**	get_next_line(3).
*/

# include <stdlib.h>
# include <stdint.h>
# include <wchar.h>
# include <unistd.h>
# include "defs.h"

typedef int		t_bool;
# define TRUE	1
# define FALSE	0

//	Array manipulation/examination

void			ft_free_arr(char **arr);
size_t			ft_get_arr_size(char **arr);

//	Character manipulation/examination

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isspace(int c);
int				ft_isprint(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

//	File I/O utility

void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_printf(const char *str, ...);
int				ft_sprintf(char *str, const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				get_next_line(const int fd, char **line);

//	Linked list utility
//	ft_lstdel(2) & ft_lstdelone(2) should call ft_elemdel(2) by default.

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddl(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_elemdel(void *content, size_t size);

//	Math utility

int				ft_abs(int n);
int				ft_clamp_i(int value, int min, int max);
double			ft_clamp_d(double value, double min, double max);
long long int	ft_pow(int i, unsigned int p);
int				ft_numlength(int nb);
int				ft_numlength_neg(intmax_t nb);
long double		ft_neg_pow_ten(long double nb, int pow);
long double		ft_brounding(long double nb, int prec);
long double		ft_brounding_ld(long double nb, int prec);
int				ft_atoi_max(const char *str);
uintmax_t		ft_uintmax_pow(uintmax_t nb, int pow);
int				ft_is_neg(double nb);
int				ft_is_neg_minus(double nb);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
long double		ft_neg_pow_ten(long double nb, int pow);

//	Memory utility

void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_swap(void *a, void *b, size_t size);
void			*ft_calloc(size_t count, size_t size);
void			ft_free_array(char **arr);

//	Process control

void			ft_getout(const char *str);

//	String manipulation/examination

char			*ft_strcat(char *a, const char *b);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strncat(char *a, const char *b, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *a, const char *b);
int				ft_strncmp(const char *a, const char *b, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
int				ft_strequ(char const *a, char const *b);
int				ft_strnequ(char const *a, char const *b, size_t n);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *a, char const *b);
size_t			ft_strlen(const char *s);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strnew(size_t size);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *stack, const char *ndl, size_t len);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
size_t			ft_wordcount(char const *s, char c);
void			ft_putnstr_fd(char *str, size_t size, int fd);
char			*ft_tolower_str(char *str);
char			*ft_toupper_str(char *str);
void			ft_putnstr(char *str, size_t size);

//	Wide string (UTF-8) I/O and examination

void			ft_putwchar(wint_t wc, int fd);
void			ft_putwstr(wchar_t *wstr, int fd);
int				ft_wcharlen(wint_t wc);
size_t			ft_wstrlen(const wchar_t *wstr);
size_t			ft_wstrnlen(const wchar_t *wstr, size_t n);

//	Type conversions

int				ft_atoi(const char *str);
char			*ft_ftoa(long double f, unsigned int prec);
char			*ft_itoa_base(int value, int base);
char			*ft_itoa_llong_base(long long nb, int base);
char			*ft_itoa_ulong_base(unsigned long long nb, int base);
char			*ft_itoa_intmax_base(intmax_t nb, int base);
char			*ft_itoa_size_t_base(size_t nb, int base);
char			*ft_itoa_uintmax_base(uintmax_t nb, int base);
char			*ft_flitoa(double nb, int prec);
char			*ft_flitoa_ldouble(long double nb, int prec);
char			*ft_itoa_exp(long double nb, int prec);
char			*ft_itoa(int n);
int				ft_atoi_max(const char *str);
char			*ft_uitoa_base(size_t ui, int base, t_bool lcase);
char			*ft_uitoa(size_t ui);

#endif
