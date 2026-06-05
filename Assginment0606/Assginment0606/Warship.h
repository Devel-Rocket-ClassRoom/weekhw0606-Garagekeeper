#pragma once
#include "BattleShipCommon.h"
#include <string>

class Warship
{
	int Id = 0;
	std::string Name = "전함";
	FPos StartPos = { 0,0 };
	FDir ShipDir = { 0,0 };
	int Size = 2;

public :
	Warship() = default;
	Warship(int _Id, std::string _Name, FPos _StarPos, FDir _ShipDir, const int _Size)
		:Id(_Id), Name(_Name), StartPos(_StarPos), ShipDir(_ShipDir), Size(_Size) {}
	Warship(int _Id, const std::string _Name, const int _Size)
		:Id(_Id), Name(_Name), Size(_Size)
	{}

	inline int GetSize() { return Size; }
	inline int GetId() { return Id; }

	virtual void OnAttack();
	virtual void OnDead();
};

