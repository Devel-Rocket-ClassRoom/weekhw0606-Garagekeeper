#include "Utils.h"

int GetRandInt(int Min, int Max)
{
	return rand() % (Max - Min + 1) + Min;
}

int GetRandInt(int Max)
{
	if (Max == 0) return 0;
	return GetRandInt(0, Max);
}