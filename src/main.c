#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"

int main()
{
    char cmd[100],cwd[100],prev_wd[100],printing_cwd[100],*home_dir,after_home[100],test[100];
    int N=0,home_dir_size,cmd_size;
    struct string_linked_list *tail=NULL,*temp;

    home_dir=getenv("HOME");
    home_dir_size=strlen(home_dir);
    // run_command("clear\n","","",home_dir,tail,N);

    printf("\033[1;33m=============================== MY COMMAND SHELL ===============================\n");
    while(1)
    {
        getcwd(cwd,100);
        substring(cwd,test,0,home_dir_size);
        if(strcmp(test,home_dir)==0)
        {
            printing_cwd[0]='~';
            printing_cwd[1]='\0';
            substring(cwd,after_home,home_dir_size,87);
            strcat(printing_cwd,after_home);
        }
        else
            strcpy(printing_cwd,cwd);
        printf("\033[1;32mmy-command-shell\033[0m:\033[1;34m%s\033[0m@ ",printing_cwd);
        fgets(cmd,100,stdin);
        N++;
        cmd_size=strlen(cmd)-1;
        temp=malloc(sizeof(struct string_linked_list));
        temp->cmd=malloc(cmd_size);
        strncpy(temp->cmd,cmd,cmd_size);
        temp->prev=tail;
        tail=temp;
        run_command(cmd,cwd,prev_wd,home_dir,tail,N);
    }
    return 0;
}