#include "get_next_line.h"
#include <stdio.h>

int		get_end_of_line(t_gnl *env)
{
	int		i;

	i = env->buff_pos - 1;
	while (env->datas[++i])
		if (env->datas[i] == '\n')
		{
			return (i);
		}
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
	//printf("save_buff_pos: %d, eol: %d\n", save_buff_pos, eol);
	//printf("save_buff_pos: %c, eol: %c\n", env->datas[save_buff_pos], env->datas[eol - 1]);
	//printf("strsub: %s\n", ft_strsub(env->datas, save_buff_pos, eol - save_buff_pos));
	//printf("----------------------------\n%s\n----------------------------------\n", env->datas);
	return (ft_strsub(env->datas, save_buff_pos, eol - save_buff_pos));
}

char	*read_datas(t_gnl *env)
{
	int		datas_read;
	char	buffer[BUFF_SIZE + 1];
	int		returned_value;
	char	*tmp;

	//printf("buff_pos: %d, buff_len: %d\n", env->buff_pos, env->buff_len);
	if (env->buff_pos < env->buff_len)
		if (get_end_of_line(env))
			return (build_line(env));
	while ((datas_read = read(env->fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[datas_read] = '\0';
		env->buff_len += datas_read;
		if (!(env->datas = ft_strjoin_free1(env->datas,  buffer)))
			return (NULL);
		//printf("eol: %d\n", get_end_of_line(env));
		if (get_end_of_line(env))
			return (build_line(env));
	}
	if (datas_read == -1)
	{
		//printf("DATAS_READ == -1\n");
		return (NULL);
	}
	env->eof = 1;
	//printf("EEOOFF\n");
	return (ft_strsub_start(env->datas, env->buff_pos));
}

t_gnl	*init_env(t_gnl **env_p, char should_delete)
{
	t_gnl	*env;

	if (should_delete == 1)
	{
		if ((*env_p)->eof)
		{
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
		if (!init_env(&env, 1))
			return (0);
		else
			return (-1);
	if (!init_env(&env, 1))
		return (0);
	return (1);
	
}

/*int		main(int argc, char **argv)
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
	return (0);
}*/
