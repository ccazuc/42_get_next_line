/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:46:08 by ccazuc            #+#    #+#             */
/*   Updated: 2017/11/08 12:23:19 by ccazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 150

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int				get_next_line(const int fd, char **line);

typedef struct 	s_env
{
	char		*datas;
	int			start;
	int			end;
	int			fd;
	int			line;
	int			curr_line;
	
}				t_env;

#endif
