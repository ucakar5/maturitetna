#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//!Textures
SDL_Texture *img = nullptr;
SDL_Texture *tile = nullptr;
SDL_Texture *red = nullptr;
SDL_Texture *blue = nullptr;
SDL_Texture *bg = nullptr;
SDL_Texture *menubg = nullptr;
SDL_Texture *arrowicon = nullptr;
SDL_Texture *arrowbutton = nullptr;
SDL_Texture *aimarrowred = nullptr;
SDL_Texture *aimarrowgreen = nullptr;
SDL_Texture *aimarrowblue = nullptr;
SDL_Texture *aimarroworange = nullptr;
SDL_Texture *title = nullptr;
SDL_Texture *button = nullptr;
SDL_Texture *board = nullptr;
SDL_Texture *smallboard = nullptr;
SDL_Texture *chest = nullptr;
SDL_Texture *skull = nullptr;
SDL_Texture *shield = nullptr;
SDL_Texture *wings = nullptr;
SDL_Texture *arrowitem = nullptr;
SDL_Texture *redplayer = nullptr;
SDL_Texture *greenplayer = nullptr;
SDL_Texture *blueplayer = nullptr;
SDL_Texture *orangeplayer = nullptr;
SDL_Texture *bigbutton = nullptr;
SDL_Texture *slime = nullptr;
SDL_Texture *coin = nullptr;
SDL_Texture *smallbutton = nullptr;
SDL_Texture *arrowred = nullptr;
SDL_Texture *arrowgreen = nullptr;
SDL_Texture *arrowblue = nullptr;
SDL_Texture *arroworange = nullptr;
SDL_Texture *ghost = nullptr;
SDL_Texture *lockedbutton = nullptr;
SDL_Texture *gem = nullptr;

//!Text
SDL_Texture *playText = nullptr;
SDL_Texture *playText2 = nullptr;
SDL_Texture *optionsText = nullptr;
SDL_Texture *optionsText2 = nullptr;
SDL_Texture *quitText = nullptr;
SDL_Texture *quitText2 = nullptr;
SDL_Texture *loadingText = nullptr;
SDL_Texture *chooseCharText = nullptr;
SDL_Texture *waitingPlayersText = nullptr;
SDL_Texture *confirmText = nullptr;
SDL_Texture *confirmText2 = nullptr;
SDL_Texture *p1text = nullptr;
SDL_Texture *p2text = nullptr;
SDL_Texture *p3text = nullptr;
SDL_Texture *p4text = nullptr;
SDL_Texture *count3Text = nullptr;
SDL_Texture *count2Text = nullptr;
SDL_Texture *count1Text = nullptr;
SDL_Texture *countgoText = nullptr;
SDL_Texture *gamemodeText = nullptr;
SDL_Texture *gameroundsText = nullptr;
SDL_Texture *deathmatchText = nullptr;
SDL_Texture *lastmanstandingText = nullptr;
SDL_Texture *rounds5Text = nullptr;
SDL_Texture *rounds10Text = nullptr;
SDL_Texture *rounds15Text = nullptr;
SDL_Texture *rounds20Text = nullptr;
SDL_Texture *gamemodepickerText = nullptr;
SDL_Texture *continueText = nullptr;
SDL_Texture *continueText2 = nullptr;

SDL_Texture *singleText = nullptr;
SDL_Texture *multiText = nullptr;
SDL_Texture *single2Text = nullptr;
SDL_Texture *multi2Text = nullptr;
SDL_Texture *playermodeText = nullptr;

SDL_Texture *playerText[4] ={
    p1text, p2text, p3text, p4text
};

SDL_Texture *startGameText = nullptr;
SDL_Texture *startGameText2 = nullptr;

SDL_Texture *backToMenuText = nullptr;
SDL_Texture *backToMenuText2 = nullptr;

SDL_Texture *volumeoptionText = nullptr;
SDL_Texture *fullscreenoptionText = nullptr;
SDL_Texture *serveroptionText = nullptr;
SDL_Texture *onoptionText = nullptr;
SDL_Texture *offoptionText = nullptr;
SDL_Texture *onoptionText2 = nullptr;
SDL_Texture *offoptionText2 = nullptr;

