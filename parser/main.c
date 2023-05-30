/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:26:25 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/30 17:49:57 by kjarmoum         ###   ########.fr       */
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
		buffer = ft_strjoin(buffer, "\0");
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
				// printf("salam\n");
				ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
				prev = token_cmd;
				token_cmd = token_cmd->next;
				if (token_cmd && token_cmd->type == prev->type)
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
				while (token_cmd && token_cmd->type == 4)
				{
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
			}
			else if (token_cmd && token_cmd->type == 3)
			{
				while (token_cmd && token_cmd->type == 3)
				{
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 1;
			}
			else if (token_cmd)
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

t_red	*init_red(int flg)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	red->file_name = NULL;
	red->flag = flg;
	return (red);
}

t_command *insert_one_cmd(char *cmd_args, char *symb_file)
{
	int			i;
	int			flag;
	char		*file;
	t_command	*new;

	i = 0;
	flag = -1;
	new = malloc(sizeof(t_command));
	if (cmd_args)
	{
		new->args = ft_split(cmd_args, ' ');
		new->cmd = ft_strdup(new->args[0]);
	}
	if (symb_file)
	{
		if (symb_file[i] == '>')
		{
			flag = 0;
			new->redir_out = malloc(sizeof(t_list));
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
			new->redir_in = malloc(sizeof(t_list));
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
		while (symb_file[i] && symb_file[i] != ' ')
		{
			file = ft_strjoin(file, char_to_string(symb_file[i]));
			i++;
		}
		if (flag == 0)
			((t_red *)new->redir_out->content)->file_name = file;
		else if (flag == 1)
			((t_red *)new->redir_in->content)->file_name = file;
	}
	return (new);
}

t_list *init_lst()
{
	t_list		*lst;

	lst = malloc(sizeof(t_list));
	lst->content = NULL;
	lst->next = NULL;
	return (lst);
}

void store_one_cmd(token_t **tokens, char *symb)
{
	t_list		*lst;
	//t_command	*new;
	char		*symb_file;
	char		*cmd_args;
	token_t		*tokens_cmd;

	tokens_cmd = NULL;
	if (tokens && *tokens && symb)
	{
		tokens_cmd = tokens_of_one_command(tokens);
		lst = NULL;
		while (tokens_cmd)
		{
			cmd_args_file(tokens_cmd, &cmd_args, &symb_file);
			ft_lstadd_back(&lst, ft_lstnew(insert_one_cmd(cmd_args, symb_file)));
			cmd_args = NULL;
			symb_file = NULL;
			tokens_cmd = tokens_of_one_command(tokens);
		}

		t_list *t;
		t = lst;
		int i = 0;
				/// AFFICHAGE
		while (t)
		{
			//	cmd
			printf("cmd :%s\n args :",((t_command *)(t->content))->cmd);
			// args
			while (((t_command *)(t->content))->args[i])
			{
				printf("%s ",((t_command *)(t->content))->args[i]);
				i++;
			}
			printf("\n");
			// in files
			while (((t_red *)((t_command *)(t->content))->redir_in)  != NULL)
			{
				printf("redir_in : %s , flag :%d\n",((t_red *)((t_command *)(t->content))->redir_in->content)->file_name
					, ((t_red *)((t_command *)(t->content))->redir_in->content)->flag);
				((t_command *)(t->content))->redir_in = ((t_command *)(t->content))->redir_in->next;
			}
			// out files
			while (((t_red *)((t_command *)(t->content))->redir_out)  != NULL)
			{
				printf("redir_out : %s , flag :%d",((t_red *)((t_command *)(t->content))->redir_out->content)->file_name
					, ((t_red *)((t_command *)(t->content))->redir_out->content)->flag);
				((t_command *)(t->content))->redir_out = ((t_command *)(t->content))->redir_out->next;
			}
			printf("\n------------------------------------------\n");
			t = t->next;
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