//
// Created by 劉瑄穎 on 2020/12/31.
//
#include "Runner.h"

Runner *Runner::runnerInstance = NULL;

Character *createRunner(SDL_Point _mapPos, SDL_Point _pixelPos)
{
    return new Runner(_mapPos, _pixelPos);
}

character_list character;

const int ANIMATION_FRAMES = 3;
const int TOTAL_FRAMES = 12;
SDL_Rect Clip [TOTAL_FRAMES];

const int Runner::gridWidth = Map::getPixelWidth();
const int Runner::gridHeight = Map::getPixelHeight();
Runner::Runner(SDL_Point& InitialMapPos,SDL_Point& InitialPixelPos, character_list character):
Character("Runner"), strength(100), map(&Map::getMap()), width(gridWidth),
height(gridHeight), updateRate(10), direction(DOWN) 
{
    initclips();

    //set Initial PixelPos
    InitialPixelPos.x = 100;
    InitialPixelPos.y = 500;
    setPixelPos(InitialPixelPos);
    //set Initial MapPos
    SDL_Point tmp;
    tmp.x = InitialPixelPos.x + gridWidth/2;
    tmp.y = InitialPixelPos.y + gridHeight/2;
    InitialMapPos = map->pixelPosTomapPos(tmp);
    setMapPos(InitialMapPos);
    if (mode == 1) {
        /*posOnWindow->x = (int);
        posOnTexture->x = (int);
        posOnWindow->y = (int);
        posOnTexture->y = (int);
        posOnWindow->w = (int);
        posOnTexture->w = (int);
        posOnWindow->h = (int);
        posOnTexture->h = (int);*/
        runnerInstance = this;
        rectOnTexture = Clip[0];
        rectOnScreen.x = PixelPos.x;
        rectOnScreen.y = PixelPos.y;
        rectOnScreen.w = width;
        rectOnScreen.h = height;

        switch (character) {
            case BEAR:
                velocity = 1;
                sprint_velocity = 2;
                username = "bear";
                texture = loadImage(RUNNER_IMAGE);
                break;
        }
    }

    //randomly create Item
    /*Item* items[20];
    for(int i=0;i<20;i++)
    {
        SDL_Point a;
        a.x = Game::GetGame().rdEngine()%1280+1;
        a.y = Game::GetGame().rdEngine()%720+1;
        ItemList create;
        int tmp =Game::GetGame().rdEngine()%3;
        if(tmp==0){create = STAR;}
        else if(tmp == 1){create = POTION;}
        else if(tmp == 2){create = MEAT;}
        items[i]=createItem(create);
    }*/
}
void Runner::setMapPos(SDL_Point &Set)
{
    MapPos.x = Set.x;
    MapPos.y = Set.y;
}
void Runner::setPixelPos(SDL_Point &Set)
{
    PixelPos.x = Set.x;
    PixelPos.y = Set.y;
    // change PixelPos to top left
    PixelPos.x -=  width/2 ;
    PixelPos.y -=  height/2;
}

/*
void Runner::setScreenPos(SDL_Point& center)
{
    rectOnScreen.x = center.x - rectOnScreen.w/2;
    rectOnScreen.y = center.y - rectOnScreen.h/2;
}
 */
Runner::~Runner(){/*show win or lose*/}
SDL_Point Runner::getMapPos()const{return MapPos;}       // get big grid on map
SDL_Point Runner::getPixelPos()const                     // get small grid on map (center)
{
    SDL_Point center;
    center.x = PixelPos.x + width/2;
    center.y = PixelPos.y + height/2;
    return center;
}

