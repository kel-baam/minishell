/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:26:25 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/15 22:23:23 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include "cmd.h"
#include "../minishell.h"


t_red	*init_red(int flg)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	red->file_name = NULL;
	red->flag = flg;
	return (red);
}

t_list *init_lst()
{
	t_list		*lst;

	lst = malloc(sizeof(t_list));
	lst->content = NULL;
	lst->next = NULL;
	return (lst);
}

void remove_s_d_qoute(char **buffer)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (buffer)
	{
		if ((*buffer)[0] == '"' || (*buffer)[0] == '\'')
		{
			(*buffer)++;
			ft_strlcpy(tmp, *buffer, ft_strlen(*buffer));
			*buffer = tmp;
		}
	}
}

void expand(char **token)
{
	char	*result;

	result = NULL;
	if (token)
	{
		if ((*token)[0] == '$')
		{
			result = get_env(&((*token)[1]));
			if (result)
				(*token) = result;
		}
	}
}

int get_char_position(char *buffer, char c)
{
	int	i;

	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] == c)
				return (i);
			i++;
		}
	}
	return (0);
}

int	len_str_to_expand(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			count++;
		i++;
	}
	return (count + 1);
}



char *expand_with_quote(token_t *token)
{
	int		i;
	int		is_s_d_qoute;
	char	*tmp;
	char	*to_expand;
	char	*before_dollar;
	char	*after_dollar;

	i = 0;
	tmp = NULL;
	is_s_d_qoute = 0;
	to_expand = NULL;
	before_dollar = NULL;
	after_dollar = NULL;
	if (token && ft_strchr(token->value, '$'))
	{
		if (token->value[0] == '"')
			is_s_d_qoute = 2;
		else if (token->value[0] == '\'')
			is_s_d_qoute = 1;
		if (is_s_d_qoute != -1)
		{
			remove_s_d_qoute(&token->value);
			if (is_s_d_qoute == 2)
			{
				tmp = token->value;
				while (tmp[i] && tmp[i] != '$')
					i++;
				before_dollar = ft_substr(token->value, 0, i);
				to_expand = ft_substr(token->value, get_char_position(token->value, '$'), len_str_to_expand(token->value));
				expand(&to_expand);
				before_dollar = ft_strjoin(before_dollar, to_expand);
				after_dollar = ft_substr(tmp, i + len_str_to_expand(token->value), ft_strlen(tmp) - i + len_str_to_expand(token->value));
				after_dollar = ft_strjoin(before_dollar, after_dollar);
				return (after_dollar);
			}
			else
				return (token->value);
		}
	}
	else
	{
		remove_s_d_qoute(&token->value);
	}
	return (token->value);
}


char **token_cmd_to_args(token_t *token_cmd)
{
	token_t *tmp;
	int		i=0;
	char **tab = malloc(sizeof(char*) * ft_lstsize_token(token_cmd) + 1);
	if (token_cmd)
	{
		tmp = token_cmd;
		if (tab)
		{
			while (tmp)
			{
				if (tmp->type != 4)
				{
					tab[i] = ft_strdup(tmp->value);
					i++;
				}
				tmp = tmp->next;
			}
			// printf("I=%d\n", i);
			tab[i] = NULL;
		}
	}
	return tab;
}

