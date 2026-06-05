#pragma once
#include <vector>
#include "WarShip.h"

class BattleShipGame
{
	const int Width = 10;
	const int Height = 10;
	const int InitEnemyCount = 4;
	const int InitTurnCount = 30;
	const int DirCnt = 4;

	std::vector<int> GridMap;
	std::vector<int> EnemyGrid;
	std::vector<Warship*> EnemyVec;

	int TurnCount = InitTurnCount;

public:
	BattleShipGame() = default;
	~BattleShipGame();

	/// <summary>
	/// 게임 초기화 함수
	/// </summary>
	void InitMap();

	/// <summary>
	/// 좌표를 입력받는 함수
	/// </summary>
	/// <returns>유효한 좌표를 FPos형으로 반환</returns>
	FPos GetCoordInput();

	/// <summary>
	/// 격자를 출력하는 함수
	/// </summary>
	/// <param name="Map">출력할 격자</param>
	void PrintGrid(std::vector<int>& Map);

	/// <summary>
	/// 남은턴, 남은 함선 수를 출력하는 함수
	/// </summary>
	void PrintInfo();

	/// <summary>
	/// 게임을 구동하는 함수
	/// </summary>
	void Run();

	/// <summary>
	/// 화면을 정리하는 함수
	/// </summary>
	void ClearScreen();

	/// <summary>
	/// 적을 소환하는 함수
	/// </summary>
	void SpawnEnemy();

	/// <summary>
	/// 적을 초기화(동적할당)하는 함수
	/// </summary>
	void InitEnemy();

	/// <summary>
	/// 함선을 랜덤으로 배치하는 함수
	/// </summary>
	/// <param name="Ship">배치할 함선의 포인터</param>
	void PlaceRand(Warship* Ship);

	/// <summary>
	/// 해당 좌표에서 4방향(RDLU)로 Size만큼 갈 수 있는지 반환하는 함수
	/// </summary>
	/// <param name="Pos"> 시작 좌표 </param>
	/// <param name="Size"> 크기 </param>
	/// <returns>가능 여부를 담은 bool vector</returns>
	std::vector<bool> boolCheckCondition(FPos Pos, const int Size);

	/// <summary>
	/// 좌표가 유효한지 확인하는 함수
	/// </summary>
	/// <param name="Pos">판단할 좌표</param>
	/// <returns>유효하면 true반환</returns>
	bool CheckPosValidate(FPos Pos);

	/// <summary>
	/// 해당 좌표에 공격을 하는 함수
	/// 성공 실패 여부를 맵에 기록
	/// </summary>
	/// <param name="Pos">공격을 할 위치</param>
	void Attack(FPos Pos);

	/// <summary>
	/// 게임 재시작을 위해서 변수들을 초기화하는 함수
	/// </summary>
	void CleanUpForRestart();

	/// <summary>
	/// 종료조건을 확인하는 함수
	/// </summary>
	/// <returns> 게임 종료여부 </returns>
	bool CheckEneCondition();

	/// <summary>
	/// 재시작을 위한 입력을 받는 함수
	/// </summary>
	/// <returns>재시작 여부</returns>
	bool GetRestartInput();
};
