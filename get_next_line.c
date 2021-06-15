/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 18:29:22 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/06/08 18:29:22 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	found;

	found = (char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == found)
		return ((char *)s + i);
	return (NULL);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i1;
	int		i2;
	char	*cc;

	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	cc = (char *)malloc(sizeof(char) * (i1 + i2 + 1));
	if (cc == NULL)
		return (NULL);
	ft_strlcpy(cc, s1, i1 + 1);
	ft_strlcat(cc + i1, s2, i2 + 1);
	return (cc);
}

static int	ft_transfer(char *plus, char **line)
{
	int	i;
	char *tmp;

	i = 0;
	while (plus[i] != '\n' && plus[i] != '\0')
		i++;
	if (plus[i] == '\0')
	{
		*line = ft_strdup(plus);
		free(plus);
		return (0);
	}
	*line = ft_substr(plus, 0, i);
	tmp = ft_strdup(plus + i + 1);
	free(plus);
	plus = tmp;
	return (1);
}

static int	ft_guide(int index, char *plus, char **line)
{
	if (index < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	else if (index == 0 && plus == NULL )
		return (0);
	else
		return (ft_transfer(plus, line));
}

int	get_next_line(int fd, char **line)
{
	t_variable	vr;

	vr.buf = (char *)malloc(BUFFER_SIZE + 1);
	if (vr.buf == NULL)
		return (-1);
	vr.index = read(fd, vr.buf, BUFFER_SIZE) > 0;
	while (vr.index > 0)
	{
		vr.buf[vr.index] = '\0';
		if (vr.plus == NULL)
			vr.plus = ft_strdup(vr.buf);
		else
		{
			vr.tmp = ft_strjoin(vr.plus, vr.buf);
			free(vr.plus)
			vr.plus = vr.tmp;
		}
		if (ft_strchr(vr.plus, '\n'))
			break ;
		vr.index = read(fd, vr.buf, BUFFER_SIZE) > 0;
	}
	free(vr.buf);
	return (ft_guide(vr.index, vr.plus, vr.line));
}
