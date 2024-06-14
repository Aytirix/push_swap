/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoTurk_Utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:10 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 02:36:14 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

t_list	*get_max(t_list *lst)
{
	t_list	*max;

	max = lst;
	while (lst)
	{
		if (*(int *)lst->content > *(int *)max->content)
			max = lst;
		lst = lst->next;
	}
	return (max);
}

t_list	*get_min(t_list *lst)
{
	t_list	*min;

	min = lst;
	while (lst)
	{
		if (*(int *)lst->content < *(int *)min->content)
			min = lst;
		lst = lst->next;
	}
	return (min);
}

/*
 * Calcul le nombre de rotation pour mettre un nombre en 1er position
 * retourne la quantité de rotation nécéssaire
 * Il retourne une valeur positive si ra
 * Il retourne une valeur négative si rra
 */
void	best_rotation_to_top(t_info *info, t_cost *cost, char stack,
		int target_index)
{
	if (stack == 'a')
	{
		if (info->len_a / 2 >= target_index)
			cost->rota = target_index;
		else
			cost->rota = -1 * (info->len_a - target_index);
	}
	else if (stack == 'b')
	{
		if (info->len_b / 2 >= target_index)
			cost->rotb = target_index;
		else
			cost->rotb = -1 * (info->len_b - target_index);
	}
}

/*
 * Execute les rotations nécéssaires dans la liste a et b
 */
void	execute_rotation(t_info *info, t_cost *cost)
{
	int	i;

	i = -1;
	if (cost->rot_common > 0)
		while (++i < cost->rot_common)
			rr(info, 1);
	else
		while (++i < -cost->rot_common)
			rrr(info, 1);
	i = -1;
	if (cost->rota > 0)
		while (++i < cost->rota)
			ra(info, 1);
	else
		while (++i < -cost->rota)
			rra(info, 1);
	i = -1;
	if (cost->rotb > 0)
		while (++i < cost->rotb)
			rb(info, 1);
	else
		while (++i < -cost->rotb)
			rrb(info, 1);
}

/*
 * Fusionne les rotations communes ra rb en rr ou rra rrb en rrr
 */
void	calcul_fusion(t_cost *cost)
{
	while (cost->rota > 0 && cost->rotb > 0)
	{
		cost->rot_common++;
		cost->rota--;
		cost->rotb--;
	}
	while (cost->rota < 0 && cost->rotb < 0)
	{
		cost->rot_common--;
		cost->rota++;
		cost->rotb++;
	}
}
