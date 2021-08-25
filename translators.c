#include "translators.h"
#include "commands.h"
#include "common.h"
#include "errors.h"
#include "translation_utils.h"
#include <string.h>

command_p arithmeticTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location){
    command_p newCmd  = newCommand(); 
    int numArgs; 
    char* args[3]; 
    int reg1, reg2, reg3;
    if (newCmd == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    numArgs = tokenizeArgs(parsedCommand ->arguments, args, 3);
    if (numArgs != 3){
        errorCode = INVALID_ARGUMETS; 
        freeCommand(newCmd);
        return NULL;
    }
    reg1 = strToRegNum(args[0]);
    reg2 = strToRegNum(args[1]);
    reg3 = strToRegNum(args[2]);
    if (reg1 == -1 || reg2 == -1 || reg3 == -1){
        freeCommand(newCmd);
        return NULL;
    }
    newCmd -> commandType = R_COMMAND_TYPE;
    newCmd ->  command.cmd_r.funct = funct;
    newCmd ->  command.cmd_r.opcode = opcode;
    newCmd ->  command.cmd_r.rs = reg1;
    newCmd ->  command.cmd_r.rt = reg2;
    newCmd ->  command.cmd_r.rd = reg3;
    return newCmd; 
}


command_p copyTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location){
     command_p newCmd  = newCommand(); 
    int numArgs; 
    char* args[2]; 
    int reg1, reg2;
    if (newCmd == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    numArgs = tokenizeArgs(parsedCommand ->arguments, args, 2);
    if (numArgs != 2){
        errorCode = INVALID_ARGUMETS; 
        freeCommand(newCmd);
        return NULL;
    }
    reg1 = strToRegNum(args[0]);
    reg2 = strToRegNum(args[1]);
    if (reg1 == -1 || reg2 == -1){
        freeCommand(newCmd);
        return NULL;
    }

    newCmd -> commandType = R_COMMAND_TYPE;
    newCmd -> command.cmd_r.rd = reg2;
    newCmd -> command.cmd_r.rs = reg1;
    newCmd -> command.cmd_r.rt = 0;
    newCmd -> command.cmd_r.unused = 0; 
    newCmd->command.cmd_r.opcode = opcode; 
    newCmd -> command.cmd_r.funct = funct;
    return newCmd; 
}


command_p arithmeticITranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location){
    command_p newCmd  = newCommand(); 
    int numArgs; 
    char* args[3]; 
    short var2; 
    int reg1, reg3;
    if (newCmd == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    numArgs = tokenizeArgs(parsedCommand ->arguments, args, 3);
    if (numArgs != 3){
        errorCode = INVALID_ARGUMETS; 
        freeCommand(newCmd);
        return NULL;
    }
    reg1 = strToRegNum(args[0]);
    var2 = strToImmed16Num(args[1]); 
    reg3 = strToRegNum(args[2]);
    if (reg1 == -1 || reg3 == -1){
        freeCommand(newCmd);
        return NULL;
    }
    if (var2 == -1 && errorCode != 0){
        freeCommand(newCmd);
        return NULL; 
    }

    newCmd -> commandType = I_COMMAND_TYPE;
    newCmd -> command.cmd_i.rs = reg1;
    newCmd -> command.cmd_i.rt = reg3;
    newCmd -> command.cmd_i.immed = var2; 
    newCmd->command.cmd_i.opcode = opcode; 
    return newCmd; 
}


command_p cmpJmpTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location){
    command_p newCmd  = newCommand(); 
    int numArgs; 
    symbol_p symbol3; 
    char* args[3]; 
    int reg1, reg2, distance;
    if (newCmd == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    numArgs = tokenizeArgs(parsedCommand ->arguments, args, 3);
    if (numArgs != 3){
        errorCode = INVALID_ARGUMETS; 
        freeCommand(newCmd);
        return NULL;
    }
    reg1 = strToRegNum(args[0]);
    reg2 = strToRegNum(args[1]);
    if (reg1 == -1 || reg2 == -1){
        freeCommand(newCmd);
        return NULL;
    }

    symbol3 = getSymbol(symbols, args[2]); 
    if (symbol3 == NULL || (symbol3 -> attributes&EXTERNAL_MASK) != 0){ errorCode = INVALID_LABEL; freeCommand(newCmd); return NULL;}
    distance = symbol3 -> location - location; /*The label location minus the current location*/
    if (isValidShort(distance) != TRUE) {errorCode = LABALE_TOO_FAR; freeCommand(newCmd); return NULL;}

    newCmd -> commandType = I_COMMAND_TYPE;
    newCmd -> command.cmd_i.rs = reg1;
    newCmd -> command.cmd_i.rt = reg2;
    newCmd -> command.cmd_i.immed = (short)distance; 
    newCmd->command.cmd_i.opcode = opcode; 
    return newCmd; 
}

command_p loadingTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location){
    command_p newCmd  = newCommand(); 
    int numArgs; 
    char* args[3]; 
    short var2; 
    int reg1, reg3;
    if (newCmd == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    numArgs = tokenizeArgs(parsedCommand ->arguments, args, 3);
    if (numArgs != 3){
        errorCode = INVALID_ARGUMETS; 
        freeCommand(newCmd);
        return NULL;
    }
    reg1 = strToRegNum(args[0]);
    var2 = strToImmed16Num(args[1]); 
    reg3 = strToRegNum(args[2]);
    if (reg1 == -1 || reg3 == -1){
        freeCommand(newCmd);
        return NULL;
    }
    if (var2 == -1 && errorCode != 0){
        freeCommand(newCmd);
        return NULL; 
    }

    newCmd -> commandType = I_COMMAND_TYPE;
    newCmd -> command.cmd_i.rs = reg1;
    newCmd -> command.cmd_i.rt = reg3;
    newCmd -> command.cmd_i.immed = var2; 
    newCmd->command.cmd_i.opcode = opcode; 
    return newCmd; 
}


command_p jmpTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location){
    command_p newCmd  = newCommand(); 
    int numArgs; 
    symbol_p symbol1; 
    char* args[1]; 
    int val;
    char reg = FALSE; 
    if (newCmd == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    numArgs = tokenizeArgs(parsedCommand ->arguments, args, 1);
    if (numArgs != 1){
        errorCode = INVALID_ARGUMETS; 
        freeCommand(newCmd);
        return NULL;
    }

    if (args[0][0] == '$'){
        val = strToRegNum(args[0]);
        if (val == -1){
            freeCommand(newCmd);
            return NULL;
        }
        reg = TRUE;
    } else {
        symbol1 = getSymbol(symbols, args[0]);
        if (symbol1 == NULL){ errorCode = INVALID_LABEL; freeCommand(newCmd); return NULL; } 
        reg = FALSE; 
        val = symbol1->location; /* because it is a symbol location no validation for range is needed */
        if ((symbol1->attributes & EXTERNAL_MASK)>0){
          if(addSymbolInstance(symbol1, location) == -1){freeCommand(newCmd); return NULL;};
        }

    }

    newCmd -> commandType = J_COMMAND_TYPE;
    newCmd -> command.cmd_j.reg = reg;
    newCmd -> command.cmd_j.address = val; 
    newCmd->command.cmd_i.opcode = opcode; 
    return newCmd; 
}

command_p oneLableTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location){
    command_p newCmd  = newCommand(); 
    int numArgs; 
    symbol_p symbol1; 
    char* args[1]; 
    int  val;
    char reg = FALSE; 
    if (newCmd == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    numArgs = tokenizeArgs(parsedCommand ->arguments, args, 1);
    if (numArgs != 1){
        errorCode = INVALID_ARGUMETS; 
        freeCommand(newCmd);
        return NULL;
    
    }
    symbol1 = getSymbol(symbols, args[0]);
    if (symbol1 == NULL){ errorCode = INVALID_LABEL; freeCommand(newCmd); return NULL; } 
    val = symbol1->location; /* because it is a symbol location no validation for range is needed */
    if ((symbol1->attributes & EXTERNAL_MASK)>0){
        if(addSymbolInstance(symbol1, location) == -1){freeCommand(newCmd); return NULL;};
    }

    newCmd -> commandType = J_COMMAND_TYPE;
    newCmd -> command.cmd_j.reg = reg;
    newCmd -> command.cmd_j.address = val; 
    newCmd->command.cmd_i.opcode = opcode; 
    return newCmd; 
}


command_p stopTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location){
    command_p newCmd  = newCommand(); 
   
    if (newCmd == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }

    newCmd -> commandType = J_COMMAND_TYPE;
    newCmd -> command.cmd_j.reg = 0;
    newCmd -> command.cmd_j.address = 0; 
    newCmd->command.cmd_i.opcode = opcode; 
    return newCmd; 
}


