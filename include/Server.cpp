#pragma once
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <algorithm>

#define DEFAULT_BUFLEN 65536
#define DEFAULT_PORT "27015"

#include <Game.h>

    int Server::CreateSocket() {
        int iResult;
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
            return 1;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the server address and port
        iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
        if (iResult != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return 1;
        }

        // Create a SOCKET for the server to listen for client connections.
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }
    

        // Setup the TCP listening socket
        iResult = ::bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        freeaddrinfo(result);
        iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        return 0;
    }

     void Server::HandleClient(SOCKET clientSocket, int clientID) {
        char recvbuf[DEFAULT_BUFLEN];
        int recvbuflen = DEFAULT_BUFLEN;
        int iResult;
        Player *playerPointer;
        std::vector <Player> :: iterator playerIterator;
        
        playerListMutex.lock();
        players.push_back(Player(rendererPnt, clientID));
        playerListMutex.unlock();

        char buff[DEFAULT_BUFLEN];
        uint32_t offset = 0;

        string leaderCommand = "";
        
        string command = "";/*
        writeBuff(buff, offset, command);
        writeBuff(buff, offset, clientID);*/

        /*socketMutex.lock();
        for (auto& socket : clientSockets) {
            iResult = send(socket, buff, offset, 0);
        }
        socketMutex.unlock();*/

        //cout << clientSocket << ", " << clientID << endl;

        do {
            playerListMutex.lock();
            for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
                if (playerIterator->playerID == clientID){
                    playerPointer=&(*playerIterator);
                    break;
                }
            }

            socketMutex.lock();
            iResult = recv(clientSocket, recvbuf, recvbuflen, 0);
            socketMutex.unlock();


            

            if (!playerPointer->active) playerPointer->active=1;
            
            //std::cout << iResult << std::endl;
            //std::cout << recvbuf << std::endl;
            //std::cout << recvbuf << " " << recvbuflen << std::endl;
            if (iResult > 0) {
                //cout << "recieved" << clientID << endl;


                uint32_t offset = 0;
                int tmpi;
                std::string tmps;

                readBuff(recvbuf, offset, command);
                readBuff(recvbuf, offset, leaderCommand);

                if (clientID==1){
                    readBuff(recvbuf, offset, gamehandler.gamemode);
                    readBuff(recvbuf, offset, gamehandler.gamerounds);
                    readBuff(recvbuf, offset, gamehandler.winner);
                    readBuff(recvbuf, offset, gamehandler.winnercolor);
                }

                if (leaderCommand=="start_game") gamehandler.gamecommand="start_game";
                if (leaderCommand=="next_round") gamehandler.gamecommand="next_round";
                if (leaderCommand=="game_ended") gamehandler.gamecommand="game_ended";
                if (leaderCommand=="winner_stats") gamehandler.gamecommand="winner_stats";
                

                if (command=="data"){
                    readBuff(recvbuf, offset, playerPointer->gamedt);

                    readBuff(recvbuf, offset, playerPointer->u2);
                    readBuff(recvbuf, offset, playerPointer->d2);
                    readBuff(recvbuf, offset, playerPointer->l2);
                    readBuff(recvbuf, offset, playerPointer->r2);
                    readBuff(recvbuf, offset, playerPointer->b2);
                    readBuff(recvbuf, offset, playerPointer->n2);

                    readBuff(recvbuf, offset, playerPointer->x);
                    readBuff(recvbuf, offset, playerPointer->y);
                    readBuff(recvbuf, offset, playerPointer->vel_x);
                    readBuff(recvbuf, offset, playerPointer->vel_y);

                    readBuff(recvbuf, offset, playerPointer->aiming);
                    readBuff(recvbuf, offset, playerPointer->rightWalled);
                    readBuff(recvbuf, offset, playerPointer->leftWalled);

                    readBuff(recvbuf, offset, playerPointer->color);
                    readBuff(recvbuf, offset, playerPointer->playerReady);
                }

                if (playerPointer->playerReady)gamehandler.availableColors[playerPointer->color-1]=0;

            } else if (iResult == 0) {
                printf("Client %d disconnected.\n", clientID);
                break; // Break from the loop if the client disconnects
            } else {
                printf("recv failed with error: %d\n", WSAGetLastError());
                break;
            }
            playerListMutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
           /* if (strcmp(recvbuf, "BYE")==0){
                    send(clientSocket, recvbuf, 4, 0);
                }*/
            
        } while (iResult > 0);
        playerListMutex.unlock();
        // Remove the client socket from the vector after the client disconnects
        /*socketMutex.lock();
        for (auto& socket : clientSockets) {
            if (socket == clientSocket){
                auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
                if (it != clientSockets.end()) 
                    clientSockets.erase(it);

                //closesocket(clientSocket);
                break;
            }
        }
        socketMutex.unlock();*/

        //?cout << "st: "<< clientSockets.size() << endl;
        //?cout << "ta socket " << clientSocket << endl;
        socketMutex.lock();
        for (auto& socket : clientSockets) {
            //cout << socket << endl;
            if (socket == clientSocket){
                auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
                //?cout <<"karkol "<< *it << endl;
                if (it != clientSockets.end()) 
                    clientSockets.erase(it);

                closesocket(clientSocket);
                //?cout << "zaprt socket " << socket << endl;
                break;
            }
            //?else cout << "ni zaprl socketa" << endl;
        }
        //cout << "sending" << endl;
        socketMutex.unlock();
        //cout << "st: "<< clientSockets.size() << endl;


        /*socketMutex.lock();
        for (auto& socket : clientSockets) {
            iResult = send(socket, buff, offset, 0);
        }
        //cout << "sending" << endl;
        socketMutex.unlock();*/

        playerListMutex.lock();
        for (auto playerIterator = players.begin(); playerIterator != players.end(); ++playerIterator) {
            if (playerIterator->playerID == clientID) {
                playerIterator = players.erase(playerIterator);
                //?cout << "Removed player with ID: " << clientID << endl;
                break;
            }
        }
        IDs[clientID-1]=0;
        gamehandler.availableColors[playerPointer->color-1]=1;
        //?cout << "Current ID: " << clientID << endl;
        for (int i=0; i<4; i++){
            //cout << IDs[i];
        }
        //cout << endl;
        playerListMutex.unlock();
        
        if (players.size()==0){
            gamehandler.nextlvl=2;
            gamehandler.gamestatus="no_game";
            for (int i=0; i<4; i++) gamehandler.availableColors[i] = i+1;
            gamehandler.prevgamecommand = "nothing";
            gamehandler.gamecommand = "pre_game";

            
            ifstream dat("level1.bin", ios::binary);
            dat.read((char *)gridPnt, sizeof(int) * 32 * 24);
            dat.read((char *)spPnt, sizeof(int) * 4 * 2);
            dat.read((char *)cpPnt, sizeof(int) * 6 * 2);
            dat.close();
            
            chestList.clear();
        }
        
        //!
        /*auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
        if (it != clientSockets.end()) {
            closesocket(clientSocket);
            clientSockets.erase(it);
            cout << "Disconnecting socket" << endl;
            for (int i=0; i<4; i++){
                if (IDs[i]==clientID){
                    IDs[i] = 0;
                    
                    playerListMutex.lock();

                    for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++)
                        if (playerIterator->playerID == clientID) {
                            players.erase(playerIterator);
                            break;
                        }
                    
                    cout << "Current ID: " << clientID << endl;

                    for (auto playerIterator = players.begin(); playerIterator != players.end(); ++playerIterator) {
                        if (playerIterator->playerID == clientID) {
                            playerIterator = players.erase(playerIterator);
                            cout << "Removed player with ID: " << clientID << endl;
                            break;
                        }
                    }
                    
                    playerListMutex.unlock();
                    
                    
                    break;
                }
            }
        }*/
        
        //?cout << "yesssssssssss" << endl;
    }



    void Server::StartListening() {
        while (true) {
            SOCKET clientSocket = accept(ListenSocket, NULL, NULL);

            if (gamehandler.gamestatus=="game" || clientSockets.size()>3){
                printf("Maximum number of clients reached. Connection rejected.\n");
                send(clientSocket, "server_full", 12, 0);
                closesocket(clientSocket);
            }
            else {
                int clientID=0;
                for (int i=0; i<4; i++){
                    if (IDs[i]!=i+1){
                        clientID = i+1;
                        IDs[i] = clientID;
                        break;
                    }
                }

                for (int i=0; i<4; i++){
                    //cout << IDs[i];
                }
                //cout << endl;

                
                std::string connectedID = "connected" + std::to_string(clientID);
                //std::cout << connectedID.substr(0, 9) << std::endl;

                send(clientSocket, connectedID.c_str(), 11, 0);
                if (clientSocket == INVALID_SOCKET) {
                    printf("accept failed with error: %d\n", WSAGetLastError());
                    closesocket(ListenSocket);
                    WSACleanup();
                    continue;
                }
                
                printf("Client %d connected.\n", clientID);

                // Add the new client socket to the vector
                socketMutex.lock();
                clientSockets.push_back(clientSocket);
                socketMutex.unlock();

                // Create a new thread to handle the client
                std::thread(&Server::HandleClient, this, clientSocket, clientID).detach();
            }

            
        }
    }

    void Server::Broadcast(){
        while (true){
            
            int iResult;
            char buff[DEFAULT_BUFLEN];
            uint32_t offset;
            std::vector <Player> :: iterator playerIterator;
            int playersReadyCount;
            int playerCount;
            string command;
            do {
                offset=0;
                playerListMutex.lock();
                playersReadyCount=0;
                playerCount = clientSockets.size();
                
                if (playerCount==0) {
                    gamehandler.gamestatus="no_game";
                    //gamehandler.winner=0;
                    //gamehandler.winnercolor=0;
                }

                gamehandler.playersRemaining=playerCount;
                command = "data";
                
                writeBuff(buff, offset, command);
                writeBuff(buff, offset, gamehandler.gamecommand);

                writeBuff(buff, offset, gamehandler.gamemode);
                writeBuff(buff, offset, gamehandler.gamerounds);
                writeBuff(buff, offset, gamehandler.winner);
                writeBuff(buff, offset, gamehandler.winnercolor);

                //cout << gamehandler.winner << gamehandler.winnercolor << endl;
                if (gamehandler.prevgamecommand=="next_round" && gamehandler.gamecommand=="nothing"){
                    string lvlname = "level" + to_string(gamehandler.nextlvl) + ".bin";
                    ifstream dat(lvlname, ios::binary);
                    dat.read((char *)gridPnt, sizeof(int) * 32 * 24);
                    dat.read((char *)spPnt, sizeof(int) * 4 * 2);
                    dat.read((char *)cpPnt, sizeof(int) * 6 * 2);
                    dat.close();
                    
                    chestList.clear();
                    /*for (int i=0; i<6; i++){
                        chestList.push_back(Chest(rendererPnt, cpPnt[i][0], cpPnt[i][1]));
                    }*/

                    //std::cout << "round: " << gamehandler.nextlvl << std::endl;

                    if (gamehandler.nextlvl >= 2) gamehandler.nextlvl=1;
                    else gamehandler.nextlvl++;
                }
                
                writeBuff(buff, offset, gamehandler.nextlvl);
                
                //std::cout << playerCount << std::endl;
                //writeBuff(buff, offset, playerCount);
                for (int i=1; i<=4; i++) {
                    for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++)
                        if (playerIterator->playerID == i) break;
                    
                    if (playerIterator != players.end() && playerIterator->active == 1 && playerIterator->status == 1){
                        writeBuff(buff, offset, playerIterator->playerID);
                        writeBuff(buff, offset, playerIterator->status);
                    
                        writeBuff(buff, offset, playerIterator->u2);
                        writeBuff(buff, offset, playerIterator->d2);
                        writeBuff(buff, offset, playerIterator->l2);
                        writeBuff(buff, offset, playerIterator->r2);
                        writeBuff(buff, offset, playerIterator->b2);
                        writeBuff(buff, offset, playerIterator->n2);

                        writeBuff(buff, offset, playerIterator->x);
                        writeBuff(buff, offset, playerIterator->y);
                        writeBuff(buff, offset, playerIterator->vel_x);
                        writeBuff(buff, offset, playerIterator->vel_y);

                        writeBuff(buff, offset, playerIterator->aiming);
                        writeBuff(buff, offset, playerIterator->dead);
                        writeBuff(buff, offset, playerIterator->rightWalled);
                        writeBuff(buff, offset, playerIterator->leftWalled);
                        writeBuff(buff, offset, playerIterator->arrowCount);
                        
                        writeBuff(buff, offset, playerIterator->shieldOn);
                        writeBuff(buff, offset, playerIterator->wingsOn);
                        
                        writeBuff(buff, offset, playerIterator->color);
                        writeBuff(buff, offset, playerIterator->playerReady);

                        writeBuff(buff, offset, playerIterator->kills);
                        writeBuff(buff, offset, playerIterator->newkills);
                        writeBuff(buff, offset, playerIterator->selfkills);

                        if (playerIterator->playerReady==1) playersReadyCount++;
                        if (playerIterator->dead==1) gamehandler.playersRemaining--;
                        if (gamehandler.gamecommand=="next_round") {
                            playerIterator->vel_x=0;
                            playerIterator->vel_y=0;
                            playerIterator->arrowCount=3;
                            playerIterator->dead=0;
                        }
                        if (gamehandler.prevgamecommand=="next_round" && gamehandler.gamecommand=="nothing"){
                            playerIterator->kills+=playerIterator->newkills-playerIterator->selfkills;
                            playerIterator->newkills=0;
                            playerIterator->selfkills=0;
                        }
                    }
                    else {
                        bool disstatus=0;
                        writeBuff(buff, offset, i);
                        writeBuff(buff, offset, disstatus);
                    }
                    
                }
                if (playersReadyCount==players.size()) gamehandler.allPlayersReady=1;
                else gamehandler.allPlayersReady=0;
                
                writeBuff(buff, offset, gamehandler.availableColors);
                writeBuff(buff, offset, gamehandler.allPlayersReady);
                writeBuff(buff, offset, gamehandler.playersRemaining);
                
                
                
                if (gamehandler.playersRemaining==1 && !gamehandler.LMSbool && gamehandler.gamestatus=="game"){
                    for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++)
                        if (!playerIterator->dead) {
                            playerIterator->newkills++;
                            break;
                        }
                    gamehandler.LMSbool=1;
                }
                
                playerListMutex.unlock();

                arrowListMutex.lock();
                int arrowsCounter=arrowList.size();
                writeBuff(buff, offset, arrowsCounter);
                for (arrowCount = arrowList.begin(); arrowCount != arrowList.end();arrowCount++){
                    writeBuff(buff, offset, arrowCount->arrowID);
                    writeBuff(buff, offset, arrowCount->playerID);
                    writeBuff(buff, offset, arrowCount->color);

                    writeBuff(buff, offset, arrowCount->isWalled);
                    
                    writeBuff(buff, offset, arrowCount->x);
                    writeBuff(buff, offset, arrowCount->y);
                    writeBuff(buff, offset, arrowCount->vel_x);
                    writeBuff(buff, offset, arrowCount->vel_y);
                }
                
                arrowListMutex.unlock();
                
                chestListMutex.lock();
                int chestsCounter=chestList.size();
                writeBuff(buff, offset, chestsCounter);
                for (chestIterator = chestList.begin(); chestIterator != chestList.end();chestIterator++){
                    writeBuff(buff, offset, chestIterator->x);
                    writeBuff(buff, offset, chestIterator->y);
                    writeBuff(buff, offset, chestIterator->open);
                    writeBuff(buff, offset, chestIterator->item);
                }
                chestListMutex.unlock();
            } while (playerCount != clientSockets.size());
            
            socketMutex.lock();
            for (auto& socket : clientSockets) {
                iResult = send(socket, buff, offset, 0);
            }
            //cout << "sending" << endl;
            socketMutex.unlock();
            
            if (gamehandler.gamecommand=="start_game" || gamehandler.gamecommand=="next_round") {
                if (gamehandler.gamecommand=="start_game") {
                    gamehandler.nextlvl=2;
                    gamehandler.gamestatus="game";
                    gamehandler.chestTime = chrono::steady_clock::now();

                    gamehandler.nextChest = 1;
                    for (int i = 0; i<6; i++) gamehandler.availableChests[i]=0;
                    gamehandler.chestNum = 6;
                    gamehandler.nextChestTime=6000;
                    gamehandler.LMSbool=0;
                }

                if (gamehandler.gamecommand=="next_round"){
                    gamehandler.chestTime = chrono::steady_clock::now();

                    gamehandler.nextChest = 1;
                    for (int i = 0; i<6; i++) gamehandler.availableChests[i]=0;
                    gamehandler.chestNum = 6;
                    gamehandler.nextChestTime=6000;
                    gamehandler.LMSbool=0;
                }

                
               
                gamehandler.newIDforArrow=1;
                arrowList.clear();

                //cout << "se kr next round" << endl;
            }

            
            gamehandler.prevgamecommand=gamehandler.gamecommand;
            gamehandler.gamecommand="nothing";
            
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        
    }

    void Server::CleanUp() {
        closesocket(ListenSocket);
        WSACleanup();
    }

/*
int main() {
    Server server;
    if (server.CreateSocket() == 0) {
        std::thread(&Server::StartListening, &server).detach();
        std::thread(&Server::Broadcast, &server).detach();

        // Main server loop to handle input or other tasks
        while (true) {
            //std::cout << "hahahahah" << std::endl;
            // Handle other tasks or input here if needed
            // For example, you can add code to accept server commands

            // Sleep to avoid high CPU usage in the main loop
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // After breaking from the loop, clean up resources
        server.CleanUp();
    }

    return 0;
}*/