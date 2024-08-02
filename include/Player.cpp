using namespace std;

Player::Player(SDL_Renderer *r, int clientID) {
    status=1;
    playerID=clientID;
    active=0;
    dead=0;
    
    shieldOn=0;
    wingsOn=0;
    
    x = 314;
    y = 160;
    upPressed = 0;
    coyoteTime = 0;
    throughWall = 0;
    vel_x = 0;
    vel_y = 0;
    top_vel_x = SPEED;
    top_vel_y = 0;
    aiming=false;
    arrowCount=3;

    u2=0, d2=0, l2=0, r2=0;

    hitbox.x = x + 10;
    hitbox.y = y;
    hitbox.w = 28;
    hitbox.h = 48;

    hitbox2.w = hitbox.w;
    hitbox2.h = hitbox.h;

    arrow.x=0;
    arrow.y=0;
    arrow.w=24;//10
    arrow.h=60;//24

    color=0;

    playerReady=0;

    leaderCommand="nothing";

    /*
    i = 0;
    sprite_dir = 96;
    sprite_frame = 0;*/
}

void Player::Draw(SDL_Renderer *r) {
    if (!dead){
        SDL_Rect rect1;
        if (facingRight == true)
            rect1.x = 0;
        else
            rect1.x = 64; //64
        rect1.y = 0;
        rect1.w = 64; //64
        rect1.h = 64; //64

        SDL_FRect rect2;
        rect2.x = x;
        rect2.y = y;
        rect2.w = 48;
        rect2.h = 48;

        SDL_FRect arrowRect;
        arrowRect.y=hitbox.y-24;
        arrowRect.w=10;
        arrowRect.h=18;

        //SDL_RenderCopyF(r, img, &rect1, &rect2);
        SDL_FPoint centerPoint;
        centerPoint.x=arrow.w/2;
        centerPoint.y=arrow.h+hitbox.h/2-24;

        SDL_FRect arrow2;
        arrow2.w=arrow.w;
        arrow2.h=arrow.h;
        arrow2.x=hitbox2.x+hitbox2.w/2 - arrow2.w/2;
        arrow2.y=hitbox2.y-arrow2.h+24;

        SDL_FPoint centerPoint2;
        centerPoint2.x=arrow2.w/2;
        centerPoint2.y=arrow2.h+hitbox2.h/2-24;
        
        if (aiming && aimingAngle!=-1 && (STAGE=="gameplay" || STAGE=="single_gameplay")) {
            //SDL_RenderCopyExF(r, aimarrowred, NULL, &arrow, aimingAngle, &centerPoint, SDL_FLIP_NONE);
            if (color==1) {
                SDL_RenderCopyExF(r, aimarrowred, NULL, &arrow, aimingAngle, &centerPoint, SDL_FLIP_NONE);
                if (throughWall)SDL_RenderCopyExF(r, aimarrowred, NULL, &arrow2, aimingAngle, &centerPoint2, SDL_FLIP_NONE);
            }
            else if (color==2){ 
                SDL_RenderCopyExF(r, aimarrowgreen, NULL, &arrow, aimingAngle, &centerPoint, SDL_FLIP_NONE);
                if (throughWall)SDL_RenderCopyExF(r, aimarrowgreen, NULL, &arrow2, aimingAngle, &centerPoint2, SDL_FLIP_NONE);
            }
            else if (color==3){ 
                SDL_RenderCopyExF(r, aimarrowblue, NULL, &arrow, aimingAngle, &centerPoint, SDL_FLIP_NONE);
                if (throughWall)SDL_RenderCopyExF(r, aimarrowblue, NULL, &arrow2, aimingAngle, &centerPoint2, SDL_FLIP_NONE);
            }
            else if (color==4){ 
                SDL_RenderCopyExF(r, aimarroworange, NULL, &arrow, aimingAngle, &centerPoint, SDL_FLIP_NONE);
                if (throughWall)SDL_RenderCopyExF(r, aimarroworange, NULL, &arrow2, aimingAngle, &centerPoint2, SDL_FLIP_NONE);
            }
        }

        //!SDL_RenderCopyF(r, red, NULL, &hitbox);
        //!if (throughWall) SDL_RenderCopyF(r, red, NULL, &hitbox2);
        SDL_Rect ogwingsRect;
        if (u2==0) ogwingsRect.x = 0;
        else ogwingsRect.x = (wingsCounter/8)*20;
        ogwingsRect.y = 0;
        ogwingsRect.w = 20;
        ogwingsRect.h = 20;

        SDL_FRect wingsRect;
        wingsRect.x = x-6;
        wingsRect.y = y-6;
        wingsRect.w = 60;
        wingsRect.h = 60;
        
        if (wingsOn) {
            SDL_RenderCopyF(r, wings, &ogwingsRect, &wingsRect); 
            if (throughWall){
                wingsRect.x = hitbox2.x-16;
                wingsRect.y = hitbox2.y-6;
                SDL_RenderCopyF(r, wings, &ogwingsRect, &wingsRect);
            }
        }
    

        SDL_SetRenderDrawColor(r, playerColors[color][0], playerColors[color][1], playerColors[color][2], 255);
        //SDL_RenderFillRectF(r, &hitbox);
        //if (throughWall) SDL_RenderFillRectF(r, &hitbox2);
        
        SDL_Rect rect3;
        rect3.x = 0;
        rect3.y = 0;
        rect3.w = 36;
        rect3.h = 36;

        SDL_FRect rect4;
        rect4.x = x-8;
        rect4.y = y-8;
        rect4.w = 64;
        rect4.h = 64;

        
        if (shieldOn) {
            if (color==1) SDL_SetTextureColorMod(shield, 189, 0, 0);
            else if (color==2) SDL_SetTextureColorMod(shield, 0, 184, 0);
            else if (color==3) SDL_SetTextureColorMod(shield, 0, 125, 169);
            else if (color==4) SDL_SetTextureColorMod(shield, 255, 136, 16);
        
            

            
            SDL_RenderCopyF(r, shield, &rect3, &rect4); 

            if (throughWall){
                rect4.x = hitbox2.x-18;
                rect4.y = hitbox2.y-8;
                SDL_RenderCopyF(r, shield, &rect3, &rect4);
            }
        }
        //else
        SDL_SetTextureColorMod(shield, 255, 255, 255);
        
        


        arrowRect.x=hitbox.x+14-arrowCount*5;
        for (int i=0; i<arrowCount; i++){
            SDL_RenderCopyF(r, arrowicon, NULL, &arrowRect);
            arrowRect.x+=9;
        }

        if (throughWall){
            arrowRect.x=hitbox2.x+14-arrowCount*5;
            arrowRect.y=hitbox2.y-24;
            for (int i=0; i<arrowCount; i++){
                SDL_RenderCopyF(r, arrowicon, NULL, &arrowRect);
                arrowRect.x+=9;
            }
        }
        
        
        
        //SDL_RenderFillRectF(r, &arrowRect);
        

        //centerPoint.x=hitbox.x+hitbox.w/2;
        //centerPoint.y=hitbox.y+hitbox.h/2;

        
        
        
        //cout << hitbox2.x << " " << hitbox2.y << endl;

        
        
        SDL_Rect rect5;
        if (running_i>0 && running_i<100) rect5.x = 13;
        else if (running_i>=100 || running_i==0)rect5.x = 0;
        rect5.y = 0;
        rect5.w = 13;
        rect5.h = 24;

        SDL_FRect rect6;
        rect6.x = x + 6;
        rect6.y = y-10;
        rect6.w = 36;
        rect6.h = 58;

        SDL_FRect rect7;
        rect7.x = hitbox2.x - 4;
        rect7.y = hitbox2.y-10;
        rect7.w = 36;
        rect7.h = 58;

        if (color==1){
            if (hurt){
                if (hurt_i>0 && hurt_i<100) SDL_SetTextureColorMod(redplayer, 70, 0, 0);
                else if (hurt_i>=100 || hurt_i==0)SDL_SetTextureColorMod(redplayer, 255, 255, 255);
            }
            else SDL_SetTextureColorMod(redplayer, 255, 255, 255);
            
            if (facingRight) SDL_RenderCopyF(r, redplayer, &rect5, &rect6);
            else SDL_RenderCopyExF(r, redplayer, &rect5, &rect6, NULL, NULL, SDL_FLIP_HORIZONTAL);

            if (throughWall){
                if (facingRight) SDL_RenderCopyF(r, redplayer, &rect5, &rect7);
                else SDL_RenderCopyExF(r, redplayer, &rect5, &rect7, NULL, NULL, SDL_FLIP_HORIZONTAL);
            }
        }
        else if (color==2){
            if (facingRight) SDL_RenderCopyF(r, greenplayer, &rect5, &rect6);
            else SDL_RenderCopyExF(r, greenplayer, &rect5, &rect6, NULL, NULL, SDL_FLIP_HORIZONTAL);
            if (throughWall){
                if (facingRight) SDL_RenderCopyF(r, greenplayer, &rect5, &rect7);
                else SDL_RenderCopyExF(r, greenplayer, &rect5, &rect7, NULL, NULL, SDL_FLIP_HORIZONTAL);
            }
        }
        else if (color==3){
            if (facingRight) SDL_RenderCopyF(r, blueplayer, &rect5, &rect6);
            else SDL_RenderCopyExF(r, blueplayer, &rect5, &rect6, NULL, NULL, SDL_FLIP_HORIZONTAL);
            if (throughWall){
                if (facingRight) SDL_RenderCopyF(r, blueplayer, &rect5, &rect7);
                else SDL_RenderCopyExF(r, blueplayer, &rect5, &rect7, NULL, NULL, SDL_FLIP_HORIZONTAL);
            }
        }
        else if (color==4){
            if (facingRight) SDL_RenderCopyF(r, orangeplayer, &rect5, &rect6);
            else SDL_RenderCopyExF(r, orangeplayer, &rect5, &rect6, NULL, NULL, SDL_FLIP_HORIZONTAL);
            if (throughWall){
                if (facingRight) SDL_RenderCopyF(r, orangeplayer, &rect5, &rect7);
                else SDL_RenderCopyExF(r, orangeplayer, &rect5, &rect7, NULL, NULL, SDL_FLIP_HORIZONTAL);
            }
        }
        
    }
}

