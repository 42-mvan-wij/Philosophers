/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_struct.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:37:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/09 11:10:42 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_STRUCT_H
# define ERROR_STRUCT_H

typedef enum e_status
{
	OK,
	ERROR,
	E_TOO_FEW_ARGS,
	E_TOO_MANY_ARGS,
	E_EXPECTED_INTEGER,
	E_MALLOC_FAIL,
	E_WRITE_FAIL,
	E_PHIL_TOO_LITTLE,
	E_DIE_TOO_LITTLE,
	E_EAT_TOO_LITTLE,
	E_SLEEP_TOO_LITTLE,
	E_NUM_EAT_TOO_LITTLE,
	E_THREAD_FAIL,
}	t_status;

#endif
