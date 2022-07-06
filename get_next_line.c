/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcosta <qcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:08:27 by qcosta            #+#    #+#             */
/*   Updated: 2022/07/06 17:28:13 by qcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define BUFFER_SIZE 7


int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s[0])
		return (NULL);
	while (s && s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
		
	}
	if (c == 0)
		return ((char *)s + i);
	return (NULL);
}
char	*ft_strdup_before_n(char *s)
{
	char	*new_str;
	int		i;


	i = 0;
	new_str = (char *)malloc(ft_strlen(s) + 1);
	if (!new_str)
		return (NULL);
	while (s && s[i] != '\n')
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	//printf("result strdup before : %s\n",new_str);
	//free(s);
	return (new_str);
}

char	*ft_after_n(char *s)
{
	char	*new_str;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (s && s[i] != '\n')
		i++;
	new_str = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!new_str)
		return (NULL);
	while (s && s[i])
	{
		//j++;
		new_str[j++] = s[i++];
		//i++;
	}
	new_str[j] = '\0';
	return (new_str);
	
	
}
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}


void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
}

char	*ft_strdup(char *s)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (new_str == NULL)
		return (NULL);
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
// une fonction qui retourne la string avant le \n.
// une fonction qui garde en memoire la string apres le \n et l'ajoute au prochain appel
// de get_next_line
//une fonction qui lit dans le file descriptor
char	*ft_read(int fd)
{
	int		ret;
	char	*buf;
	char	*new_str;
	char	*tmp;
	
	ret = 1;
	
	//new_str = NULL;  segmentation fault a cause de cette connerie
	buf =  (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
	new_str = ft_strdup("");
	while (!ft_strchr(new_str, '\n') && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		printf("le buf est de taille 7 :%s\n",buf);
		//printf("comportement du buf : %s\n",buf);
		tmp = new_str;
		new_str = ft_strjoin(tmp, buf);

		
		free(tmp);
		
		//printf("comportement du buf apres strjoin : %s\n",new_str);
	}
	//printf("chaine join --------------:%s \n",new_str);
	//free (buf);
	return new_str;
}


char	*get_next_line(int fd)
{
	static char	*before_n;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
		
	printf("before_n : %s\n", before_n);
	before_n = ft_read(fd);
	printf("string join  -------------:%s\n", before_n);
	
	line = ft_strdup_before_n(before_n);
	printf("line ---------------------:%s\n", line);
	printf("before_n : %s\n", before_n);
	before_n = ft_after_n(before_n);
	printf("after_n ------------------: %s\n", before_n);
	
	return (line);
}


// read va lire dans un fichier et le stocker dans une varible pointeur sur void.
int	main()
{
	int	fd;
	char *line;
	
	
	fd = open("42.txt", O_RDONLY);

	line = "";

	while (line != NULL)
	{
		line = get_next_line(fd);
		 printf("main : %s\n", line);
		 
	}
	free(line);
	close(fd);

	return (0);
}