void Player::ChangeColor(bool l, bool r, int availableColors[]){
    if (l && !leftPressed){
        do {
            if (color==1){
            color=4;
            }
            else color--;
            
            
        } while (availableColors[color-1]==0);
        
        leftPressed=true;
    }
    else if (!l){
        leftPressed=false;
    }

    if ((r && !rightPressed) || availableColors[color-1]==0){
        do {
            if (color==4){
                color=1;
            }
            else color++;
        } while (availableColors[color-1]==0);
        rightPressed=true;
    }
    else if (!r){
        rightPressed=false;
    }
}

void Player::ChangeGamemode(bool l, bool r, bool u, bool d, GameHandler &gamehandler){
    if (u && !upPressed){
        gamehandler.gamemodeChanging=1;
        upPressed=true;
    }
    else if (!u){
        upPressed=false;
    }

    if (d && !downPressed){
        gamehandler.gamemodeChanging=2;
        downPressed=true;
    }
    else if (!d){
        downPressed=false;
    }
    
    
    if (l && !leftPressed){
        if (gamehandler.gamemodeChanging==1){
            gamehandler.gamemode_index=0;
        }
        else if (gamehandler.gamemodeChanging==2){
            if (gamehandler.gamerounds_index>0) gamehandler.gamerounds_index--;
        }
        leftPressed=true;
    }
    else if (!l){
        leftPressed=false;
    }


    if (r && !rightPressed){
        if (gamehandler.gamemodeChanging==1){
            gamehandler.gamemode_index=1;
        }
        else if (gamehandler.gamemodeChanging==2){
            if (gamehandler.gamerounds_index<2) gamehandler.gamerounds_index++;
        }
        rightPressed=true;
    }
    else if (!r){
        rightPressed=false;
    }


    gamehandler.gamemode=availableGamemodes[gamehandler.gamemode_index];
    gamehandler.gamerounds=availableGamemodeRounds[gamehandler.gamemode_index][gamehandler.gamerounds_index];


    //?cout << gamehandler.gamemode_index << gamehandler.gamerounds_index << endl;
    //?cout << gamehandler.gamemode << gamehandler.gamerounds << endl;

}


