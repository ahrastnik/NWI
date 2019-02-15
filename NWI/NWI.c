#include "NWI.h"

// List of all supported systems
const char *systems[] = { "BGS", "NWI_108A1", NULL };
// Current System in use
volatile static int sys = -1, bus = -1, mem = -1;
volatile static unsigned int size = 0;
volatile static char **sys_prefix = NULL, **sys_suffix = NULL;

// System function pointers
typedef int(*sys_cmpl_f)(char *, var_t *, unsigned int, char **, unsigned int, unsigned int *, unsigned int *);
typedef int(*sys_bus_f)();
typedef int(*sys_size_f)();
typedef int(*sys_mem_f)();
typedef int(*sys_mem_off_f)();

// System DLL
volatile static HINSTANCE sys_dll = NULL;
// System functions
volatile static sys_cmpl_f sys_cmpl = NULL;
volatile static sys_bus_f sys_bus = NULL;
volatile static sys_size_f sys_size = NULL;
volatile static sys_mem_f sys_mem = NULL;
volatile static sys_mem_f sys_mem_off = NULL;

int loadSystem(char *system) {
	// Convert system string to upper case
	toUpper(system);
	// Check if the system exists
	int sys_index = getStringIndex(system, systems);

	if (sys_index > -1) {
		sys = sys_index;
		// Append .dll to system
		char *dll_name = NULL;
		dll_name = malloc(strlen(system) + 5);
		if (dll_name == NULL) return -1;
		strcpy(dll_name, system);
		strcat(dll_name, ".dll");
		// Load System DLL
		sys_dll = LoadLibrary(dll_name);
		free(dll_name);

		if (sys_dll) {
			// Load System functions
			sys_cmpl = (sys_cmpl_f)GetProcAddress(sys_dll, "sys_cmpl");
			sys_bus = (sys_bus_f)GetProcAddress(sys_dll, "sys_bus");
			sys_size = (sys_size_f)GetProcAddress(sys_dll, "sys_size");
			sys_mem = (sys_mem_f)GetProcAddress(sys_dll, "sys_mem");
			sys_mem_off = (sys_mem_off_f)GetProcAddress(sys_dll, "sys_mem_offset");

			if (sys_cmpl == NULL || sys_bus == NULL || sys_size == NULL || sys_mem == NULL || sys_mem_off == NULL) {
				printf("Not all system functions were loaded!\n");
				FreeLibrary(sys_dll);
				return -1;
			}
			// Get System data
			bus = sys_bus();
			size = sys_size();
			mem = sys_mem();
			return 0;
		}
		else {
			printf("Failed to load dll! %d\n", GetLastError());
		}
	}
	return -1;
}

int unloadSystem(void){
	if (sys_dll) {
		FreeLibrary(sys_dll);
	}
	return 0;
}

int compile(char *cmd, var_t *vars, unsigned int var_num, char *params[], unsigned int param_num, unsigned int *cmpl, unsigned int *cmpl_num) {
	if (sys_cmpl) {
		return sys_cmpl(cmd, vars, var_num, params, param_num, cmpl, cmpl_num);
	}
	return 0;
}

int getBus(void) {
	if (sys != -1) return bus;
	return 0;
}

unsigned int getSize(void) {
	if (sys != -1) return size;
	return 0;
}

int getMemType(void) {
	if (sys != -1) return mem;
	return 0;
}

int getMemOffset(void) {
	if (sys_mem_off != NULL) {
		return sys_mem_off();
	}
	return 0;
}

char** getSysPrefix(void) {
	return sys_prefix;
}

char** getSysSuffix(void) {
	return sys_suffix;
}