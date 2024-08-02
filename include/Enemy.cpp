using namespace std;

Enemy::Enemy(SDL_Renderer *r, string typ, SDL_Point coord, int dir){
    x=coord.x;
    y=coord.y;
    vel_x=0;
    vel_y=0;
    type=typ;
    if (dir==0 || dir==2) facingRight=1;
    else facingRight=0;
    isGrounded=0;
    rightWalled=0;
    leftWalled=0;
    throughWall=0;

    hitbox.x=x;
    hitbox.y=y;
    if (type=="slime"){
        hitbox.w=46;
        hitbox.h=46;
    }
    else if (type=="ghost"){
        hitbox.w=32;
        hitbox.h=64;
    }
    

}
void Enemy::Draw(SDL_Renderer *r) {
    if (type=="slime"){
        SDL_Rect rect1;
        rect1.x = 0;
        rect1.y = 0;
        rect1.w = 16;
        rect1.h = 16;

        SDL_FRect rect2;
        rect2.x = x;
        rect2.y = y;
        rect2.w = 46;
        rect2.h = 46;

        SDL_FRect rect3;
        rect3.x = hitbox2.x;
        rect3.y = hitbox2.y;
        rect3.w = 46;
        rect3.h = 46;

        if (facingRight) SDL_RenderCopyF(r, slime, &rect1, &rect2);
        else SDL_RenderCopyExF(r, slime, &rect1, &rect2, NULL, NULL, SDL_FLIP_HORIZONTAL);

        if (throughWall) {
            if (facingRight) SDL_RenderCopyF(r, slime, &rect1, &rect3);
            else SDL_RenderCopyExF(r, slime, &rect1, &rect3, NULL, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
    else if (type=="ghost"){
        SDL_Rect rect1;
        rect1.x = 0;
        rect1.y = 0;
        rect1.w = 13;
        rect1.h = 26;

        SDL_FRect rect2;
        rect2.x = x;
        rect2.y = y;
        rect2.w = 32;
        rect2.h = 64;

        SDL_FRect rect3;
        rect3.x = hitbox2.x;
        rect3.y = hitbox2.y;
        rect3.w = 32;
        rect3.h = 64;

        if (facingRight) SDL_RenderCopyF(r, ghost, &rect1, &rect2);
        else SDL_RenderCopyExF(r, ghost, &rect1, &rect2, NULL, NULL, SDL_FLIP_HORIZONTAL);

        if (throughWall) {
            if (facingRight) SDL_RenderCopyF(r, ghost, &rect1, &rect3);
            else SDL_RenderCopyExF(r, ghost, &rect1, &rect3, NULL, NULL, SDL_FLIP_HORIZONTAL);
        }

        //SDL_RenderDrawLineF(r, acx, acy, bcx, bcy);

        /*for (hpIterator = HomePoints.begin(); hpIterator != HomePoints.end(); hpIterator++){
            SDL_RenderDrawLineF(r, acx, acy, hpIterator->x, hpIterator->y);
        }*/
    }
}

void Enemy::Move(float dt, int grid[32][24]) {
    //float top_vel_x;
    /*if (!aiming){
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
    }*/

    if (type=="slime"){
        if (rightWalled){
            rightWalled = false;
            facingRight = false;
        }
        else if (leftWalled){
            leftWalled = false;
            facingRight = true;
        }
        
        if (!isGrounded) {
            vel_y += SPEED * 5 * dt; // (1- u*.4); //2000
            if (vel_y > SPEED * 1.5) {
                vel_y = SPEED * 1.5;
            }
            top_vel_x=0;
        }
        else {
            if (!facingRight) {
                top_vel_x = -SPEED * 0.35;
                facingRight = false;
                rightWalled = false;
            } else if (facingRight) {
                top_vel_x = SPEED * 0.35;
                facingRight = true;
                leftWalled = false;
            }
        }
        vel_x = Velocity(top_vel_x, vel_x, dt * SPEED * 5); //8.3
    }
    else if (type=="ghost"){
        Proximity(hitbox, playerPointer->hitbox);
        InSight(hitbox, playerPointer->hitbox, grid);

        //cout << pis << endl;
        if (pis && proximity<250){
            if (s<150) s+=SPEED*1.5*dt;
            
            vel_x=cos(angle)*SPEED*s*dt;
            vel_y=sin(angle)*SPEED*s*dt;
        }
        else if (proximity<500){
            if (s>75) s-=SPEED*1.5*dt;
            vel_x=cos(angle)*SPEED*75*dt;
            vel_y=sin(angle)*SPEED*75*dt;
        }
        /*else {
            if (!targetFound){
                proximity2=10000;
                for (hpIterator = HomePoints.begin(); hpIterator != HomePoints.end(); hpIterator++){
                    cout << hpIterator->x <<" " << hpIterator->y << endl;
                    cout << InSight(hitbox, *hpIterator, grid) << endl;
                    cout << Proximity(*hpIterator) << endl;
                    if (Proximity(*hpIterator)<proximity2 ){//&& InSight(hitbox, *hpIterator, grid)){
                        cout << "prox:" << endl;
                        targetX=hpIterator->x;
                        targetY=hpIterator->y;
                        proximity2=Proximity(*hpIterator);
                    }
                }
                targetFound=true;
                cout << targetX << targetY;
                
            }
            angle2 = atan2(((targetY)-(hitbox.y+hitbox.h/2)), ((targetX)-(hitbox.x+hitbox.w/2)));
            vel_x=cos(angle2)*SPEED*150*dt;
            vel_y=sin(angle2)*SPEED*150*dt;
        }*/
        else {
            
            if (vel_x<0){
                vel_x += SPEED * dt;
                if (vel_x>0) vel_x=0;
            }
            else if (vel_x>0){
                vel_x -= SPEED * dt;
                if (vel_x<0) vel_x=0;
            }
            if (vel_y<0){
                vel_y += SPEED * dt;
                if (vel_y>0) vel_y=0;
            }
            else if (vel_y>0){
                vel_y -= SPEED * dt;
                if (vel_y<0) vel_y=0;
            }
            
        }
        if (vel_x<0) facingRight=false;
        else if (vel_x>0) facingRight=true;
        
        
        
        
    }
}

void Enemy::MoveThroughWall() {
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

void Enemy::Collisions(int grid[32][24], float dt) {
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
        //jumpTime = chrono::steady_clock::now();
    }

    /*if (((grid[(int)(x1 / GRIDSIZE)][(int)(y2 / GRIDSIZE) + 1] != 0 || grid[(int)(x2 / GRIDSIZE)][(int)(y2 / GRIDSIZE) + 1] != 0) && !isGrounded) || isGrounded) {
        leftWalled = false;
        rightWalled = false;
    }

    if ((grid[(int)(x1 / GRIDSIZE) - 1][(int)(y1 / GRIDSIZE) + 1] == 0 && grid[(int)(x1 / GRIDSIZE) - 1][(int)(y2 / GRIDSIZE) - 1] == 0)) {
        leftWalled = false;
    }

    if ((grid[(int)(x1 / GRIDSIZE) + 1][(int)(y1 / GRIDSIZE) + 1] == 0 && grid[(int)(x1 / GRIDSIZE) + 1][(int)(y2 / GRIDSIZE) - 1] == 0)) {
        rightWalled = false;
    }*/

    /*x += vel_x * dt;
    y += vel_y * dt;
    hitbox.x = x + 10;
    hitbox.y = y;*/
}

void Enemy::Update(float dt){
    x += vel_x * dt;
    y += vel_y * dt;
    hitbox.x = x;
    hitbox.y = y;
/*
    if (running_i>200) running_i=0;
    if ((l2 || r2) && !(rightWalled || leftWalled || !isGrounded || aiming)) {
        running_i++;
        //cout << running_i << endl;
    }
    //else if (!isGrounded || rightWalled || leftWalled){
        //running_i=100;
    //}
    else running_i=0;*/
}

void Enemy::UpdateHitbox(){
    hitbox.x = x;
    hitbox.y = y;
}

float Enemy::Velocity(float top_vel_x, float vel_x, float dt) {
    float velDiff = top_vel_x - vel_x;
    if (velDiff > dt) {
        return vel_x + dt;
    }
    if (velDiff < (-dt)) {
        return vel_x - dt;
    }
    return top_vel_x;
}


void Enemy::Proximity(SDL_FRect a, SDL_FRect b){
    //angle = fmod(atan2(((a.y+a.h/2)-(b.y+b.h/2)), ((a.x+a.w/2)-(b.x+b.w/2))) * (180.0 / M_PI), 360.0);
    angle = atan2(((b.y+b.h/2)-(a.y+a.h/2)), ((b.x+b.w/2)-(a.x+a.w/2)));
    proximity = sqrt(pow(((a.x+a.w/2)-(b.x+b.w/2)), 2) + pow(((a.y+a.h/2)-(b.y+b.h/2)), 2));
}

float Enemy::Proximity(SDL_Point a){

    
    return sqrt(pow(((a.x)-(hitbox.x+hitbox.w/2)), 2) + pow(((a.y)-(hitbox.y+hitbox.h/2)), 2));
}

void Enemy::InSight(SDL_FRect a, SDL_FRect b, int grid[32][24]){
    int segment = ceil(proximity);
    float newx, newy;
    newx=a.x+a.w/2;
    newy=a.y+a.h/2;
    
    
    acx=a.x+a.w/2;
    acy=a.y+a.h/2;
    bcx=b.x+b.w/2;
    bcy=b.y+b.h/2;

    float lenx, leny;
    //lenx=abs(acx-bcx);
    //leny=abs(acy-bcy);
    lenx=bcx-acx;
    leny=bcy-acy;

    pis=1;

    
    
    for (int i=1; i<segment-1; i++){
        /*if (acx<bcx)newx = acx+i*(lenx/segment);
        else newx = acx-i*(proximity/segment);
        if (acy<bcy) newy = acy+i*(leny/segment);
        else newy = acy-i*(proximity/segment);
        */
        newx = acx+i*(lenx/segment);
        newy = acy+i*(leny/segment);
        //cout << newx << " " << newy << endl;
        if (grid[(int)(newx / GRIDSIZE)][(int)(newy / GRIDSIZE)] != 0){
            pis=0;
            break;
        }
        
    }
}

bool Enemy::InSight(SDL_FRect a, SDL_Point b, int grid[32][24]){
    int segment = ceil(Proximity(b));
    float newx, newy;
    newx=a.x+a.w/2;
    newy=a.y+a.h/2;
    
    float acx, acy, bcx, bcy;
    acx=a.x+a.w/2;
    acy=a.y+a.h/2;
    bcx=b.x;
    bcy=b.y;

    float lenx, leny;
    //lenx=abs(acx-bcx);
    //leny=abs(acy-bcy);
    lenx=bcx-acx;
    leny=bcy-acy;
    
    for (int i=1; i<segment-1; i++){
        /*if (acx<bcx)newx = acx+i*(lenx/segment);
        else newx = acx-i*(proximity/segment);
        if (acy<bcy) newy = acy+i*(leny/segment);
        else newy = acy-i*(proximity/segment);
        */
        newx = acx+i*(lenx/segment);
        newy = acy+i*(leny/segment);
        //cout << newx << " " << newy << endl;
        if (grid[(int)(newx / GRIDSIZE)][(int)(newy / GRIDSIZE)] != 0){
            return 0;
        }
        
    }
    return 1;
}

