#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Projectile : public Sprite
	{
	public:

		void SetProjectileIndex(int newIndex);

		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

	private:

		unsigned int ProjectileIndex;
	};

}