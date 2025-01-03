#pragma once

// Entity/scene node category used to dispatch commands
namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		PlayerEntity = 1 << 1,
		AlliedEntity = 1 << 2,
		EnemyEntity = 1 << 3,
	};
}