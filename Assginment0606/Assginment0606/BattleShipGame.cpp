#include <vector>
#include <iostream>

#include "BattleShipGame.h"
#include "BattleShipCommon.h"
#include "Aegis.h"
#include "AirCraftCarrier.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Utils.h"

BattleShipGame::~BattleShipGame()
{
	int size = EnemyVec.size();
	for (int i = 0; i < size; i++)
	{
		delete EnemyVec[i];
		EnemyVec[i] = nullptr;
	}
}

void BattleShipGame::InitMap()
{
	GridMap = std::vector<int>(Width * Height, 0);
	EnemyGrid = std::vector<int>(Width * Height, 0);
	EnemyVec = std::vector<Warship*>();
	InitEnemy();
	SpawnEnemy();
}

FPos BattleShipGame::GetCoordInput()
{
	printf("Enter attack coordinates(x y) : ");
	int X, Y;
	std::cin >> X >> Y;

	return FPos{ X, Y };
}

void BattleShipGame::PrintGrid(std::vector<int>& Map)
{
	printf("\n   ");
	for (int i = 0; i < Width; i++)
	{
		printf("%d  ", i);
	}

	printf("\n");
	for (int Y = 0; Y < Height; Y++)
	{
		printf("%d  ", Y);
		for (int X = 0; X < Width; X++)
		{
			int CellInfo = Map[Y * Width + X];
			char Char2Print = '.';
			if (0 < CellInfo && CellInfo <= EnemyVec.size())
			{
				Char2Print = '#';
			}
			if (CellInfo == static_cast<int>(EMapState::Correct))
			{
				Char2Print = 'O';
			}
			if (CellInfo == static_cast<int>(EMapState::False))
			{
				Char2Print = 'X';
			}
			printf("%c  ", Char2Print);
		}
		printf("\n");
	}
	printf("\n");
}

void BattleShipGame::PrintInfo()
{
	int AliveCnt = 0;
	for (auto e : EnemyVec)
	{
		if (e->GetSize() != 0) AliveCnt++;
	}

	printf("Turns left: %d\n", TurnCount);
	printf("Enemy ships remaining: %d\n", AliveCnt);

}

void BattleShipGame::Run()
{
	InitMap();
	FPos AttackPos;
	bool bQuit = false;
	int AliveCnt = 0;
	printf("Battle Ship game started! Sink all enemy ships within %d turns.\n", TurnCount);
	while (!bQuit)
	{

		//PrintGrid(EnemyGrid);
		PrintGrid(GridMap);
		PrintInfo();
		AttackPos = GetCoordInput();
		ClearScreen();
		if (CheckPosValidate(AttackPos))
		{
			Attack(AttackPos);
			TurnCount--;
		}
		if (CheckEneCondition())
		{
			bQuit = !GetRestartInput();
		}
	}

}

void BattleShipGame::ClearScreen()
{
	system("cls");
}

void BattleShipGame::SpawnEnemy()
{
	for (Warship* Shipptr : EnemyVec)
	{
		PlaceRand(Shipptr);
	}
}

void BattleShipGame::InitEnemy()
{
	EnemyVec.push_back(new AirCraftCarrier(1, "항공모함", 5));
	EnemyVec.push_back(new Cruiser(2, "순양함", 4));
	EnemyVec.push_back(new Destroyer(3, "구축함", 3));
	EnemyVec.push_back(new Aegis(4, "이지스함", 2));
}

void BattleShipGame::PlaceRand(Warship* Ship)
{
	int Dx[4] = { 0, 1, 0, -1 };
	int Dy[4] = { -1, 0, 1, 0 };

	bool bDone = false;
	// 해당 함선의 배치가 끝날때까지 반복
	while (!bDone)
	{
		int RandPos = GetRandInt(Width * Height - 1);
		int X = RandPos % Width;
		int Y = RandPos / Width;
		int Size = Ship->GetSize();
		FPos TargetPos = { X,Y };

		// 정한 좌표에 이미 함선이 있는 경우
		if (EnemyGrid[Y * Width + X] != 0) continue;

		// 갈 수 있는 방향을 판단
		std::vector<bool> CanGoDir = boolCheckCondition(TargetPos, Size);

		// 가능한 방향 중 랜덤으로 한 방향 선택
		std::vector<int> DirList;
		for (int i = 0; i < 4; i++)
		{
			// 갈수 있는 방향의 인덱스만 모음
			if (CanGoDir[i] == true)
				DirList.push_back(i);
		}
		// 갈수 있는 방향이 없는 경우
		if (DirList.size() == 0) continue;

		// 방향 인덱스중에 하나 임의 선택
		int DirIndex = GetRandInt(DirList.size() - 1);

		int Id = Ship->GetId();
		int Nx = X;
		int Ny = Y;

		// 격자에 정한 방향으로 사이즈 만큼 함선의 ID를 기록
		EnemyGrid[Y * Width + X] = Id;
		for (int i = 0; i < Size - 1; i++)
		{
			Nx = Nx + Dx[DirIndex];
			Ny = Ny + Dy[DirIndex];

			EnemyGrid[Ny * Width + Nx] = Id;
		}

		// 끝났다고 표시
		bDone = true;
	}
}

