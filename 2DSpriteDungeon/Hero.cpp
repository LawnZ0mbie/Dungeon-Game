#include "Hero.h"

using namespace DungeonGame;

void Hero::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	Vector2d direction(0.0f, 0.0f);

	bool playerIsAlive = playerState.PlayerHP > 0;

	//PROJECTILE COOLDOWN
	playerState.ShotCoolddownSeconds -= deltaSeconds;
	if (playerState.ShotCoolddownSeconds <= 0.0f)
	{
		playerState.ShotCoolddownSeconds = 0;
	}

	//PLAYER MOVEMENT AND SHOOTING
	if (playerIsAlive && worldState.DefeatedFoes < worldState.TotalFoes)
	{
		if (playerState.WantsToGoUp)
		{
			direction.Y = -1.0f;
		}
		else if (playerState.WantsToGoDown)
		{
			direction.Y = 1.0f;
		}

		if (playerState.WantsToGoLeft)
		{
			direction.X = -1.0f;
		}
		else if (playerState.WantsToGoRight)
		{
			direction.X = 1.0f;
		}
		direction.Normalize();
		
		//SHOOTING PROJECTILES
		if (direction != Vector2d(0.0f, 0.0f))
		{
			playerState.PreviousDirection = direction;
		}

		if (playerState.WantsToShoot)
		{
			Shoot(playerState, playerState.PreviousDirection);
		}

		Vector2d newPosition = playerState.PlayerPosition;
		newPosition += direction * 2000.0f * deltaSeconds;

		if (worldState.IsWalkableTile(newPosition))
		{
			playerState.PlayerPosition = newPosition;
		}
	}

	worldState.CameraPosition = playerState.PlayerPosition;

	Position = playerState.PlayerPosition - Vector2d(Size.X * 0.5f, Size.Y * 0.85f);          //Modify sprite centering

	if (playerState.InvulnSeconds > 0)
	{
		playerState.InvulnSeconds -= deltaSeconds;
		Visable = !Visable;
	}
	else 
	{
		Visable = playerIsAlive;
	}
}

void Hero::Shoot(PlayerState& playerState, const Vector2d& dirction)
{
	if (playerState.Projectiles.size() > 0)
	{
		if (playerState.ShotCoolddownSeconds <= 0.0f)
		{
			for (int i = 0; i < playerState.Projectiles.size(); i++)
			{
				if (!playerState.Projectiles[i].Alive)
				{
					playerState.Projectiles[i].Alive = true;
					playerState.Projectiles[i].Lifetime = 0.0f;
					playerState.Projectiles[i].Direction = dirction;
					playerState.Projectiles[i].Position = playerState.PlayerPosition;

					playerState.ShotCoolddownSeconds = 0.2f;             //Modifies Hero cooldown

					break;
				}
			}
		}
	}
}