/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:37:23 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/22 17:33:56 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H


#include "token.h"
#include "cmd.h"
#include "../minishell.h"
// typedef struct red_s
// {
// 	void		*file_name;
// 	int			flag; //1 if red out 0 if red append
// 			// struct t_red *next;
// }					red_t;


// typedef struct command_s
// {
// 	char			*cmd;
// 	char			**args;
// 	//int herdoc;         //flag for exestence of herdoc <<
// 	//char *herdoc_delim; // delimiter of herdoc
// 	//int append_redi;    // flag redirection >>
// 	//t_list			*redir_in;
// 	//t_list			*redir_out;
// }					command_t;

// typedef struct pipe_s
// {
// 	char *value;
// 	command_t *cmd;
// 	struct pipe_s	*cmd_left;
// 	struct pipe_s	*cmd_right;
// }pipe_t;



// typedef struct tree_s
// {
// 	command_t	*cmd;
// 	struct tree_s	*left_content;
// 	struct tree_s	*right_content;
// } tree_t;

int			count_token_cmd(token_t *token);
t_command 	*store_one_command(token_t **token);
char		*get_one_command(token_t **token);




#endif