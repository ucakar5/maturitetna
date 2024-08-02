#pragma once
#define WIN32_LEAN_AND_MEAN

#include <iostream>
/*
#include <winsock2.h>

#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>

#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
*/
#include <Game.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib

using namespace std;

#define PORT 8080




int Client::tryConnecting(){
    noConnection=0;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        noConnection=1;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(server_name.c_str(), DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        noConnection=1;
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET)
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            noConnection=1;
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket != INVALID_SOCKET){
        recv(ConnectSocket, recvbuf, recvbuflen, 0);
        std::string tmpString = recvbuf;
        if (tmpString == "server_full"){
            ConnectSocket=INVALID_SOCKET;
        }
        else if (tmpString.substr(0, 9) == "connected"){
            std::cout << "Connected to server successfully, socket: " << ConnectSocket <<std::endl;
            clientID=stoi(tmpString.substr(9, 1));
            std::cout << clientID << std::endl;
            playerPointer->color=clientID;

            if (clientID>1){
                for (int i=1; i<clientID; i++){
                    players.push_back(Player(rendererPnt, i));
                }
            }
        }
    }

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        closesocket(ConnectSocket);
        WSACleanup();
        noConnection=1;
        return 1;
    }
    std::thread(&Client::DataSending, this).detach();
    std::thread(&Client::DataReceiving, this).detach();
    noConnection=2;
    return 0;
}

int Client::Shutdown(){
    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    return 0;

    


    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0)
        printf("Bytes received: %d\n", iResult);
    else if (iResult == 0)
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());
    
    return iResult;
}

int Client::DataSending(){
    str = "zzz";
    do {   
        InfoToServer(playerPointer);
        iResult = send(ConnectSocket, buff, offset, 0);

        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    } while (str != "end");
    //cout << "sending zaprt" << endl;
    return 0;
}