std::vector<bool> BattleShipGame::boolCheckCondition(FPos Pos, const int Size)
{

	// U R D L
	std::vector<bool>DirArr = { true, true, true, true };

	std::vector<int>Dx = { 0, 1, 0, -1 };
	std::vector<int>Dy = { -1, 0, 1, 0 };

	int Cx = Pos.X;
	int Cy = Pos.Y;

	

	// R D L U 4방향 순회
	for (int i = 0; i < 4; i++)
	{
		int Nx = Pos.X;
		int Ny = Pos.Y;
		// 한 방향으로 size만큼 탐색 (-1인 이유는 PlaceRand에서 시작점은 거름)
		for (int j = 0; j < Size - 1; j++)
		{
			Nx += +Dx[i];
			Ny += +Dy[i];
			// 격자 바깥
			if (Nx < 0 || Nx >= Width || Ny < 0 || Ny >= Height)
			{
				DirArr[i] = false;
				break;
			}

			// 함선이 이미 존재
			if (EnemyGrid[Ny * Width + Nx] != 0)
			{
				DirArr[i] = false;
				break;
			}
			
		}
	}

	return DirArr;
}

bool BattleShipGame::CheckPosValidate(FPos Pos)
{
	bool Res = true;

	// 격자 바깥
	if (Pos.X >= Width || Pos.X < 0 || Pos.Y >= Height || Pos.Y < 0)
	{
		printf("Invalid Coordinates\n");
		Res = false;
	}

	// 이미 공격한 좌표처리
	else if (GridMap[Pos.Y * Width + Pos.X] != 0)
	{
		printf("Already attacked coordinates.\n");
		Res = false;
	}

	return Res;
}

void BattleShipGame::Attack(FPos Pos)
{
	// 2차원 좌표를 1차원으로 전환
	int OneDPos = Pos.Y * Width + Pos.X;

	// 적이 없는 경우
	if (EnemyGrid[OneDPos] == 0)
	{
		// 실패 기록
		GridMap[OneDPos] = static_cast<int>(EMapState::False);
		printf("Miss...\t");
	}
	else
	{
		// 적이 있는 경우

		//적 한칸 지움
		int EnemyId = EnemyGrid[OneDPos];
		EnemyGrid[OneDPos] = 0;
		// 성공기록
		GridMap[OneDPos] = static_cast<int>(EMapState::Correct);

		printf("Hit!!!\t");
		EnemyVec[EnemyId - 1]->OnAttack();
	}
}

void BattleShipGame::CleanUpForRestart()
{
	int size = EnemyVec.size();
	for (int i = 0; i < size; i++)
	{
		delete EnemyVec[i];
		EnemyVec[i] = nullptr;
	}
	EnemyVec.clear();

	GridMap = std::vector<int>(Width * Height, 0);
	EnemyGrid = std::vector<int>(Width * Height, 0);
	EnemyVec = std::vector<Warship*>();
	InitEnemy();
	SpawnEnemy();

	TurnCount = InitTurnCount;
	ClearScreen();
}

bool BattleShipGame::GetRestartInput()
{
	bool Res = false;
	int Input = 0;

	printf("1. 다시하기, 2. 종료하기:");
	while (Input == 0)
	{
		std::cin >> Input;
		if (Input != 1 && Input != 2)
		{
			printf(" 다시 입력하세세요! \n");
			Input = 0;
		}
	}

	if (Input == 1)
	{
		Res = true;
		CleanUpForRestart();
	}

	return Res;
}

bool BattleShipGame::CheckEneCondition()
{
	bool bDone = false;
	

	int AliveCnt = 0;
	for (auto e : EnemyVec)
	{
		if (e->GetSize() != 0) AliveCnt++;
	}
	if (TurnCount <= 0 || AliveCnt <= 0)
	{
		PrintGrid(GridMap);
		bDone = true;

		if (TurnCount > 0 && AliveCnt <= 0)
		{
			printf("당신의 승리!\n");
		}

		if (TurnCount <= 0 && AliveCnt > 0)
		{
			printf("당신의 패배!\n");
		}

		if (TurnCount <= 0 && AliveCnt <= 0)
		{
			printf("당신의 승리!\n");
		}
	}
	return bDone;
}
