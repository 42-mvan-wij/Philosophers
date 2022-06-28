/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:33:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/06/27 16:07:43 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

/**
 * Converts @p str to an integer
 * @param str
 * @return
 */
int	ft_atoi(const char *str, bool *had_overflow)
{
	int		offset;
	long	result;
	int		is_neg;

	if (had_overflow != NULL)
		*had_overflow = false;
	offset = 0;
	while (str[offset] != '\0' && ft_isspace(str[offset]))
		offset++;
	result = 0;
	is_neg = (str[offset] == '-');
	if (is_neg || str[offset] == '+')
		offset++;
	while (ft_isdigit(str[offset]))
	{
		result *= 10;
		result -= str[offset] - '0';
		if (had_overflow != NULL && ((is_neg && result != (int)result) \
		|| (!is_neg && (-result) != (int)-result)))
			*had_overflow = true;
		offset++;
	}
	if (is_neg)
		return (result);
	return (-result);
}

static void	ft_atoi_strict_skipper(char *str, size_t *i, size_t *non_digits)
{
	while (ft_isspace(str[*i]))
	{
		(*non_digits)++;
		(*i)++;
	}
	if (str[*i] == '+' || str[*i] == '-')
	{
		(*non_digits)++;
		(*i)++;
	}
	while (ft_isdigit(str[*i]))
		(*i)++;
	while (ft_isspace(str[*i]))
	{
		(*non_digits)++;
		(*i)++;
	}
}

/**
 * Converts @p str to an integer
 * @param str
 * @param result_ptr
 * @return
 */
bool	ft_atoi_strict(char *str, int *result_ptr, bool *had_overflow)
{
	size_t	i;
	size_t	non_digits;

	*had_overflow = false;
	if (str == NULL)
		return (false);
	non_digits = 0;
	i = 0;
	ft_atoi_strict_skipper(str, &i, &non_digits);
	if (i == non_digits || str[i] != '\0')
		return (false);
	*result_ptr = ft_atoi(str, had_overflow);
	return (true);
}
