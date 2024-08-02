#pragma once
/*#define WIDTH 1024
#define HEIGHT 768
#define SPEED 300*/

int WIDTH = 1024;
int HEIGHT = 768;
float SPEED = 300;
int GRIDSIZE = 32;
float FACTOR = 1;

//#define GRAVITY 200
#define SPRITE_FRAMES 24
#define SPRITE_SIZE 48
#define FRAMERATE 144
#define DISTANCE 50
//#define GRIDSIZE 32


#define DEFAULT_PORT "27015"
#define PORT 8080
#define DEFAULT_BUFLEN 65536

//#include <Client.cpp>

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

#define readBuff(buff, offset, a)         \
    memcpy(&a, buff + offset, sizeof(a)); \
    offset += sizeof(a);

#define writeBuff(buff, offset, a)        \
    memcpy(&buff[offset], &a, sizeof(a)); \
    offset += sizeof(a);

std::string STATE="menu";
std::string STAGE="menu";

int playerColors[5][3] = {
    {0, 0, 0},
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {255, 165, 0}
};

std::string availableGamemodes[2] = {"deathmatch", "lastmanstanding"};

int availableGamemodeRounds[2][3] = {
    {10, 15, 20},
    {5, 10, 15}
};


class Chest {
    public:
    float x, y;
    
    float vel_x, vel_y;

    bool open;
    int item;

    SDL_FRect hitbox;
    SDL_FRect itemhitbox;
    SDL_Rect ogitemhitbox;

    Chest(SDL_Renderer *r, float nx, float ny);
    Chest(float x1, float y1, bool open1, int item1);
    void Draw(SDL_Renderer *r);
    //void Movement(float dt);
    //void Collisions(int grid[32][24], float dt);
};


class Arrow {
    public:
    float x, y;
    
    float vel_x, vel_y;

    int arrowID;
    int playerID;
    int color;
    float distance;
    int angle;
    float currentangle;

    bool isWalled;
    bool throughWall=false;

    int shieldHitID=0;

    SDL_FRect hitbox;
    SDL_FRect hitbox2;
    

    Arrow(SDL_Renderer *r, SDL_FRect playerHitbox, int aimingAngle, int ID, int nID);
    Arrow(int arrowID1, int playerID1, int color1, bool isWalled1, float x1, float y1, float vel_x1, float vel_y1);
    void Draw(SDL_Renderer *r);
    void Movement(float dt);
    void Collisions(int grid[32][24], float dt);
    bool CollectArrow(SDL_Renderer *r, SDL_FRect a, SDL_FRect b);
    void MoveThroughWall();
};

class GameHandler {
    public:
    int nextlvl=2;

    std::string gamestatus="no_game";

    bool allPlayersReady;
    int availableColors[4] = {1, 2, 3, 4};
    std::string prevgamecommand = "nothing";
    std::string gamecommand = "pre_game";
    std::chrono::steady_clock::time_point countTime;
    bool nextCount=0;
    std::string countdownText="0";

    std::chrono::steady_clock::time_point chestTime;
    bool nextChest = 1;
    bool availableChests[6] = {0, 0, 0, 0, 0, 0};
    int chestNum = 6;
    int nextChestTime=6000;
    
    std::string gamemode;
    int gamerounds=10;
    int gamemode_index=0;
    int gamerounds_index=1;
    int gamemodeChanging=1;

    int newIDforArrow=1;
    int playersRemaining;
    bool LMSbool=0;
    bool preReplayBool=0, preReplayCount=0;
    std::chrono::steady_clock::time_point preReplayTime;
    
    int winner=1;
    int winnercolor=1;

    int levelStarter=0;
    int level=1;
    int wave=0;
    bool waveStart=1;
    bool activeWave=0;
    std::chrono::steady_clock::time_point waveStartTime;
    std::chrono::steady_clock::time_point nextSpawnTime;

    GameHandler();

};

class Enemy {
    public:
    float x, y;
    float vel_x, vel_y;
    float top_vel_x;

    std::string type;

    float acx, acy, bcx, bcy;

    bool facingRight;
    bool isGrounded, rightWalled, leftWalled;
    bool throughWall;

    SDL_FRect hitbox, hitbox2;

    float angle, angle2, proximity, proximity2;
    float targetX, targetY;
    bool targetFound=0;
    bool pis;
    int s=75;

    Enemy(SDL_Renderer *r, std::string typ, SDL_Point coord, int dir);
    void Draw(SDL_Renderer *r);

    void Move(float dt, int grid[32][24]);
    void MoveThroughWall();
    float Velocity (float top_vel_x, float vel_x, float dt);
    void Update(float dt);
    void UpdateHitbox();
    void Proximity(SDL_FRect a, SDL_FRect b);
    float Proximity(SDL_Point a);
    void InSight(SDL_FRect a, SDL_FRect b, int grid[32][24]);
    bool InSight(SDL_FRect a, SDL_Point b, int grid[32][24]);

    void Collisions(int grid[32][24], float dt);
};

