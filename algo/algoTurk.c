#include "../push_swap.h"
#include <limits.h>
#include <stdlib.h>

t_list	*get_max(t_list *lst, int **ignore)
{
	t_list	*max;
	int		is_ignored;
	int		i;

	max = NULL;
	while (lst)
	{
		is_ignored = 0;
		i = 0;
		while (i < 3 && ignore && ignore[i])
		{
			if (*(int *)(lst->content) == *ignore[i])
			{
				is_ignored = 1;
				break ;
			}
			i++;
		}
		if (!is_ignored && (!max
				|| *(int *)(lst->content) > *(int *)(max->content)))
			max = lst;
		lst = lst->next;
	}
	return (max);
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

int	find_insert_position(t_info *info, int value, int *rotation_direction,
		int *rotation_count)
{
	t_list	*current;
	int		index;
	int		first_larger_index;
	int		total_elements;

	current = info->b;
	index = 0;
	first_larger_index = -1;
	total_elements = ft_lstsize(info->b);
	while (current)
	{
		if (*(int *)current->content > value && first_larger_index == -1)
			first_larger_index = index;
		current = current->next;
		index++;
	}
	if (first_larger_index != -1)
	{
		*rotation_direction = -1;
		*rotation_count = total_elements - first_larger_index - 1;
	}
	else
	{
		*rotation_direction = 0;
		*rotation_count = 0;
	}
	return (first_larger_index);
}

void	apply_pre_insertion_rotations(t_info *info, int rotation_direction,
		int rotation_count)
{
	printf("Rotation direction: %d\n", rotation_direction);
	printf("Rotation count: %d\n", rotation_count);
	while (rotation_count-- > 0)
	{
		if (rotation_direction == 1)
			rb(info, 1);
		else if (rotation_direction == -1)
			rrb(info, 1);
	}
}

void	reorganize_b(t_info *info)
{
	t_list	*max;
	int		max_position;
	int		size_b;

	max = get_max(info->b, NULL);
	max_position = get_position(info->b, max);
	size_b = ft_lstsize(info->b);
	if (max_position <= size_b / 2)
	{
		while (max_position > 0)
		{
			rb(info, 1);
			max_position--;
		}
	}
	else
	{
		max_position = size_b - max_position;
		while (max_position > 0)
		{
			rrb(info, 1);
			max_position--;
		}
	}
}

static int	is_one_of_the_largest(t_info *info, int value)
{
	t_list	*temp;

	if (info->max3 == NULL)
	{
		info->max3 = ft_calloc(3, sizeof(int *));
		info->max3[0] = (int *)(get_max(info->a, NULL)->content);
		info->max3[1] = (int *)(get_max(info->a, info->max3)->content);
		info->max3[2] = (int *)(get_max(info->a, info->max3)->content);
	}
	return (value == *(info->max3[0]) || value == *(info->max3[1])
		|| value == *(info->max3[2]));
}

void	sort_stack(t_info *info)
{
	int	value;
	int	position;
	int	rotation_direction;
	int	rotation_count;

	while (ft_lstsize(info->a) > 3)
	{
		value = *(int *)(info->a->content);
		if (is_one_of_the_largest(info, value))
			ra(info, 1);
		else
		{
			pb(info, 1);
			break ;
		}
	}
	while (ft_lstsize(info->a) > 3)
	{
		value = *(int *)(info->a->content);
		if (is_one_of_the_largest(info, value))
		{
			ra(info, 1);
			continue ;
		}
		position = find_insert_position(info, value, &rotation_direction,
				&rotation_count);
		apply_pre_insertion_rotations(info, rotation_direction, rotation_count);
		pb(info, 1);
		printf("Inserted %d in B with position %d\n", value, position);
		printf("list B:\n");
		print_list(info->b, 'd');
	}
	printf("prev reorganize_b\n");
	printf("list B:\n");
	print_list(info->b, 'd');
	reorganize_b(info);
	printf("After reorganize_b\n");
	printf("list B:\n");
	print_list(info->b, 'd');
	// Trier les trois derniers éléments dans A
	algo3(info, info->a);
	printf("Algo3 done\n");
	printf("list A:\n");
	print_list(info->a, 'd');
	// Rapatrier tous les éléments de B vers A en maintenant l'ordre
	while (ft_lstsize(info->b) > 0)
	{
		pa(info, 1);
	}
	printf("After pa\n");
	printf("list A:\n");
	print_list(info->a, 'd');
}
