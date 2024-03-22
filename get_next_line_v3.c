/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:35:44 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/22 14:26:47 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char    *find_line(int fd, char *buffer, char *left_char);
static char     *adjust_left_char(char *filled_line);
static char     *fill_line(char *line, char *left_char);

char    *get_next_line(int fd)
{
	char		*buffer;
	static char	*left_char;
	char	*filled_line;
	char	*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
        	return (NULL);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = find_line(fd, buffer, left_char);
	left_char = adjust_left_char(line);
	filled_line = fill_line(line, left_char);
	if (filled_line[0] == '\0')
		return (free(filled_line), NULL);
	return (filled_line);
}

static char    *find_line(int fd, char *buffer, char *left_char)
{
	int	val_read;
	
	val_read = 1;
	while (val_read > 0)
	{
		val_read = read(fd, buffer, BUFFER_SIZE);
		if (val_read <= 0)
			break;
		buffer[val_read] = '\0';
		if (!left_char)
			left_char = ft_strdup(buffer);
		else
			left_char = ft_strjoin(left_char, buffer);	
		if (ft_strchr(buffer, '\n'))
			break;	
	}
	free(buffer);
	return (left_char);
}

static char	*fill_line(char	*line, char *left_char)
{
	char	*filled_line;
	int	i;

	i = 0;
	filled_line = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	if (!filled_line)
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
	{
		filled_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		filled_line[i] = '\n';
	else
		filled_line[i] = '\0';
	filled_line = ft_strjoin(left_char, filled_line);
	return (filled_line);
}


static char	*adjust_left_char(char *filled_line)
{
	char	*from_n;
	static char	*left_char;

	from_n = ft_strchr(filled_line, '\n');
	if (from_n)
		left_char = ft_strdup(from_n);
	else
		left_char = ft_strdup(filled_line);
	return (left_char);
}

int main(void)
{
	int	fd;
	char	*str;

	fd = open("./test.txt", O_RDONLY);
/*
	for (int i = 0; i < 3; i++) {
		str = get_next_line(fd);
		printf("%s\n", str);
		free(str);
	}
*/
	while ((str = get_next_line(fd))) {
		printf("%s\n", str);
		free(str);
	}
	close(fd);
	return (0);
}

