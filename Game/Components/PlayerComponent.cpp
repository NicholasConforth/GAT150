#include "PlayerComponent.h"
#include "pch.h"
#include "Components\RigidBodyComponent.h"
#include "Components/AudioComponent.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	return true;
}

void nc::PlayerComponent::Destroy()
{
}

void nc::PlayerComponent::Update()
{
	auto contacts = m_owner->GetContactsWithTag("Floor");
	bool onGround = !contacts.empty();

	nc::Vector2 force{ 0,0 };
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::buttonState::HELD)
	{
		//m_owner->m_transform.angle -= 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		force.x = -200;
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::buttonState::HELD)
	{
		//m_owner->m_transform.angle += 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		force.x = 200;
	}

	if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::buttonState::PRESSED)
	{
		//m_owner->m_transform.angle += 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		force.y = -1500;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		if (audioComponent)
		{
			audioComponent->Play();
		}
	}

	/*if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::buttonState::HELD)
	{
		force = nc::Vector2::forward * 1000;
	}*/
	//force = nc::Vector2::Rotatate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

	RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
	if (component)
	{
		component->SetForce(force);
	}

	auto coinContacts = m_owner->GetContactsWithTag("PickUp");
	for (GameObject* contact : coinContacts)
	{
		contact->m_flags[GameObject::eFlags::DESTROY] = true;
	}
}
