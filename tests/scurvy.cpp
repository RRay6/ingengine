#include "scurvy.h"

#include "../src/Components/sprite.h"
#include "../src/Components/foo.h"
#include <time.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <math.h>

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;
using std::this_thread::sleep_for;

namespace scurvy {

    int inp_key = -1;
    int vec_size = 0;
    int curr_attack = 0;
    int prev_attack = 0;
    int a = 0;

    int curr_frame = 0;

    bool r = true;
    bool forward = true;
    double t = 0;
    double radius = 10;
    bool shooting = false;

    bool moving = false;
    time_point<Clock> start;

void scurvy::Scurvy::Init()
{
    ecs::EntityID a = entity_manager.Create();

    Sprite sprite;
    sprite.image = "code.jpg";
    sprite.scale = 100;
    sprite.x = 0;
    sprite.y = 0;
    sprite.z = 0;

    vec.push_back(sprite);
    vec_size++;

    Sprite sprite2;
    sprite2.image = "black.png";
    sprite2.scale = 100;
    sprite2.x = 0;
    sprite2.y = 0;
    sprite2.z = 0;

    vec.push_back(sprite2);
    vec_size++;

    Sprite sprite4;
    sprite4.image = "ship_left.png";
    sprite4.scale = 0;
    sprite4.x = -200;
    sprite4.y = 0;
    sprite4.z = 0;

    vec.push_back(sprite4);
    vec_size++;

    Sprite sprite5;
    sprite5.image = "ship_right.png";
    sprite5.scale = 0;
    sprite5.x = 200;
    sprite5.y = 0;
    sprite5.z = 0;

    vec.push_back(sprite5);
    vec_size++;

    Sprite sprite6;
    sprite6.image = "cannonball.png";
    sprite6.scale = 0;
    sprite6.x = 0;
    sprite6.y = 0;
    sprite6.z = 0;

    vec.push_back(sprite6);
    vec_size++;

    Sprite sprite3; // 5
    sprite3.image = "sword.png";
    sprite3.scale = 100;
    sprite3.x = 125;
    sprite3.y = 20;
    sprite3.z = 0;

    vec.push_back(sprite3);
    vec_size++;

    Sprite sprite8; // 6
    sprite8.image = "sword.png";
    sprite8.scale = 100;
    sprite8.x = 225;
    sprite8.y = -20;
    sprite8.z = 0;

    vec.push_back(sprite8);
    vec_size++;

    Sprite sprite9; // 7
    sprite9.image = "sword.png";
    sprite9.scale = 100;
    sprite9.x = 325;
    sprite9.y = 20;
    sprite9.z = 0;

    vec.push_back(sprite9);
    vec_size++;
    
    for (int i = 1; i < 23; i++)
    {

        string name = "skel_"+to_string(i)+".png";

        Sprite sprite7;
        sprite7.image = name;
        sprite7.scale = 0;
        sprite7.x = 0;
        sprite7.y = 0;
        sprite7.z = 0;

        vec.push_back(sprite7);
        vec_size++;
    }

    Sprite sprite10;
    sprite10.image = "green.png";
    sprite10.scale = 2;
    sprite10.x = 0;
    sprite10.y = 0;
    sprite10.z = 0;

    vec.push_back(sprite10);
    vec_size++;

    start = Clock::now();

}

void scurvy::Scurvy::Input(int key)
{
    inp_key = key;
}

void scurvy::Scurvy::Update()
{

    if (curr_attack == 0)
    {
        srand(time(0));
        int b = true;

        while (b)
        {
            curr_attack = (rand() % 3) + 1;
            
            if (curr_attack != 0 && prev_attack != curr_attack)
            {
                prev_attack = curr_attack;
                b = false;
            }
        }
        
        srand(time(0));
        if (rand() % 2 == 0)
        {
            r = true;
        }
        else
        {
            r = false;
        }
    }

    // cout << "" << duration_cast<milliseconds>(Clock::now() - start).count() << "\n";
    if (curr_attack == 1 && duration_cast<milliseconds>(Clock::now() - start).count() > 75)
    {

        start = Clock::now();

        vec.at(1).scale = 0;
        if (curr_frame > 0)
        {
            vec.at(vec.size() - 23 + (curr_frame - 1)).scale = 0;
        }

        if (curr_frame == 22)
        {
            curr_frame = 0;
            vec.at(vec.size() - 2).scale = 0;
            vec.at(1).scale = 100;
            curr_attack = 0;
        }

        if (curr_attack != 0)
        {
            vec.at(vec.size() - 23 + curr_frame).scale = 100;
            curr_frame++;
        }
    }

    if (curr_attack == 2 && duration_cast<milliseconds>(Clock::now() - start).count() > 10)
    {

        start = Clock::now();

        if (r)
        {
            if (forward)
            {
                vec.at(3).scale = 80;

                if (vec.at(3).x > 75)
                {   
                    vec.at(3).x--;
                }
                else if (!shooting)
                {
                    shooting = true;
                    t = 0;
                    radius = 10;
                    vec.at(4).scale = 10;
                    vec.at(4).x = 20;
                    vec.at(4).y = -2;
                }

                // sprite6.x = -20;
                // sprite6.y = -2;

                if (shooting)
                {
                    vec.at(4).x = radius * cos(t) + 20;
                    vec.at(4).y = radius * sin(t) - 2;

                    t-=0.075;
                    radius+=0.5;

                    if (t <= -2 * 3.14)
                    {
                        t = 0;
                    }
                }

                if (vec.at(4).x > 200 || vec.at(4).x < -200)
                {
                    vec.at(4).scale = 0;
                    vec.at(4).x = 20;
                    vec.at(4).y = -2;

                    shooting = false;
                    forward = false;
                }
            }
            else
            {
                if (vec.at(3).x < 200)
                {   
                    vec.at(3).x++;
                }
                else
                {
                    vec.at(3).scale = 0;
                    forward = true;
                    curr_attack = 0;
                }
            }
        }
        else
        {
            if (forward)
            {
                vec.at(2).scale = 80;

                if (vec.at(2).x < -75)
                {   
                    vec.at(2).x++;
                }
                else if (!shooting)
                {
                    shooting = true;
                    t = 0;
                    radius = 10;
                    vec.at(4).scale = 10;
                    vec.at(4).x = -20;
                    vec.at(4).y = -2;
                }

                // sprite6.x = -20;
                // sprite6.y = -2;

                if (shooting)
                {
                    vec.at(4).x = radius * cos(t) - 20;
                    vec.at(4).y = radius * sin(t) - 2;

                    t+=0.075;
                    radius+=0.5;

                    if (t >= 2 * 3.14)
                    {
                        t = 0;
                    }
                }

                if (vec.at(4).x > 200 || vec.at(4).x < -200)
                {
                    vec.at(4).scale = 0;
                    vec.at(4).x = -20;
                    vec.at(4).y = -2;

                    shooting = false;
                    forward = false;
                }
            }
            else
            {
                if (vec.at(2).x > -200)
                {   
                    vec.at(2).x--;
                }
                else
                {
                    vec.at(2).scale = 0;
                    forward = true;
                    curr_attack = 0;
                }
            }
        }
    }

    if (curr_attack == 3 && duration_cast<milliseconds>(Clock::now() - start).count() > 25)
    {

        start = Clock::now();

        if (!moving)
        {
            vec.at(5).x = 125;
            vec.at(5).y = 20;

            vec.at(6).x = 225;
            vec.at(6).y = -20;

            vec.at(7).x = 325;
            vec.at(7).y = 20;

            moving = true;
        }
        else if (vec.at(5).x > -350)
        {   
            vec.at(5).x--;
            vec.at(6).x--;
            vec.at(7).x--;
        }
        else
        {
            moving = false;
            curr_attack = 0;
        }
    }

    if (inp_key == 263) // left
    {
        vec.at(vec.size() - 1).x-= 10;
    }
    else if (inp_key == 264) // up
    {
        vec.at(vec.size() - 1).y-=10;
    }
    else if (inp_key == 262) // right
    {
        vec.at(vec.size() - 1).x+=10;
    }
    else if (inp_key == 265) // down
    {
        vec.at(vec.size() - 1).y+=10;
    }

}

void scurvy::Scurvy::PlaySound()
{

}

}