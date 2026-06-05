#pragma once
#include "Warship.h"
class Destroyer :
    public Warship
{
public:
    Destroyer(int _Id, const std::string _Name, const int _Size)
        :Warship(_Id, _Name, _Size){}
};