/*each translator will consist of the binary memory that will be used to print everithing each translator
can return a sequence of blocks*/
/*TODO apdate append function to receive all */
dataBlock_p dbTranslator(parsedCommand_p parsedCommand){
    dataBlock_p dataBlock; 
    int numArgs; 
    long num; 
    unsigned char* val;
    size_t i = 0;
    char* args[MAX_ARGUMENTS]; 

    numArgs = tokenizeArgs(parsedCommand ->arguments, args, MAX_ARGUMENTS);
    if (numArgs == -1){
        errorCode = INVALID_ARGUMETS; 
        return NULL;
    }
    val = malloc(sizeof(char)*numArgs); 
    if (val == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }

    for (i=0; i < numArgs; i++){
        num = strToNum(args[i]);
        if (num == -1 && errorCode != 0){return NULL;}
        if (isValidByte(num) != TRUE){ errorCode = OUT_OF_RANGE_NUMBER; free(val); return NULL; }
        val[i] = (char)num;
    }

    dataBlock = createDataBlock(val, numArgs, FALSE);
    if (dataBlock == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }

    return dataBlock; 
}


dataBlock_p dhTranslator(parsedCommand_p parsedCommand){
    dataBlock_p dataBlock; 
    int numArgs; 
    long num; 
    unsigned char* val;
    size_t i = 0;
    char* args[MAX_ARGUMENTS]; 

    numArgs = tokenizeArgs(parsedCommand ->arguments, args, MAX_ARGUMENTS);
    if (numArgs == -1){
        errorCode = INVALID_ARGUMETS; 
        return NULL;
    }
    val = malloc(sizeof(char)*numArgs * 2); 
    if (val == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }

    for (i=0; i < numArgs*2; i+=2){
        num = strToNum(args[i/2]);
        if (num == -1 && errorCode != 0){return NULL;}
        if (isValidShort(num) != TRUE){ errorCode = OUT_OF_RANGE_NUMBER; free(val); return NULL; }
        val[i] = (num >> 0 ) & 0xFF;
        val[i+1] = (num >> 8 ) & 0xFF;
    }
    dataBlock = createDataBlock(val, numArgs*2, FALSE);
    if (dataBlock == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }

    return dataBlock; 
}
dataBlock_p dwTranslator(parsedCommand_p parsedCommand){
    dataBlock_p dataBlock; 
    int numArgs; 
    long num; 
    unsigned char* val;
    size_t i = 0;
    char* args[MAX_ARGUMENTS]; 

    numArgs = tokenizeArgs(parsedCommand ->arguments, args, MAX_ARGUMENTS);
    if (numArgs == -1){
        errorCode = INVALID_ARGUMETS; 
        return NULL;
    }
    val = malloc(sizeof(char)*numArgs * 4); 
    if (val == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }

    for (i=0; i < numArgs*4; i+=4){
        num = strToNum(args[i/4]);
        if (num == -1 && errorCode != 0){return NULL;}
        if (isValidDW(num) != TRUE){ errorCode = OUT_OF_RANGE_NUMBER; free(val); return NULL; }
        val[i] = (num >> 0 ) & 0xFF;
        val[i+1] = (num >> 8 ) & 0xFF;
        val[i+2] = (num >> 16 ) & 0xFF;
        val[i+3] = (num >> 24 ) & 0xFF;
    }

    dataBlock = createDataBlock(val, numArgs*4, FALSE);
    if (dataBlock == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }

    return dataBlock; 
}
dataBlock_p strTranslator(parsedCommand_p parsedCommand){
    dataBlock_p dataBlock;  
    char* val;

    val = extractStr(parsedCommand -> arguments);
    if (val == NULL) { if(errorCode==0){errorCode = INVALID_STRING;}  return NULL; }

    dataBlock = createDataBlock((unsigned char*)val, strlen(val)+1 , FALSE);
    if (dataBlock == NULL) { errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }

    return dataBlock; 
}