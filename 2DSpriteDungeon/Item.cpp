#include "Item.h"

using namespace DungeonGame;

void Item::SetItemIndex(int newIndex)
{
	ItemIndex = newIndex;
}

void Item::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	ItemData& currItem = worldState.Items[ItemIndex];

	Vector2d vecToPlayer = currItem.Position - playerState.PlayerPosition;
	if (currItem.Active) 
	{
		if (vecToPlayer.GetLength() < 30.0f)                                           //Modify for Sprite image width
		{
			currItem.Active = false;

			playerState.Inventory.push_back(currItem.Type);
		}
		vecToPlayer.Normalize();
	}

	Position = currItem.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);          //Modify sprite centering
	Visable = currItem.Active;
}