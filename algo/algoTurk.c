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
		if (max->content > lst->content)
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
		if (min->content < lst->content)
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
t_cost	*best_rotation_to_top(t_list *current, int size, int target_index)
{
	t_cost	*cost;

	cost->rot_common = 0;
	cost->rot = 0;
	cost->rota = 0;
	cost->rotb = 0;
	if (size / 2 >= target_index)
		cost->rot = target_index;
	else
		cost->rot = -1 * (size - target_index);
	return (cost);
}

/*
 * Retourne le nombre le plus proche inférieur à val
 */
static t_list	*find_closest_less(t_list *current, int val)
{
	t_list	*number;
	int		content;

	while (current)
	{
		content = *(int *)current->content;
		if (content < val && content > *(int *)number->content)
		{
			printf("Content %d\n", *(int *)current->content);
			number = current;
			printf("Number %d\n", *(int *)number->content);
		}
		current = current->next;
	}
	return (number);
}

static void	calcul_place_in_b(t_info *info, int val, t_cost *cost)
{
	t_list	*number;

	number = get_max(info->b);
	if (val > *(int *)number->content)
	{
		cost->rotb = best_rotation_to_top(info->b, info->len_b,
				number->index)->rot;
		return ;
	}
	number = get_min(info->b);
	if (val < *(int *)number->content)
	{
		cost->rotb = best_rotation_to_top(info->b, info->len_b,
				number->index)->rot;
		return ;
	}
	number = find_closest_less(info->b, val);
	cost->rotb = best_rotation_to_top(info->b, info->len_b, number->index)->rot;
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
	while (current)
	{
		tmp = best_rotation_to_top(info->a, info->len_a, current->index);
		printf("tmp %d\n", *(int *)current->content);
		calcul_place_in_b(info, *(int *)current->content, tmp);
		printf("Cost %d %d %d %d\n", tmp->rot_common, tmp->rot, tmp->rota, tmp->rotb);
		calcul_fusion(info, tmp);
		if (tmp->rot_common + tmp->rota + tmp->rotb < best_cost->rot_common
			+ best_cost->rota + best_cost->rotb)
			best_cost = tmp;
		if (tmp->rot_common + tmp->rota + tmp->rotb == 0)
			break ;
		current = current->next;
	}
	return (best_cost);
}

void	initialize_algo(t_info *info)
{
	t_cost	*cost;

	printf("Start\n");
	printf("List a\n");
	print_list(info->a, 'd');
	printf("List b\n\n\n");
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
		printf("Cost exe %d %d %d %d\n", cost->rot_common, cost->rot, cost->rota, cost->rotb);
		execute_rotation(info, cost);
		pb(info, 1);
		printf("List b\n");
		print_list(info->b, 'd');
	}
	algo3(info, info->a);
	ft_lstupdate(&info->a);
	printf("\n\nEnd End End End End End\n\n");
	printf("List a\n");
	print_list(info->a, 'd');
	printf("List b\n");
	print_list(info->b, 'd');
}
