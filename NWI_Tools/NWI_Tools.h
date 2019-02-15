#ifndef NWI_TOOLS
#define NWI_TOOLS

#include "common.h"

// Memory Types
#define PRINCETON	0
#define HARVARD		1

// Errors
#define ERR_ALLOC				-2	// Memory allocation or reallocation failed
#define ERR_FOPEN				-1	// Error opening file
#define ERR_OK					0	// No errors were detected
#define ERR_SYNTAX				1	// Syntax error
#define ERR_ILLEGAL_CHAR		2	// Illegal character
#define ERR_UNKNOWN_CMD			3	// Unknown command
#define ERR_UNKNOWN_PARAM		4	// Unknown parameter
#define ERR_NO_TEXT_SECT		5	// No text section discovered
#define ERR_UNKNOWN_VAR			6	// Unknown variable
#define ERR_UNKNOWN_VAR_FORMAT	7	// Unknown variable format
#define ERR_UNKNOWN_TAG			8	// Unknown pre-processor tag
#define ERR_DUPLI_SECTS			9	// Duplicated section
#define ERR_DUPLI_VAR			10	// Duplicated variable
#define ERR_DUPLI_ADDR			11	// Duplicated jump location/address
#define ERR_DUPLI_MACRO			12	// Duplicated macro
#define ERR_INC_PARAM_NUM		13	// Incompatible parameter number
#define ERR_MULTI_CON_VAR		14	// Multiple constants or variables detected

// Helper
#define FILL(SIZE)	(((1 << (SIZE - 1)) - 1) << 1) + 1 // Fill variable with ones

// Variables
typedef struct var {
	unsigned int adr, index;
	unsigned char size, slot_pos;
	char name[32];
	int val;
} var_t;

// Functions
int isPointer(char *param);

#endif // !NWI_TOOLS
