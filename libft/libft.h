/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:53:50 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 21:18:48 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlen_2d(char **str);
char	*ft_substr(char const *str, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_str_join_c(char *str, char const c);
char	**ft_split(char const *str, char c);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
char	*ft_strdup(const char *s);
char	*ft_strcpy(char *s1, const char *s2);
char	**ft_2dstrcpy(char **src, char **dest);
char	*ft_strchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
