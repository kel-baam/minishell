/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:06:28 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/25 00:53:04 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

void	store_data_before_dollar(char **token, char **store)
{
	int		pos_dollar;
	char	*to_free;

	pos_dollar = searching_for_char(*token, '$');
	if (pos_dollar != -1 && pos_dollar != 0)
	{
		to_free = *token;
		*store = ft_substr(*token, 0, pos_dollar);
		*token = ft_substr(*token, pos_dollar, ft_strlen(*token)
				- pos_dollar);
		function_free((void **)&to_free, 1);
	}
	else
		*store = ft_strdup("");
}

void	check_dollar(char *token, char **store, int *i, int *flag)
{
	char	*to_free;

	if (!ft_strcmp(token, "$") || (token[*i] == '$'
			&& !ft_isalnum(token[(*i) + 1]) && token[(*i) + 1] != '?'))
	{
		to_free = *store;
		*store = ft_strjoin(*store, "$");
		function_free((void **)&to_free, 1);
	}
	if (token[*i] == '$')
	{
		(*i)++;
		*flag = 0;
	}
	else
		*flag = 1;
}

void	string_to_expand(char *token, int *i, char **result)
{
	char	*c_string;
	char	*to_free;

	while (token[*i] && (ft_isalnum(token[*i])
			|| token[*i] == '_' || token[*i] == '?'))
	{
		to_free = *result;
		c_string = char_to_string(token[*i]);
		*result = ft_strjoin(*result, c_string);
		function_free((void **)&c_string, 1);
		function_free((void **)&to_free, 1);
		(*i)++;
	}
}

void	expand_result(char **result, int *flag, char **store)
{
	char	*value;
	char	*to_free;

	if (!*flag)
		value = get_env(*result);
	else
		value = *result;
	if (value)
	{
		to_free = *store;
		*store = ft_strjoin(*store, value);
		function_free((void **)&to_free, 1);
	}
	else
	{
		to_free = *store;
		*store = ft_strjoin(*store, "");
		function_free((void **)&to_free, 1);
	}
	*flag = 0;
}

void	store_special_char(char *token, int *i, char **result, char **store)
{
	char	*c_string;
	char	*to_free;

	while (token[*i] && !ft_isalnum(token[*i])
		&& token[*i] != '_' && token[*i] != '$')
	{
		to_free = *result;
		c_string = char_to_string(token[*i]);
		*result = ft_strjoin(*result, c_string);
		function_free((void **)&c_string, 1);
		function_free((void **)&to_free, 1);
		(*i)++;
	}
	to_free = *store;
	*store = ft_strjoin(*store, *result);
	function_free((void **)&to_free, 1);
}
