/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:02:55 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/06 13:46:52 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "token.h"
#include "lexer.h"
#include "tree.h"
#include "../minishell.h"

int count_token_cmd(token_t *token)
{
	int		i;
	token_t *tmp;

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

void cmd_args_file(token_t *token_cmd, char **cmd_args, char **symb_file)
{
	int		flag;
	token_t	*cmd_arg;
	token_t	*symb_fl;
	token_t	*prev;

	flag = -1;
	cmd_arg = NULL;
	symb_fl = NULL;
	if (token_cmd)
	{
		while (token_cmd)
		{
			if (token_cmd && (token_cmd->type == 0 || token_cmd->type == 1))
			{
				while (token_cmd && (token_cmd->type == 0 || token_cmd->type == 1))
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				while (token_cmd && token_cmd->type == 4)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				while (token_cmd && token_cmd->type == 3)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 0;
			}
			else if (token_cmd && token_cmd->type == 4)
			{
				if ((!cmd_arg && !symb_fl) || flag == 1)
				{
					while (token_cmd && token_cmd->type == 4)
					{
						ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
						token_cmd = token_cmd->next;
					}
				}
				else if (flag == 0)
				{
					while (token_cmd && token_cmd->type == 4)
					{
						ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
						token_cmd = token_cmd->next;
					}
				}
			}
			else if (token_cmd && token_cmd->type == 3)
			{
				while (token_cmd && (token_cmd->type == 3 ))
				{
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 1;
			}
		}
		*cmd_args = tokens_cmd_to_string(cmd_arg);
		*symb_file = tokens_cmd_to_string(symb_fl);
	}
}


t_command *insert_one_cmd(char *cmd_args, char *symb_file)
{
	int			i;
	int			flag;
	char		*file;
	t_list		*lst_redir_in;
	t_list		*lst_redir_out;
	t_command	*new;

	i = 0;
	flag = -1;
	new = malloc(sizeof(t_command));
	new->redir_out = malloc(sizeof(t_list));
	new->redir_in = malloc(sizeof(t_list));
	lst_redir_in = NULL;
	lst_redir_out = NULL;
	//
	if (cmd_args)
	{
		new->args = ft_split(cmd_args, ' ');
		new->cmd = ft_strdup(new->args[0]);
	}
	else
	{
		new->args[0] = NULL;
		new->cmd = NULL;
	}
	while (symb_file && symb_file[i])
	{
		if (symb_file[i] == '>')
		{
			flag = 0;
			if (symb_file[i + 1] == '>')
			{
				new->redir_out->content = init_red(0);
				i += 2;
			}
			else if (symb_file[i] == '>')
			{
				new->redir_out->content = init_red(1);
				i++;
			}
		}
		else if (symb_file[i] == '<')
		{
			flag = 1;
			if (symb_file[i + 1] == '<')
			{
				new->redir_in->content = init_red(0);
				i += 2;
			}
			else if (symb_file[i] == '<')
			{
				new->redir_in->content = init_red(1);
				i++;
			}
		}
		file = ft_strdup("");
		while (symb_file[i] && symb_file[i] == ' ')
			i++;
		while (symb_file[i] && symb_file[i] != ' ' && symb_file[i] != '<' && symb_file[i] != '>' )
		{
			file = ft_strjoin(file, char_to_string(symb_file[i]));
			i++;
		}
		if (flag == 0)
		{
			((t_red *)new->redir_out->content)->file_name = file;
			ft_lstadd_back(&lst_redir_out,ft_lstnew(new->redir_out->content));
		}
		else if (flag == 1)
		{
			((t_red *)new->redir_in->content)->file_name = file;
			ft_lstadd_back(&lst_redir_in, ft_lstnew(new->redir_in->content));
		}
		flag = -1;
	}
	new->redir_in =  lst_redir_in;
	new->redir_out = lst_redir_out;
	return (new);
}