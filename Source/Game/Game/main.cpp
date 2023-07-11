#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Core/Model.h"
#include "Input/InputSystem.h"
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

using vec2 = kiko::Vector2;

class Star
{
public:
    Star(const vec2 pos, const vec2& vel) :
        m_pos{ pos },
        m_vel{ vel } {}

    void Update(int width, int height)
    {
        m_pos += m_vel * kiko::g_time.GetDeltaTime();
        if (m_pos.x >= width) m_pos.x = 0;
        if (m_pos.y >= height) m_pos.y = 0;
    }


    void Draw(kiko::Renderer& renderer) 
    {
        renderer.DrawPoint(m_pos.x, m_pos.y);
    }

public:
    vec2 m_pos;
    vec2 m_vel;

};



///////////

int main(int argc, char* argv[])
{
    kiko::seedRandom((unsigned int)time(nullptr));
    kiko::setFilePath("assets");
    cout << kiko::getFilePath() << endl;
 
    kiko::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("CSC196", 800, 600);
    
    kiko::InputSystem inputSystem;
    inputSystem.Initialize();

    //std::vector<kiko::vec2> points { { -20, 5 }, { 10, 5 }, { 0, -5 }, { 10, -5 } }; makes shapes n stuff
    kiko::Model model;
    model.Load("ship.txt");

    kiko::vec2 v{ 5, 5 };
    v.Normalize();
    
    vector<Star> stars;
    for (int i = 0; i < 1000; i++)
    {
        vec2 pos(vec2(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight())));
        vec2 vel(kiko::randomf(1, 4), 0.0f);

        stars.push_back(Star(pos, vel));
        

    }


    int r = kiko::random(256);
    int g = kiko::random(256);
    int b = kiko::random(256);

    kiko::vec2 position{ 400, 300 };
    float speed = 200;


    bool quit = false;


    while (!quit)
    {
        kiko::g_time.Tick();
        inputSystem.Update();

        inputSystem.Update();
        if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
        {
            quit = true;
        }

        

        //mouse press: 0 -> L  1 -> Middle  2  -> right 


    kiko:vec2 direction;
        if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
        if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
        if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
        if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
        position += direction * speed * kiko::g_time.GetDeltaTime();

        if (inputSystem.GetMouseButtonDown(0)) cout << "Left" ;
        if (inputSystem.GetMouseButtonDown(1)) cout << "Middle" ;
        if (inputSystem.GetMouseButtonDown(2)) cout << "Right";

        renderer.SetColor(0, 0, 0, 0);
        renderer.BeginFrame();


        r = kiko::random(256);  //this got restated and is randomizing all the colors each
        g = kiko::random(256);
        b = kiko::random(256);

        //renderer.DrawLine(1, 1, 100, 100);
        //renderer.BeginFrame();
        // draw
        kiko::Vector2 vel(1.0f, 0.3f);
        renderer.SetColor(r, g, b, 1);


        
        //for (auto star : stars) 
        //{
        //    star.Update(renderer.GetWidth(), renderer.GetHeight());

        //    

        //    r = kiko::random(256);
        //    g = kiko::random(256);
        //    b = kiko::random(256);
        //    renderer.SetColor(r, g, b, 255);
        //   

        //    
        //}
        model.Draw(renderer, position, 5);

       /* for (int i = 0; i < 10000; i++) {

            kiko::Vector2 pos(kiko::renderer.getWidth()), kiko::renderer.getLength());

            r = kiko::random(256);
            g = kiko::random(256);
            b = kiko::random(256);
            renderer.SetColor(r, g, b, 1);
            renderer.DrawLine(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()), kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));

        
        }*/
        renderer.EndFrame();

        this_thread::sleep_for(chrono::milliseconds(10));
    }
    return 0;
}