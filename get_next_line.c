/* *****tatic char    *find_line(int fd, char *left_char, char *buffer)********************************************************************* */
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

	if (!left_char)
		left_char = "";
	if (fd <= 0)
        	return (NULL);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	temp = find_line(fd, buffer);
	if (!temp)
		return (NULL);
	filled_line = fill_line(temp, left_char);
	left_char= get_left_char(temp);
	free(temp);
	return (filled_line);
}

static char    *find_line(int fd, char *buffer)
{
	char	*temp;
	int	val_read;
	char	*to_free;

	temp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	while (!ft_strchr(temp, 10))
	{
		val_read = read(fd, buffer, BUFFER_SIZE);
		if (val_read <= 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[val_read] = '\0';
		to_free = temp;
		temp = ft_strjoin(temp, buffer);
		free (to_free);
	}
	free(buffer);
	return (temp);
}

static char	*fill_line(char	*temp, char *left_char)
{
	char	*filled_line;
	int	i;
	char	*to_free;

	i = 0;
	filled_line = ft_calloc(sizeof(char), ft_strlen(temp) + 1);
	if (!filled_line)
		return (NULL);
	while (temp[i] != '\0' && temp[i] != '\n')
	{
		filled_line[i] = temp[i];
		i++;
	}
	filled_line[i] = '\0';
	to_free = filled_line;
	filled_line = ft_strjoin(left_char, filled_line);
	free(to_free);	
	return (filled_line);
}

static char	*get_left_char(char *temp)
{
	char	*left_char;
	char	*to_free;

	left_char = malloc(ft_strlen(temp) + 1);
	if (!left_char)
		return (NULL);
	to_free = left_char;
	if (ft_strchr(temp, '\n'))
		left_char = ft_strdup(ft_strchr(temp, '\n'));
	else
		left_char = ft_strdup(ft_strchr(temp, '\0'));	
	free(to_free);
	return (left_char);
}


int main(void)
{
	int fd;
	
	fd = open("test.txt", O_RDONLY);
	printf("get next line returns %s\n", get_next_line(fd));
	printf("get next line returns %s\n", get_next_line(fd));
	printf("get next line returns %s\n", get_next_line(fd));
	printf("get next line returns %s\n", get_next_line(fd));
	close(fd);
	return (0);
}

