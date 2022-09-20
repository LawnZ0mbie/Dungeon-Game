#include "Foe.h"

using namespace DungeonGame;

void Foe::DamagePlayer(FoeData& Foe, PlayerState& playerState, WorldState& worldState)
{
	playerState.PlayerHP -= Foe.Damage;
	playerState.InvulnSeconds = Foe.InvulnSeconds;
}

void Foe::DamageFoe(FoeData& Foe, PlayerState& playerState, WorldState& worldState)
{
	Foe.Alive = false;
	worldState.DefeatedFoes++;
	playerState.Inventory.pop_back();
}

void Foe::SetFoeIndex(int newIndex)
{
	FoeIndex = newIndex;
}

void Foe::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	FoeData& currFoe = worldState.Foes[FoeIndex];

	if (currFoe.Alive)
	{
		Vector2d vecToPlayer = currFoe.Position - playerState.PlayerPosition;

		if (vecToPlayer.GetLength() < 30.0f)                                           //Modify for Sprite image width
		{
			if (playerState.PlayerHP > 0 && playerState.InvulnSeconds <= 0)
			{
				if (playerState.Inventory.size() > 0)
				{
					DamageFoe(currFoe, playerState, worldState);
				}
				else
				{
					DamagePlayer(currFoe, playerState, worldState);
				}
			}
		}
		vecToPlayer.Normalize();
		vecToPlayer *= -1.0f;
		currFoe.Position += vecToPlayer * currFoe.FoeSpeed * deltaSeconds;
	}

	Position = currFoe.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);          //Modify sprite centering
	Visable = currFoe.Alive;
}