token_t *cmd_args_file(token_t *token_cmd,  char **symb_file)
{
	int		flag;
	token_t	*cmd_arg;
	token_t	*symb_fl;
	token_t	*prev;

	char	*result = ft_strdup("");
	flag = -1;
	cmd_arg = NULL;
	symb_fl = NULL;
	int i = 0;
	char **tab;
	if (token_cmd)
	{
		while (token_cmd)
		{
			// red
			if (token_cmd->type == 0 || token_cmd->type == 1)
			{
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
				{//
					expand(&token_cmd->value);
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 0;
			}
			else if (token_cmd && token_cmd->type == 4)
			{
				while (token_cmd && token_cmd->type == 4)
				{
					remove_s_d_qoute(&token_cmd->value);
					//=======
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
			}
			else if (token_cmd && token_cmd->type == 3)
			{//
				while (token_cmd && token_cmd->type == 3)
				{
					expand(&token_cmd->value);
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 1;
			}
			else if (token_cmd)
			{
				token_t	*prev;
				token_t *tmp;

				if (token_cmd && (token_cmd->type == 5 || token_cmd->type == 6))
				{
					tmp = token_cmd;
					//  leak
					result = ft_strdup("");
					while (tmp && (tmp->type == 5 || tmp->type == 6))
					{
						result = ft_strjoin(result, expand_with_quote(tmp));
						prev = tmp;
						tmp = tmp->next;
					}
					token_cmd = prev;
					token_cmd->value = result;
				}
				else
					expand(&token_cmd->value);
				if (flag == 0)
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
				else if (flag == 1|| flag == -1)
       			{
					expand(&token_cmd->value);
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
				token_cmd = token_cmd->next;
				}
		}
	}
		*symb_file = tokens_cmd_to_string(symb_fl);

	return (cmd_arg);
}



t_command *insert_one_cmd(char **cmd_args, char *symb_file)
{
	int			i;
	int			flag;
	char		*file;
	t_command	*new;
	t_list		*lst_redir_in;
	t_list		*lst_redir_out;

	i = 0;
	flag = -1;
	new = malloc(sizeof(t_command));
	new->redir_out = malloc(sizeof(t_list));
	new->redir_in = malloc(sizeof(t_list));
	lst_redir_in = NULL;
	lst_redir_out = NULL;
	if (cmd_args)
	{
		new->args = copy_of_tab(cmd_args);
		new->cmd = new->args[0];
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
		// int j = 0;
		// 	while (new->args[j])
		// 	{
		// 		printf("p----%s\n",new->args[j]);
		// 		j++;
		// 	}
	new->redir_in =  lst_redir_in;
	new->redir_out = lst_redir_out;
	return (new);
}

t_list *store_one_cmd(token_t **tokens, char *symb)
{
	t_list		*lst;
	char		*symb_file;
	token_t 	*cmd_arg;
	token_t		*tokens_cmd;
	char **tab;

	lst = NULL;
	tokens_cmd = NULL;
	if (tokens && *tokens && symb)
	{
		tokens_cmd = tokens_of_one_command(tokens);
		while (tokens_cmd)
		{
			cmd_arg = cmd_args_file(tokens_cmd, &symb_file);
			tab = token_cmd_to_args(cmd_arg);

			// t_list *var;
			// var = malloc(sizeof(t_list));
			// var->content = (t_list *)insert_one_cmd(tab, symb_file);
			// var->next = NULL;

			ft_lstadd_back(&lst, ft_lstnew(insert_one_cmd(tab, symb_file)));
			//printf("hh %s\n",lst->)
			//cmd_args = NULL;
			symb_file = NULL;
			tokens_cmd = tokens_of_one_command(tokens);
		}
	}
	// int i;	/// AFFICHAGE
	// while (lst && lst->content)
	// {
	// 	//	cmd
	// 	t_command *command = (t_command*)lst->content;
	// 	i = 0;
	// 	printf("cmd :%s\nargs :",command->cmd);
	// 	// args
	// 	while (command->args[i])
	// 	{
	// 		printf("\n\t %s \n",command->args[i]);
	// 		i++;
	// 	}
	// 	printf("\n");
	// 	// in files
	// 	while (((t_red *)command->redir_in) != NULL)
	// 	{
	// 		printf("redir_in : %s , flag :%d\n",((t_red *)command->redir_in->content)->file_name
	// 			, ((t_red *)command->redir_in->content)->flag);
	// 		command->redir_in = command->redir_in->next;
	// 	}
	// 	// out files
	// 	while (((t_red *)command->redir_out) != NULL)
	// 	{
	// 		printf("redir_out : %s , flag :%d\n",((t_red *)command->redir_out->content)->file_name
	// 			, ((t_red *)command->redir_out->content)->flag);
	// 		command->redir_out = command->redir_out->next;
	// 	}
	// 	printf("\n------------------------------------------\n");
	// 	lst = lst->next;
	// }
	// exit(1);
	return (lst);
}

int pipe_error(token_t *tokens, token_t *prev)
{
	char	*buffer;

	buffer = NULL;
	if (tokens)
	{
		tokens = tokens->next;
		if (!prev)
		{
			buffer =  ft_strdup("syntax error near unexpected token `|");
			if (tokens && tokens->value[0] == '|')
			{
				buffer = ft_strjoin(buffer, "|");
				tokens = tokens->next;
			}
			buffer = ft_strjoin(buffer, "'");
			print_cmd_error(NULL, NULL, buffer, 258);
			return (1);
		}
		else
		{
			while (tokens && tokens->type == 4)
				tokens = tokens->next;
			if (!tokens || (tokens && tokens->type == 2))
			{
				print_cmd_error(NULL, NULL, ft_strdup("syntax error near unexpected token `|'"), 258);
				return (1);
			}
		}
	}
	return (0);
}

int qoute_error(token_t *token)
{
	if (token)
	{
		if (ft_strlen(token->value) == 1)
		{
			print_cmd_error(NULL, NULL, "syntax error", 1);
			return (1);
		}
		else if (token->value[ft_strlen(token->value) - 1] != token->value[0])
		{
			print_cmd_error(NULL, NULL, "syntax error", 1);
			return (1);
		}
	}
	return (0);
}

int redir_in_error(token_t *token)
{
	int		i;
	int		flag;
	char	*buffer;

	i = 0;
	flag = -1;
	buffer = ft_strdup("");
	if (token)
	{
		token = token->next;
		if (token && (token->type == 0))
		{
			token = token->next;
			flag = 0;
		}
		if (token && (token->type == 0))
			token = token->next;
		while (token && token->type == 4)
			token = token->next;
		if (!token || (token && flag && token->type == 1))
		{
			print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
			return (1);
		}
		else if (token->type == 0 || token->type == 1 || token->type == 2)
		{
			buffer = "syntax error near unexpected token `";
			while (token && ((token->type == 0 && i < 3) || (token->type == 1 && i < 2)))
			{
				buffer = ft_strjoin(buffer, token->value);
				token = token->next;
				i++;
			}
			if (token && token->type == 2)
				buffer = ft_strjoin(buffer, token->value);
			print_cmd_error(NULL, NULL, ft_strjoin(buffer, "'"), 258);
			return (1);
		}
	}
	return (0);
}

int redir_out_error(token_t *token)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = ft_strdup("");
	if (token)
	{
		token = token->next;
		if (token && token->type == 2)
		{
			token = token->next;
			while (token && token->type == 4)
				token = token->next;
			if (!token)
			{
				print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
				return (1);
			}
			return (0);
		}
		if (token && token->type == 1)
			token = token->next;
		while (token && token->type == 4)
			token = token->next;
		if (token && (token->type == 0 || token->type == 1 || token->type == 2))
		{
			buffer = "syntax error near unexpected token `";
			while (token && ((i < 2 && (token->type == 2 || token->type == 1))
				|| (i < 3 && token->type == 0)))
			{
				buffer = ft_strjoin(buffer, token->value);
				token = token->next;
				i++;
			}
			print_cmd_error(NULL, NULL, ft_strjoin(buffer, "'"), 258);
			return (1);
		}
		if (!token)
		{
			print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
			return (1);
		}
	}
	return (0);
}

int redir_error(token_t *token, int type)
{
	if (token)
	{
		if (type == 0 && redir_in_error(token))
			return (1);
		else if (type == 1 && redir_out_error(token))
			return (1);
	}
	return (0);
}

void	check_parsing_error(token_t *tokens, int *flg_err)
{
	token_t *prev;

	prev = NULL;
	if (tokens)
	{
		while (tokens)
		{
			if (tokens->type == 3)
				prev = tokens;
			else if (tokens->value[0] == '|')
			{
				*flg_err = pipe_error(tokens, prev);
				if (*flg_err)
					break;
			}
			else if (tokens->value[0] == '<')
			{
				*flg_err = redir_error(tokens , 0);
				if (*flg_err)
					break;
			}
			else if (tokens->value[0] == '>')
			{
				*flg_err = redir_error(tokens , 1);
				if (*flg_err)
					break;
			}
			else if (tokens->type == 5 || tokens->type == 6)
			{
				*flg_err = qoute_error(tokens);
				if (*flg_err)
					break;
			}
			*flg_err = 0;
			//------ todo--------------------------
			// else if (tokens->type == 7)
			// {

			// }
			tokens = tokens->next;
		}

	}
}

char	*remove_char_from_str(char *buffer, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] != c)
				str = ft_strjoin(str, char_to_string(buffer[i]));
			i++;
		}
	}
	return (str);
}

t_list	*parser(char *line, int *flg_err)
{
	lexer_t	*lexer;
	token_t	*token;
	char	*symb;
	char	*types;
	t_list	*lst;

	lexer = init_lexer(line);
	symb = malloc(3);
	types = malloc(9);
	symb = "<>";
	types = "<>| '\"$";
	token = get_all_tokens(lexer, types);

	check_parsing_error(token, flg_err);
	lst = store_one_cmd(&token, symb);

	herdoc(lst);
	if(*flg_err==1)
	 	add_node(&(g_data.env_vars), "?", ft_itoa(g_data.status_code),NULL);
	return (lst);
}