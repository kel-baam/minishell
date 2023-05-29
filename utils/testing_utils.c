#include "../minishell.h"

t_red *generatFile(char *file_name,int flag)
{
	t_red *red= malloc(sizeof(t_red));
	red->file_name = ft_strdup(file_name);
	red->flag = flag;
	return red;
}

t_command *generateCommand(char *cmd, char *args, char *inFile,char *outfile,int flag)
{
	t_command	*command;
	command = calloc(sizeof(t_command),1);
	if(cmd)
		command->cmd = cmd;
	if(args)
		command->args = ft_split(args, ' ');
	if (inFile)
		ft_lstadd_back(&(command->redir_in),ft_lstnew(ft_strdup(inFile)));
	if(outfile)
		ft_lstadd_back(&(command->redir_out),ft_lstnew(generatFile(outfile,flag)));
	return command;

}

t_list	*init_commands()
{
 	t_list *commands = NULL;
	ft_lstadd_back(&commands,ft_lstnew(generateCommand("exit","exit oiii 15", NULL,NULL,1)));
	return commands;
}

// void exec_herdoc(const char *delimter,int fd)
// {
//     t_list *data=NULL;// herdoc fonction i didn't store the given result of this fonction in the principal struct
// 	t_list *tmp;
// 	data=tmp;
//     char *line;
//     while(1)
//     {
// 		line=readline("> ");
//         if(!ft_strncmp(command->herdoc_delim,line,ft_strlen(command->herdoc_delim)))
// 			break ;
// 	}
// }