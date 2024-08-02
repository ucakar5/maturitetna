using namespace std;
Chest::Chest(float x1, float y1, bool open1, int item1){
    x=x1;
    y=y1;
    open=open1;
    item=item1;
}

Chest::Chest(SDL_Renderer *r, float nx, float ny){
    //x=416;//408
    //y=224;//218
    x=nx;
    y=ny;
    vel_x=0;
    vel_y=0;

    hitbox.x = x;
    hitbox.y = y+6;
    hitbox.w = 32;
    hitbox.h = 26;

    

    open=false;
    
    int randnum = rand()%100;
    //cout << randnum << endl;
    /*if (randnum>=0 && randnum<=78) item=1; //puscica
    else if (randnum>78 && randnum<=92) item=2; //shield
    else if (randnum>92 && randnum<100) item=3; //krila*/
    if (randnum>=0 && randnum<=33) item=1; //puscica
    else if (randnum>33 && randnum<=66) item=2; //shield
    else if (randnum>66 && randnum<100) item=3; //krila
    
}

void Chest::Draw(SDL_Renderer *r) {
    SDL_Rect rect1;
    
    rect1.y = 0;
    rect1.w = 10;
    rect1.h = 10;

    SDL_FRect rect2;
    rect2.x = x;
    rect2.y = y;
    rect2.w = 32;
    rect2.h = 32;

    if (item==1){
        ogitemhitbox.x = 0;
        ogitemhitbox.y = 0;
        ogitemhitbox.w = 10;
        ogitemhitbox.h = 10;

        itemhitbox.x = x+2;
        itemhitbox.y = y-80;
        itemhitbox.w = 30;
        itemhitbox.h = 30;
    }
    else if (item==2){
        ogitemhitbox.x = 0;
        ogitemhitbox.y = 0;
        ogitemhitbox.w = 36;
        ogitemhitbox.h = 36;

        itemhitbox.x = x-5;
        itemhitbox.y = y-80;
        itemhitbox.w = 40;
        itemhitbox.h = 40;
    }
    else if (item==3){
        ogitemhitbox.x = 0;
        ogitemhitbox.y = 0;
        ogitemhitbox.w = 20;
        ogitemhitbox.h = 20;
        
        itemhitbox.x = x-5;
        itemhitbox.y = y-80;
        itemhitbox.w = 40;
        itemhitbox.h = 40;
    }
    

    //SDL_RenderCopyF(r, blue, NULL, &hitbox);

    if (!open){
        rect1.x = 0;
    }
    else rect1.x = 30;
    SDL_RenderCopyF(r, chest, &rect1, &rect2);
    
    if (open) {
        //cout << item << endl;
        if (item==1) SDL_RenderCopyF(r, arrowitem, &ogitemhitbox, &itemhitbox);
        else if (item==2) SDL_RenderCopyF(r, shield, &ogitemhitbox, &itemhitbox);
        else if (item==3) SDL_RenderCopyF(r, wings, &ogitemhitbox, &itemhitbox);
    }

}
/*
void Chest::Movement(float dt){
    if (!isWalled){
        if (angle==0){
            if (distance>300 && distance<700){
                vel_y += SPEED * 7 * dt;
            }
            
        }
        else if (angle==45 || angle==135 || angle==225 || angle==315){
            if (distance>160 && distance<600){
                vel_y += SPEED * 6 * dt;
            }
            if (distance>240){
                if (angle==45 || angle==135) vel_x -= SPEED * 1.5 * dt;
                else vel_x += SPEED * 1.5 * dt;
            }
        }
        else if (angle==90 || angle==270){
            if (distance>280){
                vel_y += SPEED * 6 * dt;
            }
        }

        if (angle==0 && vel_y>SPEED*3.1)vel_y = SPEED*3.1;
        else if (vel_y>SPEED*2.8)vel_y = SPEED*2.8;
        
        if (angle==90 || angle==270) distance+=abs(vel_x * dt);
        else distance+=abs(vel_y * dt);

        x += vel_x * dt;
        y += vel_y * dt;
        hitbox.x = x;
        hitbox.y = y;

        //cout << distance << endl;
    }
}

void Arrow::Collisions(int grid[32][24], float dt){
     for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 24; j++) {
            if (grid[i][j] != 0) {
                SDL_FRect rect;
                rect.x = i * GRIDSIZE;
                rect.y = j * GRIDSIZE;
                rect.w = GRIDSIZE;
                rect.h = GRIDSIZE;
                if (Collision(hitbox, rect)) {
                    isWalled=true;
                    return;
                }
            }
        }
    }
}*/