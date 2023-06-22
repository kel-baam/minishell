/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:33:12 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 04:00:12 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

void	expand(char **token)
{
	int i;
	char *result;
	char *c_string;
	char *value;
	char *store;
	int flag;
	int len;
	int pos_dollar;

	flag = 0;
	i = 0;
	store = ft_strdup("");
	if (token && *token)
	{
		pos_dollar = searching_for_char(*token, '$');
		if (pos_dollar != -1)
		{
			store = ft_substr(*token, 0, pos_dollar);
			*token = ft_substr(*token, pos_dollar, ft_strlen(*token)
					- pos_dollar);
		}
		len = ft_strlen(*token);
		if ((*token)[i] == '$')
		{
			while (i < len)
			{
				if ((*token)[i] && (*token)[i + 1] && (*token)[i] == '$'
					&& (*token)[i + 1] == '$')
				{
					i += 2;
					flag = 1;
				}
				else
				{
					if (!ft_strcmp(*token, "$") || ((*token)[i] == '$'
							&& !ft_isalnum((*token)[i + 1])))
						store = ft_strjoin(store, "$");
					if ((*token)[i] == '$')
					{
						i++;
						flag = 0;
					}
					else
						flag = 1;
					result = ft_strdup("");
					while ((*token)[i] && (ft_isalnum((*token)[i])
							|| (*token)[i] == '_'))
					{
						c_string = char_to_string((*token)[i]);
						result = ft_strjoin(result, c_string);
						i++;
					}
					if (ft_strlen(result) > 1)
					{
						if (!flag)
							value = get_env(result);
						else
							value = ft_strdup(result);
						if (value)
							store = ft_strjoin(store, value);
						else
							store = ft_strjoin(store, ft_strdup(""));
						flag = 0;
					}
					else
					{
						while ((*token)[i] && !ft_isalnum((*token)[i])
							&& (*token)[i] != '_' && (*token)[i] != '$')
						{
							c_string = char_to_string((*token)[i]);
							result = ft_strjoin(result, c_string);
							i++;
						}
						store = ft_strjoin(store, result);
					}
				}
				result = NULL;
			}
			*token = store;
		}
	}
}