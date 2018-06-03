#include "get_next_line.h"
#include <stdio.h>

int		get_end_of_line(t_gnl *env)
{
	int		i;

	i = env->buff_pos - 1;
	while (env->datas[++i])
		if (env->datas[i] == '\n')
			return (i);
	return (0);
}

char	*build_line(t_gnl * env)
{
	int		eol;
	int		save_buff_pos;

	eol = get_end_of_line(env);
	if (!eol)
		return (NULL);
	save_buff_pos = env->buff_pos;
	env->buff_pos = eol + 1;
	return (ft_strsub(env->datas, save_buff_pos, eol - save_buff_pos));
}

char	*read_datas(t_gnl *env)
{
	int		datas_read;
	char	buffer[BUFF_SIZE + 1];

	if (env->buff_pos < env->buff_len)
		if (get_end_of_line(env))
			return (build_line(env));
	while ((datas_read = read(env->fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[datas_read] = '\0';
		env->buff_len += datas_read;
		if (!(env->datas = ft_strjoin_free1(env->datas,  buffer)))
			return (NULL);
		if (get_end_of_line(env))
			return (build_line(env));
	}
	if (datas_read == -1)
		return (NULL);
	env->eof = 1;
	env->exception = 1;
	//printf("datas: %s, buff_pos: %d\n", env->datas, env->buff_pos);
	//printf("returned: '%s'\n", ft_strsub_start(env->datas, env->buff_pos));
	if (env->buff_pos < (int)ft_strlen(env->datas))
		return (ft_strsub_start(env->datas, env->buff_pos));
	return (NULL);
}

t_gnl	*init_env(t_gnl **env_p, char should_delete)
{
	t_gnl	*env;

	if (should_delete == 1)
	{
		if ((*env_p)->eof)
		{
			printf("datas: %s\n", env->datas);
			free(env->datas);
			free(*env_p);
			*env_p = NULL;
			return (NULL);
		}
		return (*env_p);
	}
	if (!(env = malloc(sizeof(*env))))
		return (NULL);
	if (!(env->datas = malloc(1)))
		return (NULL);
	env->datas[0] = '\0';
	env->line = -1;
	env->eof = 0;
	env->buff_pos = 0;
	env->buff_len = 0;
	env->exception = 0;
	return (env);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*env;

	if (fd < 0 || !line || (!env && !(env = init_env(NULL, 0))))
		return (-1);
	if (!init_env(&env, 1))
		return (0);
	env->fd = fd;
	++env->line;
	*line = read_datas(env);
	if (!*line)
	{
		if (!init_env(&env, 1))
			return (0);
		return (-1);
	}
	if (env->exception)
	{
		init_env(&env, 1);
		return (1);
	}
	if (!init_env(&env, 1))
		return (0);
	return (1);
	
}

int		main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		i;
	int		max;
	int		returned;

	i = -1;
	fd = open(argv[1], O_RDONLY);
	max = ft_atoi(argv[2]);
	while (++i < max && (returned = get_next_line(fd, &line)) == 1)
	{
		printf("'%d' '%s'\n", returned, line);
		free(line);
	}
	returned = get_next_line(fd, &line);
	printf("last: %d\n", returned);
	while (1);
	return (0);
}
