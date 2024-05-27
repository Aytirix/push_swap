/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:49 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 04:05:20 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	controller(int ac, char **av, t_info *info)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		while (*av[i])
		{
			while (*av[i] && !ft_isdigit(*av[i]) && *av[i] != '-')
				if (*av[i++] != ' ')
					stop(info, 1);
			if (!*av[i])
				break ;
			check_exist(info, av, i);
			ft_lstadd_back(&info->a, ft_lstnew(info->temp));
			while (*av[i] && (ft_isdigit(*av[i]) || *av[i] == '-'))
				av[i]++;
		}
	}
	info->temp = NULL;
}

void	check_exist(t_info *info, char **av, int i)
{
	t_list	*temp;

	info->temp = (int *)malloc(sizeof(int));
	if (!info->temp)
		stop(info, 1);
	*(info->temp) = ft_atoi(av[i]);
	if ((*(info->temp) == 0 && ft_strncmp(av[i], "0", 1)) || (*(info->temp) == \
			-1 && ft_strncmp(av[i], "-1", 2)))
		stop(info, 1);
	temp = info->a;
	while (temp && info->temp)
	{
		if (*(int *)temp->content == *info->temp)
			stop(info, 1);
		temp = temp->next;
	}
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac == 1)
		stop(&info, 0);
	info.a = NULL;
	info.b = NULL;
	info.instruction = NULL;
	info.temp = NULL;
	controller(ac, av, &info);
	print_list(info.a, 'd');
	stop(&info, 0);
	return (0);
}
