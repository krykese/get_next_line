/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcosta <qcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:08:27 by qcosta            #+#    #+#             */
/*   Updated: 2022/06/24 16:58:24 by qcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define BUFFER_SIZE 5


int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
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
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (new_str == NULL)
		return (NULL);
	while (s[i] != '\n')
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	//free(s); ne peut pas se free tant que s est une constante
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
// une fonction qui retourne la string avant le \n.
// une fonction qui garde en memoire la string apres le \n et l'ajoute au prochain appel
// de get_next_line
//une fonction qui lit dans le file descriptor
char	*ft_read(int fd)
{
	int		ret;
	static char	*buf;
	char	*new_str;
	
	//ret = read(fd, buf, BUFFER_SIZE);
	//new_str = NULL;  segmentation fault a cause de cette connerie
	buf =  (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
	
	while (!strchr(new_str, '\n') && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		printf("comportement du buf : %s\n",buf);
		new_str = ft_strjoin(new_str, buf);
		
		printf("comportement du buf apres strjoin : %s\n",new_str);
	}
	//free (buf);
	return new_str;
}

// une fonction qui stock apres le \n

/*char	*get_line(int fd, char *line)
{
	int ret;
	static char *buf;
	static char	*after_chariot;
	buf =  (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (ret = read(fd, buf, BUFFER_SIZE))
	{
		buf[ret] = '\0';
		//if (ft_strchr(buf, '\n'))
			return (buf);
	}
	
	
	
}*/

/*char	*get_next_line(int fd)
{
	int	ret;
	static char *buf;
	//static char *buf[BUFFER_SIZE + 1];
	
	
	while (!(ft_strchr(buf, '\n')))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		//if (ft_strchr(buf, '\n'))
			//return (buf);
		buf[ret] = '\0';  // la fonction read ne lit pas le caractere nul.
		//ft_putstr(buf);
		
	}
	
	return (buf);
	//return (NULL);
	//return (buf);
}*/


// read va lire dans un fichier et le stocker dans une varible pointeur sur void.
int	main()
{
	int	fd;
	//char	*ret;
	char *str;
	//char buf[BUF_SIZE + 1];
	
	fd = open("42.txt", O_RDONLY);
	/*if (fd == -1)
	{
		ft_putstr("open() error");
		return (1);
	}*/
	
	//ret = get_next_line(fd);

	str = ft_read(fd);
	
	printf("%s\n", str);
	
	printf("%s\n", ft_strdup_before_n(str));
	free(str);
	close(fd);
	//printf("fichier lut :%s", ret);

	
	//ret = read(fd, buf, BUF_SIZE);
	//buf[ret] = '\0';
	
	
	//ft_get_nbr(ret);
	//ft_putstr(buf);
	//printf("%s", ret);
	//ft_putnbr(ret);
	return (0);
}