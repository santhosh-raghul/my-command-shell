struct string_linked_list
{
    char *cmd;
    struct string_linked_list *prev;
};

void run_command(char *cmd, char *cwd, char *prev_wd, char *home_dir, struct string_linked_list *commands_run, int no_already_run);
void extract_args(char *cmd, char *args[],int argc);
void change_directory(char *args[], char *cwd, char *prev_wd, char *home_dir);
void history(struct string_linked_list *list, char *args[],int max);
void substring(char s[], char sub[], int p, int l);