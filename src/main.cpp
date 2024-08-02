#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <mouse.h>
#include <vector>

#include "Game.h"
#include "Textures.h"
#include "GameFunctions.cpp"
#include "Player.cpp"
#include "Arrow.cpp"
#include "Chest.cpp"
#include "Client.cpp"
#include "Server.cpp"
#include "Enemy.cpp"


using namespace std;




int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Window *wind = SDL_CreateWindow("Arcadia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!wind) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *r = SDL_CreateRenderer(wind, -1, render_flags);
    if (!r) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return 0;
    }
    SDL_Surface* iconSurface = SDL_LoadBMP("media/icon.bmp");
    if (iconSurface == NULL) {
        SDL_Log("Unable to load image: %s", SDL_GetError());
        return 1;
    }
    SDL_SetWindowIcon(wind, iconSurface);
    SDL_FreeSurface(iconSurface);

    //SDL_SetWindowFullscreen(wind, SDL_WINDOW_FULLSCREEN);

    LoadTextures(r);
    LoadText(r);
    LoadRects();

    
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto Width = DM.w;
    auto Height = DM.h;

    cout << Width << " " << Height <<  endl;


    int grid[32][24];
    int spawnPos[4][2];
    int chestPos[6][2];

    

    gridPnt = grid;
    spPnt = spawnPos;
    cpPnt = chestPos;
    
    ifstream dat("level1.bin", ios::binary);
    dat.read((char *)&grid, sizeof(grid));
    dat.read((char *)&spawnPos, sizeof(spawnPos));
    dat.read((char *)&chestPos, sizeof(chestPos));
    dat.close();


    
    
    int availableLevels[5]={1,0,0,0,0};

    Player player(r, 0);
    Client client;
    Server server;
    
    SDL_Point hp1;
    
    hp1= {62,126};
    HomePoints.push_back(hp1);
    hp1= {922,126};
    HomePoints.push_back(hp1);
    hp1= {62,440};
    HomePoints.push_back(hp1);
    hp1= {922,440};
    HomePoints.push_back(hp1);
    hp1= {506,115};
    HomePoints.push_back(hp1);
    hp1= {508, 643};
    HomePoints.push_back(hp1);
    

    //Enemy enemy(r, "slime");
    string spawntype="slime";
    //enemyList.push_back(Enemy(r, spawntype));

    std::chrono::steady_clock::time_point prevTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point newTime;

    bool u = 0, d = 0, ri = 0, l = 0, b = 0, n = 0;
    float dt;
    int menu_t=0;
    bool changingIP=0;
    char ipaddress[16];
    //strcpy(ipaddress, client.server_name.c_str());
    TTF_Font *AddressSans = TTF_OpenFont("fonts/open-sans/WinterPixel.otf", 70);
    bool fullscreen=0;
    bool mouseaim=0;

    ifstream dato("options.bin", ios::binary);
    dato.read((char*)&fullscreen, sizeof(fullscreen));
    dato.read((char*)&mouseaim, sizeof(mouseaim));
    dato.read((char*)&ipaddress, sizeof(ipaddress));
    dato.close();

    client.server_name=ipaddress;
    if (fullscreen){
        FACTOR=Height/(float)HEIGHT;
        SDL_RenderSetLogicalSize(r, WIDTH, HEIGHT);
        SDL_SetWindowSize(wind, Width, Height);
        SDL_SetWindowPosition(wind, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }


    bool isServer;
    //cout << "Pritisni 0 za client, 1 za server" << endl;
    //cin >> isServer;
    isServer=1;

    if (isServer){
        //Chest tmp(r);
        /*for (int i=0; i<6; i++){
            chestList.push_back(Chest(r, chestPos[i][0], chestPos[i][1]));
        }*/
    }

    if (isServer){
        if (server.CreateSocket() == 0) {
            std::thread(&Server::StartListening, &server).detach();
            std::thread(&Server::Broadcast, &server).detach();
            STATE="game";
            //STATE="nothing";
            server.rendererPnt=r;
            serverPointer=&server;
        }
    }
    else {
        //STATE="multiplayer_menu";
        //STATE="game";
        //STATE="game";
        //STAGE="single_gameplay";
        player.color=1;
        //client.clientID=1; //!
        client.playerPointer=&player;
        playerPointer=&player;
        clientPointer=&client;
        rendererPnt=r;
        //cout << "Vnesi IP (127.0.0.1 za lokalno igro)" << endl;
        //cin >> client.server_name;
        //client.server_name="109.182.182.227";
        
    }
    /*else {
        if (client.tryConnecting()) client.cleanUp();
        //client.tmpPlayerPnt=&coplayer;
        client.playerPointer=&player;
        server.rendererPnt=r;
        playerpointer
    }*/
    
    
    
    
    
    Mouse m;
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                //client.Shutdown();
                
                running = false;
                break;
            case SDL_TEXTINPUT:
                if (changingIP==1){
                    if (strlen(ipaddress)<15) strcat(ipaddress, event.text.text);
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                        case SDLK_BACKSPACE: 
                        if (changingIP==1){
                            int len = strlen(ipaddress);
                            if (len > 0) ipaddress[len - 1] = '\0';
                        }
                    break;
                }
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_RETURN:
                    if (changingIP) changingIP=0;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    if (STATE=="menu"){
                        running=false;
                    }
                    if (STATE=="level_menu" || STATE=="multiplayer_menu" || STATE=="choose_gamemode" || STATE=="game" || STATE=="winner_stats"){
                        client.str="end";
                        client.Shutdown();
                        client.ConnectSocket = INVALID_SOCKET;
                        STATE="menu";
                        STAGE="anim";
                        menu_t=1;
                    }
                    if (STATE=="options"){
                        STATE="menu";
                        STAGE="anim";
                        menu_t=-1;

                        changingIP=0;
                        client.server_name=ipaddress;

                        ofstream data("options.bin", ios::binary);
                        data.write((char*)&fullscreen, sizeof(fullscreen));
                        data.write((char*)&mouseaim, sizeof(mouseaim));
                        data.write((char*)&ipaddress, sizeof(ipaddress));
                        data.close();
                    }
                    if (STATE=="playstyle"){
                        STATE="menu";
                        STAGE="anim";
                        menu_t=1;
                    }
                    
                    //running=false;
                    //STATE="menu";
                    break;
                case SDL_SCANCODE_SPACE:
                    cout << "space\n";
                    if (isServer){
                        
                        //if (STATE!="game")STATE="game";
                        //else if (STATE!="multiplayer_menu")STATE="multiplayer_menu";
                        //cout << "Players: "<<server.players.size() << endl;
                        //cout << "Client sockets: "<<server.clientSockets.size() << endl;
                    }
                    else { 
                        //STATE="winner_stats";
                        //STAGE="winner_stats";
                        //cout << player.hitbox.x << " " << player.hitbox.y << endl;
                        //client.str="bye";
                        //enemyList.push_back(Enemy(r, spawntype));
                        //STAGE="single_winner";
                    }
                    break;
                case SDL_SCANCODE_W:
                    u = 1;
                    break;
                case SDL_SCANCODE_S:
                    d = 1;
                    break;
                case SDL_SCANCODE_A:
                    l = 1;
                    break;
                case SDL_SCANCODE_D:
                    ri = 1;
                    break;
                case SDL_SCANCODE_B:
                    b = 1;
                    player.aiming=true;
                    break;
                case SDL_SCANCODE_N:
                    n = 1;
                    break;
                /*case SDL_SCANCODE_1:
                    //chest.open=false;
                    FACTOR=1;
                    SDL_RenderSetLogicalSize(r, WIDTH, HEIGHT);
                    break;
                case SDL_SCANCODE_2:
                    FACTOR=Height/(float)HEIGHT;
                    SDL_RenderSetLogicalSize(r, 1920, 1080);
                    //chest.open=true;
                    break;*/
                /*case SDL_SCANCODE_3:

                    break;
                case SDL_SCANCODE_4:

                break;*/

                case SDL_SCANCODE_1:
                    /*SPEED = 412.5;
                    GRIDSIZE = 44;
                    WIDTH = 1408;
                    HEIGHT = 1056;*/
                    //SDL_SetWindowFullscreen(wind, 1);
                    //SDL_RestoreWindow(wind); //Incase it's maximized...
                    /*
                    FACTOR=1;
                    SDL_RenderSetLogicalSize(r, WIDTH, HEIGHT);
                    SDL_SetWindowSize(wind, WIDTH, HEIGHT);
                    SDL_SetWindowPosition(wind, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                    */
                    //spawntype="slime";
                    break;
                case SDL_SCANCODE_2:
                    /*SPEED = 300;
                    GRIDSIZE = 32;
                    WIDTH = 1024+372;
                    HEIGHT = 768;*/
                    //SDL_SetWindowFullscreen(wind, 0);
                    /*
                    FACTOR=Height/(float)HEIGHT;
                    SDL_RenderSetLogicalSize(r, WIDTH, HEIGHT);
                    SDL_SetWindowSize(wind, Width, Height);
                    SDL_SetWindowPosition(wind, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                    */
                    //spawntype="ghost";
                    break;
                case SDL_SCANCODE_3:
                    
                    break;
                default:
                    break;
                }

                break;

            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_SPACE:
                    /*cout << "vel y: " << player.vel_y << endl;
                    cout << "x: " << player.hitbox.x << endl;
                    cout << "y: " << player.hitbox.y + player.hitbox.h << endl;*/
                    
                    break;
                case SDL_SCANCODE_W:
                    u = 0;
                    break;
                case SDL_SCANCODE_S:
                    d = 0;
                    break;
                case SDL_SCANCODE_A:
                    l = 0;
                    break;
                case SDL_SCANCODE_D:
                    ri = 0;
                    break;
                case SDL_SCANCODE_B:
                    b = 0;
                    player.aiming=false;
                    break;
                case SDL_SCANCODE_N:
                    n = 0;
                    break;

                default:
                    break;
                }
                break;
            default:
                break;
            }

        
        }
        SDL_Point mousePoint;
        if (FACTOR==1) mousePoint={m.x, m.y};
        else mousePoint = {(int)(m.x/FACTOR)-(int)(240/FACTOR), (int)(m.y/FACTOR)};

        //cout << (Width - (WIDTH*FACTOR))/2;
        

        /*float *mx, *my;

        int *nw, *nh;
        SDL_RenderGetLogicalSize(r, nw, nh);
        cout << *mx << *my << endl;

        SDL_RenderWindowToLogical(r, m.x, m.y, mx, my);
        cout << mx << my << endl;
        if (mx!=NULL && my!=NULL){
            int mx1=*mx, my1=*my;
            mousePoint = {mx1, my1};
            cout << "tojetototot" << endl;
        }*/


        newTime = std::chrono::steady_clock::now();
        dt = std::chrono::duration_cast<std::chrono::microseconds>(newTime - prevTime).count() / 1000000.0f;
        prevTime = newTime;

        // UPDATE HERE
        bool updateButtons = false;
        if (m.update(updateButtons)) {
            if (updateButtons) {
                if (m.left == true){
                    cout << "L click " << m.x << ", " << m.y << endl;

                    if (SDL_PointInRect(&mousePoint, &lvl1buttonRect) && STATE=="level_menu" && availableLevels[0]){
                        client.gamehandler.levelStarter=1;
                    }
                    if (SDL_PointInRect(&mousePoint, &lvl2buttonRect) && STATE=="level_menu" && availableLevels[1]){
                        client.gamehandler.levelStarter=2;
                    }
                    if (SDL_PointInRect(&mousePoint, &lvl3buttonRect) && STATE=="level_menu" && availableLevels[2]){
                        client.gamehandler.levelStarter=3;
                    }
                    if (SDL_PointInRect(&mousePoint, &lvl4buttonRect) && STATE=="level_menu" && availableLevels[3]){
                        client.gamehandler.levelStarter=4;
                    }
                    if (SDL_PointInRect(&mousePoint, &lvl5buttonRect) && STATE=="level_menu" && availableLevels[4]){
                        client.gamehandler.levelStarter=5;
                    }


                    if (SDL_PointInRect(&mousePoint, &bigbuttonRect) && STATE=="playstyle" && STAGE!="anim"){
                        STATE="level_menu";
                        
                    }
                    if (SDL_PointInRect(&mousePoint, &bigbutton2Rect) && STATE=="playstyle" && STAGE!="anim"){
                        STATE="multiplayer_connect";
                    }
                    
                    
                    if (SDL_PointInRect(&mousePoint, &playbuttonRect) && STATE=="menu" && STAGE!="anim"){
                        STATE="playstyle";
                        STAGE="anim";
                        //STATE="multiplayer_connect";
                    }
                    if (SDL_PointInRect(&mousePoint, &optionsbuttonRect) && STATE=="menu" && STAGE!="anim"){
                        STATE="options";
                        STAGE="anim";
                    }
                    if (SDL_PointInRect(&mousePoint, &quitbuttonRect) && STATE=="menu" && STAGE!="anim"){
                        running=false;
                    }

                    
                    
                    if (SDL_PointInRect(&mousePoint, &confirmbuttonRect) && STATE=="multiplayer_menu"){
                        player.playerReady=1;
                    }
                    if (SDL_PointInRect(&mousePoint, &startgamebuttonRect) && STATE=="choose_gamemode" && client.clientID==1){
                        player.leaderCommand="start_game";
                    }
                    if (SDL_PointInRect(&mousePoint, &continuebuttonRect) && STATE=="game" && STAGE=="stats" && client.clientID==1){
                        player.leaderCommand="next_round";
                    }
                    if (SDL_PointInRect(&mousePoint, &continuebuttonRect) && STATE=="game" && STAGE=="endgame_stats" && client.clientID==1){
                        player.leaderCommand="winner_stats";
                    }


                    if (SDL_PointInRect(&mousePoint, &menubuttonstatsRect) && STATE=="winner_stats"){
                        STATE="menu";
                        STAGE="anim";
                        menu_t=1;
                        client.Shutdown();
                        client.ConnectSocket = INVALID_SOCKET;
                    }

                    if (SDL_PointInRect(&mousePoint, &onoffbuttonRect) && STATE=="options"){
                        if (!fullscreen){
                            FACTOR=Height/(float)HEIGHT;
                            SDL_RenderSetLogicalSize(r, WIDTH, HEIGHT);
                            SDL_SetWindowSize(wind, Width, Height);
                            SDL_SetWindowPosition(wind, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                            fullscreen=1;
                        }
                        else {
                            FACTOR=1;
                            SDL_RenderSetLogicalSize(r, WIDTH, HEIGHT);
                            SDL_SetWindowSize(wind, WIDTH, HEIGHT);
                            SDL_SetWindowPosition(wind, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                            fullscreen=0;
                        }
                    }
                    if (SDL_PointInRect(&mousePoint, &onoffbuttonRect2) && STATE=="options"){
                        if (!mouseaim) mouseaim=1;
                        else mouseaim=0;
                    }

                    if (SDL_PointInRect(&mousePoint, &serverfieldRect) && STATE=="options"){
                        if (changingIP==0){
                            changingIP=1;
                            //strcpy(ipaddress, client.server_name.c_str());
                        }
                        else if (changingIP==1){
                            changingIP=0;
                            //client.server_name=ipaddress;
                        }
                    }

                    

                    if (SDL_PointInRect(&mousePoint, &nextbuttonRect) && STATE=="game" && STAGE=="single_winner"){
                        STATE="level_menu";
                        STAGE="level_menu";
                        availableLevels[client.gamehandler.level]=1;
                        player.dead=false;
                    }

                    if (SDL_PointInRect(&mousePoint, &retrybuttonRect) && STATE=="game" && STAGE=="single_lost"){
                        STATE="level_menu";
                        STAGE="level_menu";
                        client.gamehandler.levelStarter=client.gamehandler.level;
                    }

                }
                    
                if (m.right == true){
                    cout << "R click " << m.x << ", " << m.y << endl;

                }
            }
        }

        
        if (STATE=="menu"){
            if (STAGE=="anim"){
                if (menu_t==1){
                    menubgrnd.y -= dt*3500;
                    if (menubgrnd.y<-HEIGHT) {
                        menubgrnd.y=-HEIGHT;
                        STAGE="menu";
                        menu_t=0;
                    }
                }
                else if (menu_t==-1){
                    menubgrnd.y += dt*2000;
                    if (menubgrnd.y>-HEIGHT) {
                        menubgrnd.y=-HEIGHT;
                        STAGE="menu";
                        menu_t=0;
                    }
                }
                
            }
            else {

            }
        }
        else if (STATE=="options"){
            if (STAGE=="anim"){
                menubgrnd.y -= dt*2000;
                if (menubgrnd.y<-HEIGHT*1.5) {
                    menubgrnd.y=-HEIGHT*1.5;
                    STAGE="options";
                }
            }
            else {

            }
        }
        else if (STATE=="playstyle"){
            if (STAGE=="anim"){
                menubgrnd.y += dt*3500;
                if (menubgrnd.y>0) {
                    menubgrnd.y=0;
                    STAGE="playstyle";
                }
            }
            else {

            }
        }
        else if (STATE=="level_menu"){
            if (client.gamehandler.levelStarter){
                for (int i=0; i<5; i++)
                    if (WaveData[i].size()>0) WaveData[i].clear();
                
                if (enemyList.size()>0) enemyList.clear();
                if (arrowList.size()>0) arrowList.clear();
                
                int tmplvldata[2];
                EnemyData tmpenemydata;

                ifstream datad("leveldata.bin", ios::binary);
                for (int i=0; i<5; i++){
                    datad.read((char *)&tmplvldata, sizeof(tmplvldata));
                    for (int j=0; j<tmplvldata[1]; j++){
                        datad.read((char *)&tmpenemydata, sizeof(tmpenemydata));
                        //tmpenemydata.spawntime*=((float)(rand()%5+1)/10)+1;
                        WaveData[tmplvldata[0]-1].push_back(tmpenemydata);
                        //cout << tmpenemydata.spawnpoint << " " << tmpenemydata.spawntime << " " << tmpenemydata.type<< endl;
                    }
                    //cout << endl;
                }
                datad.close();

                for (int i=0; i<5; i++){
                    for (itWaveData = WaveData[i].begin(); itWaveData != WaveData[i].end(); itWaveData++){
                        //cout << itWaveData->spawnpoint << " " << itWaveData->spawntime << " " << itWaveData->type<< endl;
                    }
                   // cout << endl;
                }

                ifstream dat("slevel1.bin", ios::binary);
                dat.read((char *)&grid, sizeof(grid));
                dat.read((char *)&spawnPos, sizeof(spawnPos));
                dat.read((char *)&chestPos, sizeof(chestPos));
                dat.close();

                STATE="game";
                STAGE="singlecountdown3";

                client.gamehandler.countdownText="3";
                client.gamehandler.countTime = chrono::steady_clock::now();
                client.gamehandler.waveStartTime = chrono::steady_clock::now();
                client.gamehandler.wave=0;
                client.gamehandler.waveStart=1;
                client.gamehandler.activeWave=0;
                client.gamehandler.level=client.gamehandler.levelStarter;

                client.gamehandler.levelStarter=0;
                player.lives=5;
                player.dead=false;

                player.hurt=0;
                player.hurtStop=1;
                player.hurt_i=0;
                player.deadRespawn=1;
            }
        }
        else if (STATE=="multiplayer_connect"){
            if (client.ConnectSocket == INVALID_SOCKET){
                std::thread(&Client::tryConnecting, &client).detach();
                STATE="multiplayer_searching";   
                //STATE="game"; 
            }
            else {
                STATE="menu";     
            }
        }
        else if (STATE=="multiplayer_searching"){
            //cout << "Connecting..." << endl;
            if (client.noConnection==1) {
                client.cleanUp();
                STATE="playstyle";
            }
            else if (client.noConnection==2){
                client.playerPointer=&player;
                STATE="multiplayer_menu";
            }
        }
        else if (STATE=="multiplayer_menu"){
            if (!player.playerReady) player.ChangeColor(l, ri, client.gamehandler.availableColors);
            if (client.gamehandler.allPlayersReady){
                STATE="choose_gamemode";
                player.playerReady=0;
            } 
        }
        else if (STATE=="choose_gamemode"){
            if (client.clientID==1) player.ChangeGamemode(l, ri, u, d, client.gamehandler);
            if (client.gamehandler.gamecommand=="start_game") {
                player.leaderCommand="nothing";

                player.x=spawnPos[client.clientID-1][0]-10;
                player.y=spawnPos[client.clientID-1][1];
                player.UpdateHitbox();

                if (client.players.size()>0){
                    for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                        playerIterator->x=spawnPos[playerIterator->playerID-1][0]-10;
                        playerIterator->y=spawnPos[playerIterator->playerID-1][1];
                        playerIterator->UpdateHitbox();
                    }
                }

                STATE="game";
                STAGE="countdown3";
                client.gamehandler.countdownText="3";
                client.gamehandler.countTime = chrono::steady_clock::now();
            }
        }
        else if (STATE=="game"){
            if (!isServer){
                if (STAGE=="countdown3"){
                    client.gamehandler.nextCount=player.Timer(client.gamehandler.countTime, chrono::milliseconds(1000));
                    if (!client.gamehandler.nextCount){
                        STAGE="countdown2";
                        client.gamehandler.countdownText="2";
                        client.gamehandler.countTime = chrono::steady_clock::now();
                    }
                }
                else if (STAGE=="countdown2"){
                    client.gamehandler.nextCount=player.Timer(client.gamehandler.countTime, chrono::milliseconds(1000));
                    if (!client.gamehandler.nextCount){
                        STAGE="countdown1";
                        client.gamehandler.countdownText="1";
                        client.gamehandler.countTime = chrono::steady_clock::now();
                    }
                }
                else if (STAGE=="countdown1"){
                    client.gamehandler.nextCount=player.Timer(client.gamehandler.countTime, chrono::milliseconds(1000));
                    if (!client.gamehandler.nextCount){
                        STAGE="gameplay";
                        client.gamehandler.countdownText="GO";
                        client.gamehandler.countTime = chrono::steady_clock::now();
                    }
                }
                else if (STAGE=="singlecountdown3"){
                    client.gamehandler.nextCount=player.Timer(client.gamehandler.countTime, chrono::milliseconds(1000));
                    if (!client.gamehandler.nextCount){
                        STAGE="singlecountdown2";
                        client.gamehandler.countdownText="2";
                        client.gamehandler.countTime = chrono::steady_clock::now();
                    }
                }
                else if (STAGE=="singlecountdown2"){
                    client.gamehandler.nextCount=player.Timer(client.gamehandler.countTime, chrono::milliseconds(1000));
                    if (!client.gamehandler.nextCount){
                        STAGE="singlecountdown1";
                        client.gamehandler.countdownText="1";
                        client.gamehandler.countTime = chrono::steady_clock::now();
                    }
                }
                else if (STAGE=="singlecountdown1"){
                    client.gamehandler.nextCount=player.Timer(client.gamehandler.countTime, chrono::milliseconds(1000));
                    if (!client.gamehandler.nextCount){
                        STAGE="single_gameplay";
                        client.gamehandler.countdownText="GO";
                        client.gamehandler.countTime = chrono::steady_clock::now();
                    }
                }
                else if (STAGE=="single_gameplay"){
                    client.gamehandler.waveStart=Timer(client.gamehandler.waveStartTime, chrono::milliseconds(5000));
                    if (!client.gamehandler.waveStart && !client.gamehandler.activeWave) {
                        client.gamehandler.nextSpawnTime = chrono::steady_clock::now();
                        client.gamehandler.wave++;
                        
                        if (client.gamehandler.wave<6)client.gamehandler.activeWave=1;
                        else STAGE="single_winner";
                        
                        //cout << "Wave "<< client.gamehandler.wave <<" started" << endl;
                    }
                    
                    if (client.gamehandler.activeWave){
                        for (itWaveData = WaveData[client.gamehandler.wave-1].begin(); itWaveData != WaveData[client.gamehandler.wave-1].end();){
                            if (!Timer(client.gamehandler.nextSpawnTime, chrono::milliseconds(itWaveData->spawntime))){
                                //cout << itWaveData->spawntime << endl;
                                enemyList.push_back(Enemy(r, itWaveData->type, HomePoints[itWaveData->spawnpoint], itWaveData->spawnpoint));
                                itWaveData = WaveData[client.gamehandler.wave-1].erase(itWaveData);
                            }
                            else {
                                itWaveData++;
                            }
                            //cout << itWaveData->spawnpoint << " " << itWaveData->spawntime << " " << itWaveData->type<< endl;
                        }
                        //cout << endl;

                        if (WaveData[client.gamehandler.wave-1].size()==0 && enemyList.size()==0){
                            client.gamehandler.waveStartTime = chrono::steady_clock::now();
                            client.gamehandler.activeWave=false;
                            //cout << "new round" << endl;
                        }
                    }
                    

                    player.gamedt=dt;

                    client.gamehandler.nextCount=player.Timer(client.gamehandler.countTime, chrono::milliseconds(1000));
                    if (!client.gamehandler.nextCount) client.gamehandler.countdownText="0";

                    player.hurtStop=player.Timer(player.hurtTime, chrono::milliseconds(2000));
                    if (!player.hurtStop && player.hurt) player.hurt=0;
                    //cout << player.vel_x << endl;
                    player.coyoteTime=player.Timer(player.jumpTime, chrono::milliseconds(100));
                    player.wallJump=player.Timer(player.wallJumpTime, chrono::milliseconds(300));
                    
                    player.u2=u;
                    player.d2=d;
                    player.l2=l;
                    player.r2=ri;

                    player.b2=b;
                    player.n2=n;
                    if (!player.dead){
                        player.Aim(u, d, l, ri, b);
                        player.SingleShoot(r, n, arrowList);

                        for (int i = 0; i < 10; i++) {
                            player.Move(u, d, l, ri, b, dt/10.);
                            player.Collisions(grid, dt/10.);
                            player.Update(dt/10.);
                            player.MoveThroughWall();
                        }
                        player.HurtAnimation(dt);
                    }

                    for (enemyIterator = enemyList.begin(); enemyIterator != enemyList.end(); enemyIterator++){
                        enemyIterator->InSight(enemyIterator->hitbox, playerPointer->hitbox, grid);
                        for (int i = 0; i < 3; i++){
                            enemyIterator->Move(dt/3., grid);
                            enemyIterator->Collisions(grid, dt/3.);
                            enemyIterator->Update(dt/3.);
                            enemyIterator->MoveThroughWall();
                            //cout << enemyIterator->Proximity(enemyIterator->hitbox, player.hitbox) << endl;
                        }
                        if (Collision(enemyIterator -> hitbox, player.hitbox) && !player.hurt){
                            player.hurt=1;
                            player.hurtTime = chrono::steady_clock::now();
                            player.lives--;
                            player.hurt_i=0;
                            player.vel_y = -(SPEED * 2.1);
                            if (player.vel_x<0)player.vel_x=SPEED;
                            else if (player.vel_x>0)player.vel_x=-SPEED;
                            
                            //cout << "you aaa" << endl;
                        }
                    }

                    

                    client.arrowListMutex.lock();
                    if (arrowList.size() > 0) {
                        for (arrowCount = arrowList.begin(); arrowCount != arrowList.end();) {
                            arrowCount->Movement(dt);
                            if (arrowCount->isWalled == 0) {
                                arrowCount->Collisions(grid, dt);
                                arrowCount->MoveThroughWall(); 
                                if (enemyList.size()>0){
                                    for (enemyIterator = enemyList.begin(); enemyIterator != enemyList.end();){
                                        //cout << enemyIterator->x << endl; 
                                        if (Collision(enemyIterator -> hitbox, arrowCount->hitbox)){
                                            enemyIterator = enemyList.erase(enemyIterator);
                                        }
                                        else {
                                            enemyIterator++;
                                        }
                                    }
                                }
                            }
                            else if (arrowCount->CollectArrow(r, player.hitbox, arrowCount->hitbox) && player.arrowCount < 6){
                                player.arrowCount++;
                                arrowCount = arrowList.erase(arrowCount);
                                continue;
                            }
                            arrowCount++;
                            //vn:
                            //asm("nop");
                        }
                    }
                    client.arrowListMutex.unlock();

                    /*if (chestList.size()>0){
                        for (chestIterator = chestList.begin(); chestIterator != chestList.end();){
                            if (!chestIterator->open && Collision(player.hitbox, chestIterator->hitbox)){
                                chestIterator->open=true;
                                cout << "nekiikki" << endl;
                            }
                            else if (chestIterator->open && Collision(player.hitbox, chestIterator->itemhitbox)){
                                if (chestIterator->item==1) player.arrowCount++;
                                else if (chestIterator->item==2) player.shieldOn=true;
                                else if (chestIterator->item==3) player.wingsOn=true;

                                chestIterator = chestList.erase(chestIterator);
                                continue;
                            }
                            else chestIterator++;
                        }
                    }*/
                    if (player.lives==0 && !player.dead) {
                        player.dead=1;
                        player.deadTime = chrono::steady_clock::now();
                        //STAGE="single_lost";
                    }
                    
                    if (player.dead)player.deadRespawn=player.Timer(player.deadTime, chrono::milliseconds(2000));
                    if (!player.deadRespawn && player.dead) STAGE="single_lost";
                }
                else if (STAGE=="single_winner"){

                }
                else if (STAGE=="single_lost"){

                }
                else if (STAGE=="gameplay"){
                    if (client.gamehandler.gamecommand=="game_ended"){
                        STAGE="endgame_stats";
                    }
                    
                    client.gamehandler.nextCount=player.Timer(client.gamehandler.countTime, chrono::milliseconds(1000));
                    if (!client.gamehandler.nextCount) client.gamehandler.countdownText="0";
                    
                    if (player.pdead==0 && player.dead==1) {
                        //player.DeadAnimation();
                        player.PlayerDead();
                        //cout << "really dead" << endl;
                        player.pdead=1;
                    }

                    player.gamedt=dt;

                    //cout << player.vel_x << endl;
                    player.coyoteTime=player.Timer(player.jumpTime, chrono::milliseconds(100));
                    player.wallJump=player.Timer(player.wallJumpTime, chrono::milliseconds(300));
                    
                    player.u2=u;
                    player.d2=d;
                    player.l2=l;
                    player.r2=ri;

                    player.b2=b;
                    player.n2=n;

                    player.Aim(u, d, l, ri, b);

                    if ((player.kills+player.newkills>=client.gamehandler.gamerounds) && client.clientID==1){
                        player.leaderCommand="game_ended";
                        client.gamehandler.winner=1;
                        client.gamehandler.winnercolor=player.color;
                    }

                    if (!player.b2){
                        player.wingsCounter++;
                        if (player.wingsCounter>47){
                            player.wingsCounter=0;
                        }
                    }
                    else {
                        player.wingsCounter=0;
                    }

                    //player.Shoot(r, n, arrowList);
                    if (client.players.size()>0){
                        for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                            if ((playerIterator -> kills + playerIterator -> newkills>=client.gamehandler.gamerounds) && client.clientID==1){
                                player.leaderCommand="game_ended";
                                client.gamehandler.winner=playerIterator->playerID;
                                client.gamehandler.winnercolor=playerIterator->color;
                            }
                            
                            playerIterator -> Aim(playerIterator -> u2, playerIterator -> d2, playerIterator -> l2, playerIterator -> r2, playerIterator -> b2);
                            
                            //playerIterator -> Shoot(r, playerIterator -> n2, arrowList);
                            if (!playerIterator->b2){
                                playerIterator -> wingsCounter++;
                                if (playerIterator -> wingsCounter>47){
                                    playerIterator -> wingsCounter=0;
                                }
                            }
                            else {
                                playerIterator -> wingsCounter=0;
                            }


                        }
                    }

                    client.setDT(dt);
                    for (int i = 0; i < 10; i++) {
                        player.Move(u, d, l, ri, b, dt/10.);
                        player.Collisions(grid, dt/10.);
                        player.Update(dt/10.);
                        player.MoveThroughWall();

                        
            
                        if (client.players.size()>0){
                            for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                                    playerIterator -> Move(playerIterator -> u2, playerIterator -> d2, playerIterator -> l2, playerIterator -> r2, playerIterator -> b2, dt/10.);
                                    playerIterator -> Collisions(grid, dt/10.);
                                    playerIterator -> Update(dt/10.);
                                    playerIterator -> MoveThroughWall();

                                    
                            
                                //cout << "PlayerID sss:" << playerIterator -> playerID << endl;
                                //cout << playerIterator -> x << " " <<playerIterator -> y << endl;
                                
                            }
                        }
                    }
                    
                    

                    client.arrowListMutex.lock();
                    if (arrowList.size() > 0) {
                        for (arrowCount = arrowList.begin(); arrowCount != arrowList.end();) {
                            arrowCount->Movement(dt);
                            if (arrowCount->isWalled == 0) {
                                arrowCount->Collisions(grid, dt);
                                arrowCount->MoveThroughWall(); 
                                /*if (client.players.size()>0){
                                    for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                                        if (Collision(playerIterator -> hitbox, arrowCount->hitbox) && playerIterator->playerID == arrowCount->playerID){

                                        }
                                        else arrowCount->playerID=0;
                                        
                                        if (Collision(playerIterator -> hitbox, arrowCount->hitbox) && playerIterator->playerID != arrowCount->playerID && !playerIterator->dead){
                                            playerIterator -> dead=1;
                                            cout << "client dead: " << playerIterator -> playerID << endl;
                                            playerIterator -> x=0;
                                            playerIterator -> y=0;
                                            playerIterator -> UpdateHitbox();
                                        }
                                    }
                                }*/
                            }
                            /*else {
                                if (arrowCount->CollectArrow(r, player.hitbox, arrowCount->hitbox) && player.arrowCount < 6){
                                    player.arrowCount++;
                                    arrowCount = arrowList.erase(arrowCount);
                                    continue;
                                }
                                if (client.players.size()>0){
                                    for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                                        if (arrowCount->CollectArrow(r, playerIterator -> hitbox, arrowCount->hitbox) && playerIterator -> arrowCount < 6){
                                            playerIterator -> arrowCount++;
                                            arrowCount = arrowList.erase(arrowCount);
                                            //continue;
                                            goto vn;
                                        }
                                    }
                                }
                            }*/
                            arrowCount++;
                            vn:
                            asm("nop");
                        }
                    }
                    client.arrowListMutex.unlock();
                    
                    if ((client.gamehandler.playersRemaining==1 || client.gamehandler.playersRemaining==0) && !client.gamehandler.preReplayBool){  
                        client.gamehandler.preReplayTime = chrono::steady_clock::now();
                        client.gamehandler.preReplayBool=1;
                        //client.gamehandler.countdownText="GO";
                    }
                    if (client.gamehandler.preReplayBool){
                        client.gamehandler.preReplayCount=player.Timer(client.gamehandler.preReplayTime, chrono::milliseconds(3000));
                        if (client.gamehandler.playersRemaining==0){
                            client.gamehandler.preReplayTime = chrono::steady_clock::now();
                            client.gamehandler.preReplayBool=0;
                            STAGE="pre_replay";
                        }
                        if (!client.gamehandler.preReplayCount){
                            STAGE="replay";
                            client.gamehandler.preReplayBool=0;
                        }
                    }
                }
                else if (STAGE=="pre_replay"){
                    client.gamehandler.preReplayCount=player.Timer(client.gamehandler.preReplayTime, chrono::milliseconds(3000));
                    if (!client.gamehandler.preReplayCount){
                        STAGE="replay";
                        client.gamehandler.countdownText="0";
                    }
                }
                else if (STAGE=="replay"){
                    STAGE="stats";
                }
                else if (STAGE=="stats" || STAGE=="endgame_stats"){
                    if (client.gamehandler.gamecommand=="winner_stats") {
                        //client.Shutdown();
                        STATE="winner_stats";
                    }
                    if (client.gamehandler.gamecommand=="next_round") {
                        string lvlname = "level" + to_string(client.gamehandler.nextlvl) + ".bin";
                        //cout << lvlname << endl;
                        
                        ifstream dat(lvlname, ios::binary);
                        dat.read((char *)&grid, sizeof(grid));
                        dat.read((char *)&spawnPos, sizeof(spawnPos));
                        dat.read((char *)&chestPos, sizeof(chestPos));
                        dat.close();
                        
                        
                        player.x=spawnPos[client.clientID-1][0]-10;
                        player.y=spawnPos[client.clientID-1][1];
                        player.vel_x=0;
                        player.vel_y=0;
                        player.dead=0;
                        player.pdead=0;
                        player.arrowCount=3;
                        player.UpdateHitbox();

                        if (client.players.size()>0){
                            for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                                playerIterator->x=spawnPos[playerIterator->playerID-1][0]-10;
                                playerIterator->y=spawnPos[playerIterator->playerID-1][1];
                                playerIterator->UpdateHitbox();
                            }
                        }

                        STATE="game";
                        STAGE="countdown3";
                        client.gamehandler.countdownText="3";
                        client.gamehandler.countTime = chrono::steady_clock::now();

                        player.leaderCommand="nothing";
                    }
                }
            }
            else {
                if (server.players.size()>0){
                    for (playerIterator = server.players.begin(); playerIterator != server.players.end(); playerIterator++){
                        playerIterator -> Aim(playerIterator -> u2, playerIterator -> d2, playerIterator -> l2, playerIterator -> r2, playerIterator -> b2);
                        server.arrowListMutex.lock();
                        playerIterator -> Shoot(r, playerIterator -> n2, arrowList);
                        server.arrowListMutex.unlock();
                    }
                   
                    
                    for (playerIterator = server.players.begin(); playerIterator != server.players.end(); playerIterator++){
                            for (int i = 0; i < 10; i++){
                                playerIterator -> Move(playerIterator -> u2, playerIterator -> d2, playerIterator -> l2, playerIterator -> r2, playerIterator -> b2, dt/10.);
                                playerIterator -> Collisions(grid, dt/10.);
                                playerIterator -> Update(dt/10.);
                                playerIterator -> MoveThroughWall();
                            }
                    }
                }
                
                if (arrowList.size() > 0) {
                    server.arrowListMutex.lock();
                    for (arrowCount = arrowList.begin(); arrowCount != arrowList.end();) {
                        arrowCount->Movement(dt);
                        if (arrowCount->isWalled == 0) {
                            arrowCount->Collisions(grid, dt);
                            arrowCount->MoveThroughWall();
                            if (server.players.size()>0){
                                for (playerIterator = server.players.begin(); playerIterator != server.players.end(); playerIterator++){
                                    if (Collision(playerIterator -> hitbox, arrowCount->hitbox) && playerIterator->playerID != arrowCount->playerID && playerIterator->playerID != arrowCount->shieldHitID && !playerIterator->dead){
                                        if (!playerIterator->shieldOn){
                                            playerIterator -> dead=1;
                                            playerIterator -> wingsOn=0;
                                            //cout << "client dead: " << playerIterator -> playerID << endl;
                                            if (client.gamehandler.gamemode=="deathmatch"){
                                                if (playerIterator->color == arrowCount->color) {
                                                    if (playerIterator->newkills!=0) playerIterator->newkills--;
                                                    playerIterator->selfkills=1;
                                                }
                                                for (playerIterator2 = server.players.begin(); playerIterator2 != server.players.end(); playerIterator2++)
                                                    if (playerIterator2->playerID==arrowCount->color){
                                                        playerIterator2->newkills++;
                                                        break;
                                                    }
                                            }
                                            /*playerIterator -> x=0;
                                            playerIterator -> y=0;
                                            playerIterator -> UpdateHitbox();*/
                                        }
                                        else {
                                            playerIterator->shieldOn=false;
                                            arrowCount->shieldHitID=playerIterator->playerID;
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            if (server.players.size()>0){
                                for (playerIterator = server.players.begin(); playerIterator != server.players.end(); playerIterator++){
                                    if (arrowCount->CollectArrow(r, playerIterator -> hitbox, arrowCount->hitbox) && playerIterator -> arrowCount < 6){
                                        playerIterator -> arrowCount++;
                                        arrowCount = arrowList.erase(arrowCount);
                                        //continue;
                                        goto vn2;
                                    }
                                }
                            }
                        }
                        arrowCount++;
                        vn2:
                        asm("nop");
                    }
                    server.arrowListMutex.unlock();
                }
                
                server.chestListMutex.lock();
                if (server.gamehandler.gamestatus=="game"){
                    server.gamehandler.nextChest=Timer(server.gamehandler.chestTime, chrono::milliseconds(server.gamehandler.nextChestTime));
                    if (!server.gamehandler.nextChest && server.gamehandler.chestNum>0){
                        int in = rand() % 10 + 1;
                        int i = -1;
                        while (in!=0){
                            i++;
                            if (i>5) i=0;
                            if (server.gamehandler.availableChests[i]==0) in--;
                        }
                        //cout << in <<" "<< i << endl;
                        server.gamehandler.availableChests[i]=1;
                        chestList.push_back(Chest(r, chestPos[i][0], chestPos[i][1]));
                        server.gamehandler.chestNum--;

                        server.gamehandler.nextChestTime = rand() % 3000 + 2000;

                        if (server.gamehandler.chestNum>0) server.gamehandler.chestTime = chrono::steady_clock::now();
                    }
                }


                if (chestList.size()>0){
                    for (chestIterator = chestList.begin(); chestIterator != chestList.end();){
                        if (server.players.size()>0){
                            for (playerIterator = server.players.begin(); playerIterator != server.players.end(); playerIterator++){
                                if (!chestIterator->open && Collision(playerIterator->hitbox, chestIterator->hitbox)){
                                    chestIterator->open=true;
                                }
                                else if (chestIterator->open && Collision(playerIterator->hitbox, chestIterator->itemhitbox)){
                                    if (chestIterator->item==1) {
                                        if (playerIterator->arrowCount>=6) playerIterator->arrowCount=6;
                                        else playerIterator->arrowCount++;
                                    }
                                    else if (chestIterator->item==2) playerIterator->shieldOn=true;
                                    else if (chestIterator->item==3) playerIterator->wingsOn=true;

                                    chestIterator = chestList.erase(chestIterator);
                                    goto vnd;
                                }
                            }
                            chestIterator++;
                            vnd:
                            asm("nop");
                        }
                        else break;
                    }
                }
                server.chestListMutex.unlock();
            }


            
            
        }
        else if (STATE=="winner_stats"){
            
        }
        

        SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // r b g a 213, 140, 86
        SDL_RenderClear(r);

        
        // DRAW HERE
        



        if (STATE=="menu"){
            SDL_RenderCopy(r, menubg, NULL, &menubgrnd);

            if (STAGE!="anim"){
                SDL_RenderCopy(r, button, NULL, &playbuttonRect);
                if (SDL_PointInRect(&mousePoint, &playbuttonRect))SDL_RenderCopy(r, playText2, NULL, &playtextRect);
                else SDL_RenderCopy(r, playText, NULL, &playtextRect);
                
                SDL_RenderCopy(r, button, NULL, &optionsbuttonRect);
                if (SDL_PointInRect(&mousePoint, &optionsbuttonRect)) SDL_RenderCopy(r, optionsText2, NULL, &optionstextRect);
                else SDL_RenderCopy(r, optionsText, NULL, &optionstextRect);
                
                SDL_RenderCopy(r, button, NULL, &quitbuttonRect);
                if (SDL_PointInRect(&mousePoint, &quitbuttonRect)) SDL_RenderCopy(r, quitText2, NULL, &quittextRect);
                else SDL_RenderCopy(r, quitText, NULL, &quittextRect);
                
                SDL_RenderCopy(r, title, NULL, &titleRect);
            }
        }
        else if (STATE=="level_menu"){
            SDL_RenderCopy(r, bg, NULL, &bgrnd);
            SDL_RenderCopy(r, smallboard, NULL, &smallboardRect);

            string winner;
            winner = "LEVELS";
            SDL_Surface *winnerSurface = TTF_RenderText_Solid(AddressSans, winner.c_str(), SDL_Color({252, 176, 64}));
            SDL_Texture *winnerTexture = SDL_CreateTextureFromSurface(r, winnerSurface);
            SDL_FreeSurface(winnerSurface);
            SDL_Rect winnertextRect;
            winnertextRect.y=220;
            SDL_QueryTexture(winnerTexture, NULL, NULL, &winnertextRect.w, &winnertextRect.h);
            winnertextRect.x=WIDTH/2-winnertextRect.w/2;
            SDL_RenderCopy(r, winnerTexture, NULL, &winnertextRect);
            SDL_DestroyTexture(winnerTexture);

            if (availableLevels[0]){
                SDL_RenderCopy(r, smallbutton, NULL, &lvl1buttonRect);
                if (SDL_PointInRect(&mousePoint, &lvl1buttonRect))SDL_RenderCopy(r, text11, NULL, &text1Rect);
                else SDL_RenderCopy(r, text1, NULL, &text1Rect);
            }
            else SDL_RenderCopy(r, lockedbutton, NULL, &lvl1buttonRect);

            if (availableLevels[1]){
                SDL_RenderCopy(r, smallbutton, NULL, &lvl2buttonRect);
                if (SDL_PointInRect(&mousePoint, &lvl2buttonRect))SDL_RenderCopy(r, text22, NULL, &text2Rect);
                else SDL_RenderCopy(r, text2, NULL, &text2Rect);
            }
            else SDL_RenderCopy(r, lockedbutton, NULL, &lvl2buttonRect);

            if (availableLevels[2]){
                SDL_RenderCopy(r, smallbutton, NULL, &lvl3buttonRect);
                if (SDL_PointInRect(&mousePoint, &lvl3buttonRect))SDL_RenderCopy(r, text33, NULL, &text3Rect);
                else SDL_RenderCopy(r, text3, NULL, &text3Rect);
            }
            else SDL_RenderCopy(r, lockedbutton, NULL, &lvl3buttonRect);

            if (availableLevels[3]){
                SDL_RenderCopy(r, smallbutton, NULL, &lvl4buttonRect);
                if (SDL_PointInRect(&mousePoint, &lvl4buttonRect))SDL_RenderCopy(r, text44, NULL, &text4Rect);
                else SDL_RenderCopy(r, text4, NULL, &text4Rect);
            }
            else SDL_RenderCopy(r, lockedbutton, NULL, &lvl4buttonRect);

            if (availableLevels[4]){
                SDL_RenderCopy(r, smallbutton, NULL, &lvl5buttonRect);
                if (SDL_PointInRect(&mousePoint, &lvl5buttonRect))SDL_RenderCopy(r, text55, NULL, &text5Rect);
                else SDL_RenderCopy(r, text5, NULL, &text5Rect);
            }
            else SDL_RenderCopy(r, lockedbutton, NULL, &lvl5buttonRect);

            /*SDL_RenderCopy(r, lockedbutton, NULL, &lvl2buttonRect);
            SDL_RenderCopy(r, lockedbutton, NULL, &lvl3buttonRect);
            SDL_RenderCopy(r, lockedbutton, NULL, &lvl4buttonRect);
            SDL_RenderCopy(r, lockedbutton, NULL, &lvl5buttonRect);*/
        }
        else if (STATE=="options"){
            SDL_RenderCopy(r, menubg, NULL, &menubgrnd);
            if (STAGE!="anim"){
                SDL_RenderCopy(r, board, NULL, &boardRect);
            
                

                SDL_RenderCopy(r, fullscreenoptionText, NULL, &fullscreenoptiontextRect);
                SDL_RenderCopy(r, smallbutton, NULL, &onoffbuttonRect);
                
                onoptiontextRect.y = 169;
                offoptiontextRect.y = 169;
                if (!fullscreen){
                    if (SDL_PointInRect(&mousePoint, &onoffbuttonRect)) SDL_RenderCopy(r, offoptionText2, NULL, &offoptiontextRect);
                    else SDL_RenderCopy(r, offoptionText, NULL, &offoptiontextRect);
                }
                else {
                    if (SDL_PointInRect(&mousePoint, &onoffbuttonRect)) SDL_RenderCopy(r, onoptionText2, NULL, &onoptiontextRect);
                    else SDL_RenderCopy(r, onoptionText, NULL, &onoptiontextRect);
                }
                
                onoptiontextRect.y = 346;
                offoptiontextRect.y = 346;
                SDL_RenderCopy(r, volumeoptionText, NULL, &volumeoptiontextRect);
                SDL_RenderCopy(r, smallbutton, NULL, &onoffbuttonRect2);
                if (!mouseaim){
                    if (SDL_PointInRect(&mousePoint, &onoffbuttonRect2)) SDL_RenderCopy(r, offoptionText2, NULL, &offoptiontextRect);
                    else SDL_RenderCopy(r, offoptionText, NULL, &offoptiontextRect);
                }
                else {
                    if (SDL_PointInRect(&mousePoint, &onoffbuttonRect2)) SDL_RenderCopy(r, onoptionText2, NULL, &onoptiontextRect);
                    else SDL_RenderCopy(r, onoptionText, NULL, &onoptiontextRect);
                }

                if (changingIP) SDL_SetRenderDrawColor(r, 108, 76, 52, 255);
                else SDL_SetRenderDrawColor(r, 87, 61, 41, 255);
                SDL_RenderFillRect(r, &serverfieldRect);
                SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
                
                SDL_Surface *addressSurface = TTF_RenderText_Solid(AddressSans, ipaddress, SDL_Color({252, 176, 64}));
                SDL_Texture *adressTexture = SDL_CreateTextureFromSurface(r, addressSurface);
                SDL_FreeSurface(addressSurface);
                SDL_QueryTexture(adressTexture, NULL, NULL, &ipaddresstextRect.w, &ipaddresstextRect.h);
                ipaddresstextRect.x=WIDTH/2-ipaddresstextRect.w/2;
                SDL_RenderCopy(r, adressTexture, NULL, &ipaddresstextRect);
                SDL_DestroyTexture(adressTexture);
                
                SDL_RenderCopy(r, serveroptionText, NULL, &serveroptiontextRect);
            }
        }
        else if (STATE=="playstyle"){
            //SDL_RenderCopy(r, bg, NULL, &bgrnd);
            SDL_RenderCopy(r, menubg, NULL, &menubgrnd);

            if (STAGE!="anim"){
                SDL_RenderCopy(r, playermodeText, NULL, &playermodeRect);

                SDL_RenderCopy(r, bigbutton, NULL, &bigbuttonRect);
                if (SDL_PointInRect(&mousePoint, &bigbuttonRect))SDL_RenderCopy(r, single2Text, NULL, &singletextRect);
                else SDL_RenderCopy(r, singleText, NULL, &singletextRect);

                SDL_RenderCopy(r, bigbutton, NULL, &bigbutton2Rect);
                if (SDL_PointInRect(&mousePoint, &bigbutton2Rect))SDL_RenderCopy(r, multi2Text, NULL, &multitextRect);
                else SDL_RenderCopy(r, multiText, NULL, &multitextRect);
            }
        }
        else if (STATE=="multiplayer_searching"){
            SDL_RenderCopy(r, bg, NULL, &bgrnd);
            SDL_RenderCopy(r, loadingText, NULL, &loadingtextRect);
        }
        else if (STATE=="multiplayer_menu"){
            SDL_RenderCopy(r, bg, NULL, &bgrnd);

            SDL_RenderCopy(r, board, NULL, &boardRect);

            if (!player.playerReady) SDL_RenderCopy(r, chooseCharText, NULL, &choosechartextRect);
            else SDL_RenderCopy(r, waitingPlayersText, NULL, &waitingplayerstextRect);
                

            SDL_Rect playerRect = {-99, 200, 172, 300};
            
            for (int i=0; i<4; i++){
            
                //cout << "PlayerID: " << client.playerPointer -> playerID << endl;
                
                int currentColor;
                
                if (!isServer){
                    if (client.clientID == i+1){
                        currentColor=player.color;
                        //cout << player.color;
                    } 
                    else if (client.players.size()>0){
                        for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                            if (playerIterator->playerID == i+1 && playerIterator != client.players.end()) {
                                currentColor=playerIterator->color;
                                //cout << playerIterator->color;
                                break;
                            }
                            else currentColor=0;
                        }
                    }
                    else currentColor=0;
                    //SDL_SetRenderDrawColor(r, playerColors[currentColor][0], playerColors[currentColor][1], playerColors[currentColor][2], 255);
                    SDL_SetRenderDrawColor(r, playerColors[currentColor][0], playerColors[currentColor][1], playerColors[currentColor][2], 255);
                }
                else {
                   if (server.players.size()>0){
                        for (playerIterator = server.players.begin(); playerIterator != server.players.end(); playerIterator++){
                            if (playerIterator->playerID == i+1 && playerIterator != client.players.end()) {
                                currentColor=playerIterator->color;
                                break;
                            }
                            else currentColor=0;
                        }
                    }
                    else currentColor=0;
                    SDL_SetRenderDrawColor(r, 234, 123, 64, 255);
                }


                
                playerRect.x=playerRect.x + 210;
                SDL_RenderFillRect(r, &playerRect);


                /*textRect.x = playerRect.x + 62;
                textRect.y = 510;
                SDL_QueryTexture(playerText[i], NULL, NULL, &textRect.w, &textRect.h);*/
                
                //SDL_RenderCopy(r, playerText[i], NULL, &playertextRects[i]);
                
            }
            //cout << endl;
            SDL_RenderCopy(r, p1text, NULL, &p1textRect);
            SDL_RenderCopy(r, p2text, NULL, &p2textRect);
            SDL_RenderCopy(r, p3text, NULL, &p3textRect);
            SDL_RenderCopy(r, p4text, NULL, &p4textRect);

            arrowbuttonRect.x = 167 + (client.clientID-1)*210;
            SDL_RenderCopy(r, arrowbutton, NULL, &arrowbuttonRect);
            
            
            if (!player.playerReady){
                SDL_RenderCopy(r, button, NULL, &confirmbuttonRect);
                if (SDL_PointInRect(&mousePoint, &confirmbuttonRect))SDL_RenderCopy(r, confirmText2, NULL, &confirmtextRect);
                else SDL_RenderCopy(r, confirmText, NULL, &confirmtextRect);
            }

            
        }
        else if (STATE=="choose_gamemode"){
            SDL_RenderCopy(r, bg, NULL, &bgrnd);

            SDL_RenderCopy(r, board, NULL, &boardRect);

            SDL_RenderCopy(r, gamemodeText, NULL, &gamemodetextRect);
            SDL_RenderCopy(r, gameroundsText, NULL, &gameroundstextRect);


            if (client.gamehandler.gamemode=="deathmatch") SDL_RenderCopy(r, deathmatchText, NULL, &deathmatchtextRect);
            else if (client.gamehandler.gamemode=="lastmanstanding") SDL_RenderCopy(r, lastmanstandingText, NULL, &lastmanstandingtextRect);

            if (client.gamehandler.gamerounds==5) SDL_RenderCopy(r, rounds5Text, NULL, &rounds5textRect);
            else if (client.gamehandler.gamerounds==10) SDL_RenderCopy(r, rounds10Text, NULL, &rounds10textRect);
            else if (client.gamehandler.gamerounds==15) SDL_RenderCopy(r, rounds15Text, NULL, &rounds15textRect);
            else if (client.gamehandler.gamerounds==20) SDL_RenderCopy(r, rounds20Text, NULL, &rounds20textRect);
            
            
            
            if (client.clientID==1){
                 if (client.gamehandler.gamemodeChanging==1) gamemodepickertextRect.y = 100;
                else if (client.gamehandler.gamemodeChanging==2) gamemodepickertextRect.y = 350;
                SDL_RenderCopy(r, gamemodepickerText, NULL, &gamemodepickertextRect);

                SDL_RenderCopy(r, button, NULL, &confirmbuttonRect);
                if (SDL_PointInRect(&mousePoint, &confirmbuttonRect)){
                    SDL_RenderCopy(r, startGameText2, NULL, &startgametextRect);
                }
                else {
                    SDL_RenderCopy(r, startGameText, NULL, &startgametextRect);
                }
            }

        }
        else if (STATE=="game"){
            SDL_RenderCopy(r, bg, NULL, &bgrnd);
            
            for (int i = 0; i < 32; i++) {
                for (int j = 0; j < 24; j++) {
                    if (grid[i][j] !=0) {
                        blockrect.x = ((grid[i][j]-1)%4)*10;
                        blockrect.y = (int)((grid[i][j]-1)/4)*10;

                        tilerect.x = GRIDSIZE * i;
                        tilerect.y = GRIDSIZE * j;
                        tilerect.w = GRIDSIZE;
                        tilerect.h = GRIDSIZE;
                        SDL_RenderCopy(r, tile, &blockrect, &tilerect);
                    }
                }
            }

            if (!isServer) {
                player.Draw(r);
                if (client.players.size()>0){
                    for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                        playerIterator->Draw(r);
                    }
                }
            }
            else {
                if (server.players.size()>0){
                    for (playerIterator = server.players.begin(); playerIterator != server.players.end(); playerIterator++){
                        playerIterator->Draw(r);
                    }
                }
            }
            
            if (!isServer){
                if (enemyList.size()>0){
                    for (enemyIterator = enemyList.begin(); enemyIterator != enemyList.end(); enemyIterator++){
                        enemyIterator->Draw(r);
                    }
                }
                
            }
            
            
            

            if (isServer) server.arrowListMutex.lock();
            else client.arrowListMutex.lock();
            if (arrowList.size() > 0) {
                for (arrowCount = arrowList.begin(); arrowCount != arrowList.end(); arrowCount++) {
                    arrowCount->Draw(r);
                }
            }
            if (isServer) server.arrowListMutex.unlock();
            else client.arrowListMutex.unlock();


            if (isServer) server.chestListMutex.lock();
            else client.chestListMutex.lock();
            if (chestList.size() > 0) {
                for (chestIterator = chestList.begin(); chestIterator != chestList.end(); chestIterator++) {
                    chestIterator->Draw(r);
                }
            }
            if (isServer) server.chestListMutex.unlock();
            else client.chestListMutex.unlock();



            if (client.gamehandler.countdownText=="3") SDL_RenderCopy(r, count3Text, NULL, &count3textRect);
            else if (client.gamehandler.countdownText=="2")SDL_RenderCopy(r, count2Text, NULL, &count2textRect);
            else if (client.gamehandler.countdownText=="1")SDL_RenderCopy(r, count1Text, NULL, &count1textRect);
            else if (client.gamehandler.countdownText=="GO")SDL_RenderCopy(r, countgoText, NULL, &countgotextRect);

            if (STAGE=="stats" || STAGE=="endgame_stats"){
                SDL_RenderCopy(r, smallboard, NULL, &smallboardRect);

                int playersCount = client.players.size() + 1;

                if (playersCount==2)skullRect.y=337;
                else if (playersCount==3)skullRect.y=307;
                else if (playersCount==4)skullRect.y=278;

                for (int i=0; i<playersCount; i++){
                    if (client.gamehandler.gamerounds==5)skullRect.x=458;
                    else if (client.gamehandler.gamerounds==10)skullRect.x=363;
                    else if (client.gamehandler.gamerounds==15)skullRect.x=268;
                    else if (client.gamehandler.gamerounds==20)skullRect.x=173;
                    
                    bool onTheEnd=0;

                    if (client.players.size()>0){
                        for (playerIterator = client.players.begin(); playerIterator != client.players.end(); playerIterator++){
                            if (playerIterator->playerID == i+1) break;
                        }
                        if (playerIterator == client.players.end()) onTheEnd=1;
                    }
                    for (int j=0; j<client.gamehandler.gamerounds; j++){
                        if (client.gamehandler.gamemode=="deathmatch"){
                            if (!onTheEnd){
                                if (j<playerIterator->kills)SDL_SetTextureColorMod(skull, 255, 255, 255);
                                else if (j<(playerIterator->kills+playerIterator->newkills-playerIterator->selfkills))SDL_SetTextureColorMod(skull, 255, 230, 128);
                                else if (j<(playerIterator->kills+playerIterator->newkills))SDL_SetTextureColorMod(skull, 195, 81, 58);
                                else SDL_SetTextureColorMod(skull, 0, 0, 0);
                            }
                            else {
                                if (j<player.kills)SDL_SetTextureColorMod(skull, 255, 255, 255);
                                else if (j<(player.kills+player.newkills-player.selfkills))SDL_SetTextureColorMod(skull, 255, 230, 128);
                                else if (j<(player.kills+player.newkills))SDL_SetTextureColorMod(skull, 195, 81, 58);
                                else SDL_SetTextureColorMod(skull, 0, 0, 0);
                            }

                            SDL_RenderCopy(r, skull, NULL, &skullRect);
                            skullRect.x+=skullRect.w+8;
                        }
                        else if (client.gamehandler.gamemode=="lastmanstanding"){
                            if (!onTheEnd){
                                if (j<playerIterator->kills)SDL_SetTextureColorMod(coin, 255, 255, 255);
                                else if (j<(playerIterator->kills+playerIterator->newkills-playerIterator->selfkills))SDL_SetTextureColorMod(coin, 255, 230, 128);
                                else if (j<(playerIterator->kills+playerIterator->newkills))SDL_SetTextureColorMod(coin, 195, 81, 58);
                                else SDL_SetTextureColorMod(coin, 0, 0, 0);
                            }
                            else {
                                if (j<player.kills)SDL_SetTextureColorMod(coin, 255, 255, 255);
                                else if (j<(player.kills+player.newkills-player.selfkills))SDL_SetTextureColorMod(coin, 255, 230, 128);
                                else if (j<(player.kills+player.newkills))SDL_SetTextureColorMod(coin, 195, 81, 58);
                                else SDL_SetTextureColorMod(coin, 0, 0, 0);
                            }

                            SDL_RenderCopy(r, coin, NULL, &skullRect);
                            skullRect.x+=skullRect.w+8;
                        }
                    }
                    skullRect.y+=skullRect.h+30;
                }

                //if (client.gamehandler.gamerounds==5)p1textRect.x=99;
                if (client.gamehandler.gamerounds==5)p1textRect.x=384;
                else if (client.gamehandler.gamerounds==10)p1textRect.x=289;
                else if (client.gamehandler.gamerounds==15)p1textRect.x=194;
                else if (client.gamehandler.gamerounds==20)p1textRect.x=99;

                if (playersCount==2)p1textRect.y=330;
                else if (playersCount==3)p1textRect.y=300;
                else if (playersCount==4)p1textRect.y=271;
                
                


                p2textRect.x=p1textRect.x;
                p2textRect.y=p1textRect.y+(skullRect.h+30);
                p3textRect.x=p1textRect.x;
                p3textRect.y=p1textRect.y+2*(skullRect.h+30);
                p4textRect.x=p1textRect.x;
                p4textRect.y=p1textRect.y+3*(skullRect.h+30);
                SDL_RenderCopy(r, p1text, NULL, &p1textRect);
                SDL_RenderCopy(r, p2text, NULL, &p2textRect);
                if (playersCount==3 || playersCount==4)SDL_RenderCopy(r, p3text, NULL, &p3textRect);
                if (playersCount==4)SDL_RenderCopy(r, p4text, NULL, &p4textRect);
                
                if (client.clientID==1){
                    
                    SDL_RenderCopy(r, button, NULL, &continuebuttonRect);
                    if (SDL_PointInRect(&mousePoint, &continuebuttonRect)){
                        SDL_RenderCopy(r, continueText2, NULL, &continuetextRect);
                    }
                    else {
                        SDL_RenderCopy(r, continueText, NULL, &continuetextRect);
                    }
                }
            }
            else if (STAGE=="single_winner"){
                SDL_RenderCopy(r, smallboard, NULL, &smallboardRect);

                string winner;
                winner = "LEVEL " + to_string(client.gamehandler.level) + " COMPLETE";
                SDL_Surface *winnerSurface = TTF_RenderText_Solid(AddressSans, winner.c_str(), SDL_Color({252, 176, 64}));
                SDL_Texture *winnerTexture = SDL_CreateTextureFromSurface(r, winnerSurface);
                SDL_FreeSurface(winnerSurface);
                SDL_Rect winnertextRect;
                winnertextRect.y=300;
                SDL_QueryTexture(winnerTexture, NULL, NULL, &winnertextRect.w, &winnertextRect.h);
                winnertextRect.x=WIDTH/2-winnertextRect.w/2;
                SDL_RenderCopy(r, winnerTexture, NULL, &winnertextRect);
                SDL_DestroyTexture(winnerTexture);

                
                
                SDL_RenderCopy(r, button, NULL, &nextbuttonRect);
                if (SDL_PointInRect(&mousePoint, &nextbuttonRect)){
                    SDL_RenderCopy(r, nextText2, NULL, &nexttextRect);
                }
                else {
                    SDL_RenderCopy(r, nextText, NULL, &nexttextRect);
                }
            }
            else if (STAGE=="single_lost"){
                SDL_RenderCopy(r, smallboard, NULL, &smallboardRect);

                string winner;
                winner = "YOU LOST";
                SDL_Surface *winnerSurface = TTF_RenderText_Solid(AddressSans, winner.c_str(), SDL_Color({252, 176, 64}));
                SDL_Texture *winnerTexture = SDL_CreateTextureFromSurface(r, winnerSurface);
                SDL_FreeSurface(winnerSurface);
                SDL_Rect winnertextRect;
                winnertextRect.y=300;
                SDL_QueryTexture(winnerTexture, NULL, NULL, &winnertextRect.w, &winnertextRect.h);
                winnertextRect.x=WIDTH/2-winnertextRect.w/2;
                SDL_RenderCopy(r, winnerTexture, NULL, &winnertextRect);
                SDL_DestroyTexture(winnerTexture);

                
                
                SDL_RenderCopy(r, button, NULL, &retrybuttonRect);
                if (SDL_PointInRect(&mousePoint, &retrybuttonRect)){
                    SDL_RenderCopy(r, retryText2, NULL, &retrytextRect);
                }
                else {
                    SDL_RenderCopy(r, retryText, NULL, &retrytextRect);
                }
            }

            if (!isServer && STAGE=="single_gameplay"){
                SDL_Rect gemRect;
                gemRect.x=10;
                gemRect.y=10;
                gemRect.w=28;
                gemRect.h=40;
                for (int i=0; i<player.lives; i++){
                    SDL_RenderCopy(r, gem, NULL, &gemRect);
                    gemRect.x+=gemRect.w+10;
                }
                
            }
            
        }
        else if (STATE=="winner_stats") {
            SDL_RenderCopy(r, bg, NULL, &bgrnd);

            SDL_RenderCopy(r, board, NULL, &boardRect);

            string winner;
            if (client.gamehandler.winner==client.clientID) winner = "YOU WON!";
            else winner = "PLAYER " + to_string(client.gamehandler.winner) + " WON";
            SDL_Surface *winnerSurface = TTF_RenderText_Solid(AddressSans, winner.c_str(), SDL_Color({252, 176, 64}));
            SDL_Texture *winnerTexture = SDL_CreateTextureFromSurface(r, winnerSurface);
            SDL_FreeSurface(winnerSurface);
            SDL_QueryTexture(winnerTexture, NULL, NULL, &winnertextRect.w, &winnertextRect.h);
            winnertextRect.x=WIDTH/2-winnertextRect.w/2;
            SDL_RenderCopy(r, winnerTexture, NULL, &winnertextRect);
            SDL_DestroyTexture(winnerTexture);

            SDL_RenderCopy(r, bigbutton, NULL, &bigbuttonstatsRect);
            if (client.gamehandler.winnercolor==1) SDL_RenderCopy(r, redplayer, &playerstatsRect, &playerstats2Rect);
            else if (client.gamehandler.winnercolor==2) SDL_RenderCopy(r, greenplayer, &playerstatsRect, &playerstats2Rect);
            else if (client.gamehandler.winnercolor==3) SDL_RenderCopy(r, blueplayer, &playerstatsRect, &playerstats2Rect);
            else if (client.gamehandler.winnercolor==4) SDL_RenderCopy(r, orangeplayer, &playerstatsRect, &playerstats2Rect);
            SDL_RenderCopy(r, button, NULL, &menubuttonstatsRect);
            if (SDL_PointInRect(&mousePoint, &confirmbuttonRect)){
                SDL_RenderCopy(r, backToMenuText2, NULL, &backtomenutextRect);
            }
            else {
                SDL_RenderCopy(r, backToMenuText, NULL, &backtomenutextRect);
            }

            
        }
        // PRESENT RENDERED IMAGE
        SDL_RenderPresent(r);
    }

    //SDL_DestroyTexture(textTexture);
    
    server.CleanUp();

    if (isServer){

    }
    else {
        client.Shutdown();
    }
    
    SDL_DestroyTexture(img);

    TTF_Quit();
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 0;
}