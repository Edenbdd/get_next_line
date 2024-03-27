/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:35:44 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/14 11:42:40 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char    *find_line(int fd, char *buffer);
static char     *fill_line(char *temp, char *left_char);
static char     *get_left_char(char *temp);

char    *get_next_line(int fd)
{
	char		*buffer;
	static char	*left_char;
	char	*filled_line;
	char	*temp;

	if (fd <= 0 || BUFFER_SIZE <= 0)
        	return (NULL);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	temp = find_line(fd, buffer);
	if (!temp)
		return (NULL);
	filled_line = fill_line(temp, left_char);
	left_char= get_left_char(temp);
	return (free(temp), filled_line);
}

static char    *find_line(int fd, char *buffer)
{
	char	*temp;
	int	val_read;
	char	*to_free;

	temp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if(!temp)
		return (free(buffer), NULL);
	val_read = 1;
	while (val_read > 0)
	{
		val_read = read(fd, buffer, BUFFER_SIZE);
		if (val_read == -1)
			return (free(temp), NULL);
		if (val_read == 0)
			return (free(temp), NULL);
		buffer[val_read] = '\0';
		to_free = temp;
		temp = ft_strjoin(to_free, buffer);
		if (!temp)
			return (free(temp), NULL);
		if (ft_strchr(buffer, '\n'))
				break;
		free(buffer);
	}
	return (temp);
}

static char	*fill_line(char	*temp, char *left_char)
{
	char	*filled_line;
	int	i;
	char	*to_free;
	char	*to_free_temp;

	i = 0;
	filled_line = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!filled_line)
		return (NULL);
	while (temp[i] && temp[i] != '\n')
	{
		filled_line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
		filled_line[i] = '\n';
	else
		filled_line[i] = '\0';
	if (left_char)
	{
		to_free = filled_line;
		to_free_temp = left_char;
		filled_line = ft_strjoin(to_free_temp, filled_line);	
		free(to_free);
	}
	return (filled_line);
}

static char	*get_left_char(char *temp)
{
	char	*left_char;
	char	*from_n;
	
	from_n = ft_strchr(temp, '\n');
	if (from_n)
		left_char = ft_strdup(from_n);
	else
		left_char = ft_strdup(temp);	
	if (!left_char)
		return (NULL);
	return (left_char);
}
/*
int main(void)
{
	int	fd;
	char	*str;

	fd = open("test", O_RDONLY);
	for (int i = 0; i < 1; i++) 
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}
*/
