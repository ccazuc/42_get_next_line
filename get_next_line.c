/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:17:41 by ccazuc            #+#    #+#             */
/*   Updated: 2018/04/30 13:49:43 by ccazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*build_line(t_gnl *env)
{
	int		i;

	i = -1;
	env->curr_line = 0;
	while (env->datas[++i] && env->end != i)
		if (env->datas[i] == '\n')
		{
			++env->curr_line;
			if (env->curr_line == env->line)
				env->start = i;
			else if (env->curr_line == env->line + 1)
				env->end = i;
		}
	if (env->curr_line <= env->line || env->end == -1)
	{
		env->eof = 1;
		while (i >= 0 && env->datas[i] != '\n')
			--i;
		return (i == (int)ft_strlen(env->datas) - 1 ? NULL :
		ft_strsub_start(env->datas, i + 1));
	}
	env->buff_pos = i + 1;
	if (env->start == -1)
		return (ft_strsub(env->datas, 0, env->end));
	return (ft_strsub(env->datas, env->start + 1, env->end - env->start - 1));
}

static int		add_datas(char *datas, t_gnl *env)
{
	int		i;

	if (!(env->datas = ft_strjoin_free1(env->datas, datas)))
		return (-1);
	i = -1;
	env->curr_line = -1;
	while (env->datas[++i])
		if (env->datas[i] == '\n')
		{
			++env->curr_line;
			if (env->curr_line == env->line)
				return (1);
		}
	return (0);
}

static char		*get_n_line(t_gnl *env)
{
	int		datas_read;
	char	buffer[BUFF_SIZE + 1];
	int		returned_value;
	char	*tmp;

	env->curr_line = 0;
	if (env->buff_pos < env->buff_len)
		if ((tmp = build_line(env)))
			return (tmp);
	while ((datas_read = read(env->fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[datas_read] = '\0';
		env->buff_len += datas_read;
		returned_value = add_datas(buffer, env);
		if (returned_value == -1)
			return (NULL);
		if (returned_value == 1)
			return (build_line(env));
	}
	if (datas_read == -1)
		return (NULL);
	return (build_line(env));
}

t_gnl			*init_env(void)
{
	t_gnl	*env;

	if (!(env = malloc(sizeof(*env))))
		return (NULL);
	if (!(env->datas = malloc(1)))
		return (NULL);
	env->datas[0] = '\0';
	env->buff_len = 0;
	env->buff_pos = 0;
	env->line = -1;
	env->eof = 0;
	return (env);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl		*env;

	if (fd < 0 || fd > 255 || (!env && (!(env = init_env()))))
		return (-1);
	if (env->eof)
		return (0);
	++env->line;
	env->fd = fd;
	env->start = -1;
	env->end = -1;
	if (!(*line = get_n_line(env)))
		return (-1);
	return (1);
}

int		main(int argc, char **argv)
{
	/*char	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "efghijkl", 8);
	close(p[1]);
	dup2(out, fd);
	printf("%d, line: '%s'\n\n\n\n", get_next_line(p[0], &line), line);
	printf("%d, line: '%s'\n\n\n\n", get_next_line(p[0], &line), line);
	printf("%d, line: '%s'\n\n\n\n", get_next_line(p[0], &line), line);
	printf("%d, line: '%s'\n\n\n\n", get_next_line(p[0], &line), line);*/
	
	char	*line;
	int		fd;
	int		i;
	int		max;
	int		returned_value;

	i = -1;
	fd = open(argv[1], O_RDONLY);
	max = ft_atoi(argv[2]);
	while (++i < max && (returned_value = get_next_line(fd, &line)) == 1)
		printf("'%d' '%s'\n", returned_value, line);
	printf("last: %d\n", get_next_line(fd, &line));
	return (0);
}
