/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:37:52 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/20 15:50:45 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = calloc(1, sizeof(t_token));
	token->value = ft_strdup(value);
	token->type = type;
	return (token);
}

char *char_to_string(char c)
{
	char *str;
	str = malloc(2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token *get_one_token(t_lexer *lexer, char *types)
{
	char		qoute;
	t_token		*token;
	char		*buffer;

	buffer = ft_strdup("");
	// 	>
	if (lexer->c == '>')
		return (token = init_token(">", red_output) ,lexer_advance(lexer), token);
	// <
	if (lexer->c == '<')
		return (token = init_token("<", red_input) ,lexer_advance(lexer), token);
	// |
	if (lexer->c == '|')
		return (token = init_token("|", token_pipe), lexer_advance(lexer), token);
	// space
	if (lexer->c == ' ')
		return (token = init_token(" ", token_space), lexer_advance(lexer), token);
	// ' OR "
	if (lexer->c == '\"' || lexer->c == '\'')
	{
		qoute = lexer->c;
		buffer = ft_strjoin(buffer, char_to_string(lexer->c));
		lexer_advance(lexer);
		while (lexer->c != '\0' && lexer->c != qoute)
		{
			buffer = ft_strjoin(buffer, char_to_string(lexer->c));
			lexer_advance(lexer);
		}
		buffer = ft_strjoin(buffer, char_to_string(lexer->c));
		lexer_advance(lexer);
		return (init_token(buffer, token_s_qoute));
	}
	// $
	if (lexer->c == '$')
	{
		buffer = ft_strjoin(buffer, char_to_string(lexer->c));
		lexer_advance(lexer);
		while (!ft_strchr(" '\"\0", lexer->c))
		{
			buffer = ft_strjoin(buffer, char_to_string(lexer->c));
			lexer_advance(lexer);
		}
		return (init_token(buffer, token_dollar));
	}
	// text
	while (!ft_strchr(types, lexer->c))
	{
		buffer = ft_strjoin(buffer, char_to_string(lexer->c));
		lexer_advance(lexer);
	}
	return (init_token(buffer, token_text));
}


t_token *get_all_tokens(t_lexer *lexer, char *types)
{
	t_token	*head;
	t_token	*token;

	head = NULL;
	while (lexer->c != '\0')
	{
		token = get_one_token(lexer, types);
		if (token != NULL)
			ft_lstadd_back_token(&head, token);
	}
	ft_lstadd_back_token(&head, NULL);
	return (head);
}