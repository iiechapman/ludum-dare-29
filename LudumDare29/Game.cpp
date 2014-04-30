//
//  Game.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <cmath>
#include "Game.h"
#include "SoundManager.h"
#include "InputHandler.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Trail.h"
#include "Spike.h"
#include "Powerup.h"
#include <ctime>


Game* Game::s_pInstance = 0;
int Game::m_bubblesPerMile = 20;
int Game::m_milesPassed = 0;
int Game::m_bubblesPassed = 0;
int Game::s_level = 5;



Game* Game::Instance(){
    if (!s_pInstance){
        s_pInstance = new Game();
    }
    return s_pInstance;
}

Game::Game()
:m_running(true){
    cout << "Created new Game\n";
}

Game::~Game(){
    cout << "Deleting Game\n";
}

bool Game::running(){
    return m_running;
}

SDL_Renderer* Game::getRenderer(){
    return m_pRenderer;
}

vector<GameObject*> Game::GetObjects(string layer){
    if (layer == "gameobject"){
        return m_gameObjects;
    }
    
    if (layer == "foreground"){
        return m_foregroundObjects;
    }
    
    if (layer == "background"){
        return m_backgroundObjects;
    }
    
    
    return m_gameObjects;
}

bool Game::init(int width, int height, string name){
    cout << "Init game\n";
    
    m_Name = name;
    
    // Initialize the SDL library.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return false;
	}
	
	m_pWindow = SDL_CreateWindow(m_Name.c_str(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,
                                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_WarpMouseInWindow(m_pWindow, 300, 320);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(SDL_FALSE);
    TTF_Init();
    
    if (m_pWindow && m_pRenderer){
        cout << "Created window and renderer successfully\n";
        return true;
    }
    
    return false;
}

void Game::handleEvents(){
    InputHandler::Instance()->update();
}

void Game::update(){
    for (auto gameObject : m_gameObjects){
        gameObject->update();
    }
    
    for (auto gameObject : m_foregroundObjects){
        gameObject->update();
    }
    
    for (auto gameObject : m_backgroundObjects){
        gameObject->update();
    }
    
    cursor->GetParams().setY(InputHandler::Instance()->getMousePos().y - 31);
    cursor->GetParams().setX(InputHandler::Instance()->getMousePos().x - 20);
    
    ClearOffscreenObjects();
    
    m_mileCoolDownTimer--;
    
    if ((m_markerTimer >= m_markerTimerTick) && m_mileCoolDownTimer <=0){
        PlaceMarker();
        m_markerTimer = 0;
    }
    
    if (m_bubblesPassed >= m_bubblesPerMile){
        s_level++;
        if (s_level < 100){
            m_bubblesPerMile += s_level/4;
        }
        m_bubblesPassed = 0;
        m_milesPassed++;
        if (m_milesPassed > m_hiScore){
            m_hiScore = m_milesPassed;
        }
        PlaceMileMarker();
        m_mileCoolDownTimer = m_mileCoolDownTime;
    }

    
    m_trailSpeed = -s_level * m_trailSpeedMod;
    //cout << "Total objects on screen " << m_gameObjects.size() << endl;
    
    
}

void Game::resetMiles(){
    m_milesPassed = 0;
    m_bubblesPassed = 0;
}


void Game::ClearOffscreenObjects(){
    //clear old items off screen
    
    auto gameObject = m_backgroundObjects.begin();
    
    while (gameObject !=m_backgroundObjects.end()){
        if (((*gameObject)->GetParams().getX() < -500 ||
             (*gameObject)->GetParams().getY() < -500 )){
            delete (*gameObject);
            (*gameObject) = nullptr;
            gameObject = m_backgroundObjects.erase(gameObject);
        } else {
            gameObject++;
        }
    }
    
    
    gameObject = m_foregroundObjects.begin();
    
    while (gameObject !=m_foregroundObjects.end()){
        if (((*gameObject)->GetParams().getX() < -500 ||
             (*gameObject)->GetParams().getY() < -500 )){
            delete (*gameObject);
            (*gameObject) = nullptr;
            gameObject = m_foregroundObjects.erase(gameObject);
        } else {
            gameObject++;
        }
    }
    
    
    
    gameObject = m_gameObjects.begin();
    
    while (gameObject !=m_gameObjects.end()){
        if (*gameObject){
            if (((*gameObject)->GetParams().getX() < -100 ||
                 (*gameObject)->GetParams().getY() < -100 )){
                if ((*gameObject)->GetParams().getName() == "trail"){
                    m_bubblesPassed++;
                    //cout << "bubbles passed " << m_bubblesPassed << endl;
                }
                //cout << "object deleted\n";
                delete (*gameObject);
                (*gameObject) = nullptr;
                gameObject = m_gameObjects.erase(gameObject);
            } else {
                gameObject++;
            }
        }
    }
}

void Game::render(){
    SDL_SetRenderDrawColor(m_pRenderer, 0, 191, 255, 255);
    SDL_RenderClear(m_pRenderer);
    
    for (auto gameObject : m_backgroundObjects){
        gameObject->draw();
    }
    
    for (auto gameObject : m_gameObjects){
        gameObject->draw();
    }
    
    for (auto gameObject : m_foregroundObjects){
        gameObject->draw();
    }
    
    
    TTF_Font* font;
    
    SDL_Surface* text_surface;
    SDL_Texture* tempTexture;
    
    TTF_Init();
    // load font.ttf at size 16 into font
    font=TTF_OpenFont("font.ttf", 24);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    } else {
        //cout << "font loaded\n";
    }
    
    SDL_Color color={201,43,43};

    
    string normalscore = to_string(m_milesPassed);
    string hiScore = to_string(m_hiScore);
    
    SDL_Rect dst;
    dst.x = 260;
    dst.y = 580;
    dst.w = 60;
    dst.h = 80;
    
    if(!(text_surface=TTF_RenderText_Blended(font,normalscore.c_str(),color))) {
        //handle error here, perhaps print TTF_GetError at least
        cout << "failed to render text" <<endl;
    } else {
        //perhaps we can reuse it, but I assume not for simplicity.
        tempTexture = SDL_CreateTextureFromSurface(m_pRenderer, text_surface);
        SDL_RenderCopy(m_pRenderer, tempTexture, NULL, &dst);
        SDL_DestroyTexture(tempTexture);
        SDL_FreeSurface(text_surface);
        tempTexture = 0;
    }
    

    color={48,226,52};
    
    dst.x = 255;
    dst.y = 575;
    dst.w = 60;
    dst.h = 80;
    
    if(!(text_surface=TTF_RenderText_Solid(font,normalscore.c_str(),color))) {
        //handle error here, perhaps print TTF_GetError at least
        cout << "failed to render text" <<endl;
    } else {
        //perhaps we can reuse it, but I assume not for simplicity.
        tempTexture = SDL_CreateTextureFromSurface(m_pRenderer, text_surface);
        SDL_RenderCopy(m_pRenderer, tempTexture, NULL, &dst);
        SDL_DestroyTexture(tempTexture);
        SDL_FreeSurface(text_surface);
        tempTexture = 0;
    }
    

    

    //--------------------------------------
    
    
    //hi score
    color={201,43,43};
    dst.x = 1070;
    dst.y = 580;
    dst.w = 60;
    dst.h = 80;
    
    
    if(!(text_surface=TTF_RenderText_Solid(font,hiScore.c_str(),color))) {
        //handle error here, perhaps print TTF_GetError at least
        cout << "failed to render text" <<endl;
    } else {
        //perhaps we can reuse it, but I assume not for simplicity.
        tempTexture = SDL_CreateTextureFromSurface(m_pRenderer, text_surface);
        SDL_RenderCopy(m_pRenderer, tempTexture, NULL, &dst);
        SDL_DestroyTexture(tempTexture);
        SDL_FreeSurface(text_surface);
        tempTexture = 0;
    }
    
    
    color={48,226,52};
    dst.x = 1065;
    dst.y = 575;
    dst.w = 60;
    dst.h = 80;


    if(!(text_surface=TTF_RenderText_Solid(font,hiScore.c_str(),color))) {
        //handle error here, perhaps print TTF_GetError at least
        cout << "failed to render text" <<endl;
    } else {
        //perhaps we can reuse it, but I assume not for simplicity.
        tempTexture = SDL_CreateTextureFromSurface(m_pRenderer, text_surface);
        SDL_RenderCopy(m_pRenderer, tempTexture, NULL, &dst);
        SDL_DestroyTexture(tempTexture);
        SDL_FreeSurface(text_surface);
        tempTexture = 0;
    }
    
    SDL_FreeSurface(text_surface);

    TTF_CloseFont(font);
    TTF_Quit();
    

    //--------------------------------------
    
    cursor->draw();
    title->draw();
    score->draw();
    hi_score->draw();
    
    SDL_RenderPresent(m_pRenderer);
}

