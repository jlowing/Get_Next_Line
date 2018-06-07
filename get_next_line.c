#include "libft.h"
#include "get_next_line.h"
int		ft_malloc(char **check)
{
	char	*temporary;

	if (!(temporary = ft_strnew(ft_strlen(*check))))
		return (0);
	ft_strcpy(temporary, *check);
	*check = NULL;
	if (!(*check = ft_strnew(ft_strlen(temporary) + BUFF_SIZE)))
		return (0);
	ft_strcpy(*check, temporary);
	return (1);
}

int		fill(int j, char **check, char **line)
{
	int		i;
	int		y;

	y = 0;
	i = 0;
	if (j != 0 || ft_strlen((*check)) != 0)
	{
		while ((*check)[i] != '\n')
		{
			(*line)[i] = (*check)[i];
			i++;
		}
		(*line)[i++] = '\0';
		if ((*check)[0] == '\n')
		{
			while ((*check)[i])
				(*check)[y++] = (*check)[i++];
			(*check)[y] = '\0';
			return (2);
		}
		while ((*check)[i])
			(*check)[y++] = (*check)[i++];
		(*check)[y] = '\0';
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			j;
	static char	*check;

	if (fd < 0 || (!check && !(check = ft_strnew(BUFF_SIZE))))
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char) * BUFF_SIZE)))
		return (-1);
	while ((j = read(fd, *line, BUFF_SIZE)) > 0)
	{
		if (!(ft_malloc(&check)))
			return (-1);
		ft_strncat(check, *line, BUFF_SIZE);
		if (ft_memchr(*line, '\n', BUFF_SIZE))
			break ;
	}
	if ((fill(j, &check, &(*line))) == 2)
		return (1);
	if (ft_memcmp((*line), check, ft_strlen(*line)) == 0)
	{
		if (!(*line = ft_strdup("")))
			return (1);
		return (0);
	}
	return (1);
}