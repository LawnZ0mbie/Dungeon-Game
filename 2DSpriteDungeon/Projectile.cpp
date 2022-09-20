#include "Projectile.h"

using namespace DungeonGame;

void Projectile::SetProjectileIndex(int newIndex)
{
	ProjectileIndex = newIndex;
}

void Projectile::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	ProjectileData& currProjectile = playerState.Projectiles[ProjectileIndex];

	Vector2d vecToPlayer = currProjectile.Position - playerState.PlayerPosition;
	if (currProjectile.Alive)
	{
		Vector2d newPosition = currProjectile.Position;
		newPosition += currProjectile.Direction * 5000.0f * deltaSeconds;    //Modifies speed of projectile
		currProjectile.Position = newPosition;

		for (int i = 0; i < worldState.Foes.size(); i++)                     //Hits and destroies enemies with projectiles
		{
			FoeData& currFoe = worldState.Foes[i];
			Vector2d vecToFoe = currFoe.Position - currProjectile.Position;
			if (vecToFoe.GetLength() < 30.0f)
			{
				currProjectile.Alive = false;
				currFoe.Alive = false;
				worldState.DefeatedFoes++;
				break;
			}
		}

		currProjectile.Lifetime += deltaSeconds;
		if (currProjectile.Lifetime > 0.2)                    //Modifies rate of fire for projectile
		{
			currProjectile.Alive = false;
		}
	}

	Position = currProjectile.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.75f);          //Modify sprite centering
	Visable = currProjectile.Alive;
}