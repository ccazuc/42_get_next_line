/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:17:41 by ccazuc            #+#    #+#             */
/*   Updated: 2017/11/08 09:19:51 by ccazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_next_line(t_list **list, int line)
{
	t_list	*tmp;
	int		curr_line;
	int		i;
	int		should_add;

	curr_line = 0;
	tmp = *list;
	while (tmp)
	{
		if (
	}
	while ()
	while (list)
	{
		tmp = list->next;
		free(list->data);
		free(list);
		list = tmp;
	}
	list = NULL;
}

static int	add_datas_list(char *datas, t_list **list, int *curr_line, t_env *env)
{
	t_list *new_list;
	int		i;

	if (!(new_list = malloc(sizeof(*new_list))))
		return (-1);
	new_list->next = NULL;
	new_list->data = ft_strndup(datas, ft_strlen(datas));
	new_list->nb_eol = 0;
	new_list->last_eol = 0;
	i = -1;
	while (datas[++i])
		if (datas[i] == '\n')
		{
			new_list->nb_eol++;
			*curr_line++;
			if (*curr_line == env->line)
			{
				new_list->last_eol = 1;
				return (1);
			}
		}
}

static char	*get_n_line(t_env *env)
{
	int		datas_read;
	char	buffer[BUFFER_SIZE];
	int		curr_line;
	int		returned_value;
	char	*result;

	curr_line = 0;
	while ((datas_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[datas_read] = '\0';
		returned_value = add_datas_list(buffer, &result, &curr_line);
		if (returned_value == -1)
			return (NULL);
		if (curr_line == 1)
			return (build_line(list);
	}
}

int			get_next_line(const int fd, char **line)
{
	static int	line;
	t_env		*env;

	if (!(env = malloc(*t_env)))
		return (-1);
	env->fd = fd;
	env->line = line;
	line = -1;
	++line;
	if (!get_n_line(fd, line))
		return (-1);	
			
}
