#include "pch.h"
#include "RigidBodyComponent.h"
#include "Physics/PhysicsSystem.h"

bool nc::RigidBodyComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	m_drag = 0.95f;
	return true;
}

void nc::RigidBodyComponent::Destroy()
{
	m_owner->m_engine->GetSystem<PhysicsSystem>()->DestroyBody(m_body);
}

void nc::RigidBodyComponent::Update()
{
	if (m_body == nullptr)
	{
		m_body = m_owner->m_engine->GetSystem<PhysicsSystem>()->CreateBody(m_owner->m_transform.position, m_owner->m_transform.angle, m_data, m_owner);
		m_body->SetGravityScale(m_data.GravityScale);
		m_body->SetLinearDamping(1.0f);
	}
	m_owner->m_transform.position = PhysicsSystem::WorldToScreen(m_body->GetPosition());
	m_owner->m_transform.angle = nc::RadiansToDegrees(m_body->GetAngle());

	m_velocity = m_body->GetLinearVelocity();
	m_velocity.x = nc::Clamp(m_velocity.x, -5.0f, 5.0f);
	m_body->SetLinearVelocity(m_velocity);
}

void nc::RigidBodyComponent::Read(const rapidjson::Value& value)
{
	nc::json::Get(value, "isDynamic", m_data.isDynamic);
	nc::json::Get(value, "IsSensor", m_data.isSensor);
	nc::json::Get(value, "lockAngle", m_data.lockAngle);
	nc::json::Get(value, "size", m_data.size);
	nc::json::Get(value, "density", m_data.density);
	nc::json::Get(value, "friction", m_data.friction);
	nc::json::Get(value, "restitution", m_data.restitution);
	nc::json::Get(value, "GravityScale", m_data.GravityScale);
}

void nc::RigidBodyComponent::ApplyForce(const Vector2& force)
{
	if (m_body)
	{
	m_body->ApplyForceToCenter(force, true);
	}
	
}
