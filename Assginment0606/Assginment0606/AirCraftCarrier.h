#pragma once
#include "Warship.h"
class AirCraftCarrier :
    public Warship
{
public:
    AirCraftCarrier(int _Id, const std::string _Name, const int _Size)
        :Warship(_Id, _Name, _Size){}
};

