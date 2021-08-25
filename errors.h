#ifndef ERROS
#define ERROs

/*
    The plan was to do something like my own errno so could 
    know what was the problem and print a better error message for each erro 
    but because of time limitation it is not finised. 
*/
#define UNFAMILIAR_DATA_TYPE 410
#define INVALID_STRING 409
#define OUT_OF_RANGE_NUMBER 408
#define LABEL_DOES_NOT_EXIST 407
#define LABALE_TOO_FAR 406
#define INVALID_LABEL 405
#define INVALID_NUM_ARGUMENT 404
#define TOO_MANY_ARGUMENTS 403
#define INVALID_ARGUMETS 402
#define INVALID_REGISTER 401
#define NOT_VALID_LABEL_ERROR_CODE 400 
#define MEMORY_ALLOCATION_ERROR_CODE 500
#define OUT_OF_MEMORY 300 


extern int errorCode;  
#endif