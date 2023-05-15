/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:41:46 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/11 18:13:15 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len ++;
	return (len);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	*ptr;

	if (s == NULL)
		return (NULL);
	ptr = (char *)s;
	if (c == 0)
		return (ptr + ft_strlen_gnl(s));
	while (*ptr)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

char	*ft_strdup_gnl(const char *s, int i)
{
	int		len;
	int		index;
	char	*dest;

	index = 0;
	if (i < ft_strlen_gnl (s))
		len = i;
	else
		len = ft_strlen_gnl(s);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	while (index < len)
	{
		dest[index] = s[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char *static_buff, char const *read_buffer)
{
	size_t	len;
	size_t	i;
	char	*joined;

	if (static_buff == NULL)
		static_buff = ft_strdup_gnl("", 0);
	if (read_buffer == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen_gnl(static_buff) + ft_strlen_gnl(read_buffer) + 1;
	joined = (char *)malloc(len * sizeof(char));
	if (!joined)
		return (NULL);
	while (static_buff[i])
	{
		joined[i] = static_buff[i];
		i ++;
	}
	while (*read_buffer)
		joined[i++] = *read_buffer++;
	joined[i] = '\0';
	free(static_buff);
	return (joined);
}
