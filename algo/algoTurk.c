#include "../push_swap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static t_list	*get_max(t_list *lst)
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

static t_list	*get_min(t_list *lst)
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

	* Calcul le nombre de rotation nécéssaire pour mettre un nombre en premiere position
 * retourne la quantité de rotation nécéssaire
 * Il retourne une valeur positive si ra
 * Il retourne une valeur négative si rra
 */
static void	best_rotation_to_top(t_info *info, t_cost *cost, char stack,
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

static void	calcul_place_in_b(t_info *info, int val, t_cost *cost)
{
	t_list	*nmax;
	t_list	*nmin;

	nmax = get_max(info->b);
	nmin = get_min(info->b);
	if (val < *(int *)nmax->content && val > *(int *)nmin->content)
		nmax = find_closest_less(info->b, val);
	best_rotation_to_top(info, cost, 'b', nmax->index);
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
static void	calcul_fusion(t_info *info, t_cost *cost)
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
		calcul_place_in_b(info, *(int *)current->content, tmp);
		calcul_fusion(info, tmp);
		if (ft_abs(tmp->rot_common) + ft_abs(tmp->rota) + ft_abs(tmp->rotb)
			< ft_abs(best_cost->rot_common) + ft_abs(best_cost->rota)
			+ ft_abs(best_cost->rotb))
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
	t_cost *cost;

	info->min = *(int *)get_min(info->a)->content;
	info->max = *(int *)get_max(info->a)->content;
	if (*(int *)info->a->content != info->min
		&& *(int *)info->a->content != info->max)
		execute_instruction(info, 1, (int (*[])(t_info *, int)){pb, pb}, 2);
	else
		pb(info, 1);
	while (info->len_a > 3)
	{
		cost = search_rentability(info);
		execute_rotation(info, cost);
		free(cost);
		pb(info, 1);
	}
	algo3(info, info->a);

	// remettre le plus petit nombre de b en haut de la pile
	// t_list *min = get_max(info->b);
	// cost = ft_calloc(sizeof(t_cost), 1);
	// cost->rot_common = 0;
	// cost->rota = 0;
	// cost->rotb = 0;
	// best_rotation_to_top(info, cost, 'b', min->index);
	// execute_rotation(info, cost);
	// free(cost);
	while (info->b)
		pa(info, 1);
}
