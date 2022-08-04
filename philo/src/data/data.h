/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 13:19:08 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:19:55 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "../structs.h"

void		free_data(t_data *data);
t_status	create_data(int argc, char **argv, t_data *data);

#endif
