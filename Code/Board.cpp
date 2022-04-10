#include "Board.h"
#include <iostream>


Board::Board()
{
	InitTiles();
}

void Board::DeleteAllTiles()
{
	if (m_Tiles == NULL)
		return;

	for (int i = 0; i < m_TileCount.y; ++i)
	{
		delete[] m_Tiles[i];
	}
	
	delete[] m_Tiles;
}

Board::~Board()
{
	DeleteAllTiles();
}

void Board::InitTiles()
{
	m_Tiles = new Tile*[m_TileCount.x];
	for (int i = 0; i < m_TileCount.x; ++i)
	{
		m_Tiles[i] = new Tile[m_TileCount.y];
	}
}

void Board::CreateAllTiles()
{
	Vector2f tilePos;
	for (int i = 0; i < m_TileCount.x; ++i)
	{
		for (int j = 0; j < m_TileCount.y; ++j)
		{
			tilePos = m_AreaPostion + Vector2f(i * m_TileSize.x, j * m_TileSize.y);
			m_Tiles[i][j].CreateTile(tilePos,m_TileSize);
		}
	}

	m_UnrevealedTileCount = m_TileCount.x * m_TileCount.y;
}

void Board::SetBombs()
{
	srand(time(0));
	int x, y;
	for (int i = 1; i <= m_BombCount ; ++i)
	{
		do
		{
			x = rand() % m_TileCount.x;
			y = rand() % m_TileCount.y;
		} while (m_Tiles[x][y].IsBomb());

		m_Tiles[x][y].SetBomb();
	}

	m_BombRemaining = m_BombCount;
}

bool Board::CheckInBounds(int xIndex, int yIndex)
{
	return xIndex >= 0
		&& yIndex >= 0
		&& xIndex < m_TileCount.x
		&& yIndex < m_TileCount.y;
}

int Board::SetSingleAdjacent(int xIndex, int yIndex)
{
	Vector2i index;
	int count = 0;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			index.x = xIndex + i;
			index.y = yIndex + j;
			if (CheckInBounds(index.x, index.y))
			{
				if (m_Tiles[index.x][index.y].IsBomb())
					count++;
			}
		}
	}

	return count;
}

void Board::SetAllAdjacentNumbers()
{
	for (int i = 0; i < m_TileCount.x; ++i)
	{
		for (int j = 0; j < m_TileCount.y; ++j)
		{
			m_Tiles[i][j].SetAdjacent(SetSingleAdjacent(i, j));
		}
	}
}

void Board::SetTileProperties()
{
	CreateAllTiles();
	SetBombs();
	SetAllAdjacentNumbers();
}

Vector2i Board::FindTileIndex(Vector2i mousePos)
{
	mousePos -= (Vector2i)m_AreaPostion;
	mousePos.x /= m_TileSize.x;
	mousePos.y /= m_TileSize.y;
	
	std::cout << mousePos.x << " " << mousePos.y<<"\n";
	
	return mousePos;
}

void Board::CreateNewBoard(RectangleShape area, int bombCount)
{
	m_BombCount = bombCount;
	m_AreaPostion = area.getPosition();
	m_TileSize.x = area.getSize().x / m_TileCount.x;
	m_TileSize.y = area.getSize().y / m_TileCount.y;
	ResetBoard();
}

void Board::ResetBoard()
{
	m_BombRemaining = m_BombCount;
	m_isBombBlasted = false;

	DeleteAllTiles();
	InitTiles();
	SetTileProperties();
}

void Board::FloodFill(Vector2i pos)
{
	if (m_Tiles[pos.x][pos.y].GetAdjacentCount() == 0)
	{
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				int x = pos.x + i;
				int y = pos.y + j;

				if (x != pos.x || y != pos.y)
				{
					if (CheckInBounds(x, y))
					{
						bool revealed = m_Tiles[x][y].Reveal(false);
						if (revealed)
						{
							m_UnrevealedTileCount--;
							FloodFill(Vector2i(x, y));
						}
					}
				}
			}

		}
	}
}

void Board::PlayLeft(Vector2i mousePos)
{
	Vector2i index = FindTileIndex(mousePos);
	bool revealed = m_Tiles[index.x][index.y].Reveal(true);
	
	if (revealed)
	{
		if (m_Tiles[index.x][index.y].IsBomb())
		{
			m_isBombBlasted = true;
		}
		else if (m_Tiles[index.x][index.y].GetAdjacentCount() == 0)
		{
			FloodFill(index);
			m_UnrevealedTileCount--;
		}
		else
		{
			m_UnrevealedTileCount--;
		}
	}

}

void Board::PlayRight(Vector2i mousePos)
{
	Vector2i index = FindTileIndex(mousePos);
	bool marked = m_Tiles[index.x][index.y].Mark();
	if (marked)
	{
		--m_BombRemaining;
	}
	else
	{
		++m_BombRemaining;
	}
}

void Board::RevealAll()
{
	// reveal all the hideen tiles
	for (int i = 0; i < m_TileCount.x; ++i)
	{
		for (int j = 0; j < m_TileCount.y; ++j)
		{
			m_Tiles[i][j].Reveal(false);
		}
	}
}

bool Board::IsLoss()
{
	if (m_isBombBlasted)
	{
		RevealAll();
	}

	return m_isBombBlasted;
}

bool Board::IsVictory()
{
	if (m_BombCount == m_UnrevealedTileCount)
	{
		RevealAll();
		return true;
	}
	return false;
}

int Board::GetRemainingBombs()
{
	return m_BombRemaining;
}

void Board::RenderBoard(RenderWindow* window)
{
	for (int i = 0; i < m_TileCount.x; ++i)
	{
		for (int j = 0; j < m_TileCount.y; ++j)
		{
			m_Tiles[i][j].Render(window);
		}
	}
}