class Player {
    public:
    bool status;
    int playerID;
    
    float x, y;
    
    float vel_x, vel_y;
    float top_vel_x, top_vel_y;
    
    bool u2, d2, l2, r2, b2, n2;

    std::string leaderCommand;

    float gamedt;
    bool active;
    bool dead, pdead;
    bool hurt=0;
    bool hurtStop=1;
    std::chrono::steady_clock::time_point hurtTime;
    int hurt_i=0;
    int lives=5;
    std::chrono::steady_clock::time_point deadTime;
    bool deadRespawn=1;

    bool shieldOn, wingsOn;
    int wingsCounter;
    
    float running_i=0;

    bool facingRight;
    bool isGrounded, rightWalled, leftWalled;
    bool coyoteTime, wallJump;
    bool throughWall;
    bool aiming;
    int aimingAngle;
    bool shootPressed;
    std::chrono::steady_clock::time_point jumpTime, wallJumpTime, releaseTime;

    bool leftPressed, rightPressed, upPressed, downPressed;

    int arrowCount;
    
    SDL_FRect hitbox, hitbox2;
    SDL_FRect arrow;

    int color;
    bool playerReady;

    int kills=0, newkills=0, selfkills=0;

    Player(SDL_Renderer *r, int clientID);
    void Draw(SDL_Renderer *r);
    
    void Move(bool u, bool d, bool l, bool r, bool b, float dt);
    void MoveThroughWall();
    float Velocity (float top_vel_x, float vel_x, float dt);
    void Update(float dt);
    void UpdateHitbox();

    void Collisions(int grid[32][24], float dt);
    void Aim(bool u, bool d, bool l, bool r, bool b);
    void Shoot(SDL_Renderer *r, bool n, std::vector<Arrow>& arrowList);
    void SingleShoot(SDL_Renderer *r, bool n, std::vector<Arrow>& arrowList);

    void ChangeColor(bool l, bool r, int availableColors[]);
    void ChangeGamemode(bool l, bool r, bool u, bool d, GameHandler &gamehandler);

    void PlayerDead();

    void HurtAnimation(float dt);
    
    bool Timer(const std::chrono::time_point<std::chrono::steady_clock>& timestamp, std::chrono::milliseconds duration);
};




class Client {
    
    float dt;
    WSADATA wsaData;
    
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    const char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int riResult;
    int recvbuflen = DEFAULT_BUFLEN;
    
    
    
    std::string endToken="";
    
    
    
    public:
    std::string server_name = "127.0.0.1";
    GameHandler gamehandler;
    
    std::mutex arrowListMutex;
    std::mutex chestListMutex;
    std::mutex enemyListMutex;

    SOCKET ConnectSocket = INVALID_SOCKET;

    char buff[DEFAULT_BUFLEN];
    uint32_t offset;
    int clientID = 0;
    std::string str;

    int noConnection;

    Player *playerPointer;

    Player *tmpPlayerPnt;

    SDL_Renderer *rendererPnt;

    std::vector<Player> players;
    int tryConnecting();
    int Shutdown();
    int DataSending();
    int DataReceiving();
    void cleanUp();
    void InfoToServer(Player *player);
    void setDT(float ndt) {dt=ndt;}
};


class Server {

    
    WSADATA wsaData;
    //int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;

    
    //std::vector<Player> playerList;
    //std::vector <Player> :: iterator playerIterator;

    std::mutex playerListMutex;
    
    std::mutex socketMutex;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    //char recvbuf[DEFAULT_BUFLEN];
    //int recvbuflen = DEFAULT_BUFLEN;

    int IDs[4]={0, 0, 0, 0};
    std::string Data[4] = {"0", "0", "0", "0"};

public:

    GameHandler gamehandler;
    
    std::mutex arrowListMutex;
    std::mutex chestListMutex;

    std::vector<Player> players;
    std::vector<SOCKET> clientSockets;
    
    SDL_Renderer *rendererPnt;
    
    int CreateSocket();
    void HandleClient(SOCKET clientSocket, int clientID);
    void StartListening();
    void Broadcast();
    void CleanUp();
};

struct EnemyData {
    int spawnpoint;
    int spawntime;
    std::string type;
};

std::vector <Arrow> arrowList;
std::vector <Player> :: iterator playerIterator;
std::vector <Player> :: iterator playerIterator2;
std::vector <Arrow> :: iterator arrowCount;

std::vector <Chest> chestList;
std::vector <Chest> :: iterator chestIterator;

std::vector <Enemy> enemyList;
std::vector <Enemy> :: iterator enemyIterator;

Client *clientPointer;
Server *serverPointer;

int (*gridPnt)[24];
int (*spPnt)[2];
int (*cpPnt)[2];
Player *playerPointer;
SDL_Renderer *rendererPnt;

std::vector <SDL_Point> HomePoints;
std::vector <SDL_Point> :: iterator hpIterator;

std::vector<EnemyData> WaveData[5];
std::vector<EnemyData> ::  iterator itWaveData;