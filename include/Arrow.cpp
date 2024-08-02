using namespace std;

Arrow::Arrow(int arrowID1, int playerID1, int color1, bool isWalled1, float x1, float y1, float vel_x1, float vel_y1){
    arrowID=arrowID1;
    playerID=playerID1;
    color=color1;
    isWalled=isWalled1;
    x=x1;
    y=y1;
    vel_x=vel_x1;
    vel_y=vel_y1;
}

Arrow::Arrow(SDL_Renderer *r, SDL_FRect playerHitbox, int aimingAngle, int ID, int nID) {
    angle=aimingAngle;
    playerID=ID;
    arrowID=nID;
    color=playerID;

    if (aimingAngle==0){
        vel_y = -(SPEED*2.8);
    }
    else if (aimingAngle==45 || aimingAngle==315){
        vel_y=-(SPEED)*2;//vel_y = -(SPEED*1.7);

    }
    else if (aimingAngle==135 || aimingAngle==225){
        vel_y = (SPEED*2);
    }
    else if (aimingAngle==90 || aimingAngle==270){
        vel_y=0;
    }
    else if (aimingAngle==180){
        vel_y = SPEED*2.8;
    }
    
    
    if (aimingAngle==225 || aimingAngle==315){
        vel_x = -SPEED*2;
    }
    else if (aimingAngle==45 || aimingAngle==135){
        vel_x = SPEED*2;//vel_x = SPEED*1.7;
    }
    else if (aimingAngle==0 || aimingAngle==180){
        vel_x=0;
    }
    else if (aimingAngle==90){
        vel_x=SPEED*2.8;
    }
    else if (aimingAngle==270){
        vel_x=-SPEED*2.8;
    }

    distance=0;
    isWalled=false;

    hitbox.w=3;
    hitbox.h=3;
    
    x = playerHitbox.x+playerHitbox.w/2-hitbox.w/2;
    y = playerHitbox.y+playerHitbox.h/2-hitbox.h/2;
    
    hitbox.x=x;
    hitbox.y=y;
}

void Arrow::Draw(SDL_Renderer *r) {
    SDL_FRect rect1;
    rect1.x = x-4.5;
    rect1.y = y+1;
    rect1.w = 11;
    rect1.h = 28;

    SDL_FRect rect2;
    rect2.x = hitbox2.x-4.5;
    rect2.y = hitbox2.y+1;
    rect2.w = 11;
    rect2.h = 28;

    //SDL_RenderCopyF(r, blue, NULL, &hitbox);
    
    SDL_FPoint centerPoint;
    centerPoint.x = 5.5;
    centerPoint.y = 0;
    
    currentangle = fmod(atan2(vel_y, vel_x) * (180.0 / M_PI) + 90, 360.0);

    if (color==1){
        SDL_RenderCopyExF(r, arrowred, NULL, &rect1, currentangle, &centerPoint, SDL_FLIP_NONE);
        if (throughWall) SDL_RenderCopyExF(r, arrowred, NULL, &rect2, currentangle, &centerPoint, SDL_FLIP_NONE);
    }
    else if (color==2){
        SDL_RenderCopyExF(r, arrowgreen, NULL, &rect1, currentangle, &centerPoint, SDL_FLIP_NONE);
        if (throughWall) SDL_RenderCopyExF(r, arrowgreen, NULL, &rect2, currentangle, &centerPoint, SDL_FLIP_NONE);
    }
    else if (color==3){
        SDL_RenderCopyExF(r, arrowblue, NULL, &rect1, currentangle, &centerPoint, SDL_FLIP_NONE);
        if (throughWall) SDL_RenderCopyExF(r, arrowblue, NULL, &rect2, currentangle, &centerPoint, SDL_FLIP_NONE);
    }
    else if (color==4){
        SDL_RenderCopyExF(r, arroworange, NULL, &rect1, currentangle, &centerPoint, SDL_FLIP_NONE);
        if (throughWall) SDL_RenderCopyExF(r, arroworange, NULL, &rect2, currentangle, &centerPoint, SDL_FLIP_NONE);
    }

    
    //SDL_SetRenderDrawColor(r, 234, 123, 64, 255);
    //SDL_RenderFillRectF(r, &temp);
}

void Arrow::Movement(float dt){
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

        if ((angle==0 && vel_y>0) || (angle==180 && distance>150)){
            playerID=0;
        }
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
}

bool Arrow::CollectArrow(SDL_Renderer *r, SDL_FRect a, SDL_FRect b){
    SDL_FRect temp;
    temp=b;
    
    temp.x+=-cos(((currentangle-90)/180.)*3.14)*14;
    temp.y+=-sin(((currentangle-90)/180.)*3.14)*14;

    temp.x-=5;
    temp.y-=5;
    temp.w+=10;
    temp.h+=10;


    /*SDL_FRect temp;
    temp=b;
    temp.x-=20;
    temp.y-=20;
    temp.w+=40;
    temp.h+=40;*/

    return Collision(a, temp);
}


void Arrow::MoveThroughWall() {
    if (hitbox.x < 0) {
        throughWall = true;
        hitbox2.x = WIDTH + hitbox.x;
        hitbox2.y = hitbox.y;
    } else if (hitbox.x + hitbox.w - 1>WIDTH){
        throughWall = true;
        hitbox2.x = hitbox.x - WIDTH;
        hitbox2.y = hitbox.y;
    }
    else if (hitbox.y < 0) {
        throughWall = true;
        hitbox2.x = hitbox.x;
        hitbox2.y = HEIGHT + hitbox.y;
    } 
    else if (hitbox.y + hitbox.h - 1 > HEIGHT){
        throughWall = true;
        hitbox2.x = hitbox.x;
        hitbox2.y = hitbox.y - HEIGHT;
    }
    else {
        throughWall = false;
    }

    if ((hitbox.x < -(hitbox.w)) || (hitbox.x > WIDTH) || (hitbox.y < -(hitbox.h)) ||(hitbox.y>HEIGHT)) {
        x = hitbox2.x;
        y = hitbox2.y;
        hitbox.x = hitbox2.x;
        hitbox.y = hitbox2.y;
        throughWall = false;
    }

    //cout << x << " " << y << endl;
}