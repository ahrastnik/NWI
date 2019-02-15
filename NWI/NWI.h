#ifndef NWI_PROC
#define NWI_PROC

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "NWI_Tools.h"
#include "common.h"

// Systems
#define BGS			0
#define NWI_108A1	1

// Operation
#define COMMAND		0
#define PARAMETER	1

// Memory Types
//#define PRINCETON	0
//#define HARVARD		1

// System Data
#define SYS_BUS			getBus()		// System bus size[bits]
#define SYS_BUS_BYTE	(getBus() / 8)	// System bus size[bytes]
#define SYS_SIZE		getSize()		// System program memory size[bytes]
#define SYS_MEM			getMemType()	// System memory type: PRINCETON, HARVARD
#define SYS_MEM_OFF		getMemOffset()	// System data memory offset

/*typedef struct var {
	unsigned int adr, index;
	unsigned char size, slot_pos;
	char name[32];
	int val;
} var_t;*/

// Main
int loadSystem(char *system);
int unloadSystem(void);
int compile(char *cmd, var_t *vars, unsigned int var_num, char *params[], unsigned int param_num, unsigned int *cmpl, unsigned int *cmpl_num);
// System data
int getBus(void);
unsigned int getSize(void);
int getMemType(void);
int getMemOffset(void);
char **getSysPrefix(void);
char **getSysSuffix(void);

#endif // !NWI_PROC