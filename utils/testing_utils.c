#include "../minishell.h"

t_red *generatFile(char *file_name,int flag)
{
	t_red *red= malloc(sizeof(t_red));
	red->file_name = ft_strdup(file_name);
	red->flag = flag;
	return red;
}

t_command *generateCommand(char *cmd, char *args, char *inFile, char *outFiles)
{
	t_command	*command;
	command = calloc(sizeof(t_command),1);
	command->cmd = cmd;
	if(args)
		command->args = ft_split(args, ' ');
	if (inFile)
		ft_lstadd_back(&(command->redir_in),ft_lstnew(ft_strdup(inFile)));
	return command;

}

t_list	*init_commands()
{
 	t_list *commands = NULL;
	ft_lstadd_back(&commands,ft_lstnew(generateCommand(NULL,NULL, "test5.txt",NULL)));
	// ft_lstadd_back(&commands,ft_lstnew(generateCommand("gre","cat")));
	ft_lstadd_back(&commands,ft_lstnew(generateCommand("ls","ls",NULL,"")));
	return commands;
}
