/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 16:08:28 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 12:54:47 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "../structs.h"

char		*append(char *src, char *dst, size_t dst_size);

int			ft_atoi(const char *str, bool *had_overflow);
bool		ft_atoi_strict(char *str, int *result_ptr, bool *had_overflow);

t_status	set_err(t_status err);
t_status	get_err(void);
void		print_err(void);

char		*ft_itob(int64_t nbr, char *res, size_t res_size);

bool		print_msg_unchecked(t_phil *phil, char *msg);
bool		print_msg(t_phil *phil, char *msg);

void		msleep(unsigned int ms, t_data *data);

long		get_current_timestamp(t_data *data);

#endif
