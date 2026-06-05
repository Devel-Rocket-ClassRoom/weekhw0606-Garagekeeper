#pragma once

struct FPos
{
	int X;
	int Y;
};

struct FDir
{
	int X;
	int Y;
};

enum class EMapState
{
	None = 0,
	Correct = 10,
	False = 11,
};

enum class EDir
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3,
	EDirLen = 4,
};
