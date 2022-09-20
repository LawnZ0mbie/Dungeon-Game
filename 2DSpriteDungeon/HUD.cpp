#include "HUD.h"
#include "Sprite.h"

namespace DungeonGame
{
	void HUD::InitailizeInventorySprites(SDL_Renderer* pRenderer, const std::string& bookFilepath, const std::string& sbookFilepath, const std::string& healthFilePath, const std::string& gameoverFilepath, const std::string& gamewonFilepath)
	{
		BookTexture = LoadTexture(pRenderer, bookFilepath);
		SBookTexture = LoadTexture(pRenderer, sbookFilepath);
		HealthTexture = LoadTexture(pRenderer, healthFilePath);
		GameOverTexture = LoadTexture(pRenderer, gameoverFilepath);
		GameWonTexture = LoadTexture(pRenderer, gamewonFilepath);
	}

	void HUD::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
	{
		//Game Over Display
		if (playerState.PlayerHP <= 0)
		{
			SDL_Rect destRect = {
					360.0f,
					110.0f,
					512.0f,
					512.0f };
			SDL_RenderCopy(pRenderer, GameOverTexture, nullptr, &destRect);
		}
		//Game Won Display
		if (worldState.DefeatedFoes >= worldState.TotalFoes)
		{
			SDL_Rect destRect = {
					360.0f,
					110.0f,
					512.0f,
					512.0f };
			SDL_RenderCopy(pRenderer, GameWonTexture, nullptr, &destRect);
		}

		//Inventory Display
		for (unsigned int i = 0; i < playerState.Inventory.size(); i++)
		{
			ItemType currItem = playerState.Inventory[i];

			switch (currItem)
			{
			case Item_BOOK:
				MyTexture = BookTexture;
				break;
			case Item_SBOOK:
				MyTexture = SBookTexture;
				break; 
			default:
				MyTexture = nullptr;
				break;
			}

			if (MyTexture != nullptr)
			{
				SDL_Rect destRect = {
					(int)(0.0f + 56.0f * i),
					(int)72.0f,
					(int)Size.X,
					(int)Size.Y };
				SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
			}
		}
		//Health Display
		for (unsigned int i = 0; i < playerState.PlayerHP; i++)
		{
			MyTexture = HealthTexture;

			if (MyTexture != nullptr)
			{
				SDL_Rect destRect = {
					(int)(0.0f + 56.0f * i),
					(int)0.0f,
					(int)Size.X,
					(int)Size.Y };
				SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
			}
		}
	}
}