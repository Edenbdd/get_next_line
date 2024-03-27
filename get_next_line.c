/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:12:40 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/27 14:18:25 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

char     *filled_line(int fd, char *buffer, char *line);
char     *adjust_line(char *line);
char    *left_char(char *line);

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
	free(buffer);
	adjusted_line = adjust_line(line);
	line = left_char(line);
	return (adjusted_line);
}

char	*filled_line(int fd, char *buffer, char *line)
{
	int		val_read;

	val_read = 1;
	while (val_read)
	{
		val_read = read(fd, buffer, BUFFER_SIZE);
		if (val_read == -1)
			return (free(buffer), NULL);
		if (val_read == 0)
			break;
		buffer[val_read] = '\0';
		line = ft_strjoin(line, buffer);
		if (!line)
			return (free(buffer), NULL);
	}
	return (line);
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

char    *left_char(char *line)
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

int main(void)
{
	int	fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	while ((str = get_next_line(fd))) {
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}

