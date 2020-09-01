#include "PlayerComponent.h"
#include "pch.h"
#include "Core/EventManager.h"
#include "Components/SpriteComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponent::CollisionEnter, this, std::placeholders::_1), m_owner);
	EventManager::Instance().Subscribe("CollisionExit", std::bind(&PlayerComponent::CollisionExit, this, std::placeholders::_1), m_owner);
	
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
		force.y = -1900;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		audioComponent->SetSoundName("JORA.wav");
		audioComponent->Play();
	}

	/*if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::buttonState::HELD)
	{
		force = nc::Vector2::forward * 1000;
	}*/
	//force = nc::Vector2::Rotatate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

	RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
	if (component)
	{
		component->ApplyForce(force);
		Vector2 velocity = component->GetVelocity();

		SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
		if (velocity.x <= -0.5) spriteComponent->Flip();
		if (velocity.x >= 0.5) spriteComponent->Flip(false);
	}

	/*auto coinContacts = m_owner->GetContactsWithTag("PickUp");
	for (GameObject* contact : coinContacts)
	{
		contact->m_flags[GameObject::eFlags::DESTROY] = true;
	}*/
}

void nc::PlayerComponent::CollisionEnter(const Event& event)
{
	GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

	if (gameObject->m_tag == "Enemy")
	{
		gameObject->m_flags[GameObject::eFlags::DESTROY] = true;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		audioComponent->SetSoundName("TheHand.wav");
		audioComponent->Play();
	}

	if (gameObject->m_tag == "PickUp")
	{
		gameObject->m_flags[GameObject::eFlags::DESTROY] = true;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		audioComponent->SetSoundName("Doshyan.wav");
		audioComponent->Play();
	}

	std::cout << "CollisionEnter: " << gameObject->m_name << std::endl;
}

void nc::PlayerComponent::CollisionExit(const Event& event)
{
	GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

	std::cout << "CollisionExit: " << gameObject->m_name << std::endl;
}
