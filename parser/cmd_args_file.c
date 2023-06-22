/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:33:18 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 03:38:17 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

t_token	*cmd_args_file(t_token *token_cmd, char **symb_file)
{
	int			flag;
	char		*result;
	char		*prev_str;
	char		*to_free;
	t_token		*cmd_arg;
	t_token		*symb_fl;
	t_token		*prev;
	t_token		*tmp;

	flag = -1;
	cmd_arg = NULL;
	symb_fl = NULL;
	if (token_cmd)
	{
		while (token_cmd)
		{
			if (token_cmd->e_type == 0 || token_cmd->e_type == 1)
			{
				ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
						token_cmd->e_type));
				prev = token_cmd;
				token_cmd = token_cmd->next;
				if (token_cmd && token_cmd->e_type == prev->e_type)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
							token_cmd->e_type));
					token_cmd = token_cmd->next;
				}
				while (token_cmd && token_cmd->e_type == 4)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
							token_cmd->e_type));
					token_cmd = token_cmd->next;
				}
				while (token_cmd && (token_cmd->e_type == 3|| token_cmd->e_type == 7))
				{
					check_tild(&token_cmd);
					prev_str = ft_strdup(token_cmd->value);
					expand(&token_cmd->value);

					if (token_cmd->value[0]=='\0')
						token_cmd->value = prev_str;
					function_free((void**)&prev_str, 1);
					expand_with_quote(token_cmd);
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
							token_cmd->e_type));
					token_cmd = token_cmd->next;
				}
				flag = 0;
			}
			else if (token_cmd && token_cmd->e_type == 4)
			{
				while (token_cmd && token_cmd->e_type == 4)
				{
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value,
							token_cmd->e_type));
					token_cmd = token_cmd->next;
				}
			}
			else
			if (token_cmd && token_cmd->e_type == 3)
			{
				tmp = token_cmd;
				result = ft_strdup("");

				while (tmp && (tmp->e_type == 3 || tmp->e_type == 5 || tmp->e_type == 6))
				{
					//  leak
					to_free = result;
					result = ft_strjoin(result, expand_with_quote(tmp));
					function_free((void**)&to_free, 1);

					prev = tmp;
					tmp = tmp->next;
				}

					token_cmd = prev;
					function_free((void**)&token_cmd->value , 1);
					token_cmd->value = ft_strdup(result);

					function_free((void**)&result , 1);
					check_tild(&token_cmd);
					expand(&token_cmd->value);

				remove_s_d_qoute(&token_cmd->value);
				ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value,
						token_cmd->e_type));
				token_cmd = token_cmd->next;
				flag = 1;

			}
			else
			if (token_cmd)
			{
				if (token_cmd && (token_cmd->e_type == 5 || token_cmd->e_type == 6))
				{
					tmp = token_cmd;
					//  leak
					result = ft_strdup("");
					while (tmp && (tmp->e_type == 5 || tmp->e_type == 6))
					{
						to_free = result;
						result = ft_strjoin(result, expand_with_quote(tmp));
						function_free((void**)&to_free, 1);
						prev = tmp;
						tmp = tmp->next;
					}

					function_free((void**)&token_cmd->value, 1);
					token_cmd = prev;
					token_cmd->value = result;
				}
				else
					expand(&token_cmd->value);

				if (flag == 0)
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
							token_cmd->e_type));
				else if (flag == 1 || flag == -1)
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value,
							token_cmd->e_type));
				token_cmd = token_cmd->next;
			}
		}
		*symb_file = tokens_cmd_to_string(symb_fl);
		function_free((void**)&symb_fl, 2);
	}
	return (cmd_arg);
}
