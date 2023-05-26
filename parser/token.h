/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:39:02 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/26 19:14:57 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H


#include "lexer.h"


typedef struct token_s
{
	char *value;
	enum
	{
		red_input,
		red_output,
		token_pipe,
		token_text,
		token_space,
		token_s_qoute,
		token_d_qoute,
		token_dollar
	} type;
	struct token_s *next;
} token_t;

token_t	*init_token(char *value, int type);
token_t *get_one_token(lexer_t *lexer, char *types);
token_t *get_all_tokens(lexer_t *lexer, char *types);
token_t *tokens(token_t **token);
void	ft_lstadd_back_token(token_t **lst, token_t *new);
token_t	*ft_lstlast_token(token_t *lst);



#endif