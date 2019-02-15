#include "NWI_Tools.h"

int isPointer(char *param) {
	if (strlen(param) > 0) {
		if (countChars(param, '[') == 1 && *param == '[') {
			if (countChars(param, ']') != 1 || param[strlen(param) - 1] != ']') return -1;
			// Remove first bracket
			memcpy(param, param + 1, strlen(param));
			// Remove last bracket
			param[strlen(param) - 1] = '\0';
			return 1;
		}
	}
	return 0;
}
