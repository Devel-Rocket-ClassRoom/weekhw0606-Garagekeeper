#pragma once
#include "Warship.h"
class Cruiser :
    public Warship
{
public:
    Cruiser(int _Id, const std::string _Name, const int _Size)
        :Warship(_Id, _Name, _Size){}
};

