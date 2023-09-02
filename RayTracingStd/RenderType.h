#include "RenderStructure.h"

typedef struct
{
	long		NumThread;
	long		TotalThread;
	long		NbLines;
	TYPE_ALGO	TypeAlgo;
	long		Duree;
	bool		bTerminated;
} StructRenderType;