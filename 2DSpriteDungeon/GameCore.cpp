#include "GameCore.h"
#include "Sprite.h"
#include "Hero.h"
#include "RoomRenderer.h"
#include "Item.h"
#include "Foe.h"
#include "HUD.h"
#include "BG.h"
#include "Projectile.h"

namespace DungeonGame
{
	std::vector<Sprite*> SpriteList;

	bool WorldState::IsWalkableTile(const Vector2d& inPosition)
	{
		int column = (int)inPosition.X / (int)TileSizeInPixels.X;
		int row = (int)inPosition.Y / (int)TileSizeInPixels.Y;

		char currentTile = ' ';
		int index = row * TilesPerRow + column;

		if (index >= 0 && index < (int)Tiles.size())
		{
			currentTile = Tiles[index];
		}

		return currentTile == '.' || ','; //add OR to designate a tile as walkable
	}

	void InializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)
	{
		playerState.HasFinishedGame = false;
		playerState.PlayerHP = 3;
		playerState.InvulnSeconds = 0.0f;
		playerState.ShotCoolddownSeconds = 0.0f;

		playerState.PreviousDirection = Vector2d(1.0f, 0.0f);

		playerState.WantsToGoUp = false;
		playerState.WantsToGoDown = false;
		playerState.WantsToGoLeft = false;
		playerState.WantsToGoRight = false;
		playerState.WantsToShoot = false;

		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(0.0f, 0.0f) }); //test code, remove later
		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(0.0f, 0.0f) }); //test code, remove later
		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(0.0f, 0.0f) }); //test code, remove later
		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(0.0f, 0.0f) }); //test code, remove later
		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(0.0f, 0.0f) }); //test code, remove later
		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(0.0f, 0.0f) }); //test code, remove later

		worldState.DefeatedFoes = 0;
		worldState.TotalFoes = 0;

		worldState.SecondsAfterDefeat = 0;
		worldState.TilesPerRow = 20;                                  //Change as room width changes
		worldState.TileSizeInPixels = Vector2d(72.0f, 72.0f);         //Change depending on image size
		worldState.Tiles = 
			"####################"
			"#..............,.,.#"
			"#..,....,..........#"
			"#..........,......,#"
			"#.....,.......,....#"
			"#.,.........,......#"
			"#......,.......,...#"
			"#..,..,...,........#"
			"#............,...,.#"
			"#..,.....,.........#"
			"#..................#"
			"#,.....,......,....#"
			"#.........,........#"
			"#...,........,.....#"
			"#..................#"
			"#,.....,...,.....,.#"
			"####################";

		worldState.Items.push_back({ true, Item_BOOK, Vector2d{10.0f * worldState.TileSizeInPixels.X, 8.0f * worldState.TileSizeInPixels.Y} });
		worldState.Items.push_back({ true, Item_BOOK, Vector2d{4.0f * worldState.TileSizeInPixels.X, 8.0f * worldState.TileSizeInPixels.Y} });
		worldState.Items.push_back({ true, Item_BOOK, Vector2d{4.0f * worldState.TileSizeInPixels.X, 4.0f * worldState.TileSizeInPixels.Y} });
		worldState.Items.push_back({ true, Item_BOOK, Vector2d{10.0f * worldState.TileSizeInPixels.X, 10.0f * worldState.TileSizeInPixels.Y} });
		worldState.Items.push_back({ true, Item_BOOK, Vector2d{9.0f * worldState.TileSizeInPixels.X, 2.0f * worldState.TileSizeInPixels.Y} });
		worldState.Items.push_back({ true, Item_BOOK, Vector2d{2.0f * worldState.TileSizeInPixels.X, 15.0f * worldState.TileSizeInPixels.Y} });

		worldState.Items.push_back({ true, Item_SBOOK, Vector2d{6.0f * worldState.TileSizeInPixels.X, 5.0f * worldState.TileSizeInPixels.Y} });

		worldState.Foes.push_back({ true, Foe_GOBLIN, Vector2d{12.0f * worldState.TileSizeInPixels.X, 12.0f * worldState.TileSizeInPixels.Y}, 1, 0.15f, 1200.0f }); //change to 1200.of
		worldState.TotalFoes++;
		worldState.Foes.push_back({ true, Foe_GOBLIN, Vector2d{1.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y}, 1, 0.15f, 1200.0f });
		worldState.TotalFoes++;
		worldState.Foes.push_back({ true, Foe_GOBLIN, Vector2d{2.0f * worldState.TileSizeInPixels.X, 2.0f * worldState.TileSizeInPixels.Y}, 1, 0.15f, 1200.0f });
		worldState.TotalFoes++;
		worldState.Foes.push_back({ true, Foe_GOBLIN, Vector2d{7.0f * worldState.TileSizeInPixels.X, 8.0f * worldState.TileSizeInPixels.Y}, 1, 0.15f, 1200.0f });
		worldState.TotalFoes++;
		worldState.Foes.push_back({ true, Foe_GOBLIN, Vector2d{8.0f * worldState.TileSizeInPixels.X, 7.0f * worldState.TileSizeInPixels.Y}, 1, 0.15f, 1200.0f });
		worldState.TotalFoes++;
		worldState.Foes.push_back({ true, Foe_GOBLIN, Vector2d{12.0f * worldState.TileSizeInPixels.X, 12.0f * worldState.TileSizeInPixels.Y}, 1, 0.15f, 1200.0f });
		worldState.TotalFoes++;

		worldState.Foes.push_back({ true, Foe_KGOBLIN, Vector2d{13.0f * worldState.TileSizeInPixels.X, 11.0f * worldState.TileSizeInPixels.Y}, 3, 0.15f, 500.0f });
		worldState.TotalFoes++;

		BG* bg = new BG;                                        //Order in which these sprites are added determines what layer they render on, first on top last
		bg->Initailize(pRenderer, "Assets/background.bmp");
		bg->Position = Vector2d(0.0f, -0.0f);
		bg->Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT);
		SpriteList.push_back(bg);

		RoomRenderer* newRoomRenderer = new RoomRenderer;
		newRoomRenderer->InitailizeRoomTiles(pRenderer, "Assets/floor.bmp", "Assets/sbooktemp.bmp", "Assets/wall.bmp"); //change to floor2.bmp
		SpriteList.push_back(newRoomRenderer);

		for (unsigned int i = 0; i < worldState.Items.size(); i++)
		{
			std::string itemFilePath = "Assets/book.bmp";
			switch (worldState.Items[i].Type)
			{
			case Item_BOOK:
				itemFilePath = "Assets/book.bmp";
				break;
			case Item_SBOOK:
				itemFilePath = "Assets/sbook.bmp";
				break;
			}

			Item* newItem = new Item;
			newItem->Initailize(pRenderer, itemFilePath);
			newItem->SetItemIndex(i);
			SpriteList.push_back(newItem);
		}

		for (unsigned int i = 0; i < worldState.Foes.size(); i++)
		{
			std::string foeFilePath = "Assets/goblin.bmp";
			switch (worldState.Foes[i].Type)
			{
			case Foe_GOBLIN:
				foeFilePath = "Assets/goblin.bmp";
				break;
			case Foe_KGOBLIN:
				foeFilePath = "Assets/kgoblin.bmp";
				break;
			case Foe_SPIKE:
				foeFilePath = "Assets/spike.bmp";
				break;
			}

			Foe* newFoe = new Foe;
			newFoe->Initailize(pRenderer, foeFilePath);
			newFoe->SetFoeIndex(i);
			SpriteList.push_back(newFoe);
		}

		Hero* newHero = new Hero;
		newHero->Initailize(pRenderer, "Assets/hero.bmp");
		playerState.PlayerPosition = Vector2d(4.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y);
		SpriteList.push_back(newHero);

		for (unsigned int i = 0; i < playerState.Projectiles.size(); i++)
		{
			std::string shotFilePath = "Assets/ball.bmp";

			Projectile* newShot = new Projectile;
			newShot->Initailize(pRenderer, shotFilePath);
			newShot->SetProjectileIndex(i);
			SpriteList.push_back(newShot);
		}

		HUD* newHUD = new HUD;
		newHUD->InitailizeInventorySprites(pRenderer, "Assets/book.bmp", "Assets/sbook.bmp", "Assets/hero.bmp", "Assets/lose.bmp", "Assets/win.bmp");
		SpriteList.push_back(newHUD);
	}
	
	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				playerState.HasFinishedGame = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_ESCAPE:
					playerState.HasFinishedGame = true;
					break;

				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUp = true;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					playerState.WantsToGoDown = true;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = true;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = true;
					break;

				case SDLK_SPACE:
					playerState.WantsToShoot = true;
					break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUp = false;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					playerState.WantsToGoDown = false;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = false;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = false;
					break;

				case SDLK_SPACE:
					playerState.WantsToShoot = false;
					break;
				}
			}
		}
	}
	
	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
	{
		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Update(deltaSeconds, playerState, worldState);
		}
		if (playerState.PlayerHP <= 0)
		{
			worldState.SecondsAfterDefeat += deltaSeconds;

			if (worldState.SecondsAfterDefeat > 0.6f)
			{
				playerState.HasFinishedGame = true;
			}
		}
		if (playerState.PlayerHP > 0)
		{
			if (worldState.DefeatedFoes >= worldState.TotalFoes)
			{
				worldState.SecondsAfterDefeat += deltaSeconds;

				if (worldState.SecondsAfterDefeat > 0.6f)
				{
					playerState.HasFinishedGame = true;
				}
			}
		}
	}
	
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{
		SDL_RenderClear(pRenderer);

		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Render(pRenderer, playerState, worldState, Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - worldState.CameraPosition);
		}

		SDL_RenderPresent(pRenderer);
	}
	
	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		for (unsigned int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList[i]->Cleanup();
			delete SpriteList[i];
		}
		SpriteList.clear();

		Sprite::CleanupTextures();
	}
}