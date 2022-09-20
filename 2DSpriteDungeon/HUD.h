#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class HUD : public Sprite
	{
	public:
		void InitailizeInventorySprites(SDL_Renderer* pRenderer, const std::string& bookFilepath, const std::string& sbookFilepath, const std::string& healthFilepath, const std::string& gameoverFilepath, const std::string& gamewonFilepath);

		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	private:
		SDL_Texture* BookTexture;
		SDL_Texture* SBookTexture;

		SDL_Texture* HealthTexture;

		SDL_Texture* GameOverTexture;
		SDL_Texture* GameWonTexture;
	};
}