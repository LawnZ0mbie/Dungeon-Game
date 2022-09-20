#pragma once
#include "SDL.h"
#include <string>
#include <vector>

namespace DungeonGame
{
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	struct Vector2d
	{
		float X;
		float Y;

		Vector2d() :
			X(0.0f),
			Y(0.0f)
		{
		}

		Vector2d(float inX, float inY) :
			X(inX),
			Y(inY)
		{
		}

		bool operator==(const Vector2d& otherPosition) const
		{
			return X == otherPosition.X && Y == otherPosition.Y;
		}

		bool operator!=(const Vector2d& otherPosition) const
		{
			return !(*this == otherPosition);
		}

		Vector2d& operator+=(const Vector2d& rhs)
		{
			this->X += rhs.X;
			this->Y += rhs.Y;
			return *this;
		}

		const Vector2d operator+(const Vector2d& rhs) const
		{
			return Vector2d(*this) += rhs;
		}
		
		Vector2d& operator-=(const Vector2d& rhs)
		{
			this->X -= rhs.X;
			this->Y -= rhs.Y;
			return *this;
		}

		const Vector2d operator-(const Vector2d& rhs) const
		{
			return Vector2d(*this) -= rhs;
		}

		Vector2d operator*=(float scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			return *this;
		}

		const Vector2d operator*(float scalar) const
		{
			return Vector2d(*this) *= scalar;
		}

		float GetLength()
		{
			return sqrtf(X * X + Y * Y);
		}

		void Normalize()
		{
			float length = GetLength();
			if (length > 0.0f)
			{
				X = X / length;
				Y = Y / length;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
			}
		}
	};

	enum ItemType
	{
		Item_BOOK,
		Item_SBOOK
	};

	enum FoeType
	{
		Foe_GOBLIN,
		Foe_KGOBLIN,
		Foe_SPIKE
	};

	struct ProjectileData
	{
		bool Alive;
		float Lifetime;
		Vector2d Direction;
		Vector2d Position;
	};

	struct PlayerState
	{
		bool HasFinishedGame;

		bool WantsToGoUp;
		bool WantsToGoDown;
		bool WantsToGoLeft;
		bool WantsToGoRight;

		bool WantsToShoot;
		float ShotCoolddownSeconds;

		int PlayerHP;
		float InvulnSeconds;

		Vector2d PlayerPosition;

		Vector2d PreviousDirection;

		std::vector<ItemType> Inventory;

		std::vector<ProjectileData> Projectiles;
	};

	struct ItemData
	{
		bool Active;
		ItemType Type;
		Vector2d Position;

	};

	struct FoeData
	{
		bool Alive;
		FoeType Type;
		Vector2d Position;
		int Damage;
		float InvulnSeconds;
		float FoeSpeed;

	};

	struct WorldState
	{
		int TilesPerRow;
		std::string Tiles;

		unsigned int TotalFoes;
		unsigned int DefeatedFoes;

		Vector2d TileSizeInPixels;

		std::vector<ItemData> Items;
		std::vector<FoeData> Foes;

		Vector2d CameraPosition;

		float SecondsAfterDefeat;

		bool IsWalkableTile(const Vector2d& inPosition);
	};

	void InializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState);
	void GetInput(PlayerState& playerState, const WorldState& worldState);
	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState);
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState);
	void CleanupGame(PlayerState& playerState, WorldState& worldState);
}