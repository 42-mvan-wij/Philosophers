/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itob.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:31:45 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 12:43:36 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>

static void	ft_itob_internal(int64_t nbr, char **res, size_t *res_size)
{
	if (*res_size <= 1)
		return ;
	if (nbr / 10 != 0)
		ft_itob_internal(nbr / 10, res, res_size);
	else if (nbr < 0)
	{
		**res = '-';
		(*res)++;
		(*res_size)--;
		if (*res_size <= 1)
			return ;
	}
	if (nbr < 0)
		**res = '0' - (nbr % 10);
	else
		**res = '0' + (nbr % 10);
	(*res)++;
	(*res_size)--;
}

/**
 * Returns a pointer to after the last digit
 */
char	*ft_itob(int64_t nbr, char *res, size_t res_size)
{
	ft_itob_internal(nbr, &res, &res_size);
	if (res_size > 0)
		*res = '\0';
	return (res);
}
