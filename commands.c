#include "commands.h"
#include <stdlib.h>



command_p newCommand(){
    command_p newCmd = calloc(1, sizeof(struct Command));
    if (newCmd == NULL){ return newCmd; }
    newCmd -> next = NULL; 
    newCmd -> commandType = 0;    
    return newCmd;
}


void freeCommand(command_p cmd){
    if (cmd == NULL) {return;}
    free(cmd); 
}

void freeCommands(command_p cmd){
    if (cmd != NULL && cmd->next != NULL){
        freeCommands(cmd -> next);
    }
    freeCommand(cmd);
}