void Game::quit(){
    cout << "Quit action processed\n";
    m_running = false;
}

void Game::clean(){
    cout << "Cleaning game\n";
    
    if (m_pWindow){
        SDL_DestroyWindow(m_pWindow);
        SDL_DestroyRenderer(m_pRenderer);
        SDL_Quit();
    }
}

void Game::loadData(){
    m_trailSpeed = -s_level * m_trailSpeedMod;
    
    srand (static_cast<int>(time(NULL)));

    
    TextureManager::Instance()->load("title.png", "title", m_pRenderer);
    TextureManager::Instance()->load("score.png", "score", m_pRenderer);
    TextureManager::Instance()->load("best.png", "hi_score", m_pRenderer);
    TextureManager::Instance()->load("cursor.png", "cursor", m_pRenderer);
    TextureManager::Instance()->load("shipnew.png", "playership", m_pRenderer);
    TextureManager::Instance()->load("ship2.png", "enemyship", m_pRenderer);
    TextureManager::Instance()->load("bubble.png", "bubble", m_pRenderer);
    TextureManager::Instance()->load("smokebubble.png", "smokebubble", m_pRenderer);
    TextureManager::Instance()->load("entrancebubble.png", "entrance", m_pRenderer);
    TextureManager::Instance()->load("goalbubble.png", "goal", m_pRenderer);
    TextureManager::Instance()->load("spike.png", "spike", m_pRenderer);
    TextureManager::Instance()->load("badtrail.png", "bluetrail", m_pRenderer);
    TextureManager::Instance()->load("redtrail.png", "redtrail", m_pRenderer);
    TextureManager::Instance()->load("bg3.png", "bg1", m_pRenderer);
    
    TextureManager::Instance()->load("capsule_mini.png", "capsule_mini", m_pRenderer);
    TextureManager::Instance()->load("capsule_turbo.png", "capsule_turbo", m_pRenderer);
    TextureManager::Instance()->load("capsule_shield.png", "capsule_shield", m_pRenderer);
    
    
    
    SoundManager::Instance()->loadSound("sound/splash2.wav", "splash");
    SoundManager::Instance()->loadSound("sound/smallbubble2.wav", "smallbubble");
    SoundManager::Instance()->loadSound("sound/bubbles.wav", "bubbles");
    SoundManager::Instance()->loadSound("sound/bubble.wav", "bubble");
    SoundManager::Instance()->loadSound("sound/speedup.wav", "speedup");
    
    SoundManager::Instance()->loadSound("sound/blip.wav", "capsule_mini");
    SoundManager::Instance()->loadSound("sound/shield.wav", "capsule_shield");
    SoundManager::Instance()->loadSound("sound/turbo.wav", "capsule_turbo");
    
    SoundManager::Instance()->loadSound("sound/death.wav", "death");
    SoundManager::Instance()->loadSound("sound/shrink.wav", "losepowerup");
    
    SoundManager::Instance()->loadSong("sound/main2.ogg", "maintheme");
    
    SoundManager::Instance()->playSound("splash");
    SoundManager::Instance()->playSound("bubbles");
    SoundManager::Instance()->playSong("maintheme");
    
}

