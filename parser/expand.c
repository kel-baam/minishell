/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:29:23 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/25 04:41:59 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

int	expand_advance_index(int *i, int *flag, char *token)
{
	if (token[(*i)] && token[(*i) + 1]
		&& token[(*i)] == '$' && token[(*i) + 1] == '$')
	{
		(*i) += 2;
		*flag = 1;
		return (1);
	}
	return (0);
}

typedef struct s_expand
{
	int		i;
	int		len;
	int		flag;
	char	*store;
	char	*result;
}	t_expand;

void	norm_function(t_expand *exp, char **token)
{
	if (!expand_advance_index(&(exp)->i, &(exp)->flag, *token))
	{
		check_dollar(*token, &(exp)->store, &(exp)->i, &(exp)->flag);
		(exp)->result = ft_strdup("");
		string_to_expand(*token, &(exp)->i, &(exp)->result);
		if (ft_strlen((exp)->result) > 1 || !ft_strcmp((exp)->result, "?"))
			expand_result(&(exp)->result, &(exp)->flag, &(exp)->store);
		else
			store_special_char(*token, &(exp)->i, &(exp)->result,
				&(exp)->store);
	}
}

void	expand(char **token)
{
	t_expand	exp;

	exp.i = 0;
	exp.flag = 0;
	if (token && *token && ft_strchr(*token, '$'))
	{
		store_data_before_dollar(token, &exp.store, &exp.len);
		if ((*token)[exp.i] == '$')
		{
			while (exp.i < exp.len)
			{
				norm_function(&exp, token);
				function_free((void **)&exp.result, 1);
			}
			function_free((void **)token, 1);
			*token = exp.store;
		}
	}
}