SDL_Texture *nextText = nullptr;
SDL_Texture *nextText2 = nullptr;

SDL_Texture *text1 = nullptr;
SDL_Texture *text11 = nullptr;
SDL_Texture *text2 = nullptr;
SDL_Texture *text22 = nullptr;
SDL_Texture *text3 = nullptr;
SDL_Texture *text33 = nullptr;
SDL_Texture *text4 = nullptr;
SDL_Texture *text44 = nullptr;
SDL_Texture *text5 = nullptr;
SDL_Texture *text55 = nullptr;

SDL_Texture *retryText = nullptr;
SDL_Texture *retryText2 = nullptr;

//!Rects
SDL_Rect textRect;
SDL_Rect playtextRect;
SDL_Rect optionstextRect;
SDL_Rect quittextRect;
SDL_Rect loadingtextRect;
SDL_Rect choosechartextRect;
SDL_Rect waitingplayerstextRect;
SDL_Rect confirmtextRect;
SDL_Rect startgametextRect;
SDL_Rect count3textRect;
SDL_Rect count2textRect;
SDL_Rect count1textRect;
SDL_Rect countgotextRect;
SDL_Rect p1textRect;
SDL_Rect p2textRect;
SDL_Rect p3textRect;
SDL_Rect p4textRect;

SDL_Rect playertextRects[4] = {
    p1textRect, p2textRect, p3textRect, p4textRect
};

SDL_Rect gamemodetextRect;
SDL_Rect gameroundstextRect;
SDL_Rect deathmatchtextRect;
SDL_Rect lastmanstandingtextRect;
SDL_Rect rounds5textRect;
SDL_Rect rounds10textRect;
SDL_Rect rounds15textRect;
SDL_Rect rounds20textRect;
SDL_Rect gamemodepickertextRect;
SDL_Rect continuetextRect;

SDL_Rect menubgrnd;
SDL_Rect tilerect;
SDL_Rect blockrect;
SDL_Rect playbuttonRect;
SDL_Rect optionsbuttonRect;
SDL_Rect quitbuttonRect;
SDL_Rect confirmbuttonRect;
SDL_Rect continuebuttonRect;
SDL_Rect bgrnd;
SDL_Rect titleRect;
SDL_Rect boardRect;
SDL_Rect smallboardRect;
SDL_Rect startgamebuttonRect;
SDL_Rect arrowbuttonRect;
SDL_Rect skullRect;

SDL_Rect bigbuttonRect;
SDL_Rect bigbutton2Rect;

SDL_Rect singletextRect;
SDL_Rect multitextRect;
SDL_Rect playermodeRect;

SDL_Rect playerstatsRect;
SDL_Rect playerstats2Rect;
SDL_Rect bigbuttonstatsRect;
SDL_Rect menubuttonstatsRect;
SDL_Rect backtomenutextRect;

SDL_Rect ipaddresstextRect;
SDL_Rect volumeoptiontextRect;
SDL_Rect fullscreenoptiontextRect;
SDL_Rect serveroptiontextRect;
SDL_Rect onoffbuttonRect;
SDL_Rect onoffbuttonRect2;
SDL_Rect onoptiontextRect;
SDL_Rect offoptiontextRect;
SDL_Rect serverfieldRect;
SDL_Rect winnertextRect;
SDL_Rect nextbuttonRect;
SDL_Rect nexttextRect;

SDL_Rect lvl1buttonRect;
SDL_Rect lvl2buttonRect;
SDL_Rect lvl3buttonRect;
SDL_Rect lvl4buttonRect;
SDL_Rect lvl5buttonRect;

SDL_Rect text1Rect;
SDL_Rect text2Rect;
SDL_Rect text3Rect;
SDL_Rect text4Rect;
SDL_Rect text5Rect;

SDL_Rect retrybuttonRect;
SDL_Rect retrytextRect;