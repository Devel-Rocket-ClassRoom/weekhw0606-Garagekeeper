#include "WarShip.h"

void Warship::OnAttack()
{
	Size--;
	if (Size <= 0)
	{
		Size = 0;
		OnDead();
	}
}

void Warship::OnDead()
{
	printf("%s이 바닷속으로 사라졌습니다!", Name.c_str());
}