Runner::Runner(Runner &runner)
{
    this->username = runner.username;
    this->direction = runner.direction;
    PixelPos.x = runner.PixelPos.x;
    PixelPos.y = runner.PixelPos.y;
    MapPos.x = runner.PixelPos.x;
    MapPos.y = runner.MapPos.y;
    velocity_x = runner.velocity_x;
    velocity_y = runner.velocity;
    velocity = runner.velocity;
    strength = runner.strength;
    sprint_velocity = sprint_velocity;
    width = runner.width;
    height = runner.height;
    updateRate = runner.updateRate;
    backpack = runner.backpack;
    map = runner.map;
}
void Runner::updateMapPos(SDL_Point& currentMappos)       // ask map for big grid and update MapPos
{currentMappos = map->getRunnerMapPos();}

bool Runner::handleEvents(SDL_Event &e)
{
    bool success=false;
    if(mode==1)
    {
        //if a key is pressed
        if(e.type==SDL_KEYDOWN )
        {
            //adjust velocity
            switch(e.key.keysym.sym)
            {
                case SDLK_s:
                    velocity_y = velocity;
                    velocity_x = 0;
                    direction = DOWN;
                    return  true;
                case SDLK_w:
                    velocity_y = -velocity;
                    velocity_x = 0;
					direction = UP;
                    return true;
                case SDLK_d:
                    velocity_x = velocity;
                    velocity_y = 0;
                    direction = RIGHT;
                    return true;
                case SDLK_a:
                    velocity_x = -velocity;
                    velocity_y = 0;
                    direction = LEFT;
                    return true;
                default:
                	return false;
            }
        }
       
        //if a key is released
        
        else if(e.type==SDL_KEYUP )
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_SPACE:
                    velocity -= sprint_velocity;
                    updateRate = 10;
                    return true;
                case SDLK_w:
                    velocity_y = 0;
                    return true;
                case SDLK_s:
                    velocity_y = 0;
                    return true;
                case SDLK_a:
                    velocity_x = 0;
                    return true;
                case SDLK_d:
                    velocity_x = 0;
                    return true;
            }
        }
        else if(e.type == ITEM_USED)
        {
            if(e.user.code == POTION){strength = 100;}
            if(e.user.code == MEAT){(*this)++;}
            return true;
        }
        
    }
    return success;
}

void Runner::move()
{
    //right and left
    PixelPos.x += velocity_x;
    //up and down
    PixelPos.y += velocity_y;
    //checkCollision();
}

bool Runner::checkbackpack()    // if backpack is empty return true
{
    if(backpack == NULL){return true;}
    else{return false;}
}

bool Runner::collisionBox(SDL_Rect& square)
{
    bool collision = true;
    if(PixelPos.x        > square.x+square.w){return false;}
    if(PixelPos.x+width  < square.x){return false;}
    if(PixelPos.y        < square.y+square.h){return false;}
    if(PixelPos.y+height > square.y){return false;}
    return collision;
}

