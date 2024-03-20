/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:35:44 by aubertra          #+#    #+#             */
/*   Updated: 2024/03/20 14:52:34 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char    *find_line(int fd, char *buffer);
static char     *fill_line(char *temp, char *left_char);
static char     *get_left_char(char *temp);
int				check_temp(char *temp, char *left_char);
char    *get_next_line(int fd)
{
	char		*buffer;
	static char	*left_char;
	char	*filled_line;
	char	*temp;
	char	*to_free;
		
	if (fd <= 0 || BUFFER_SIZE <= 0)
        	return (NULL);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	temp = find_line(fd, buffer);
	if (check_temp(temp, left_char) == 1)
		return (temp);
	if (check_temp(temp, left_char) == 0)
		return (NULL);
	if (!left_char)
		left_char = ft_calloc(sizeof(char), ft_strlen(temp) + 1);
	if (!left_char)
		return (NULL);
	filled_line = fill_line(temp, left_char);
	to_free = left_char;
	free(to_free);
	left_char = get_left_char(temp);
	if (!left_char[0])
		return (free(temp), free(left_char), NULL);
	return (free(temp), filled_line);
}

int	check_temp(char *temp, char *left_char)
{
	if (!temp) 
	{
		free(left_char);
		left_char = NULL;
		return (0);
	}
	if (!temp[0]) {
		temp = left_char;
		left_char = NULL;
		return (1);
	}
	return (2);
}




static char    *find_line(int fd, char *buffer)
{
	char	*temp;
	int	val_read;
	char	*to_free;

	temp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	while (!ft_strchr(temp, '\n'))
	{
		val_read = read(fd, buffer, BUFFER_SIZE);
		if (val_read == 0) 
			break;
		if (val_read <= 0)
		{
			free(buffer);
			return (free(temp), NULL);
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
	filled_line = ft_calloc(sizeof(char), ft_strlen(temp) + 2);
	if (!filled_line)
		return (NULL);
	while (temp[i] != '\0' && temp[i] != '\n')
	{
		filled_line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
		filled_line[i] = '\n';
	filled_line[i + 1] = '\0';
	to_free = filled_line;
	filled_line = ft_strjoin(left_char, filled_line);
	free(to_free);
	return (filled_line);
}

static char	*get_left_char(char *temp)
{
	char	*left_char;
	char	*to_free;

	left_char = ft_calloc(sizeof(char), ft_strlen(temp) + 1);
	if (!left_char)
		return (NULL);
	to_free = left_char;
	if (ft_strchr(temp, '\n'))
		left_char = ft_strdup(ft_strchr(temp, '\n'));
	else
		left_char = ft_strdup(temp);
	free(to_free);
	return (left_char);
}


int main(int ac, char **av)
{
	int fd;
	
	(void)ac;
	fd = open(av[1], O_RDONLY);
	char *str;

	/* while ((str = get_next_line(fd))) { */
	/* 	printf("%s\n", str); */
	/* 	free(str); */
	/* } */
	for (int i = 0; i < 3; i++) {
		str = get_next_line(fd);
		printf("%s", str);
	}
	close(fd);
	return (0);
}
