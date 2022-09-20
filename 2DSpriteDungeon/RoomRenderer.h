#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class RoomRenderer : public Sprite
	{
	public:
		void InitailizeRoomTiles(SDL_Renderer* pRenderer, const std::string& floor1Filepath, const std::string& floor2Filepath, const std::string& wallFilepath);

		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	private:
		SDL_Texture* Floor1Texture;
		SDL_Texture* Floor2Texture;
		SDL_Texture* WallTexture;
	};
}