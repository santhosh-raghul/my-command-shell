#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include"functions.h"

void run_command(char *cmd,char *cwd,char *prev_wd,char *home_dir,struct string_linked_list *commands_run,int no_already_run)
{
    int argc=1;
    for(char *c=cmd;*c!='\n';c++)
        if(*c==' ')
            argc++;

    char **args = malloc(sizeof (char *)*(argc+1));
    extract_args(cmd,args,argc);
    
    if(args[0][0]=='!')
    {
        history(commands_run,args,no_already_run);
        return;
    }
    else if(strcmp(args[0],"cd")==0)
    {
        change_directory(args,cwd,prev_wd,home_dir);
        return;
    }
    else if(strcmp(args[0],"exit")==0)
        exit(0);

    pid_t pid;
    pid=fork();
    if(pid==-1)
    {
        printf("myshell: fork failed. could not execute '%s'",cmd);
        exit(1);
    }
    else if(pid>0) // parent block
        wait(NULL);
    else if(pid==0) // child block
    {
        execvp(args[0],args);
        // to terminate the extra process if exec call fails
        printf("myshell: %s: could not execute command\n",args[0]);
        exit(1);
    }
}

void extract_args(char *cmd, char *args[],int argc)
{
    int i;
    char *c,*p;
    for(i=0;i<=argc;i++)
        args[i]=malloc(100);
    i=0;
    p=&args[0][0];
    for(c=cmd;*c!='\n';c++)
    {
        if(*c!=' ')
        {
            *p=*c;
            p++;
        }
        else
        {
            *p='\0';
            i++;
            p=&args[i][0];
        }
    }
    *p='\0';
    i++;
    args[i]=NULL;
    return;
}

void change_directory(char *args[], char *cwd, char *prev_wd, char *home_dir)
{
    if(args[1]==NULL||args[1][0]=='~')
    {
        strcpy(args[0],home_dir);
        if(args[1]!=NULL)
            strcat(args[0],&args[1][1]);
        chdir(args[0]);
        strcpy(prev_wd,cwd);
    }
    else if(strcmp(args[1],"-")==0 && args[2]==NULL)
    {
        if(prev_wd[0]=='\0')
        {
            printf("myshell: cd: prev_wd not set\n");
            return;
        }
        printf("%s\n",prev_wd);
        chdir(prev_wd);
        strcpy(prev_wd,cwd);
    }
    else if(args[2]==NULL)
    {
        int x=chdir(args[1]);
        if(x==-1)
            printf("myshell: cd: %s: No such file or directory\n",args[1]);
        else
            strcpy(prev_wd,cwd);
    }
    else
        printf("myshell: cd: too many arguments\n");
    return;
}

void history(struct string_linked_list *list, char *args[],int max)
{
    struct string_linked_list *temp;
    int x=atoi(&args[0][1]);
    if(x==0||args[1]!=NULL)
        printf("history: incorrect usage\nTry '!n' to view the last n commands\n");
    else if(max==1)
        printf("YoU JuSt OpeNeD \033[1;30mm\033[1;31my\033[1;32ms\033[1;33mh\033[1;34me\033[1;35ml\033[1;36ml\033[0m wHaT dO yOu ExPeCt To seE iN thE HisToRy?\n");
    else if(x>max)
        printf("history: you have executed only %d commands so far including '%s'\n",max,list->cmd);
    else
    {
        printf("history of commands executed (recent first) :\n");
        temp=list;
        for(int i=0;i<x;i++)
        {
            printf("%6d  %s\n",max-i,temp->cmd);
            temp=temp->prev;
        }
    }
}

void substring(char s[], char sub[], int p, int l)
{
    int c=p;   
    while(c<l)
    {
        sub[c-p]=s[c];
        c++;
    }
    sub[c]='\0';
}