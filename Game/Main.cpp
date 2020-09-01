#include "pch.h"
#include "Graphics/Texture.h"
#include "Math/Vector2.h"
#include "Engine.h"
#include "Object/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Core/JSON.h"
#include "Core/Factory.h"
#include "Object/ObjectFactory.h"
#include "Object/Scene.h"
#include "TileMap.h"
nc::Engine engine;
nc::Scene scene;

int main(int, char**)
{
	engine.Startup();
	
	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
	nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object>);

	scene.Create(&engine);

	//new stuff
	rapidjson::Document document;
	nc::json::Load("Scene.txt", document);
	scene.Read(document);

	nc::TileMap tileMap;
	nc::json::Load("tileMap.txt", document);
	tileMap.Read(document);
	tileMap.Create(&scene);
	/*for (size_t i = 0; i < 10; i++)
	{
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoBox");
		gameObject->m_transform.position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		gameObject->m_transform.angle = nc::random(0,360);
		scene.AddGameObject(gameObject);
	}*/
	
	//for (size_t i = 0; i < 10; i++)
	//{
	//	nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
	//	gameObject->m_transform.position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
	//	scene.AddGameObject(gameObject);
	//}

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		engine.Update();
		scene.Update();
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::buttonState::PRESSED)
		{
			quit = true;
		}

		engine.GetSystem<nc::Renderer>()->Begin();
		scene.Draw();

		engine.GetSystem<nc::Renderer>()->End();
	}
	scene.Destroy();
	engine.Shutdown();
	return 0;
}