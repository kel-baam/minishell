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
	ft_lstadd_back(&commands,ft_lstnew(generateCommand("ls","ls", NULL,NULL,1)));
	//ft_lstadd_back(&commands,ft_lstnew(generateCommand("cat","cat",NULL,NULL,0)));
	return commands;
}


void printBST(t_node* root, int isRightChild, int depth) {
    if (root != NULL) {
        printBST(root->right, 1, depth + 1);

        for (int i = 0; i < depth; i++) {
            printf(" +  ");
        }
        printf("%s\n\n", root->key);

        printBST(root->left, 0, depth + 1);
    }
}
