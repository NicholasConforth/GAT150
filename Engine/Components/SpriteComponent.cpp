#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

bool nc::SpriteComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	return true;
}

void nc::SpriteComponent::Destroy()
{
	
}

void nc::SpriteComponent::Read(const rapidjson::Value& value)
{
	nc::json::Get(value, "texture", m_textureName);
	nc::json::Get(value, "origin", m_origin);
	nc::json::Get(value, "rect", m_rect);
}

void nc::SpriteComponent::Update()
{
}

void nc::SpriteComponent::Draw()
{
	//{ 128, 120, 48, 98 }
	Texture* texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<Renderer>());
	texture->Draw(m_rect, m_owner->m_transform.position, m_owner->m_transform.angle, nc::Vector2{ 1, 1 } * m_owner->m_transform.scale, m_origin);
}
