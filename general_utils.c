#include <string.h>
#include "general_utils.h"

int endsWith(char* src, char* suffix){
	int sufLen = strlen(suffix);
	int srcLen = strlen(src); 
	if (sufLen > srcLen){
		return -1; 
	}
	return strcmp(suffix, &src[srcLen - sufLen]); 
}

