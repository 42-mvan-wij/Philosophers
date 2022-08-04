/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   append.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:31:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 12:51:21 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst == src)
		return (dst);
	while (n)
	{
		((char *)dst)[n - 1] = ((char *)src)[n - 1];
		n--;
	}
	return (dst);
}

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*append(char *src, char *dst, size_t dst_size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len <= dst_size - 1)
	{
		ft_memcpy(dst, src, (src_len + 1) * sizeof(char));
		return (&dst[src_len]);
	}
	else if (dst_size != 0)
	{
		ft_memcpy(dst, src, (dst_size - 1) * sizeof(char));
		dst[dst_size - 1] = '\0';
		return (&dst[dst_size - 1]);
	}
	return (&dst[0]);
}
