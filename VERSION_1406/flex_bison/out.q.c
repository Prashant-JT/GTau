#include "Qlib.h"
#include "Q.h"

#define INI 0
BEGIN
L 0:
	STAT(0)
		MEM(0x11ffc, 4);		 # Reservamos en memoria estática para variable primitiva
		MEM(0x11ff8, 4);		 # Reservamos en memoria estática para variable primitiva
		MEM(0x11ff4, 4);		 # Reservamos en memoria estática para variable primitiva
	CODE(0)
		GT(-2); 		# Terminamos la ejecución
END
