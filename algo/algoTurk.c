#include "../push_swap.h"
#include <limits.h>
#include <stdlib.h>

t_list	*get_max(t_list *lst)
{
	t_list	*max;

	max = lst;
	while (lst)
	{
		if (*(int *)(lst->content) > *(int *)(max->content))
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
		if (*(int *)(lst->content) < *(int *)(min->content))
			min = lst;
		lst = lst->next;
	}
	return (min);
}

int	get_position(t_list *lst, t_list *node)
{
	int	position;

	position = 0;
	while (lst)
	{
		if (lst == node)
			break ;
		position++;
		lst = lst->next;
	}
	return (position);
}

void	calculate_cost(t_info *info, int position_a, int position_b)
{
	int	size_a;
	int	size_b;

	size_a = ft_lstsize(info->a);
	size_b = ft_lstsize(info->b);
	if (position_a <= size_a / 2)
		info->rotate_a = position_a;
	else
		info->rotate_a = position_a - size_a;
	if (position_b <= size_b / 2)
		info->rotate_b = position_b;
	else
		info->rotate_b = position_b - size_b;
	info->total = abs(info->rotate_a) + abs(info->rotate_b);
}

int	find_insert_position(t_info *info, int value)
{
	t_list	*current;
	int		position;
	int		min_total;
	int		best_position;

	current = info->b;
	position = 0;
	min_total = INT_MAX;
	best_position = 0;
	if (ft_lstsize(info->b) == 0)
		return (0);
	if (value > *(int *)(get_max(info->b)->content))
		return (0);
	if (value < *(int *)(get_min(info->b)->content))
		return (ft_lstsize(info->b) + 1);
	while (current)
	{
		if (*(int *)(current->content) > value && (current->next == NULL
				|| *(int *)(current->next->content) < value))
		{
			calculate_cost(info, 0, position + 1);
			if (info->total < min_total)
			{
				min_total = info->total;
				best_position = position + 1;
			}
		}
		current = current->next;
		position++;
	}
	return (best_position);
}

void	push_to_correct_position(t_info *info)
{
	int	i;

	i = -1;
	if (info->rotate_a < 0)
		while (++i < -info->rotate_a)
			rra(info, 1);
	else
		while (++i < info->rotate_a)
			ra(info, 1);
	pb(info, 1);
	i = -1;
	if (info->rotate_b < 0)
		while (++i < -info->rotate_b)
			rrb(info, 1);
	else
		while (++i < info->rotate_b)
			rb(info, 1);
}

void	sort_stack(t_info *info)
{
	t_list	*current;
	t_list	*cheapest;
	int		min_total;
	int		value;
	int		position;
	int		value;
	int		position;
	t_list	*min;

	printf("Initial state:\n");
	print_list(info->a, 'd');
	print_list(info->b, 'd');
	while (ft_lstsize(info->a) > 3)
	{
		current = info->a;
		cheapest = current;
		min_total = INT_MAX;
		while (current)
		{
			value = *(int *)(current->content);
			position = find_insert_position(info, value);
			calculate_cost(info, get_position(info->a, current), position);
			if (info->total < min_total)
			{
				min_total = info->total;
				cheapest = current;
			}
			current = current->next;
		}
		value = *(int *)(cheapest->content);
		position = find_insert_position(info, value);
		calculate_cost(info, get_position(info->a, cheapest), position);
		printf("Pushing element %d to position %d\n", value, position);
		push_to_correct_position(info);
		printf("After pushing element from A to B:\n");
		print_list(info->a, 'd');
		printf("List B: \n");
		print_list(info->b, 'd');
	}
	algo3(info, info->a);
	while (ft_lstsize(info->b) > 0)
		pa(info, 1);
	min = get_min(info->a);
	while (*(int *)(info->a->content) != *(int *)(min->content))
		ra(info, 1);
	printf("Final state:\n");
	print_list(info->a, 'd');
	print_list(info->b, 'd');
}
