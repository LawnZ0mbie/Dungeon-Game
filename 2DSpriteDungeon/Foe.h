#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Foe : public Sprite
	{
	public:

		void SetFoeIndex(int newIndex);

		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

		void DamagePlayer(FoeData& Foe, PlayerState& playerState, WorldState& worldState);

		void DamageFoe(FoeData& Foe, PlayerState& playerState, WorldState& worldState);

	private:

		unsigned int FoeIndex;
	};

}