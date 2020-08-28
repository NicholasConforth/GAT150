#pragma once
#include "Object/Object.h"
#include "Engine.h"
#include "Math/Transform.h"
#include "ObjectFactory.h"
#include <list>
#include <vector>
#include <bitset>

namespace nc
{
	class Component;

	class GameObject : public Object
	{
	public:
		enum eFlags
		{
			ACTIVE,
			VISIBLE,
			DESTROY,
			TRANSIENT
		};
	public:
		GameObject() = default;
		GameObject(const GameObject& other);
		// Inherited via Object
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new GameObject{ *this }; }

		virtual void Read(const rapidjson::Value& value) override;

		void Update();
		void Draw();

		void BeginContact(GameObject* other);
		void EndContact(GameObject* other);
		std::vector<GameObject*> GetContactsWithTag(const std::string& tag);

		template<typename T>
		T* GetComponent()
		{
			T* result{ nullptr };
			for (auto component : m_components)
			{
				result = dynamic_cast<T*>(component);
				if (result) break;
			}
			return result;
		}

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponent();

		friend class Component;
		friend class PhysicsComponent;

		void ReadComponents(const rapidjson::Value& value);

	public:
		std::string m_name;
		std::string m_tag;
		std::bitset<32> m_flags;
		float m_lifetime{ 0 };
		Transform m_transform;
		Engine* m_engine{ nullptr };
	protected:
		std::vector<Component*> m_components;
		std::list<GameObject*> m_contacts;
	};
}