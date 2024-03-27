/*include header*/

#include "get_next_line.h"

static char     *filled_line(int fd, char *buffer, char *line);
static char     *adjust_line(char *line);
static char    *left_char(char *line);

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	char		*adjusted_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!line)
		line = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!line)
		return(free(buffer), NULL);
	line = filled_line(fd, buffer, line);
	adjusted_line = adjust_line(line);
	line = left_char(line);
	return (adjusted_line);
}

char	*filled_line(int fd, char *buffer, char *line)
{
	int		val_read;

	val_read = 1;
	while (val_read > 0)
	{
		val_read = read(fd, buffer, BUFFER_SIZE);
		if (val_read == -1)
			return (free(buffer), NULL);
		if (val_read == 0)
			return (NULL);
		buffer[val_read] = '\0';
		line = ft_strjoin(line, buffer);
		if (!line)
			return (free(buffer), NULL);
		if (ft_strchr(buffer, '\n'))
				break;
	}
	return (free(buffer), line);
}
char	*adjust_line(char *line)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;

	if (!line || !line[0])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	temp = ft_calloc(sizeof(char), (i + 2));
	if (!temp)
		return (NULL);
	while (j <= i)
	{
		temp[j] = line[j];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

static char    *left_char(char *line)
{
        char    *temp;
	char	*from_n;

        if (!line)
                return (free(line), NULL);
	from_n = ft_strchr(line, '\n');
	if (from_n)
		temp = ft_strdup(from_n);
	else
		temp = ft_strdup(line);
	return (free(line), temp);
}
/*
int main(void)
{
	int	fd;
	char	*str;

	fd = open("test", O_RDONLY);
	for (int i = 0; i < 5; i++)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}
*/
