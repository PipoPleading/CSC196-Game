#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"

#include "Input/InputSystem.h"
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

using namespace kiko;//vec2 = kiko::Vector2;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;

};


int main(int argc, char* argv[])
{
	//auto m1 = kiko::Max(4.0f, 3.0f); // auto good for a "for each" loop
	//auto m2 = kiko::Max(4, 3);
	//constexpr float a = kiko::DegreesToRadians(180.0f); // does at compile time

	kiko::seed_random((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	//kiko::Renderer renderer;
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	//kiko::InputSystem inputSystem; // replaced down below
	kiko::g_inputSystem.Initialize();

	//std::vector<kiko::vec2> points{ {-10, 5}, {10, 5}, {0, -5}, { -10, 5 } }; //vector of points that expect kiko::vec2
	//kiko::Model model(points); //Will take points and model them

	g_audioSystem.AddAudio("hit", "piphit.wav");

	kiko::Model model;
	model.Load("ship.txt");

	kiko::vec2 v{5, 5};
	v.Normalize();


	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kiko::Vector2 pos(Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(randomf(100, 1000), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	kiko::vec2 position { 400, 300 };
	kiko::Transform transform{ { 400, 300 }, 0, 3};
	
	float speed = 350;
	constexpr float turnRate = kiko::DegreesToRadians(180.0f); //? //cast to fix

	Player player{ 200, kiko::Pi, { {400, 300 }, 0, 6 }, model };

	std::vector<Enemy> enemies;
	for (int i = 0; i < 50; i++)
	{
		Enemy enemy{ 300, kiko::Pi, { {kiko::random(800), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 3}, model };
		enemies.push_back(enemy);
	}

	//Resource  Manager?
	int r = kiko::random(256);
	int g = kiko::random(256);
	int b = kiko::random(256);

	//main game loop
	bool quit = false;
	while (!quit) 
	{
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && (!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)))
		{
			g_audioSystem.PlayOneShot("hit");
		}

		g_audioSystem.Update();


		//update game
		player.Update(kiko::g_time.GetDeltaTime());
		for (auto& enemy : enemies) enemy.Update(kiko::g_time.GetDeltaTime());

		kiko::vec2 direction;

		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		if (kiko::g_inputSystem.GetMouseButtonDown(0) || kiko::g_inputSystem.GetMouseButtonDown(1) || kiko::g_inputSystem.GetMouseButtonDown(2))
		{
			cout << "mouse pressed" << endl;
			cout << "mouse located at: " << kiko::g_inputSystem.GetMousePosition().x << "," << kiko::g_inputSystem.GetMousePosition().y << endl;
		}

		position += direction * speed * g_time.GetDeltaTime();


		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		r = kiko::random(256);  //this got restated and is randomizing all the colors each
		g = kiko::random(256);
		b = kiko::random(256);

		//draw
		kiko::Vector2 vel(1.0f, 0.3f);

		

		for (auto& star : stars) {
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);

			star.Draw(kiko::g_renderer);
		}

		player.Draw(kiko::g_renderer);

		for (auto& enemy : enemies) 
		{
			enemy.Draw(kiko::g_renderer);
		}

		//model.Draw(renderer, transform.position, transform.rotation, transform.scale);
		//model.Draw(renderer, {400,300}, 10.0f); // old
		
		kiko::g_renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100)); // Fake Lag
	}

	return 0;
}