int Client::DataReceiving(){
    do
    {
        riResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        
        uint32_t offset = 0;
        
        int playerCount, playerID;
        int arrowsCounter, chestsCounter;
        bool status;
        

        string command;
        std::vector <Player> :: iterator playerIterator;

        readBuff(recvbuf, offset, command);
        
        
        
        if (command=="data"){
            readBuff(recvbuf, offset, gamehandler.gamecommand);
            readBuff(recvbuf, offset, gamehandler.gamemode);
            readBuff(recvbuf, offset, gamehandler.gamerounds);
            readBuff(recvbuf, offset, gamehandler.winner);
            readBuff(recvbuf, offset, gamehandler.winnercolor);

            readBuff(recvbuf, offset, gamehandler.nextlvl);
            //std::cout << gamehandler.round << std::endl;
            //readBuff(recvbuf, offset, playerCount);

            //std::cout << playerCount << " " << playerID << " " << x2 << " " << y2<< " " << vel_x2 << " " << vel_y2 << std::endl;
            for (int i=1; i<=4; i++){
                readBuff(recvbuf, offset, playerID);
                for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++)
                        if (playerIterator->playerID == playerID) break;
                
                readBuff(recvbuf, offset, status);
                if (status==1){
                    if (playerIterator == players.end() && playerID!=clientID){
                        players.push_back(Player(rendererPnt, playerID));
                        for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++)
                            if (playerIterator->playerID == playerID) break;
                    }
                    
                    if (playerID!=clientID && playerIterator != players.end()){
                        readBuff(recvbuf, offset, playerIterator->u2);
                        readBuff(recvbuf, offset, playerIterator->d2);
                        readBuff(recvbuf, offset, playerIterator->l2);
                        readBuff(recvbuf, offset, playerIterator->r2);
                        readBuff(recvbuf, offset, playerIterator->b2);
                        readBuff(recvbuf, offset, playerIterator->n2);

                        float newx, newy;
                        float k;
                        k = pow(0.0001, dt*8);

                        readBuff(recvbuf, offset, newx);
                        readBuff(recvbuf, offset, newy);
                        if (STAGE=="gameplay"){
                            if (playerIterator->throughWall){
                                playerIterator->x=newx;
                                playerIterator->y=newy;
                            }
                            else {
                                playerIterator->x=playerIterator->x*k+newx*(1-k);
                                playerIterator->y=playerIterator->y*k+newy*(1-k);
                            }
                        }
                        
                        readBuff(recvbuf, offset, playerIterator->vel_x);
                        readBuff(recvbuf, offset, playerIterator->vel_y);
                        
                        readBuff(recvbuf, offset, playerIterator->aiming);
                        readBuff(recvbuf, offset, playerIterator->dead);
                        readBuff(recvbuf, offset, playerIterator->rightWalled);
                        readBuff(recvbuf, offset, playerIterator->leftWalled);
                        readBuff(recvbuf, offset, playerIterator->arrowCount);

                        readBuff(recvbuf, offset, playerIterator->shieldOn);
                        readBuff(recvbuf, offset, playerIterator->wingsOn);
                        
                        readBuff(recvbuf, offset, playerIterator->color);
                        readBuff(recvbuf, offset, playerIterator->playerReady);

                        readBuff(recvbuf, offset, playerIterator->kills);
                        readBuff(recvbuf, offset, playerIterator->newkills);
                        readBuff(recvbuf, offset, playerIterator->selfkills);
                    }
                    else {
                        bool tmpb;
                        float tmpf;
                        int tmpi;
                        
                        readBuff(recvbuf, offset, tmpb);
                        readBuff(recvbuf, offset, tmpb);
                        readBuff(recvbuf, offset, tmpb);
                        readBuff(recvbuf, offset, tmpb);
                        readBuff(recvbuf, offset, tmpb);
                        readBuff(recvbuf, offset, tmpb);
                        
                        readBuff(recvbuf, offset, tmpf);
                        readBuff(recvbuf, offset, tmpf);
                        readBuff(recvbuf, offset, tmpf);
                        readBuff(recvbuf, offset, tmpf);

                        readBuff(recvbuf, offset, tmpb);
                        readBuff(recvbuf, offset, tmpb);
                        if (tmpb==1) playerPointer->dead=1;
                        readBuff(recvbuf, offset, tmpb);
                        readBuff(recvbuf, offset, tmpb);
                        readBuff(recvbuf, offset, playerPointer->arrowCount);

                        readBuff(recvbuf, offset, playerPointer->shieldOn);
                        readBuff(recvbuf, offset, playerPointer->wingsOn);
                        
                        readBuff(recvbuf, offset, tmpi);
                        readBuff(recvbuf, offset, tmpb);

                        readBuff(recvbuf, offset, playerPointer->kills);
                        readBuff(recvbuf, offset, playerPointer->newkills);
                        readBuff(recvbuf, offset, playerPointer->selfkills);
                    }
                }
                else if (playerIterator != players.end() && playerIterator->playerID == playerID){
                    playerIterator = players.erase(playerIterator);
                }
            }
            readBuff(recvbuf, offset, gamehandler.availableColors);
            readBuff(recvbuf, offset, gamehandler.allPlayersReady);
            readBuff(recvbuf, offset, gamehandler.playersRemaining);

            arrowListMutex.lock();
            arrowList.clear();
            int arrowID1, playerID1, color1;
            float x1, y1, vel_x1, vel_y1;
            bool isWalled1;

            readBuff(recvbuf, offset, arrowsCounter);
            for (int i=0; i<arrowsCounter; i++){
                readBuff(recvbuf, offset, arrowID1);
                readBuff(recvbuf, offset, playerID1);
                readBuff(recvbuf, offset, color1);
                
                readBuff(recvbuf, offset, isWalled1);

                readBuff(recvbuf, offset, x1);
                readBuff(recvbuf, offset, y1);
                readBuff(recvbuf, offset, vel_x1);
                readBuff(recvbuf, offset, vel_y1);
                arrowList.push_back(Arrow(arrowID1, playerID1, color1, isWalled1, x1, y1, vel_x1, vel_y1));
            }
            
            arrowListMutex.unlock();

            chestListMutex.lock();
            chestList.clear();
            bool open1;
            int item1;

            readBuff(recvbuf, offset, chestsCounter);
            for (int i=0; i<chestsCounter; i++){
                readBuff(recvbuf, offset, x1);
                readBuff(recvbuf, offset, y1);
                readBuff(recvbuf, offset, open1);
                readBuff(recvbuf, offset, item1);

                chestList.push_back(Chest(x1, y1, open1, item1));
            }
            chestListMutex.unlock();
        }
        /*else if (command=="newplayer"){
            int ID;
            readBuff(recvbuf, offset, ID);
            cout << "New player connected: " << ID << endl;
            if (ID!=clientID) players.push_back(Player(rendererPnt, ID));
        }*/



        if (riResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        //!printf("Bytes Received: %ld\n", riResult);

        //std::cout << recvbuf << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    } while (str != "end");
    
    /*offset=0;
    string command="shutdown";
    writeBuff(buff, offset, command);
    */
    
    //Shutdown();
    //cout << "receiving zaprt" << endl;
    return 0;
}

void Client::cleanUp() {
    closesocket(ConnectSocket);
    WSACleanup();
}


void Client::InfoToServer(Player *player){
    offset=0;

    string command="data";
    
    writeBuff(buff, offset, command);
    writeBuff(buff, offset, player->leaderCommand);
    
    if (clientID==1){
        writeBuff(buff, offset, gamehandler.gamemode);
        writeBuff(buff, offset, gamehandler.gamerounds);
        writeBuff(buff, offset, gamehandler.winner);
        writeBuff(buff, offset, gamehandler.winnercolor);
    }
    
    writeBuff(buff, offset, player->gamedt);

    writeBuff(buff, offset, player->u2);
    writeBuff(buff, offset, player->d2);
    writeBuff(buff, offset, player->l2);
    writeBuff(buff, offset, player->r2);
    writeBuff(buff, offset, player->b2);
    writeBuff(buff, offset, player->n2);

    writeBuff(buff, offset, player->x);
    writeBuff(buff, offset, player->y);
    writeBuff(buff, offset, player->vel_x);
    writeBuff(buff, offset, player->vel_y);

    writeBuff(buff, offset, player->aiming);
    writeBuff(buff, offset, player->rightWalled);
    writeBuff(buff, offset, player->leftWalled);

    writeBuff(buff, offset, player->color);
    writeBuff(buff, offset, player->playerReady);
}

