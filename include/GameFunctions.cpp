#pragma once
#include <Game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void LoadTextures(SDL_Renderer *r){
    img = IMG_LoadTexture(r, "media/player.png");
    tile = IMG_LoadTexture(r, "media/tileset.png");
    red = IMG_LoadTexture(r, "media/red.png");
    blue = IMG_LoadTexture(r, "media/blue.png");
    bg = IMG_LoadTexture(r, "media/bg.png");
    menubg = IMG_LoadTexture(r, "media/menubg.png");
    arrowicon = IMG_LoadTexture(r, "media/arrowicon.png");
    arrowbutton = IMG_LoadTexture(r, "media/arrowbutton.png");
    aimarrowred = IMG_LoadTexture(r, "media/aimarrowred.png");
    aimarrowgreen = IMG_LoadTexture(r, "media/aimarrowgreen.png");
    aimarrowblue = IMG_LoadTexture(r, "media/aimarrowblue.png");
    aimarroworange = IMG_LoadTexture(r, "media/aimarroworange.png");
    title = IMG_LoadTexture(r, "media/title.png");
    button = IMG_LoadTexture(r, "media/button.png");
    board = IMG_LoadTexture(r, "media/board.png");
    smallboard = IMG_LoadTexture(r, "media/smallboard.png");
    chest = IMG_LoadTexture(r, "media/chest.png");
    skull = IMG_LoadTexture(r, "media/skull.png");
    shield = IMG_LoadTexture(r, "media/shield.png");
    wings = IMG_LoadTexture(r, "media/wings.png");
    arrowitem = IMG_LoadTexture(r, "media/arrowitem.png");
    redplayer = IMG_LoadTexture(r, "media/redplayer.png");
    greenplayer = IMG_LoadTexture(r, "media/greenplayer.png");
    blueplayer = IMG_LoadTexture(r, "media/blueplayer.png");
    orangeplayer = IMG_LoadTexture(r, "media/orangeplayer.png");
    bigbutton = IMG_LoadTexture(r, "media/bigbutton.png");
    slime = IMG_LoadTexture(r, "media/slime.png");
    coin = IMG_LoadTexture(r, "media/coin.png");
    smallbutton = IMG_LoadTexture(r, "media/smallbutton.png");
    arrowred = IMG_LoadTexture(r, "media/arrowred.png");
    arrowgreen = IMG_LoadTexture(r, "media/arrowgreen.png");
    arrowblue = IMG_LoadTexture(r, "media/arrowblue.png");
    arroworange = IMG_LoadTexture(r, "media/arroworange.png");
    ghost = IMG_LoadTexture(r, "media/ghost.png");
    lockedbutton = IMG_LoadTexture(r, "media/lockedbutton.png");
    gem = IMG_LoadTexture(r, "media/gem.png");
}

