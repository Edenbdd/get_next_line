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

char    *get_next_line(int fd)
{
    char    *buffer;
    char    *left_char;
    char    *filled_line;
    if (fd <= 0)
        return (NULL);
    buffer = malloc(BUFFER_SIZE +1);
    left_char = "";
    filled_line = fill_buffer(fd, left_char, buffer);
    free(buffer);
    return (filled_line);
}

char    *fill_buffer(int fd, char *left_char, char *buffer)
{
    read(fd, buffer, 10);
    left_char ++;
    return (buffer);
}
/*
char    *get_left_char(char *line_buffer)
{

}
*/
int main(void)
{
    int fd;
    
    fd = open("test.txt", O_RDONLY);
    printf("%s\n", get_next_line(fd));
    return (0);
}