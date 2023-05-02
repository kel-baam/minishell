#include "../minishell.h"

t_red *generat(char *file_name,int flag)
{
	t_red *red= malloc(sizeof(t_red));
	red->file_name = ft_strdup(file_name);
	red->flag = flag;
	return red;
}

t_command	*init_command()
{
	t_command	*command;
	command = calloc(sizeof(t_command),1);
	command->cmd = "cat";
	command->args = ft_split("cat", ' ');
	command->redi_in=1;
	command->herdoc_delim="end";

	ft_lstadd_back(&(command->redir_out), ft_lstnew(generat("test.txt",1)));
	ft_lstadd_back(&(command->redir_out), ft_lstnew(generat("test2.txt",1)));
	ft_lstadd_back(&(command->redir_in), ft_lstnew(ft_strdup("test2.txt")));
	ft_lstadd_back(&(command->redir_in), ft_lstnew(ft_strdup("hello.txt")));
	return (command);
}