void LoadText(SDL_Renderer *r){
    TTF_Init();
    //TTF_Font *Sans = TTF_OpenFont("fonts/open-sans/OpenSans-Regular.ttf", 24);
    TTF_Font *Sans = TTF_OpenFont("fonts/open-sans/WinterPixel.otf", 48);
    TTF_Font *ChoosingSans = TTF_OpenFont("fonts/open-sans/WinterPixel.otf", 54);
    TTF_Font *LoadingSans = TTF_OpenFont("fonts/open-sans/WinterPixel.otf", 70);
    TTF_Font *CountSans = TTF_OpenFont("fonts/open-sans/WinterPixel.otf", 150);
    SDL_Surface *textSurface;
    
    textSurface = TTF_RenderText_Blended(Sans, "PLAY", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    playText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "PLAY", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    playText2 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "OPTIONS", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    optionsText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "OPTIONS", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    optionsText2 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "QUIT", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    quitText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "QUIT", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    quitText2 = SDL_CreateTextureFromSurface(r, textSurface);

    
    textSurface = TTF_RenderText_Blended(LoadingSans, "SINGLE", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    singleText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "SINGLE", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    single2Text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "MULTI", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    multiText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "MULTI", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    multi2Text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "PLAYER MODE SELECTION", SDL_Color({255, 255, 255})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    playermodeText = SDL_CreateTextureFromSurface(r, textSurface);

    
    textSurface = TTF_RenderText_Blended(LoadingSans, "CONNECTING TO SERVER", SDL_Color({255, 255, 255})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    loadingText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "CHOOSE YOUR CHARACTER", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    chooseCharText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "WAITING FOR OTHER PLAYERS", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    waitingPlayersText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "CONFIRM", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    confirmText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "CONFIRM", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    confirmText2 = SDL_CreateTextureFromSurface(r, textSurface);


    textSurface = TTF_RenderText_Blended(Sans, "P1", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    p1text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "P2", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    p2text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "P3", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    p3text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "P4", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    p4text = SDL_CreateTextureFromSurface(r, textSurface);


    textSurface = TTF_RenderText_Blended(Sans, "START", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    startGameText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "START", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    startGameText2 = SDL_CreateTextureFromSurface(r, textSurface);


    textSurface = TTF_RenderText_Blended(CountSans, "3", SDL_Color({255, 255, 255})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    count3Text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(CountSans, "2", SDL_Color({255, 255, 255})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    count2Text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(CountSans, "1", SDL_Color({255, 255, 255})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    count1Text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(CountSans, "GO", SDL_Color({255, 255, 255})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    countgoText = SDL_CreateTextureFromSurface(r, textSurface);


    textSurface = TTF_RenderText_Blended(LoadingSans, "GAMEMODE", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    gamemodeText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "ROUNDS", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    gameroundsText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "DEATHMATCH", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    deathmatchText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "LAST MAN STANDING", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    lastmanstandingText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "5", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    rounds5Text = SDL_CreateTextureFromSurface(r, textSurface);
    
    textSurface = TTF_RenderText_Blended(ChoosingSans, "10", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    rounds10Text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "15", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    rounds15Text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "20", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    rounds20Text = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "))                                ((", SDL_Color({189, 134, 53})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    gamemodepickerText = SDL_CreateTextureFromSurface(r, textSurface);



    textSurface = TTF_RenderText_Blended(Sans, "CONTINUE", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    continueText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "CONTINUE", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    continueText2 = SDL_CreateTextureFromSurface(r, textSurface);

    
    
    textSurface = TTF_RenderText_Blended(Sans, "MENU", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    backToMenuText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "MENU", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    backToMenuText2 = SDL_CreateTextureFromSurface(r, textSurface);



    textSurface = TTF_RenderText_Blended(LoadingSans, "MOUSE AIM", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    volumeoptionText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "FULLSCREEN", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    fullscreenoptionText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "SERVER", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    serveroptionText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "ON", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    onoptionText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "ON", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    onoptionText2 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(ChoosingSans, "OFF", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    offoptionText = SDL_CreateTextureFromSurface(r, textSurface);
    
    textSurface = TTF_RenderText_Blended(ChoosingSans, "OFF", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    offoptionText2 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "NEXT", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    nextText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "NEXT", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    nextText2 = SDL_CreateTextureFromSurface(r, textSurface);


    textSurface = TTF_RenderText_Blended(LoadingSans, "1", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text1 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "1", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text11 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "2", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text2 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "2", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text22 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "3", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text3 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "3", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text33 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "4", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text4 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "4", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text44 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "5", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text5 = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(LoadingSans, "5", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    text55 = SDL_CreateTextureFromSurface(r, textSurface);


    textSurface = TTF_RenderText_Blended(Sans, "RETRY", SDL_Color({96, 56, 19})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    retryText = SDL_CreateTextureFromSurface(r, textSurface);

    textSurface = TTF_RenderText_Blended(Sans, "RETRY", SDL_Color({252, 176, 64})); // use TTF_RenderText_Solid != TTF_RenderText_Blended for aliesed (stairs) edges
    retryText2 = SDL_CreateTextureFromSurface(r, textSurface);

    

    SDL_FreeSurface(textSurface);
}

void LoadRects(){
    //SDL_QueryTexture(bg, NULL, NULL, &bgrnd.w, &bgrnd.h);
    menubgrnd.x = 0;
    menubgrnd.y = -HEIGHT;//-(HEIGHT*2.5)/1.67;
    menubgrnd.w = WIDTH;
    menubgrnd.h = HEIGHT*2.5;


    
    tilerect.x = 0;
    tilerect.y = 0;
    tilerect.w = 32;
    tilerect.h = 32;

    
    blockrect.x = 0;
    blockrect.y = 0;
    blockrect.w = 10;
    blockrect.h = 10;


    
    SDL_QueryTexture(button, NULL, NULL, &playbuttonRect.w, &playbuttonRect.h);
    playbuttonRect.x = 320;
    playbuttonRect.y = 400;
    playbuttonRect.w = playbuttonRect.w*3.5;
    playbuttonRect.h = playbuttonRect.h*3.5;
    //SDL_RenderCopy(r, button, NULL, &playbuttonRect);
    

    optionsbuttonRect = playbuttonRect;
    optionsbuttonRect.y=500;

    quitbuttonRect = playbuttonRect;
    quitbuttonRect.y=600;

    confirmbuttonRect = playbuttonRect;
    confirmbuttonRect.y=590;


    playtextRect.x = 463;
    playtextRect.y = 410;
    SDL_QueryTexture(playText, NULL, NULL, &playtextRect.w, &playtextRect.h);

    optionstextRect.x = 426;
    optionstextRect.y = 510;
    SDL_QueryTexture(optionsText, NULL, NULL, &optionstextRect.w, &optionstextRect.h);

    quittextRect.x = 463;
    quittextRect.y = 610;
    SDL_QueryTexture(quitText, NULL, NULL, &quittextRect.w, &quittextRect.h);


    bgrnd.x = 0;
    bgrnd.y = 0;
    bgrnd.w = WIDTH;
    bgrnd.h = HEIGHT;

    
    titleRect.x = 0;
    titleRect.y = 0;
    SDL_QueryTexture(title, NULL, NULL, &titleRect.w, &titleRect.h);
    
    titleRect.x = (WIDTH-titleRect.w*1.6)/2;
    titleRect.y = 30;
    titleRect.w=titleRect.w*1.6;
    titleRect.h=titleRect.h*1.6;

    loadingtextRect.x = 163;
    loadingtextRect.y = 352;
    SDL_QueryTexture(loadingText, NULL, NULL, &loadingtextRect.w, &loadingtextRect.h);

    
    boardRect.x = 60;
    boardRect.y = 60;
    boardRect.w = WIDTH-120;
    boardRect.h = HEIGHT-120;

    choosechartextRect.x = 227;
    choosechartextRect.y = 100;
    SDL_QueryTexture(chooseCharText, NULL, NULL, &choosechartextRect.w, &choosechartextRect.h);

    waitingplayerstextRect.x = 179;
    waitingplayerstextRect.y = 100;
    SDL_QueryTexture(waitingPlayersText, NULL, NULL, &waitingplayerstextRect.w, &waitingplayerstextRect.h);

    confirmtextRect.x = 423;
    confirmtextRect.y = 600;
    SDL_QueryTexture(confirmText, NULL, NULL, &confirmtextRect.w, &confirmtextRect.h);

    startgametextRect.x = 450;
    startgametextRect.y = 600;
    SDL_QueryTexture(startGameText, NULL, NULL, &startgametextRect.w, &startgametextRect.h);

    startgamebuttonRect=confirmbuttonRect;
    
    continuebuttonRect=confirmbuttonRect;
    continuebuttonRect.y+=30;

    continuetextRect.x = 416;
    continuetextRect.y = 630;
    SDL_QueryTexture(continueText, NULL, NULL, &continuetextRect.w, &continuetextRect.h);


    count3textRect.x = WIDTH/2-30;
    count3textRect.y = HEIGHT/2-68;
    SDL_QueryTexture(count3Text, NULL, NULL, &count3textRect.w, &count3textRect.h);

    count2textRect.x = WIDTH/2-30;
    count2textRect.y = HEIGHT/2-68;
    SDL_QueryTexture(count2Text, NULL, NULL, &count2textRect.w, &count2textRect.h);

    count1textRect.x = WIDTH/2-30;
    count1textRect.y = HEIGHT/2-68;
    SDL_QueryTexture(count1Text, NULL, NULL, &count1textRect.w, &count1textRect.h);

    countgotextRect.x = WIDTH/2-83;
    countgotextRect.y = HEIGHT/2-68;
    SDL_QueryTexture(countgoText, NULL, NULL, &countgotextRect.w, &countgotextRect.h);


    gamemodetextRect.x = WIDTH/2-172;
    gamemodetextRect.y = 100;
    SDL_QueryTexture(gamemodeText, NULL, NULL, &gamemodetextRect.w, &gamemodetextRect.h);

    gameroundstextRect.x = WIDTH/2-120;
    gameroundstextRect.y = 350;
    SDL_QueryTexture(gameroundsText, NULL, NULL, &gameroundstextRect.w, &gameroundstextRect.h);

    deathmatchtextRect.x = WIDTH/2-151;
    deathmatchtextRect.y = 200;
    SDL_QueryTexture(deathmatchText, NULL, NULL, &deathmatchtextRect.w, &deathmatchtextRect.h);

    lastmanstandingtextRect.x = WIDTH/2-232;
    lastmanstandingtextRect.y = 200;
    SDL_QueryTexture(lastmanstandingText, NULL, NULL, &lastmanstandingtextRect.w, &lastmanstandingtextRect.h);


    rounds5textRect.x = WIDTH/2-11;
    rounds5textRect.y = 450;
    SDL_QueryTexture(rounds5Text, NULL, NULL, &rounds5textRect.w, &rounds5textRect.h);

    rounds10textRect.x = WIDTH/2-22;
    rounds10textRect.y = 450;
    SDL_QueryTexture(rounds10Text, NULL, NULL, &rounds10textRect.w, &rounds10textRect.h);

    rounds15textRect.x = WIDTH/2-22;
    rounds15textRect.y = 450;
    SDL_QueryTexture(rounds15Text, NULL, NULL, &rounds15textRect.w, &rounds15textRect.h);

    rounds20textRect.x = WIDTH/2-27;
    rounds20textRect.y = 450;
    SDL_QueryTexture(rounds20Text, NULL, NULL, &rounds20textRect.w, &rounds20textRect.h);

    gamemodepickertextRect.x = WIDTH/2-277;
    gamemodepickertextRect.y = 100;
    SDL_QueryTexture(gamemodepickerText, NULL, NULL, &gamemodepickertextRect.w, &gamemodepickertextRect.h);



    p1textRect.x = 175;
    p1textRect.y = 510;
    SDL_QueryTexture(p1text, NULL, NULL, &p1textRect.w, &p1textRect.h);

    p2textRect.x = 383;
    p2textRect.y = 510;
    SDL_QueryTexture(p2text, NULL, NULL, &p2textRect.w, &p2textRect.h);

    p3textRect.x = 593;
    p3textRect.y = 510;
    SDL_QueryTexture(p3text, NULL, NULL, &p3textRect.w, &p3textRect.h);

    p4textRect.x = 800;
    p4textRect.y = 510;
    SDL_QueryTexture(p4text, NULL, NULL, &p4textRect.w, &p4textRect.h);


    arrowbuttonRect.x = 167;//377
    arrowbuttonRect.y = 170;
    SDL_QueryTexture(arrowbutton, NULL, NULL, &arrowbuttonRect.w, &arrowbuttonRect.h);
    arrowbuttonRect.w=arrowbuttonRect.w*3;
    arrowbuttonRect.h=arrowbuttonRect.h*3;


    skullRect.x=200;
    skullRect.y=200;
    skullRect.w=30;
    skullRect.h=30;

    smallboardRect.x = 40;
    smallboardRect.y = 182;
    smallboardRect.w = WIDTH-80;
    smallboardRect.h = HEIGHT/2+20;


    


    SDL_QueryTexture(bigbutton, NULL, NULL, &bigbuttonRect.w, &bigbuttonRect.h);
    bigbuttonRect.x = 128;
    bigbuttonRect.y = 224;
    bigbuttonRect.w = bigbuttonRect.w*4;
    bigbuttonRect.h = bigbuttonRect.h*4;

    bigbutton2Rect=bigbuttonRect;
    bigbutton2Rect.x = 576;


    singletextRect.x = 191;
    singletextRect.y = 352;
    SDL_QueryTexture(singleText, NULL, NULL, &singletextRect.w, &singletextRect.h);

    multitextRect.x = 652;
    multitextRect.y = 352;
    SDL_QueryTexture(multiText, NULL, NULL, &multitextRect.w, &multitextRect.h);

    playermodeRect.x = 152;
    playermodeRect.y = 30;
    SDL_QueryTexture(playermodeText, NULL, NULL, &playermodeRect.w, &playermodeRect.h);



    playerstatsRect.x = 0;
    playerstatsRect.y = 0;
    playerstatsRect.w = 13;
    playerstatsRect.h = 24;

    playerstats2Rect.x = 444;
    playerstats2Rect.y = 230;
    playerstats2Rect.w = 143;
    playerstats2Rect.h = 262;

    bigbuttonstatsRect.x = 352;
    bigbuttonstatsRect.y = 224;
    bigbuttonstatsRect.w = bigbuttonRect.w;
    bigbuttonstatsRect.h = bigbuttonRect.h;

    menubuttonstatsRect=confirmbuttonRect;
    
    backtomenutextRect.x = 454;
    backtomenutextRect.y = 600;
    SDL_QueryTexture(backToMenuText, NULL, NULL, &backtomenutextRect.w, &backtomenutextRect.h);

    ipaddresstextRect.x=200;
    ipaddresstextRect.y=576;



    fullscreenoptiontextRect.x = 252;
    fullscreenoptiontextRect.y = 165;
    SDL_QueryTexture(fullscreenoptionText, NULL, NULL, &fullscreenoptiontextRect.w, &fullscreenoptiontextRect.h);


    volumeoptiontextRect.x = 254;
    volumeoptiontextRect.y = 342;
    SDL_QueryTexture(volumeoptionText, NULL, NULL, &volumeoptiontextRect.w, &volumeoptiontextRect.h);
    
    serveroptiontextRect.x = 400;
    serveroptiontextRect.y = 489;
    SDL_QueryTexture(serveroptionText, NULL, NULL, &serveroptiontextRect.w, &serveroptiontextRect.h);
    

    onoffbuttonRect.x = 652;
    onoffbuttonRect.y = 135;
    onoffbuttonRect.w = 120;
    onoffbuttonRect.h = 120;

    onoffbuttonRect2.x = 652;
    onoffbuttonRect2.y = 312;
    onoffbuttonRect2.w = 120;
    onoffbuttonRect2.h = 120;

    onoptiontextRect.x = 682;
    onoptiontextRect.y = 169;
    SDL_QueryTexture(onoptionText, NULL, NULL, &onoptiontextRect.w, &onoptiontextRect.h);

    offoptiontextRect.x = 672;
    offoptiontextRect.y = 169;
    SDL_QueryTexture(offoptionText, NULL, NULL, &offoptiontextRect.w, &offoptiontextRect.h);


    serverfieldRect.x=188;
    serverfieldRect.y=572;
    serverfieldRect.w=645;
    serverfieldRect.h=70;

    winnertextRect.y=110;

    nextbuttonRect=menubuttonstatsRect;
    nextbuttonRect.y=400;


    nexttextRect.x=backtomenutextRect.x+6;
    nexttextRect.y=410;
    SDL_QueryTexture(nextText, NULL, NULL, &nexttextRect.w, &nexttextRect.h);


    lvl1buttonRect.x=112;
    lvl1buttonRect.y=330;
    lvl1buttonRect.w=120;
    lvl1buttonRect.h=120;

    lvl2buttonRect=lvl1buttonRect;
    lvl2buttonRect.x=282;

    lvl3buttonRect=lvl1buttonRect;
    lvl3buttonRect.x=452;

    lvl4buttonRect=lvl1buttonRect;
    lvl4buttonRect.x=622;

    lvl5buttonRect=lvl1buttonRect;
    lvl5buttonRect.x=792;


    
    SDL_QueryTexture(text1, NULL, NULL, &text1Rect.w, &text1Rect.h);
    text1Rect.x=157;
    text1Rect.y=358;
    SDL_QueryTexture(text2, NULL, NULL, &text2Rect.w, &text2Rect.h);
    text2Rect.x=327;
    text2Rect.y=358;
    SDL_QueryTexture(text3, NULL, NULL, &text3Rect.w, &text3Rect.h);
    text3Rect.x=497;
    text3Rect.y=358;
    SDL_QueryTexture(text4, NULL, NULL, &text4Rect.w, &text4Rect.h);
    text4Rect.x=662;
    text4Rect.y=358;
    SDL_QueryTexture(text5, NULL, NULL, &text5Rect.w, &text5Rect.h);
    text5Rect.x=837;
    text5Rect.y=358;



    retrybuttonRect=menubuttonstatsRect;
    retrybuttonRect.y=400;


    retrytextRect.x=backtomenutextRect.x+6;
    retrytextRect.y=410;
    SDL_QueryTexture(retryText, NULL, NULL, &retrytextRect.w, &retrytextRect.h);

}

GameHandler::GameHandler(){
    allPlayersReady=0;


}


bool Collision(SDL_FRect a, SDL_FRect b) {
    if (a.x + a.w >= b.x &&
        a.x <= b.x + b.w &&
        a.y + a.h >= b.y &&
        a.y <= b.y + b.h) {
        return true;
    }
    return false;
}


bool Timer(const std::chrono::time_point<std::chrono::steady_clock> &timestamp, std::chrono::milliseconds duration) {
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - timestamp);

    return timeElapsed <= duration;
}