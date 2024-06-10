/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:49 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 04:05:20 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	execute_instruction(t_info *info, int instruction, int (**ins)(t_info *info,
			int instruction), int len)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < len)
		result += ins[i++](info, instruction);
	return (result);
}

int	check_sorted(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp->next)
	{
		if (*(int *)temp->content > *(int *)temp->next->content)
			return (0);
		temp = temp->next;
	}
	return (1);
}
