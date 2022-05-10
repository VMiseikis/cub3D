/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:41:40 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/05/10 18:43:32 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_check_rgb(char **str, int *nbr)
{
	if (!ft_trim_str_front(str, ' ') || !ft_trim_str_back(str, ' '))
		return (ft_print_error("Incorrect map color rgb parameter"));
	if (ft_strlen(*str) == 0)
		return (ft_print_error("Incorrect map color rgb parameter"));
	if (!ft_is_arr_only_nbr(*str))
		return (ft_print_error("Incorrect map color rgb parameter"));
	*nbr = ft_atoi(*str);
	if (*nbr < 0 || *nbr > 255)
		return (ft_print_error("Incorrect map color rgb parameter"));
	return (TRUE);
}

int	ft_check_texture_path_extension(char **line, char **path)
{
	*path = ft_substr(*line, 3, ft_strlen(*line));
	if (!ft_trim_str_front(path, ' ') || !ft_trim_str_back(path, ' ')
		|| !ft_is_extention_valid(*path, ".xpm"))
		return (ft_print_error("Unsupported map texture extension"));
	if (!ft_is_file_valid(*path))
		return (ft_print_error("No such map texture file"));
	return (TRUE);
}