void Game::start(){

    
    title = new Background(new GameObjectParams("title",10,10,400,100,{0,0},false,false,"title"));
    cursor = new Background(new GameObjectParams("title",1000,300,49,49,{0,0},false,false,"cursor"));
    score = new Background(new GameObjectParams("score",5,590,200,50,{0,0},false,false,"score"));
    hi_score = new Background(new GameObjectParams("hi_score",850,590,200,50,{0,0},false,false,"hi_score"));
    
    
    m_backgroundObjects.push_back
    (new Background(new GameObjectParams("background",0,0,1136,640,{0,0},false,false,"bg1")));
    
    
    m_foregroundObjects.push_back
    (new Player(new GameObjectParams("player",-200,300,86,55,{0,0},false,false,"playership")));
    
    
    m_foregroundObjects.push_back
    (new Enemy(new GameObjectParams("enemy1",1100,40,75,46,{0,-1},false,true,"enemyship")));
    
    m_foregroundObjects.push_back
    (new Enemy(new GameObjectParams("enemy2",1100,560,75,46,{0,-1},false,true,"enemyship")));
    
    PlaceEntranceMarker();
    BubbleFill(100);
    BubbleSplash(100);
    
}

void Game::run(){
    
    //Tick timers
    m_trailTimer++;
    m_markerTimer++;
    m_spikeTimer++;
    m_powerupTimer++;
    
    //Speed up trail timer based on level
    m_trailTimerTick = 15 - s_level ;
    if (m_trailTimerTick <= 3 ){
        m_trailTimerTick = 3;
    }
    
    if (m_trailTimer >= m_trailTimerTick ){
        PlaceSpike();
        PlaceTrail();
        PlaceBubble();
        m_trailTimer = 0;
    }
    
    
    if (m_powerupTimer >= m_powerupTimerTick){
        PlacePowerup();
        m_powerupTimer = 0;
    }
    
    //Cap level so game isnt too fast
    if (s_level >= 80){
        s_level  = 80;
    }
    
    m_trailTimerTick = 50 / abs(m_trailSpeed);
    
    //Update all scrolling objects to match speed
    for (auto enemy : m_gameObjects){
        if (enemy->GetParams().isHazard()){
            enemy->GetParams().getVelocity().x = m_trailSpeed;
        }
    }
    
    for (auto enemy : m_foregroundObjects){
        if (enemy->GetParams().getName() == "entrance" ||
            enemy->GetParams().getName() == "trail" ||
            enemy->GetParams().getName() == "marker"||
            enemy->GetParams().getName() == "mile"
            ){
            enemy->GetParams().getVelocity().x = m_trailSpeed;
        }
    }
    
}