bool Player::Timer(const std::chrono::time_point<std::chrono::steady_clock> &timestamp, std::chrono::milliseconds duration) {
    chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();
    chrono::milliseconds timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - timestamp);

    return timeElapsed <= duration;
}

void Player::MoveThroughWall() {
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
        x = hitbox2.x - 10;
        y = hitbox2.y;
        hitbox.x = hitbox2.x;
        hitbox.y = hitbox2.y;
        throughWall = false;
    }

    //cout << x << " " << y << endl;
}

void Player::Aim(bool u, bool d, bool l, bool r, bool b){
    if (b){
        aiming=true;

        arrow.x=hitbox.x+hitbox.w/2 - arrow.w/2;
        arrow.y=hitbox.y-arrow.h+24;
        
        int aimDirection[2];
        aimDirection[0]=0;
        aimDirection[1]=0;

        if (u) aimDirection[1]-=1;
        if (d) aimDirection[1]+=1;
        if (l) aimDirection[0]-=1;
        if (leftWalled) aimDirection[0]+=1;
        if (r) aimDirection[0]+=1;
        if (rightWalled) aimDirection[0]-=1;

        //cout << aimDirection[0] << " " << aimDirection[1] << endl;

        
        
        if (aimDirection[1]==-1){
            if (aimDirection[0]==-1) {
                aimingAngle=315;
                facingRight=false;
            }
            else if (aimDirection[0]==1) {
                aimingAngle=45;
                facingRight=true;
            }
            else aimingAngle=0;
        }
        else if (aimDirection[1]==1) {
            if (aimDirection[0]==-1) {
                aimingAngle=225;
                facingRight=false;
            }
            else if (aimDirection[0]==1) {
                aimingAngle=135;
                facingRight=true;
            }
            else aimingAngle=180;
        }
        else {
            if (aimDirection[0]==-1) {
                aimingAngle=270;
                facingRight=false;
            }
            else if (aimDirection[0]==1) {
                aimingAngle=90;
                facingRight=true;
            }
            else if (!(leftWalled || rightWalled)) aiming=false; 
            else aimingAngle=-1;
        }

    }
}