void Runner::checkCollision()
{
    SDL_Point tmp;
    // right
    if(velocity_x>0)
    {
        // check right top
        tmp.x = MapPos.x+1;
        tmp.y = MapPos.y-1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
        // chek right middle
        tmp.x = MapPos.x+1;
        tmp.y = MapPos.y;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
        // check right bottom
        tmp.x = MapPos.x+1;
        tmp.y = MapPos.y+1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
    }

    // left
    if(velocity_x<0)
    {
        // check left top
        tmp.x = MapPos.x-1;
        tmp.y = MapPos.y-1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
        // chek left middle
        tmp.x = MapPos.x-1;
        tmp.y = MapPos.y;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
        // check left bottom
        tmp.x = MapPos.x-1;
        tmp.y = MapPos.y+1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
    }

    // up
    if(velocity_y<0)
    {
        // check top left
        tmp.x = MapPos.x-1;
        tmp.y = MapPos.y-1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
        // chek top middle
        tmp.x = MapPos.x;
        tmp.y = MapPos.y-1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
        // check top right
        tmp.x = MapPos.x+1;
        tmp.y = MapPos.y-1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
    }

    // down
    if(velocity_y>0)
    {
        // check below left
        tmp.x = MapPos.x-1;
        tmp.y = MapPos.y+1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
        // chek below middle
        tmp.x = MapPos.x;
        tmp.y = MapPos.y+1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
        // check below right
        tmp.x = MapPos.x+1;
        tmp.y = MapPos.y+1;
        if(map->isWall(tmp))
        {
            SDL_Rect wall;
            wall.x = tmp.x;
            wall.y = tmp.y;
            wall.w = gridWidth;
            wall.h = gridHeight;
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
    }
}

bool Runner::update()
{
	if(PixelPos.x < 50) PixelPos.x = 50;
	if(PixelPos.y < 50) PixelPos.y = 50;
	if(PixelPos.x > 1400) PixelPos.x = 1400;
	if(PixelPos.y > 1400) PixelPos.y = 1400;
	
	rectOnScreen.x = PixelPos.x ;
    rectOnScreen.y = PixelPos.y ;
    static int frame = 0;
    // move(update PixelPos)
    move();
    // deal strength
    if(velocity_x!=0||velocity_y!=0)
    {
        strength -= 0.0005;
        if(abs(velocity_x) == sprint_velocity+velocity || abs(velocity_y) == sprint_velocity+velocity)
        {strength -= 0.05;}
    }
    if(strength > 100)
    {
        strength = 100;
        velocity =4;
    }
    else if(strength > 75){velocity = 4;}
    else if(strength > 50 && strength<75){velocity = 3;}
    else if(strength > 25 && strength<50){velocity = 2;}
    else if(strength <25 && strength>0){velocity =1;}
    else if(strength <0)
    {
        strength = 0;
        velocity = 1;
    }
	//if(map->isWall(MapPos))
	//	printf("aaaaaaa");
    // use map function to calculate MapPos and update
    MapPos = map->mapPosTopixelPos(SDL_Point({PixelPos.x+width/2,PixelPos.y+height/2}));

    //Render current frame
    rectOnTexture = Clip[direction*3+frame/updateRate];
    //render??;

    // go to next frame
    frame ++;
    // cycle animation
    if(frame/updateRate == ANIMATION_FRAMES){frame=0;}

    return true;
}


int Runner::getStrength() const {return strength;}

void Runner::operator++(int) {strength += 30;}
void Runner::initclips()                // init render clips
{
    // Down
    Clip[0].x = 0;
    Clip[0].y = 0;
    Clip[0].w = 56;
    Clip[0].h = 56;

    Clip[1].x = 56;
    Clip[1].y = 0;
    Clip[1].w = 56;
    Clip[1].h = 56;

    Clip[2].x = 112;
    Clip[2].y = 0;
    Clip[2].w = 56;
    Clip[2].h = 56;

    //Left
    Clip[3].x = 0;
    Clip[3].y = 56;
    Clip[3].w = 56;
    Clip[3].h = 56;

    Clip[4].x = 56;
    Clip[4].y = 56;
    Clip[4].w = 56;
    Clip[4].h = 56;

    Clip[5].x = 112;
    Clip[5].y = 56;
    Clip[5].w = 56;
    Clip[5].h = 56;

    //Right
    Clip[6].x = 0;
    Clip[6].y = 112;
    Clip[6].w = 56;
    Clip[6].h = 56;

    Clip[7].x = 56;
    Clip[7].y = 112;
    Clip[7].w = 56;
    Clip[7].h = 56;

    Clip[8].x = 112;
    Clip[8].y = 112;
    Clip[8].w = 56;
    Clip[8].h = 56;

    //Up
    Clip[9].x = 0;
    Clip[9].y = 168;
    Clip[9].w = 56;
    Clip[9].h = 56;

    Clip[10].x = 56;
    Clip[10].y = 168;
    Clip[10].w = 56;
    Clip[10].h = 56;

    Clip[11].x = 112;
    Clip[11].y = 168;
    Clip[11].w = 56;
    Clip[11].h = 56;
}

