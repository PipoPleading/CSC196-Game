#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include <iostream>
#include <vector>

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
        m_pos += m_vel;
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

 
    kiko::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("CSC196", 800, 600);
    
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
    while (true)
    {
        renderer.SetColor(0, 0, 0, 0);
        renderer.BeginFrame();
        renderer.DrawLine(1, 1, 100, 100);
        //renderer.BeginFrame();
        // draw
        kiko::Vector2 vel(1.0f, 0.3f);


        for (auto star : stars) 
        {
            star.Update(renderer.GetWidth(), renderer.GetHeight());

            

            r = kiko::random(256);
            g = kiko::random(256);
            b = kiko::random(256);
            renderer.SetColor(r, g, b, 255);
            star.Draw(renderer);


        }

       /* for (int i = 0; i < 10000; i++) {

            kiko::Vector2 pos(kiko::renderer.getWidth()), kiko::renderer.getLength());

            r = kiko::random(256);
            g = kiko::random(256);
            b = kiko::random(256);
            renderer.SetColor(r, g, b, 1);
            renderer.DrawLine(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()), kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));

        
        }*/
        renderer.EndFrame();
    }
}