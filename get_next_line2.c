/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:17:41 by ccazuc            #+#    #+#             */
/*   Updated: 2017/11/08 13:29:52 by ccazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*build_line(t_env *env)
{
	int		i;

	i = -1;
	//printf("Build line start\n");
	env->curr_line = 0;
	//printf("line: %d, env->datas: %s\n", env->line, env->datas);
	//printf("Line: %d\n", env->line);
	while (env->datas[++i])
		if (env->datas[i] == '\n')
		{
			//printf("N found BUILD: %d, line: %d\n", i, env->line);
			++env->curr_line;
			if (env->curr_line == env->line) //check if it start with a \n
				env->start = i;
			else if (env->curr_line == env->line + 1)
			{
				env->end = i;
				break;
			}
		}
	//printf("END BUILD, buff_pos: %d, buff_len: %d\n", env->buff_pos, env->buff_len);
	//printf("Start str_sub\n");
	//printf("env->start: %d, env->end: %d, env->line: %d\n", env->start, env->end, env->line);
	//printf("%s\n", ft_strsub_start(env->datas, env->start));
	//printf("First sub done\n");
	//printf("%s\n", ft_strsub(env->datas, 0, env->end));
	//printf("Second sub done\n");
	//printf("%s\n", ft_strsub(env->datas, env->start, env->end));
	//printf("Third sub done\n");
	if (env->curr_line <= env->line)
		return (NULL);
	env->buff_pos = i + 1;
	if (env->end == -1)
		return (ft_strsub_start(env->datas, env->start));
	if (env->start == -1)
		return (ft_strsub(env->datas, 0, env->end));
	return (ft_strsub(env->datas, env->start + 1, env->end - env->start - 1));
}

static int	add_datas(char *datas, t_env *env)
{
	int		i;

	//printf("env->datas: %s, datas: %s\n", env->datas, datas);
	if (!(env->datas = ft_strjoin_free1(env->datas, datas)))
		return (-1);
	i = -1;
	//printf("1\n");
	env->curr_line = -1;
	while (env->datas[++i])
	{
	//	printf("2\n");
		if (env->datas[i] == '\n')
		{
			//printf("N found ADD: %d, line: %d\n", i, env->line);
			++env->curr_line;
			//printf("env->curr_line: %d, env->line: %d\n", env->curr_line, env->line);
			if (env->curr_line == env->line)
				return (1);
		}
	}
	return (0);
}

static char	*get_n_line(t_env *env)
{
	int		datas_read;
	char	buffer[BUFF_SIZE + 1];
	int		returned_value;
	char	*tmp;

	env->curr_line = 0;
	//printf("buff_pos: %d, buff_len: %d\n", env->buff_pos, env->buff_len);
	if (env->buff_pos < env->buff_len)
	{
		//printf("BUFF CONDITION\n");
		if ((tmp = build_line(env)))
			return (tmp);
	}
	while ((datas_read = read(env->fd, buffer, BUFF_SIZE)) > 0)
	{
	//	printf("BUFF READ\n");
		buffer[datas_read] = '\0';
		env->buff_len += datas_read;
		//printf("data_read: '%s', line: %d\n", buffer, env->line);
		//printf("c\n");
		returned_value = add_datas(buffer, env);
		//printf("Returned value: %d\n", returned_value);
		//printf("d\n");
		if (returned_value == -1)
			return (NULL);
		if (returned_value == 1)
		{
			//printf("build_line: %s, line: %d\n", build_line(env), env->line);
			return (build_line(env));
		}
	}
	return (NULL);
}

int			get_next_line(const int fd, char **line)
{
	static int			s_line = -1;
	static t_env		*env;

	if (!env)
	{
		if (!(env = malloc(sizeof(*env))))
			return (-1);
		env->datas = malloc(1);
		env->buff_len = 0;
		env->buff_pos = 0;
	}
	++s_line;
	env->fd = fd;
	env->line = s_line;
	env->start = -1;
	env->end = -1;
	if (!(*line = get_n_line(env)))
		return (-1);
	return (1);
}

int		main(void)
{
	char	*line;
	int		fd;

	printf("before open\n");
	fd = open("libft.h", O_RDONLY);
	printf("open\n");
	while (get_next_line(fd, &line) == 1)
		printf("%s\n", line);
	return (0);
}
