#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"





t_command	*insert_one_cmd(char **cmd_args, char *symb_file)
{
	int			i;
	char		*to_free;
	char		*file;
	t_command	*new;
	t_list		*lst_redir;
	char		*c_string;
	

	i = 0;
	new = malloc(sizeof(t_command));
	lst_redir = NULL;
	if (cmd_args && *cmd_args)
	{
		new->args = copy_of_tab(cmd_args);
		new->cmd = ft_strdup(new->args[0]);
	}
	else
	{
		new->args=NULL ;
		new->cmd = NULL;
	}
			
	while (symb_file && symb_file[i])
	{
		new->redir_in_out = malloc(sizeof(t_list));
		if (new->redir_in_out)
		{
			if (symb_file[i] == '>')
			{
				if (symb_file[i + 1] == '>')
				{
					new->redir_in_out->content = init_red(2);
					i += 2;
				} 
				else if (symb_file[i++] == '>')
					new->redir_in_out->content = init_red(3);
			}
			else if (symb_file[i] == '<')
			{
				if (symb_file[i + 1] == '<')
				{
					new->redir_in_out->content = init_red(0);
					i += 2;
				}
				else if (symb_file[i++] == '<')
					new->redir_in_out->content = init_red(1);
			}
			file = ft_strdup("");
			printf("%p\n",file);
			while (symb_file[i] && symb_file[i] == ' ')
				i++;
			while (symb_file[i] && symb_file[i] != ' ' && symb_file[i] != '<'
				&& symb_file[i] != '>')
			{
				to_free = file;
				c_string = char_to_string(symb_file[i]);
				file = ft_strjoin(file, c_string);
				function_free((void**)&c_string, 1);
				function_free((void**)&to_free, 1);
				i++;
			}
			
			((t_red *)new->redir_in_out->content)->file_name = file;
			ft_lstadd_back(&lst_redir, ft_lstnew(new->redir_in_out->content));
		
				
		}
	}
	new->redir_in_out = lst_redir;
	return (new);
}

t_list	*store_all_cmd(t_token **tokens, char *symb)
{
	char		**tab;
	char		*symb_file;
	t_list		*lst;
	t_token 	*cmd_arg;
	t_token 	*tokens_cmd;
	t_token		*tmp_tokens;
	t_token *to_free;

	lst = NULL;
	tokens_cmd = NULL;
	if (*tokens && symb)
	{

		tmp_tokens = *tokens;
		tokens_cmd = tokens_of_one_command(&tmp_tokens);
		while (tokens_cmd)
		{
			cmd_arg = cmd_args_file(tokens_cmd, &symb_file);

			//while(1);
			tab = token_cmd_to_args(cmd_arg);
			ft_lstadd_back(&lst, ft_lstnew(insert_one_cmd(tab, symb_file)));

			function_free((void **)&symb_file, 1);
			 function_free((void **)&tokens_cmd, 2);
			function_free((void **)tab, 3);
			function_free((void **)&cmd_arg, 2);

			to_free=tokens_cmd;
			tokens_cmd = tokens_of_one_command(&tmp_tokens);
			function_free((void**)&to_free, 2);
		}
	}
	return (lst);
}