void Player::Shoot(SDL_Renderer *r, bool n, std::vector<Arrow>& arrowList){
    if (n && !shootPressed && aiming && aimingAngle!=-1 && arrowCount>0){
        arrowList.push_back(Arrow(r, hitbox, aimingAngle, playerID, serverPointer->gamehandler.newIDforArrow));
        serverPointer->gamehandler.newIDforArrow++;
        shootPressed=true;
        aiming=false;
        arrowCount--;
    }
    else if (!n){
        shootPressed=false;
    }
}

void Player::SingleShoot(SDL_Renderer *r, bool n, std::vector<Arrow>& arrowList){
    if (n && !shootPressed && aiming && aimingAngle!=-1 && arrowCount>0){
        arrowList.push_back(Arrow(r, hitbox, aimingAngle, color, 0));
        shootPressed=true;
        aiming=false;
        arrowCount--;
    }
    else if (!n){
        shootPressed=false;
    }
}


void Player::Move(bool u, bool d, bool l, bool r, bool b, float dt) {
    if (!aiming){
        if (l == 1) {
            top_vel_x = -SPEED;
            facingRight = false;
            rightWalled = false;
        } else if (r == 1) {
            top_vel_x = SPEED;
            facingRight = true;
            leftWalled = false;
        } else
            top_vel_x = 0;

        if (l == 1 && r == 1) top_vel_x = 0;
    }
    else top_vel_x = 0;
        

    vel_x = Velocity(top_vel_x, vel_x, dt * SPEED * 8.3);


    if (!b){
        if (wingsOn && u){
            vel_y -= SPEED * 0.2;
            if (vel_y < -(SPEED * 1.4)){
                vel_y = -(SPEED * 1.4);
            }
            isGrounded = false;
        }
        else if (u && !upPressed && isGrounded) {
            vel_y = -(SPEED * 2.1);
            isGrounded = false;
            upPressed = true;
        } else if (u && !upPressed && coyoteTime) {
            vel_y = -(SPEED * 2.1);
            isGrounded = false;
            upPressed = true;
        } else if (u && !upPressed && ((leftWalled || rightWalled) || wallJump)) {
            if (leftWalled) {
                vel_x = SPEED;
                leftWalled = false;
            } else {
                vel_x = -SPEED;
                rightWalled = false;
            }
            vel_y = -(SPEED * 2.1);
            upPressed = true;

        } else if (!u) {
            upPressed = false;
        }
    }


    if (((l && leftWalled) || (r && rightWalled)) && vel_y > 0) {
        vel_y = 0;
    }

    if (!l && leftWalled) {
        leftWalled = false;
        wallJumpTime = chrono::steady_clock::now();
    }
    if (!r && rightWalled) {
        rightWalled = false;
        wallJumpTime = chrono::steady_clock::now();
    }

    
    if (!isGrounded) {
        if (vel_y > -SPEED*0.3 && vel_y < SPEED*0.3) {
            vel_y += SPEED * 5 * dt; //vel_y += 2250 * dt * (1- u*.4); //1500
        } else
            vel_y += SPEED * 6.7 * dt; //* (1- u*.4); //2000

        if (vel_y > SPEED * 2.1) {
            vel_y = SPEED * 2.1;
        }
    }
}

