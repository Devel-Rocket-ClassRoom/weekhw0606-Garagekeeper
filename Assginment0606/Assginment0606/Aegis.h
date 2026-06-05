#pragma once
#include "Warship.h"
class Aegis :
    public Warship
{
public :
	Aegis(int _Id, const std::string _Name, const int _Size)
		:Warship(_Id, _Name, _Size){}
};

