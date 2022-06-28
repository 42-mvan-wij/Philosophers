/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 16:08:28 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/06/27 16:09:24 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdbool.h>

int		ft_atoi(const char *str, bool *had_overflow);
bool	ft_atoi_strict(char *str, int *result_ptr, bool *had_overflow);

#endif
