/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoTurk.h                                         :+:      :+:    :+:   */
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

/*
 * Retourne le nombre le plus proche inférieur à val
 */
static t_list	*find_closest_less(t_list *current, int val)
{
	t_list	*number;
	int		content;

	number = NULL;
	while (current)
	{
		content = *(int *)current->content;
		if (content < val && (number == NULL
				|| content > *(int *)number->content))
			number = current;
		current = current->next;
	}
	return (number);
}

/*
 * Retourne le nombre le plus proche supérieur à val
 */
static t_list	*find_closest_greater(t_list *current, int val)
{
	t_list	*number;
	int		content;

	number = NULL;
	while (current)
	{
		content = *(int *)current->content;
		if (content > val && (number == NULL
				|| content < *(int *)number->content))
			number = current;
		current = current->next;
	}
	return (number);
}

static void	calcul_place_in(t_info *info, char stack, int val, t_cost *cost)
{
	t_list	*nmax;
	t_list	*nmin;

	if (stack == 'a')
	{
		nmax = get_max(info->a);
		nmin = get_min(info->a);
		if (val > *(int *)nmax->content && val < *(int *)nmin->content)
			nmax = find_closest_less(info->a, val);
		best_rotation_to_top(info, cost, 'a', nmax->index);
	}
	else if (stack == 'b')
	{
		nmax = get_max(info->b);
		nmin = get_min(info->b);
		if (val < *(int *)nmax->content && val > *(int *)nmin->content)
			nmax = find_closest_less(info->b, val);
		best_rotation_to_top(info, cost, 'b', nmax->index);
	}
}

static t_cost	*search_rentability(t_info *info)
{
	t_list	*current;
	t_cost	*tmp;
	t_cost	*best_cost;

	current = info->a;
	tmp = ft_calloc(sizeof(t_cost), 1);
	best_cost = ft_calloc(sizeof(t_cost), 1);
	if (!best_cost || !tmp)
		stop(info, 1);
	best_cost->rot_common = info->len_a + info->len_b;
	best_cost->rota = info->len_a + info->len_b;
	best_cost->rotb = info->len_a + info->len_b;
	while (current)
	{
		tmp->rot_common = 0;
		tmp->rota = 0;
		tmp->rotb = 0;
		best_rotation_to_top(info, tmp, 'a', current->index);
		calcul_place_in(info, 'b', *(int *)current->content, tmp);
		calcul_fusion(info, tmp);
		if (ft_abs(tmp->rot_common) + ft_abs(tmp->rota)
			+ ft_abs(tmp->rotb) < ft_abs(best_cost->rot_common)
			+ ft_abs(best_cost->rota) + ft_abs(best_cost->rotb))
		{
			best_cost->rot_common = tmp->rot_common;
			best_cost->rota = tmp->rota;
			best_cost->rotb = tmp->rotb;
		}
		current = current->next;
	}
	return (free(tmp), best_cost);
}

void	initialize_algo(t_info *info)
{
	t_cost	*cost;
	t_list	*min_in_a;

	info->min = *(int *)get_min(info->a)->content;
	info->max = *(int *)get_max(info->a)->content;
	if (*(int *)info->a->content != info->min
		&& *(int *)info->a->content != info->max)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){pb, pb}, 2);
	else
		pb(info, 1);
	while (info->len_a > 0)
	{
		cost = search_rentability(info);
		execute_rotation(info, cost);
		free(cost);
		pb(info, 1);
	}
	while (info->b)
		pa(info, 1);
	cost = ft_calloc(sizeof(t_cost), 1);
	min_in_a = get_min(info->a);
	best_rotation_to_top(info, cost, 'a', min_in_a->index);
	execute_rotation(info, cost);
	free(cost);
}
