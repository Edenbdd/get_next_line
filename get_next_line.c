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
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	temp = find_line(fd, buffer);
	if (!temp)
		return (NULL);
	free(buffer);
	filled_line = fill_line(temp, left_char);
	left_char= get_left_char(temp);
	free(temp);
	return (filled_line);
}

static char    *find_line(int fd, char *buffer)
{
	char	*temp;

	temp = "";
	while (!ft_strchr(temp, 10))
	{
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			free(buffer);
			return (NULL);
		}
		temp = ft_strjoin(temp, buffer);
	}
	return (temp);
}

static char	*fill_line(char	*temp, char *left_char)
{
	char	*filled_line;
	int	i;

	i = 0;
	filled_line = malloc(ft_strlen(temp) + 1);
	if (!filled_line)
		return (NULL);
	while (temp[i] != '\0' && temp[i] != '\n')
	{
		filled_line[i] = temp[i];
		i++;
	}
	filled_line[i] = '\0';
	filled_line = ft_strjoin(left_char, filled_line);	
	return (filled_line);
}

static char	*get_left_char(char *temp)
{
	char	*left_char;
	
	left_char = malloc(ft_strlen(temp) + 1);
	if (!left_char)
		return (NULL);
	if (ft_strchr(temp, '\n'))
		left_char = ft_strdup(ft_strchr(temp, '\n'));
	else
		left_char = ft_strdup(ft_strchr(temp, '\0'));	
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

