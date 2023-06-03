/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:02:55 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/22 17:05:27 by kjarmoum         ###   ########.fr       */
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



// function get buffer of one command
// char	*get_one_command(token_t **token)
// {
// 	int			i;
// 	char		*buffer;

// 	i = 0;
// 	buffer = NULL;
// 	if (token && *token)
// 	{
// 		buffer = ft_strdup("");
// 		while (*token && (*token)->value[0] != '|')
// 		{
// 			buffer = ft_strjoin(buffer, (*token)->value);
// 			if ((*token)->value[0] != '<' && (*token)->value[0] != '>')
// 				buffer = ft_strjoin(buffer, " ");
// 			if ((*token)->next && (*token)->next->value[0] !=  '<' && (*token)->next->value[0] !=  '>')
// 				buffer = ft_strjoin(buffer, " ");
// 			(*token) = (*token)->next;
// 		}
// 		if (*token && (*token)->value[0] == '|')
// 			(*token) = (*token)->next;
// 	}
// 	return (buffer);
// }

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

// t_command *get_one_command(token_t **tokens)
// {
// 	int			i;
// 	int			counter_t;
// 	t_command	*cmnd;

// 	i = 0;
// 	cmnd = NULL;
// 	if (tokens && *tokens)
// 	{
// 		cmnd = malloc(sizeof(t_command));
// 		cmnd->cmd = (*tokens)->value;
// 		counter_t = count_token_cmd(*tokens);
// 		cmnd->args = malloc(counter_t + 1);
// 		while (*tokens && (*tokens)->value[0] != '|')
// 		{
// 			cmnd->args[i] = (*tokens)->value;
// 			i++;
// 			*tokens = (*tokens)->next;
// 		}
// 		if (*tokens &&  (*tokens)->value[0] == '|')
// 			*tokens = (*tokens)->next;
// 	}
// 	return (cmnd);
// }

// void store_redin(char *buffer, t_command **cmd)
// {
// 	int		i;
// 	char	*tab;

// 	i = 0;
// 	if (buffer)
// 	{
// 		// syntax : < delimiter command OR << file command
// 		if (ft_strncmp(buffer, "<<", 2) == 0)
// 		{
// 			(*cmd)->herdoc = 1;
// 			tab = ft_split(buffer + 2, ' ');
// 			(*cmd)->herdoc_delim = tab[i];
// 			i++;
// 			(*cmd)->cmd = tab[i];
// 			while (tab[i] && tab[i] != "<")
// 			{
// 				args[i] = tab[i];
// 				i++;
// 			}
// 			//
// 		}
// 		else if (ft_strncmp(buffer, "< ", 2) == 0)
// 			//
// 		//  syntax : command << delimiter OR command < delimiter

// 	}
// }

// //
// t_command *store_one_command(token_t **token)
// {
// 	char		*buffer;
// 	token_t		*tmp;
// 	t_command	*cmd;

// 	cmd = NULL;
// 	if (token && *token)
// 	{
// 		cmd = malloc(sizeof(t_command));
// 		buffer = get_one_command(token);
// 		if (str_search(buffer, '<') == 1)
// 			store_redin(buffer, &cmd);
// 		if (str_search(buffer, '>') == 1)
// 			store_redout();

// 			//function

// 	}
// 	return NULL;
// }



