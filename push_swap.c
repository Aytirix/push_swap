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

int	main(int ac, char **av)
{
	t_info	info;

	info.a = NULL;
	info.b = NULL;
	info.instruction = NULL;
	info.temp = NULL;
	if (ac == 1)
		stop(&info, 0);
	controller(ac, av, &info);
	printf("\nmain");
	printf("\nList A:\n");
	print_list(info.a, 'd');
	printf("\n\nTRAITEMENT\n\n");
	algo(&info);
	printf("\n\n FIN  TRAITEMENT\n\n");
	printf("\nInstruction %d:\n", ft_lstsize(info.instruction));
	print_list(info.instruction, 's');
	printf("\nList A trier:\n");
	print_list(info.a, 'd');
	printf("\nList B:\n");
	print_list(info.b, 'd');
	stop(&info, 0);
	return (0);
}
