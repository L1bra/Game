#include "magic.h"


PlayerMagic::PlayerMagic(const TextureHolder& textures)
	:
	m_sprite(textures.get(Textures::MAGIC0)),
	m_type(Magic0)
{
	//sf::FloatRect bounds = m_sprite.getLocalBounds();
	//m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

PlayerMagic::~PlayerMagic()
{
}

void PlayerMagic::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

unsigned int PlayerMagic::get_category() const
{
	switch (m_type)
	{
		case Magic0:	return Category::PlayerEntity;
		case Magic1:	return Category::AlliedEntity;
		case Magic2:	return Category::AlliedEntity;
		default:		return Category::EnemyEntity;
	}
}