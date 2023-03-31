/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:11:43 by kel-baam          #+#    #+#             */
/*   Updated: 2022/10/23 23:05:27 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			last_node = ft_lstlast(*lst);
			last_node->next = new;
		}
	}
}
