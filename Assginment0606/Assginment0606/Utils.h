#pragma once
#include <stdlib.h>

/// <summary>
/// Min부터 Max까지의 범위에서 난수를 반환하는 함수
/// </summary>
/// <param name="Min">최소 포함값</param>
/// <param name="Max">최대 포함값</param>
/// <returns>생성된 난수</returns>
int GetRandInt(int Min, int Max);

/// <summary>
/// 0부터 Max까지의 범위에서 난수를 반환하는 함수
/// </summary>
/// <param name="Max">최대 포함값</param>
/// <returns>생성된 난수</returns>
int GetRandInt(int Max);