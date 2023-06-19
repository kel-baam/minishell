/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:02:55 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/18 18:20:17 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "token.h"
#include "lexer.h"
#include "../minishell.h"

int count_token_cmd(t_token *token)
{
	int		i;
	t_token *tmp;

	i = 0;
	tmp = token;
	if (token)
	{
		while (tmp && tmp->value[0] != '|')
		{
			i++;
			tmp = tmp->next;
		}
	}
	return (i);
}

int str_search(char *buffer, char c)
{
	int i;

	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] == c)
				return (1);
			i++;
		}
	}
	return (0);
}
