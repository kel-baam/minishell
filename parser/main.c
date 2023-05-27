/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:26:25 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/27 16:41:23 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include "cmd.h"
#include "../minishell.h"

token_t	*ft_lstlast_token(token_t *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_token(token_t **lst, token_t *new)
{
	token_t	*last_node;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			last_node = ft_lstlast_token(*lst);
			last_node->next = new;
		}
	}
}

token_t *copy_of_list(token_t *original, int size)
{
	int		i;
	token_t *copy;

	i = 0;
	copy = NULL;
	if (original)
	{
		while (original && i < size)
		{
			ft_lstadd_back_token(&copy, init_token(original->value, original->type));
			original = original->next;
			i++;
		}
	}
	return (copy);
}

int	number_of_tokens_before_pipe(token_t *token)
{
	int i;

	i = 0;
	if (token)
	{
		while (token && token->value[0] != '|')
		{
			i++;
			token = token->next;
		}
	}
	return (i);
}

token_t *tokens_of_one_command(token_t **token)
{
	int		i;
	int		count_token;
	token_t *tokens_cmd;

	i = 0;
	tokens_cmd = NULL;

	if (token && *token)
	{
		count_token = number_of_tokens_before_pipe(*token);
		tokens_cmd = copy_of_list(*token ,count_token);
		while (*token  && i <= count_token)
		{
			*token = (*token)->next;
			i++;
		}
	}
	return (tokens_cmd);
}

char	*tokens_cmd_to_string(token_t *token)
{
	char	*buffer;

	buffer = ft_strdup("");
	if (token)
	{
		while (token)
		{
			buffer = ft_strjoin(buffer, token->value);
			token = token->next;
		}
	}
	return (buffer);
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
			if (token_cmd->type == 0 || token_cmd->type == 1)
			{
				ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
				prev = token_cmd;
				token_cmd = token_cmd->next;
				if (token_cmd->type == prev->type)
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
			else if (token_cmd->type == 3)
			{
				ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
				token_cmd = token_cmd->next;
				flag = 1;
			}
			else
			{
				if (flag == 0)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				else if (flag == 1)
				{
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
			}

		}
		*cmd_args = tokens_cmd_to_string(cmd_arg);
		*symb_file = tokens_cmd_to_string(symb_fl);
	}
}

t_red	*init_red(char *file_n, int flg)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	red->file_name = file_n;
	red->flag = flg;
	return (red);
}

void insert_cmd(t_list **lst, char *cmd_args, char *symb_file)
{
	int			i;
	char		*file;
	//char		**tab_file;
	t_command	*cmd;

	i = 0;
	cmd = NULL;
	file = NULL;
	if (lst && *lst && cmd_args)
	{
		cmd = malloc(sizeof(t_command));
		cmd->args = ft_split(cmd_args, ' ');
		cmd->cmd = ft_strdup(cmd->args[0]);
		if (symb_file)
		{
			while (symb_file[i])
			{
				if (symb_file[i] == '>' && symb_file[i + 1] == '>')
				{
					cmd->redir_out->content = init_red(NULL, 0);
					i += 2;
				}
				else if (symb_file[i] == '>')
				{
					cmd->redir_out->content = init_red(NULL, 1);
					i++;
				}
				else if (symb_file[i] == '<' && symb_file[i + 1] == '<')
				{
					cmd->redir_in->content = init_red(NULL, 0);
					i += 2;
				}
				else if (symb_file[i] == '<')
				{
					cmd->redir_in->content = init_red(NULL, 1);
					i++;
				}
				((t_red *)cmd->redir_in->content)->file_name = ft_strdup("");
				while (symb_file[i] && symb_file[i] != '<' && symb_file[i] != '>')
				{
					((t_red *)cmd->redir_in->content)->file_name = ft_strjoin(((t_red *)cmd->redir_in->content)->file_name, ft_strdup(&symb_file[i]));
					i++;
				}
				//ft_lstadd_back(cmd->redin, ft_lstnew(init_red(symb[])));
			}
		}
	}
}

t_list *init_lst(void)
{
	t_list *lst;

	lst = malloc(sizeof(t_list));
	lst->content = NULL;
	lst->next = NULL;
	return (lst);
}

void store_one_cmd(token_t **tokens, char *symb)
{
	//t_list		*lst;
	char		*symb_file;
	char		*cmd_args;
	token_t		*tokens_cmd;

	tokens_cmd = NULL;
	if (tokens && *tokens && symb)
	{
		while (*tokens)
		{
			tokens_cmd = tokens_of_one_command(tokens);
			if (ft_strchr_str(tokens_cmd_to_string(tokens_cmd), symb))
			{
				cmd_args_file(tokens_cmd, &cmd_args, &symb_file);
				printf("%s\n", cmd_args);
				printf("%s\n", symb_file);
				exit(1);
				//lst = init_lst();
				//insert_cmd(&lst, cmd_args, symb_file);
				break;
			}
			// else
			// {
			// }
		}
	}
}

int main()
{
	//token_t	*token_cmd;
	lexer_t	*lexer;
	token_t	*token;
	char	*symb;
	char	*types;

	lexer = init_lexer(readline("minishell_1337 : $ "));
	symb = malloc(3);
	types = malloc(9);
	symb = "<>";
	types = "<>| '\"$";
	token = get_all_tokens(lexer, types);
	store_one_cmd(&token, symb);
	// while (token)
	// {
	// 	printf("|%s|\n",token->value);
	// 	token = token->next;
	// }
	//store_one_cmd(&token, symb);
}