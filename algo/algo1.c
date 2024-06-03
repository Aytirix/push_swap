/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:49 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 04:05:20 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	algo(t_info *info)
{
	int	len;

	len = ft_lstsize(info->a);
	if (len == 2
		&& *(int *)info->a->content > *(int *)info->a->next->content)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){sa}, 1);
	else if (len == 3)
		algo3(info);
	else if (len > 3)
	{
		execute_instruction(info, 1, (int (*[])(t_info *, int)){pb, pb}, 2);
		turkAlgorithm(info);
	}
}

void	algo3(t_info *info)
{
	int a;
	int b;
	int c;

	a = *(int *)info->a->content;
	b = *(int *)info->a->next->content;
	c = *(int *)info->a->next->next->content;
	if (a > b && b < c && a < c)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){sa}, 1);
	else if (a > b && b > c)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){sa, rra}, 2);
	else if (a > b && b < c && a > c)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){ra}, 1);
	else if (a < b && b > c && a > c)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){rra}, 1);
	else if (a < b && b > c && a < c)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){sa, ra}, 2);
}