float Player::Velocity(float top_vel_x, float vel_x, float dt) {
    float velDiff = top_vel_x - vel_x;
    if (velDiff > dt) {
        return vel_x + dt;
    }
    if (velDiff < (-dt)) {
        return vel_x - dt;
    }
    return top_vel_x;
}

void Player::Collisions(int grid[32][24], float dt) {
    float x1 = hitbox.x;
    float y1 = hitbox.y;
    float x2 = hitbox.x + hitbox.w - 1;
    float y2 = hitbox.y + hitbox.h - 1;

    SDL_FRect next_pos;
    next_pos.x = hitbox.x + vel_x * dt;
    next_pos.y = hitbox.y + vel_y * dt;
    next_pos.w = hitbox.w;
    next_pos.h = hitbox.h;

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 24; j++) {
            if (grid[i][j] != 0) {
                //cout << "x: " << i*32 << "y: " << j*32 << endl;
                SDL_FRect rect;
                rect.x = i * GRIDSIZE;
                rect.y = j * GRIDSIZE;
                rect.w = GRIDSIZE;
                rect.h = GRIDSIZE;
                if (Collision(next_pos, rect)) {
                    bool bx = false, by = false;
                    SDL_FRect tmp = next_pos;
                    tmp.x = hitbox.x;
                    if (Collision(tmp, rect)) {
                        bx = true;
                        if (vel_y > 0) isGrounded = true;
                        vel_y = 0;
                    }
                    tmp = next_pos;
                    tmp.y = hitbox.y;
                    if (Collision(tmp, rect)) {
                        by = true;
                        if (vel_x < 0) {
                            leftWalled = true;
                        }
                        if (vel_x > 0) {
                            rightWalled = true;
                        }
                        vel_x = 0;
                    }
                    if (!bx && !by) {
                        vel_x = 0;
                    }
                }
            }
        }
    }
    if ((grid[(int)(x1 / GRIDSIZE)][(int)(y2 / GRIDSIZE) + 1] == 0 && grid[(int)(x2 / GRIDSIZE)][(int)(y2 / GRIDSIZE) + 1] == 0) && isGrounded) {
        isGrounded = false;
        jumpTime = chrono::steady_clock::now();
    }

    if (((grid[(int)(x1 / GRIDSIZE)][(int)(y2 / GRIDSIZE) + 1] != 0 || grid[(int)(x2 / GRIDSIZE)][(int)(y2 / GRIDSIZE) + 1] != 0) && !isGrounded) || isGrounded) {
        leftWalled = false;
        rightWalled = false;
    }

    if ((grid[(int)(x1 / GRIDSIZE) - 1][(int)(y1 / GRIDSIZE) + 1] == 0 && grid[(int)(x1 / GRIDSIZE) - 1][(int)(y2 / GRIDSIZE) - 1] == 0)) {
        leftWalled = false;
    }

    if ((grid[(int)(x1 / GRIDSIZE) + 1][(int)(y1 / GRIDSIZE) + 1] == 0 && grid[(int)(x1 / GRIDSIZE) + 1][(int)(y2 / GRIDSIZE) - 1] == 0)) {
        rightWalled = false;
    }

    /*x += vel_x * dt;
    y += vel_y * dt;
    hitbox.x = x + 10;
    hitbox.y = y;*/
}

void Player::Update(float dt){
    x += vel_x * dt;
    y += vel_y * dt;
    hitbox.x = x + 10;
    hitbox.y = y;

    if (running_i>200) running_i=0;
    if ((l2 || r2) && !(rightWalled || leftWalled || !isGrounded || aiming)) {
        running_i=running_i+dt*800;
        //cout << running_i << endl;
    }
    /*else if (!isGrounded || rightWalled || leftWalled){
        running_i=100;
    }*/
    else running_i=0;

    //cout << running_i << endl;
}

void Player::UpdateHitbox(){
    hitbox.x = x + 10;
    hitbox.y = y;
}

void Player::PlayerDead(){
    x=0;
    y=0;
    hitbox.x=x+10;
    hitbox.y=y;
}

void Player::HurtAnimation(float dt){
    hurt_i=hurt_i+dt*1600;
    if (hurt_i>200) hurt_i=0;
    

}