int Game::getLevel(){
    return s_level;
}

void Game::setLevel(int level){
    s_level = level;
    
    m_bubblesPerMile = 50;
    
    if (s_level <= 5){
        s_level = 5;
    }
}

void Game::BubbleFill(int numBubbles){
    //Add bubbles in background anywhere
    
    for (int i = 0 ; i < numBubbles ; i++){
        float randomSize =-(rand()%5) + 15 +(rand()%25) ;
        m_backgroundObjects.push_back
        (new Trail(new GameObjectParams("bubble",
                                        rand() % 1300,
                                        rand() % 700,
                                        randomSize,randomSize,
                                        {static_cast<float>(m_trailSpeed * (randomSize * .02)),0},false,false,"bubble")));
    }
}

void Game::BubbleSplash(int numBubbles){
    //Add bubbles in background anywhere and rise up
    
    for (int i = 0 ; i < numBubbles ; i++){
        float randomSize =-(rand()%5) + 15 +(rand()%45) ;
        m_backgroundObjects.push_back
        (new Trail(new GameObjectParams("splash",
                                        rand() % 1100,
                                        700 + rand() % 900,
                                        randomSize,randomSize,
                                        {0,-static_cast<float>((randomSize * .3))},false,false,"bubble")));
    }
}

void Game::PlaceBubble(){
    //Add bubbles in background
    int numBubbles = 3;
    for (int i = 0 ; i < numBubbles ; i++){
        float randomSize =-(rand()%14) + 15 +(rand()%25) ;
        m_backgroundObjects.push_back
        (new Trail(new GameObjectParams("bubble",
                                        1300,
                                        rand() % 700,
                                        randomSize,randomSize,
                                        {static_cast<float>(m_trailSpeed * (randomSize * .02)),0},false,false,"bubble")));
    }
    
}

void Game::PlaceBubble(string type ,int x, int y, float x_speed, float y_speed){
    //Add bubbles in background
    float randomSize =-(rand()%5) + 15 +(rand()%25) ;
    m_backgroundObjects.push_back
    (new Trail(new GameObjectParams("bubble",
                                    x,
                                    y,
                                    randomSize,randomSize,
                                    {m_trailSpeed * x_speed * randomSize,m_trailSpeed * y_speed * randomSize},false,false,type)));
    
}

