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
	if (len == 0 || check_sorted(info->a))
		return ;
	if (len == 2 && *(int *)info->a->content > *(int *)info->a->next->content)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){sa}, 1);
	else if (len == 3)
		algo3(info, info->a);
	else if (len == 5 || len == 4)
		algo5(info);
	if (len > 5)
		initialize_algo(info);
}

void	algo3(t_info *info, t_list *list)
{
	int	a;
	int	b;
	int	c;

	a = *(int *)list->content;
	b = *(int *)list->next->content;
	c = *(int *)list->next->next->content;
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

void	algo5(t_info *info)
{
	t_list	*min;
	t_cost	*cost;

	min = get_min(info->a);
	cost = ft_calloc(1, sizeof(t_cost));
	best_rotation_to_top(info, cost, 'a', min->index);
	execute_rotation(info, cost);
	pb(info, 1);
	if (ft_lstsize(info->a) == 4)
	{
		min = get_min(info->a);
		best_rotation_to_top(info, cost, 'a', min->index);
		execute_rotation(info, cost);
		pb(info, 1);
	}
	free(cost);
	algo3(info, info->a);
	execute_instruction(info, 1, (int (*[])(t_info *, int)){pa, pa}, 2);
}
