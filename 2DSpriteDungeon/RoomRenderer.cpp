#include "RoomRenderer.h"

namespace DungeonGame
{
	void RoomRenderer::InitailizeRoomTiles(SDL_Renderer* pRenderer, const std::string& floor1Filepath, const std::string& floor2Filepath, const std::string& wallFilepath)
	{
		Floor1Texture = LoadTexture(pRenderer, floor1Filepath);
		Floor2Texture = LoadTexture(pRenderer, floor2Filepath);
		WallTexture = LoadTexture(pRenderer, wallFilepath);
	}

	void RoomRenderer::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
	{
		int columnsRendered = 0;
		int rowsRendered = 0;

		for (int i = 0; i < worldState.Tiles.size(); i++)
		{
			char currentTile = worldState.Tiles[i];

			switch (currentTile)
			{
			case '#':
				MyTexture = WallTexture;
				break;
			case '.':
				MyTexture = Floor1Texture;
				break;
			case ',':
				MyTexture = Floor2Texture;
				break;
			default:
				MyTexture = nullptr;
				break;
			}

			if (MyTexture != nullptr)
			{
				SDL_Rect destRect = { 
					columnsRendered * (int)worldState.TileSizeInPixels.X + (int)baseTranslation.X,
					rowsRendered * (int)worldState.TileSizeInPixels.Y + (int)baseTranslation.Y,
					(int)worldState.TileSizeInPixels.X,
					(int)worldState.TileSizeInPixels.Y };
				SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
			}

			columnsRendered++;
			if (columnsRendered % worldState.TilesPerRow == 0)
			{
				rowsRendered++;
				columnsRendered = 0;
			}
		}
	}
}