void Game::PlaceEntranceMarker(){
    for (auto enemy : m_foregroundObjects){
        if (enemy->GetParams().isEnemy()){
            m_foregroundObjects.push_back
            (new Trail(new GameObjectParams("entrance",
                                            enemy->GetParams().getX() - 60,
                                            enemy->GetParams().getY() - 30,
                                            100,100,{m_trailSpeed,0},true,false,"entrance")));
        }
    }
}

void Game::PlaceSpike(){
    int placeSpike = rand() % (m_spikeOdds + s_level);
    
    if (placeSpike <= 80 - s_level){
        
        int endRange = Enemy::GetLowerBounds() - Enemy::GetUpperBounds() + 1 ;
        int beginRange = Enemy::GetUpperBounds() + 1;
        
        int position = rand() % endRange + beginRange;
        
        float randomSize =-(rand()%2) + 45 +(rand()%45) ;
        
        m_foregroundObjects.push_back
        (new Spike(new GameObjectParams("spike",
                                        1400,
                                        position ,
                                        randomSize,randomSize,
                                        {static_cast<float>(m_trailSpeed * (randomSize * .01)),0},true,false,"spike")));
        
    }
}

void Game::PlacePowerup(){
    int placePowerup = rand() % m_powerupOdds - s_level;
    
    //cout << "checking for powerup" << endl;
    
    if (placePowerup <= s_level){
        cout << "place powerup \n";
        int endRange = Enemy::GetLowerBounds() - Enemy::GetUpperBounds() + 1 ;
        int beginRange = Enemy::GetUpperBounds() + 1;
        int type = rand() % 3;
        int position = rand() % endRange + beginRange;
        
        float randomSize =-(rand()%2) + 45 +(rand()%45) ;
        
        switch (type) {
            case 0:
                m_foregroundObjects.push_back
                (new Powerup(new GameObjectParams("capsule_turbo",
                                                  1400,
                                                  position ,
                                                  100,50,
                                                  {static_cast<float>(m_trailSpeed * (randomSize * .005)),0},false,false,"capsule_turbo")));
                break;
                
            case 1:
                m_foregroundObjects.push_back
                (new Powerup(new GameObjectParams("capsule_mini",
                                                  1400,
                                                  position ,
                                                  100,50,
                                                  {static_cast<float>(m_trailSpeed * (randomSize * .005)),0},false,false,"capsule_mini")));
                break;
                
            case 2:
                m_foregroundObjects.push_back
                (new Powerup(new GameObjectParams("capsule_shield",
                                                  1400,
                                                  position ,
                                                  100,50,
                                                  {static_cast<float>(m_trailSpeed * (randomSize * .005)),0},false,false,"capsule_shield")));
                break;
                
            default:
                break;
        }
    }
}

void Game::PlaceTrail(){
    //Create trail every trail tick
    for (auto enemy : m_foregroundObjects){
        if (enemy != 0){
            if (enemy->GetParams().isEnemy()){
                m_gameObjects.push_back
                (new Trail(new GameObjectParams("trail",
                                                enemy->GetParams().getX() - 20,
                                                enemy->GetParams().getY(),
                                                40,40,{m_trailSpeed,0},true,false,"bluetrail")));
            }
        }
    }
}

void Game::PlaceMileMarker(){
    //Place "mile marker" buoys
    SoundManager::Instance()->playSound("speedup");
    
    for (auto enemy : m_foregroundObjects){
        if (enemy->GetParams().isEnemy()){
            m_foregroundObjects.push_back
            (new Trail(new GameObjectParams("mile",
                                            enemy->GetParams().getX() - 20,
                                            enemy->GetParams().getY() -10,
                                            70,70,{m_trailSpeed,0},true,false,"goal")));
        }
    }
    
}

void Game::PlaceMarker(){
    SoundManager::Instance()->playSound("smallbubble");
    //Place "pace marker" buoys
    for (auto enemy : m_foregroundObjects){
        if (enemy){
            if (enemy->GetParams().isEnemy()){
                m_foregroundObjects.push_back
                (new Trail(new GameObjectParams("marker",
                                                enemy->GetParams().getX() - 25,
                                                enemy->GetParams().getY() -5,
                                                50,50,{m_trailSpeed,0},true,false,"redtrail")));
            }
        }
    }
}


























































//END