/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:46:08 by ccazuc            #+#    #+#             */
/*   Updated: 2018/04/30 13:50:39 by ccazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int				get_next_line(const int fd, char **line);

typedef struct 	s_gnl
{
	char		*datas;
	int			start;
	int			end;
	int			fd;
	int			line;
	int			curr_line;
	int			buff_pos;
	int			buff_len;
	int			eof;
}				t_gnl;

#endif
