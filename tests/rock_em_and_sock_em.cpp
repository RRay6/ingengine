#include "rock_em_and_sock_em.h"

#include "../src/Components/sprite.h"
#include "../src/Components/foo.h"

namespace rock_em_and_sock_em {

bool start = true, up = true;
int count = 0;
int spr_num1, spr_num2, spr_num3, spr_num4, spr_num5, spr_num6, spr_num7, spr_num8, height_start;
int inp_key = -1;
int red = 0;
int blue = 0;
bool back_red  = false, forward_red = false, back_blue = false, forward_blue = false;
int prev_pos_red, prev_pos_blue;
bool game_over = false, damage_taken = false;

float red_health = 100.0, blue_health = 100.0, damage = 20.0;

void rock_em_and_sock_em::RockEmAndSockEm::Init()
{

    // ecs::EntityID a(entity_manager.Create());
    //ecs::EntityID b(entity_manager.Create());

    // ecs::EntityID a = entity_manager.Create();
    // ecs::EntityID b = entity_manager.Create();

    // ecs::EntityID a(1);
    // ecs::EntityID b(2);

    //a.Get<Sprite>().x = 16;
    //b.Get<Sprite>().x = 24;

    // entity_manager.Get<Sprite>(a.id);

    //Sprite x = entity_manager.Get<Sprite>(a.id);
    // entity_manager.Get<Sprite>(a).x = 17;
    // entity_manager.Get<Foo>(a.id) = 17;
    // entity_manager.Get<Sprite>(b) = 23;
    //Sprite y = entity_manager.Get<Sprite>(b.id);
    //entity_manager.Get<Sprite>(b.id).x = 38;
    //b.Get<Sprite>().x = 23;

    //cout << "a.Get<Sprite>(): " << a.id << " " << a.Get<Sprite>().x << '\n';
    //cout << "b.Get<Sprite>(): " << b.id << " " << b.Get<Sprite>().x << '\n';

    // cout << "a.Get<Sprite>(): " << a.id << " " << entity_manager.Get<Sprite>(a).x << '\n';
    // cout << "b.Get<Sprite>(): " << b.id << " " << entity_manager.Get<Sprite>(b).x << '\n';

    //cout << "x : " << x << '\n';
    //cout << "y : " << y << '\n';

    Sprite sprite;
    sprite.image = "black.png";
    sprite.scale = 100;
    sprite.x = 0;
    sprite.y = 0;
    sprite.z = 0;

    // vec.insert(sprite, 1);
    vec.push_back(sprite);

    // Sprite sprite2;
    // sprite2.image = "purple1.png";
    // sprite2.scale = 25;
    // sprite2.x = -75;
    // sprite2.y = 95;
    // sprite2.z = 0;

    // Sprite sprite4;
    // sprite4.image = "purple2.png";
    // sprite4.scale = 25;
    // sprite4.x = -25;
    // sprite4.y = 85;
    // sprite4.z = 0;

    int change;

    for (int i = 95; i > -55; i-=10)
    {
        if ((i - 5) % 20 == 0)
        {
            change = -25;
        }
        else
        {
            change = 0;
        }

        for (int j = -75+change; j < 175; j += 50)
        {
            int num;

            if (change == 0)
            {
                num = (vec.size() % 5) + 1;
            }
            else
            {
                num = ((vec.size() + rand())  % 5) + 1;
            }

            //cout << "Does this work?: " << num << "\n";

            string name = "purple"+to_string(num)+".png";

            while (vec.at(vec.size() - 1).image.compare(name) == 0)
            {
                num = (rand() % 5) + 1;
                name = "purple"+to_string(num)+".png";
            }

            Sprite sprite2;
            sprite2.image = "purple"+to_string(num)+".png";
            //sprite2.image = sprite2.image+".png";

            // cout << "Does this work?: " << sprite2.image << "\n";

            sprite2.scale = 25;
            sprite2.x = j;
            sprite2.y = i;
            sprite2.z = 0;

            vec.push_back(sprite2);
        }
    }

    count = vec.size() - 1;

    Sprite sprite3;
    sprite3.image = "stage.png";
    sprite3.scale = 100;
    sprite3.x = 0;
    sprite3.y = 0;
    sprite3.z = 0;

    vec.push_back(sprite3);

    Sprite sprite4; // 2 -16
    sprite4.image = "robot1_arm.png";
    sprite4.scale = 100;
    sprite4.x = -25;
    sprite4.y = 0;
    sprite4.z = 0;

    vec.push_back(sprite4);

    Sprite sprite5; // 4 - 15
    sprite5.image = "robot1_b.png";
    sprite5.scale = 100;
    sprite5.x = 27;
    sprite5.y = 0;
    sprite5.z = 0;

    vec.push_back(sprite5);

    Sprite sprite6; // 2 - 14
    sprite6.image = "robot1.png";
    sprite6.scale = 100;
    sprite6.x = -25;
    sprite6.y = 0;
    sprite6.z = 0;

    vec.push_back(sprite6);

    Sprite sprite7; // 4 - 13
    sprite7.image = "robot1_barm.png";
    sprite7.scale = 100;
    sprite7.x = 27;
    sprite7.y = 0;
    sprite7.z = 0;

    vec.push_back(sprite7);

    prev_pos_red = 16;
    prev_pos_blue = 15;

    for (int i = 2; i < 5; i++)
    {

        string name = "robot"+to_string(i)+"_arm.png";

        Sprite sprite5; // - 12 - 8 - 4
        sprite5.image = name;
        sprite5.scale = 0;
        sprite5.x = 2;
        sprite5.y = 0;
        sprite5.z = 0;

        vec.push_back(sprite5);

        name = "robot"+to_string(i)+"_b.png";

        Sprite sprite8; // - 11 - 7 - 3
        sprite8.image = name;
        sprite8.scale = 0;
        sprite8.x = 4;
        sprite8.y = 0;
        sprite8.z = 0;

        vec.push_back(sprite8); 

        name = "robot"+to_string(i)+".png";

        Sprite sprite6; // - 10 - 6 - 2
        sprite6.image = name;
        sprite6.scale = 0;
        sprite6.x = 4;
        sprite6.y = 0;
        sprite6.z = 0;

        vec.push_back(sprite6); 

        name = "robot"+to_string(i)+"_barm.png";

        Sprite sprite7; // - 9 - 5 - 1
        sprite7.image = name;
        sprite7.scale = 0;
        sprite7.x = 2;
        sprite7.y = 0;
        sprite7.z = 0;

        vec.push_back(sprite7); 

    }


    sounds.Startup();

    

    // vec = { sprite, sprite2, sprite4, sprite3 };
}

void rock_em_and_sock_em::RockEmAndSockEm::Input(int key)
{
    // cout << "Does this work?: " << key << "\n";
    inp_key = key;
}

void rock_em_and_sock_em::RockEmAndSockEm::Update()
{
    // cout << "Does this work?: \n";

    // if (right)
    // {
    //     vec[1].x = vec[1].x + 1;

    //     if (vec[1].x > 100)
    //     {
    //         right = false;
    //     }
    // }
    // else
    // {
    //     vec[1].x = vec[1].x - 1;

    //     if (vec[1].x < 1)
    //     {
    //         right = true;
    //     }
    // }

    // cout << "Does this work?: " << vec[1].x << "\n";

    if (!game_over)
    {

    if (start)
    {
        spr_num1 = (rand() % (count - 1)) + 1;
        spr_num2 = (rand() % (count - 1)) + 1;
        spr_num3 = (rand() % (count - 1)) + 1;
        spr_num4 = (rand() % (count - 1)) + 1;
        spr_num5 = (rand() % (count - 1)) + 1;
        spr_num6 = (rand() % (count - 1)) + 1;
        spr_num7 = (rand() % (count - 1)) + 1;
        spr_num8 = (rand() % (count - 1)) + 1;

        start = false;
        height_start = vec[spr_num1].y;
    }
    else
    {
        if (up)
        {
            vec[spr_num1].y = vec[spr_num1].y + 1;
            vec[spr_num2].y = vec[spr_num2].y + 1;
            vec[spr_num3].y = vec[spr_num3].y + 1;
            vec[spr_num4].y = vec[spr_num4].y + 1;
            vec[spr_num5].y = vec[spr_num5].y + 1;
            vec[spr_num6].y = vec[spr_num6].y + 1;
            vec[spr_num7].y = vec[spr_num7].y + 1;
            vec[spr_num8].y = vec[spr_num8].y + 1;

            if ((vec[spr_num1].y - height_start) > 7) // 35 - 30
            {
                up = false;
            }
        }
        else
        {
            vec[spr_num1].y = vec[spr_num1].y - 1;
            vec[spr_num2].y = vec[spr_num2].y - 1;
            vec[spr_num3].y = vec[spr_num3].y - 1;
            vec[spr_num4].y = vec[spr_num4].y - 1;
            vec[spr_num5].y = vec[spr_num5].y - 1;
            vec[spr_num6].y = vec[spr_num6].y - 1;
            vec[spr_num7].y = vec[spr_num7].y - 1;
            vec[spr_num8].y = vec[spr_num8].y - 1;

            if ((vec[spr_num1].y - height_start) < 1) 
            {
                up = true;
                start = true;
            }
        }
    }

    if (forward_red)
    {
        if (prev_pos_red != 16)
        {
            vec.at(vec.size() - (prev_pos_red)).scale = 0;
            vec.at(vec.size() - (prev_pos_red - 2)).scale = 0;
        }

        vec.at(vec.size() - 16).scale = 100;
        vec.at(vec.size() - 14).scale = 100;

        vec.at(vec.size() - 16).x = vec.at(vec.size() - 16).x + 3;
        vec.at(vec.size() - 14).x = vec.at(vec.size() - 14).x + 3;

        if (vec.at(vec.size() - 16).x >= 2)
        {
            forward_red = false;
        }
    }

    if (back_red)
    {
        if (prev_pos_red != 16)
        {
            vec.at(vec.size() - (prev_pos_red)).scale = 0;
            vec.at(vec.size() - (prev_pos_red - 2)).scale = 0;
        }

        vec.at(vec.size() - 16).scale = 100;
        vec.at(vec.size() - 14).scale = 100;
        vec.at(vec.size() - 16).x = vec.at(vec.size() - 16).x - 3;
        vec.at(vec.size() - 14).x = vec.at(vec.size() - 14).x - 3;

        if (vec.at(vec.size() - 16).x <= -25)
        {
            back_red = false;
        }
    }


    if (!forward_red && !back_red)
    {

        switch(red) {
            case 0: // Defense

                //vec.at(vec.size() - 20).image = "robot1_arm.png";
                //vec.at(vec.size() - 18).image = "robot1.png";

                prev_pos_red = 16;

                if (inp_key == 68) // D
                {
                    forward_red = true;
                    red = 1;
                }
                break;
            case 1: // Fighting waiting

                prev_pos_red = 16;

                if (inp_key == 68) // D
                {
                    red = 2;
                }
                else if (inp_key == 87) // W
                {
                    red = 4;
                }
                else if (inp_key == 65) // A
                {
                    back_red= true;
                    red = 0;
                }
                else if (inp_key == 83) // S
                {
                    red = 3;
                }
                break;
            case 2: // right

                vec.at(vec.size() - (prev_pos_red)).scale = 0;
                vec.at(vec.size() - (prev_pos_red - 2)).scale = 0;

                vec.at(vec.size() - (12)).scale = 100;
                vec.at(vec.size() - (10)).scale = 100;

                prev_pos_red = 12;

                //vec.at(vec.size() - 4).image = "robot2_arm.png";
                //vec.at(vec.size() - 2) = sprite4;

                //vec.at(vec.size() - 20) = "robot2_arm.png";
                //vec.at(vec.size() - 18) = "robot2.png";

                if (inp_key == 87) // W
                {
                    red = 4;
                }
                else if (inp_key == 65) // A
                {
                    back_red= true;
                    red = 0;
                }
                else if (inp_key == 83) // S
                {
                    red = 3;
                }
                break;
            case 3: // down

                // vec.at(vec.size() - 4) = sprite5;
                // vec.at(vec.size() - 2) = sprite6;

                vec.at(vec.size() - (prev_pos_red)).scale = 0;
                vec.at(vec.size() - (prev_pos_red - 2)).scale = 0;

                vec.at(vec.size() - (8)).scale = 100;
                vec.at(vec.size() - (6)).scale = 100;

                prev_pos_red = 8;

                if (inp_key == 68) // D
                {
                    red = 2;
                }
                else if (inp_key == 87) // W
                {
                    red = 4;
                }
                else if (inp_key == 65) // A
                {
                    back_red= true;
                    red = 0;
                }
                break;
            case 4: // up

                // vec.at(vec.size() - 4) = sprite7;
                // vec.at(vec.size() - 2) = sprite8;

                vec.at(vec.size() - (prev_pos_red)).scale = 0;
                vec.at(vec.size() - (prev_pos_red - 2)).scale = 0;

                vec.at(vec.size() - (4)).scale = 100;
                vec.at(vec.size() - (2)).scale = 100;

                prev_pos_red = 4;

                if (inp_key == 68) // D
                {
                    red = 2;
                }
                else if (inp_key == 65) // A
                {
                    back_red= true;
                    red = 0;
                }
                else if (inp_key == 83) // S
                {
                    red = 3;
                }
                break;
            default:
                break;
        }

    }


    if (back_blue)
    {
        if (prev_pos_blue != 15)
        {
            vec.at(vec.size() - (prev_pos_blue)).scale = 0;
            vec.at(vec.size() - (prev_pos_blue - 2)).scale = 0;
        }

        vec.at(vec.size() - 15).scale = 100;
        vec.at(vec.size() - 13).scale = 100;

        vec.at(vec.size() - 15).x = vec.at(vec.size() - 15).x + 3;
        vec.at(vec.size() - 13).x = vec.at(vec.size() - 13).x + 3;

        if (vec.at(vec.size() - 15).x >= 27)
        {
            back_blue = false;
        }
    }

    if (forward_blue)
    {
        if (prev_pos_blue != 15)
        {
            vec.at(vec.size() - (prev_pos_blue)).scale = 0;
            vec.at(vec.size() - (prev_pos_blue - 2)).scale = 0;
        }

        vec.at(vec.size() - 15).scale = 100;
        vec.at(vec.size() - 13).scale = 100;
        vec.at(vec.size() - 15).x = vec.at(vec.size() - 15).x - 3;
        vec.at(vec.size() - 13).x = vec.at(vec.size() - 13).x - 3;

        if (vec.at(vec.size() - 15).x <= 4)
        {
            forward_blue = false;
        }
    }


    if (!forward_blue && !back_blue)
    {

        switch(blue) {
            case 0: // Defense

                //vec.at(vec.size() - 20).image = "robot1_arm.png";
                //vec.at(vec.size() - 18).image = "robot1.png";

                prev_pos_blue = 15;

                if (inp_key == 263) // left
                {
                    forward_blue = true;
                    blue = 1;
                }
                break;
            case 1: // Fighting waiting

                prev_pos_blue = 15;

                if (inp_key == 263) // left
                {
                    blue = 2;
                }
                else if (inp_key == 265) // up
                {
                    blue = 4;
                }
                else if (inp_key == 262) // right
                {
                    back_blue= true;
                    blue = 0;
                }
                else if (inp_key == 264) // down
                {
                    blue = 3;
                }
                break;
            case 2: // right

                vec.at(vec.size() - (prev_pos_blue)).scale = 0;
                vec.at(vec.size() - (prev_pos_blue - 2)).scale = 0;

                vec.at(vec.size() - (11)).scale = 100;
                vec.at(vec.size() - (9)).scale = 100;

                prev_pos_blue = 11;

                if (inp_key == 265) // up
                {
                    blue = 4;
                }
                else if (inp_key == 262) // right
                {
                    back_blue= true;
                    blue = 0;
                }
                else if (inp_key == 264) // down
                {
                    blue = 3;
                }
                break;
            case 3: // down

                vec.at(vec.size() - (prev_pos_blue)).scale = 0;
                vec.at(vec.size() - (prev_pos_blue - 2)).scale = 0;

                vec.at(vec.size() - (7)).scale = 100;
                vec.at(vec.size() - (5)).scale = 100;

                prev_pos_blue = 7;

                if (inp_key == 263) // left
                {
                    blue = 2;
                }
                else if (inp_key == 265) // up
                {
                    blue = 4;
                }
                else if (inp_key == 262) // right
                {
                    back_blue= true;
                    blue = 0;
                }
                break;
            case 4: // up

                vec.at(vec.size() - (prev_pos_blue)).scale = 0;
                vec.at(vec.size() - (prev_pos_blue - 2)).scale = 0;

                vec.at(vec.size() - (3)).scale = 100;
                vec.at(vec.size() - (1)).scale = 100;

                prev_pos_blue = 3;

                if (inp_key == 263) // left
                {
                    blue = 2;
                }
                else if (inp_key == 262) // right
                {
                    back_blue= true;
                    blue = 0;
                }
                else if (inp_key == 264) // down
                {
                    blue = 3;
                }
                break;
            default:
                break;
        }

    }

    if (inp_key != -1)
    {
        damage_taken = true;
    }

    if ((red == 2 && blue == 3 
    || red == 3 && blue == 4
    || red == 4 && blue == 2) && damage_taken)
    {
        blue_health = blue_health - damage;
        damage_taken = false;
    }
    else if ((red == 3 && blue == 2
    || red == 4 && blue == 3
    || red == 2 && blue == 4) && damage_taken)
    {
        red_health = red_health - damage;
        damage_taken = false;
    }

    if (blue_health < 0)
    {
        game_over = true;
        cout << "Red wins!\n";
        PlaySound();
    }

    if (red_health < 0)
    {
        game_over = true;
        cout << "Blue wins!\n";
        PlaySound();
    }

    }

}

void rock_em_and_sock_em::RockEmAndSockEm::PlaySound()
{
    string path_string = resources.ResolvePath("sounds", "bell.wav").u8string();
    sounds.LoadSound("bell.wav", path_string);
}

}