#pragma once

#include "Tile.h"

class Board
{
private:
	Vector2f m_TileSize;
	Vector2i m_TileCount = Vector2i(12,12);

	Tile** m_Tiles;

	Vector2f m_AreaPostion;
	Vector2f m_AreaSize;

	int m_BombCount = 0;
	int m_BombRemaining = 0;
	int m_UnrevealedTileCount = 0;

	bool m_isBombBlasted = false;

	void RevealAll();
	void InitTiles();


	bool CheckInBounds(int xIndex, int yIndex);

	void CreateAllTiles();
	void SetBombs();
	int SetSingleAdjacent(int xIndex, int yIndex);
	void SetAllAdjacentNumbers();
	void SetTileProperties();

	Vector2i FindTileIndex(Vector2i mousePos);
	void FloodFill(Vector2i pos);

	void DeleteAllTiles();

public:
	Board();
	virtual ~Board();

	void CreateNewBoard(RectangleShape area, int bombCount);
	void ResetBoard();

	void PlayLeft(Vector2i mousePos);
	void PlayRight(Vector2i mousePos);

	bool IsLoss();
	bool IsVictory();

	int GetRemainingBombs();

	void RenderBoard(RenderWindow* window);
};

