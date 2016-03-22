
#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include "bitmapdll.h"

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
struct PointXY
{
//static const float PI = 3.141592654;
static const float PI;

float x, y;
int AngleDegrees, Radius;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void RotateDegrees( int degrees )
{
	AngleDegrees += degrees;
	AngleDegrees = AngleDegrees % 360;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ConvertPolar2Rectangular()
{
	x = cos( AngleDegrees * PI/180 ) * Radius;
	y = -sin( AngleDegrees * PI/180 ) * Radius;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float PointXY::PI = 3.141592654;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
class GameObject
{
public:
  static const float PI;
  static const int ID_NOTHING = 0,
    ID_ASTEROID = 1,
    ID_SHIP = 2,
    ID_PROJECTILE = 3,
    ID_SCOREBAR = 4,
    ID_EXPLODING_SHIP = 5;
  static const int SCREEN_WIDTH_PIXELS = 800, SCREEN_HEIGHT_PIXELS = 600;
  
  int Id;
  static void *ItsWorld;
  
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
GameObject()
{
  Id = ID_NOTHING;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*  
virtual void Do() {}
virtual void Draw() {}
virtual void InputKey( int pressflag, int vk_code ) {}
virtual void InputMouse() {}
virtual void InputGamePad() {}
virtual ~GameObject() {}

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
static float Distance( float X1, float Y1, float X2, float Y2 )
{
    return sqrt( (X1 - X2) * (X1 - X2) +  (Y1 - Y2) * (Y1 - Y2));
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void *GameObject::ItsWorld = NULL;

const float GameObject::PI = 3.141592654;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
class Asteroid : public GameObject
{
public:
  static const int MAX_VERTICES = 10;
  static const int BORDER_PIXELS = 50;
  
  PointXY VertexList[MAX_VERTICES];
  Point PointList[MAX_VERTICES];
  float X_Center, Y_Center;
  int AverageRadius, Angle;
  
  static const float SPEED;  
  static const int MIN_RADIUS = 10, MAX_RADIUS = 40;
  static const int RADIUS_VARIATION = 4, ROTATE_DEGREES_SPEED = 2;
  static const int CHILD_COUNT = 5;
 
Asteroid();  
void Init(int nAverageRadius, int xcenter, int ycenter);
void Do();
void Draw();
void BreakUp();
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float Asteroid::SPEED = 3.0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
class Ship : public GameObject
{
public:
  static const int MAX_VERTICES = 3;
  static const int SHIP_RADIUS = 20;
  static const int MAX_VECTORS = 359;
  static const float SPEED_INCREMENT;
  static const float MAX_SPEED;
  static const float FRICTION;
  static const int BORDER_PIXELS = SHIP_RADIUS * 2;
  
  PointXY VertexList[MAX_VERTICES];
  Point PointList[MAX_VERTICES];
  float X_Center, Y_Center;
  int Angle;
  float Vectors[MAX_VECTORS];
  float X_Sum, Y_Sum;
  
  static const int MAX_PROJECTILES = 10;
  static const int PROJECTILE_DELAY = 5;
  int ProjectileDelayCounter;
  
  static const int WARP_DELAY = 5;
  int WarpCounter, WarpFlag;
  
Ship();
void Do();
void Draw();
void InputKey( int pressflag, int vk_code ); 

protected:
    
int AccelerateFlag, ShootFlag, RotateLeftFlag, RotateRightFlag;
    
void ProcessVectors();
void Shoot();
void Accelerate();
void Rotate( int degrees );   
void UpdatePointList();
void Warp();
int CheckCollide();
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float Ship::SPEED_INCREMENT = 0.70;
const float Ship::MAX_SPEED = 10.0;
const float Ship::FRICTION = -0.3;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
class ExplodingShip : public GameObject
{
public:
  static const int MAX_SEGMENTS = 3;
  static const float SPEED;
  static const int LIFE_SPAN_TICKS = 50;
  
  int X1_List[MAX_SEGMENTS];
  int Y1_List[MAX_SEGMENTS];
  int X2_List[MAX_SEGMENTS];
  int Y2_List[MAX_SEGMENTS];  
  int AngleList[MAX_SEGMENTS];
  int LifeSpanTicks;

ExplodingShip( Ship *pShip );
void Do();
void Draw();
  
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float ExplodingShip::SPEED = 4.0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
class Projectile : public GameObject
{
public:    
    static const float SPEED;
    static const int LIFE_SPAN_TICKS = 30;
    static const int RADIUS = 5;
    
    float X_Center, Y_Center;
    int Angle, TickCount;     
    float X_Speed_Plus, Y_Speed_Plus;

Projectile( float xcenter, float ycenter, int angle );
void Do();
void Draw();
int CheckCollide();      
void AddSpeed( float x_sum, float y_sum );
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

const float Projectile::SPEED = 20.0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
class ScoreBar : public GameObject
{
public:
  static const int GAME_STATE_GAME_OVER = 0;
  static const int GAME_STATE_PLAYING = 1;
  static const int GAME_STATE_SHIP_DEAD = 2;
  static int GameState;
  
  static int CurrentLives, CurrentLevel, CurrentScore, HighScore;

ScoreBar();
void Do();
void Draw();  
void InputKey( int pressflag, int vk_code );
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
class World
{
  public:
   static const int MAX_GAME_OBJECTS = 1000;
   GameObject *GameObjectList[MAX_GAME_OBJECTS];
   //SoundBox ItsSoundBox;

World();
void Init(int level);
void Do();
void Draw();
void InputKey( int pressflag, int vk_code);
void Add( GameObject *obj );
int GetCount( int Object_Id );

/*
Using DrawLine() as wrapper for Bitmap_Dll_Loader::Bitmap_DrawLine to workaround 
the segmentation fault issue that happened when the latter function is called

This problem appeared when the program is compiled with Orwell DevCpp.
*/

void PlaySound( int index );
};
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
Asteroid::Asteroid()
{
    Id = ID_ASTEROID;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
void Asteroid::Init(int nAverageRadius, int xcenter, int ycenter )
{ 
  if( nAverageRadius <= 0 )
  {
     AverageRadius =  MAX_RADIUS;
     X_Center = rand() % SCREEN_WIDTH_PIXELS;
     Y_Center = rand() % SCREEN_HEIGHT_PIXELS;     
  }
  else
  {
    X_Center = xcenter; Y_Center = ycenter;
    AverageRadius = nAverageRadius;
  }
  
  int i;
  for( i = 0; i < MAX_VERTICES; i++ )
  {
  	 VertexList[i].AngleDegrees = 360/MAX_VERTICES * i;
  	 VertexList[i].Radius = abs(AverageRadius - rand() % RADIUS_VARIATION);  	 
  	 VertexList[i].ConvertPolar2Rectangular();  	 
  	 PointList[i].X = VertexList[i].x + X_Center;  PointList[i].Y = VertexList[i].y + Y_Center;
  }
  Angle = rand() % 360;
	
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Asteroid::Do()
{
    
  int i;
  for( i = 0; i < MAX_VERTICES; i++ )
  {
  	 VertexList[i].AngleDegrees = ( VertexList[i].AngleDegrees + ROTATE_DEGREES_SPEED ) % 360;	 
  	 VertexList[i].ConvertPolar2Rectangular();
  	 PointList[i].X = VertexList[i].x + X_Center;  PointList[i].Y = VertexList[i].y + Y_Center;
  }
  
  X_Center += SPEED * cos(Angle * PI/180);
  Y_Center += SPEED * sin(Angle * PI/180);
  
  if( X_Center < -BORDER_PIXELS )
      X_Center = SCREEN_WIDTH_PIXELS + BORDER_PIXELS - 1;
  else
  if( X_Center > SCREEN_WIDTH_PIXELS + BORDER_PIXELS )
      X_Center = -BORDER_PIXELS + 1;

  if( Y_Center < -BORDER_PIXELS )
      Y_Center = SCREEN_HEIGHT_PIXELS + BORDER_PIXELS - 1;
  else
  if( Y_Center > SCREEN_HEIGHT_PIXELS + BORDER_PIXELS )
      Y_Center = -BORDER_PIXELS + 1;
            
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Asteroid::Draw()
{
    Bitmap_Dll_Loader::Bitmap_DrawPolygon( 1, PointList, MAX_VERTICES ); 	 
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*    
void Asteroid::BreakUp()
{       
   World *WorldPtr = (World*)ItsWorld;
   Id = ID_NOTHING;
 
   if( AverageRadius/2 < MIN_RADIUS )
       return;
          
   int i;
   Asteroid *as;
   
   for( i = 0; i < CHILD_COUNT; i++ )
   {
      as = new Asteroid();
      as->Init(AverageRadius/2, X_Center, Y_Center);
      WorldPtr->Add(as);
   }
     
   //WorldPtr->ItsSoundBox.PlaySound(1);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~* 
World::World()
{
 int i;
 for( i = 0; i < MAX_GAME_OBJECTS; i++ )
      GameObjectList[i] = NULL;

/*
 ItsSoundBox.LoadSound(0, "c:/windows/media/tada.wav");
 ItsSoundBox.LoadSound(1, "c:/windows/media/notify.wav");      
*/  

}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*       
void World::Init(int level)
{

 int i;
 for( i = 0; i < MAX_GAME_OBJECTS; i++ )
 {
     if( GameObjectList[i] != NULL )
      if( GameObjectList[i]->Id != GameObject::ID_SCOREBAR )
      {
         delete GameObjectList[i];         
         GameObjectList[i] = NULL;
      }
 }
 
 Asteroid *as;
      
 for( i = 0; i < level + 3; i++ )
 {
    as = new Asteroid();
    as->Init(0,0,0);
    Add( (GameObject*)as );
 }
 
 Ship *ship = new Ship();
 Add(ship);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::Do()
{   
	int i;
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] != NULL )
	   {
	       GameObjectList[i]->Do();
	       if( GameObjectList[i]->Id == GameObject::ID_NOTHING )
	       {
	          delete GameObjectList[i];
	          GameObjectList[i] = NULL;
	       }
       }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::Draw()
{
	int i;
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] != NULL )
	       GameObjectList[i]->Draw();
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::InputKey(int pressflag, int vk_code)
{
	int i;
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] != NULL )
	       GameObjectList[i]->InputKey(pressflag, vk_code);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::Add( GameObject *obj )
{
	int i;
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] == NULL )
	   {
	      GameObjectList[i] = obj;
          break;
       }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int World::GetCount( int Object_Id )
{    
	int i, count = 0;
	
	for( i = 0; i < MAX_GAME_OBJECTS; i++ )
	   if( GameObjectList[i] != NULL )
	     if( GameObjectList[i]->Id == Object_Id )
	         count++;
    
    return count;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void World::PlaySound( int index )
{
  Bitmap_Dll_Loader::Sound_PlayWaveFile(index);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
Ship::Ship()
{
   Id = ID_SHIP;
   
   X_Center = SCREEN_WIDTH_PIXELS/2; Y_Center = SCREEN_HEIGHT_PIXELS/2;
   Angle = 90;
   
   int i;
   
   for( i = 0; i < MAX_VERTICES; i++ )
   {
     if( i == 0 )
       VertexList[i].AngleDegrees = Angle - 140;
     else
     if( i == 1 )
       VertexList[i].AngleDegrees = Angle;
     else
     if( i == 2 )
       VertexList[i].AngleDegrees = Angle + 140;
     
     VertexList[i].AngleDegrees %= 360;
     VertexList[i].Radius = SHIP_RADIUS;
     VertexList[i].ConvertPolar2Rectangular();
     PointList[i].X = VertexList[i].x + X_Center;
     PointList[i].Y = VertexList[i].y + Y_Center;
   }
   for( i = 0; i < MAX_VECTORS; i++ )
     Vectors[i] = 0.0;
     
   AccelerateFlag = ShootFlag = RotateLeftFlag = RotateRightFlag = 0;
   ProjectileDelayCounter = 0;
   WarpCounter = WarpFlag = 0;
   X_Sum = Y_Sum = 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Do()
{
    if( WarpFlag == 1 )
    {
       WarpCounter++;
       
       if( WarpCounter > WARP_DELAY )
       {
           WarpCounter = 0;
           WarpFlag = 0;
           
           X_Center = rand() % SCREEN_WIDTH_PIXELS ; 
           Y_Center = rand() % SCREEN_HEIGHT_PIXELS;
       }
    }
    
    ProcessVectors();
    CheckCollide();
    
  if( X_Center < -BORDER_PIXELS )
      X_Center = SCREEN_WIDTH_PIXELS + BORDER_PIXELS - 1;
  else
  if( X_Center > SCREEN_WIDTH_PIXELS + BORDER_PIXELS )
      X_Center = -BORDER_PIXELS + 1;

  if( Y_Center < -BORDER_PIXELS )
      Y_Center = SCREEN_HEIGHT_PIXELS + BORDER_PIXELS - 1;
  else
  if( Y_Center > SCREEN_HEIGHT_PIXELS + BORDER_PIXELS )
      Y_Center = -BORDER_PIXELS + 1;      
      
 
  if( AccelerateFlag == 1 )
      Accelerate();  
  if( RotateLeftFlag == 1 )
      Rotate(16);
  if( RotateRightFlag == 1 )
      Rotate(-16);
  if( ShootFlag == 1 )
  {
    if( ProjectileDelayCounter <= 0 )
    {
      Shoot();               
      ProjectileDelayCounter = PROJECTILE_DELAY; 
    }
  }
  
  if( ProjectileDelayCounter > 0 )      
      ProjectileDelayCounter--;    
         
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Draw()
{
    int pen_index = 0;
    
    if( WarpFlag == 1 )
        pen_index = 3;
    else
        pen_index = 2;
        
    Bitmap_Dll_Loader::Bitmap_DrawPolygon( pen_index, PointList, MAX_VERTICES ); 
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::InputKey( int pressflag, int vk_code )
{    
   World *WorldPtr = (World*)ItsWorld;
   
   if( pressflag == 1 )
   {
     switch( vk_code )
     {
       case VK_UP:     
         AccelerateFlag = 1;     
         //Accelerate();
         break;
       case VK_DOWN:
         break;
       case VK_LEFT:   
         RotateLeftFlag = 1;
         //Rotate(8);
         break;
       case VK_RIGHT:    
         RotateRightFlag = 1;  
         //Rotate(-8);  
         break;
       case 'F':
         ShootFlag = 1;
         //WorldPtr->ItsSoundBox.PlaySound(0);
         //WorldPtr->ItsSoundBox.PlaySound(1);
         //Shoot();
         break;
       case 'W':
         Warp();
         break;
       default:
         break; 
     }
   }
   else
   if( pressflag == 0 )
   {
     switch( vk_code )
     {
       case VK_UP:     
         AccelerateFlag = 0;     
         break;
       case VK_DOWN:
         break;
       case VK_LEFT:   
         RotateLeftFlag = 0;
         break;
       case VK_RIGHT:    
         RotateRightFlag = 0;   
         break;
       case 'F':
         ShootFlag = 0;
         break;
       default:
         break; 
     }
   }   
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::ProcessVectors()
{
   int i;
   float sum_x = 0, sum_y = 0;
   
   for( i = 0; i < MAX_VECTORS; i++ )
   {
     sum_x += Vectors[i] * cos(i * PI/180);
     sum_y += Vectors[i] * -sin(i * PI/180);   
   }
   
   X_Center += sum_x;
   Y_Center += sum_y;

   X_Sum = sum_x; Y_Sum = sum_y;
   
   for( i = 0; i < MAX_VECTORS; i++ )
   {
     Vectors[i] += FRICTION;
     if( Vectors[i] < 0 )
         Vectors[i] = 0;
   }    
   UpdatePointList();
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Shoot()
{   
   World *WorldPtr = (World*)ItsWorld;
   
   if( WorldPtr->GetCount(ID_PROJECTILE) < MAX_PROJECTILES )
   {
     Projectile *proj = new Projectile( X_Center, Y_Center, Angle );      
     proj->AddSpeed( X_Sum, Y_Sum );
     WorldPtr->Add(proj);   
   }
   
  WorldPtr->PlaySound(0);
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Accelerate()
{
    Vectors[Angle] += SPEED_INCREMENT;
    if( Vectors[Angle] > MAX_SPEED )
        Vectors[Angle] = MAX_SPEED;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Rotate( int degrees )
{
    Angle += degrees;
    
    if( Angle < 0 )
    {
       Angle = 360 + Angle;
    }
    else
    {
       Angle = Angle % 360;
    }
    
    UpdatePointList();  
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::UpdatePointList()
{
   int i;
   
   for( i = 0; i < MAX_VERTICES; i++ )
   {
     if( i == 0 )
       VertexList[i].AngleDegrees = Angle - 140;
     else
     if( i == 1 )
       VertexList[i].AngleDegrees = Angle;
     else
     if( i == 2 )
       VertexList[i].AngleDegrees = Angle + 140;
              
     VertexList[i].AngleDegrees %= 360;
     VertexList[i].Radius = SHIP_RADIUS;
     VertexList[i].ConvertPolar2Rectangular();
     PointList[i].X = VertexList[i].x + X_Center;
     PointList[i].Y = VertexList[i].y + Y_Center;
   }      
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Ship::Warp()
{
  World *WorldPtr = (World *)ItsWorld;
  
  if( WarpFlag == 0 )
  {  
    WarpCounter = 0; WarpFlag = 1;
    WorldPtr->PlaySound(2);
  }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Ship::CheckCollide()
{
  World *WorldPtr = (World*)ItsWorld;
  GameObject *go;
  Asteroid *ast;
  ExplodingShip *es;
  float distance;
  int CollideFlag = 0;

  int i; 
  for( i = 0; i < World::MAX_GAME_OBJECTS; i++ )
  {
     go = WorldPtr->GameObjectList[i];
     
     if( go != NULL )
      if( go->Id == ID_ASTEROID )
      {
        ast = (Asteroid *)go;
        distance = Distance( X_Center, Y_Center, ast->X_Center, ast->Y_Center );
        if( distance <= ast->AverageRadius )
        {
            CollideFlag = 1;
            break;
        }
      }
  }
  
  if( CollideFlag == 1 )
  {
      Id = ID_NOTHING;      
      es = new ExplodingShip(this);
      WorldPtr->Add(es);      
      
      WorldPtr->PlaySound(3);
  }
  return CollideFlag;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
ExplodingShip::ExplodingShip( Ship *pShip )
{
   Id = ID_EXPLODING_SHIP;   
   
    int i;
    
    X1_List[0] = pShip->PointList[0].X;
    Y1_List[0] = pShip->PointList[0].Y;
    X2_List[0] = pShip->PointList[1].X;
    Y2_List[0] = pShip->PointList[1].Y;    
    
    X1_List[1] = pShip->PointList[1].X;
    Y1_List[1] = pShip->PointList[1].Y;
    X2_List[1] = pShip->PointList[2].X;
    Y2_List[1] = pShip->PointList[2].Y;    
    
    X1_List[2] = pShip->PointList[2].X;
    Y1_List[2] = pShip->PointList[2].Y;
    X2_List[2] = pShip->PointList[0].X;
    Y2_List[2] = pShip->PointList[0].Y;     
    
    for( i = 0; i < MAX_SEGMENTS; i++ )
       AngleList[i] = rand() % 360;     
     
    LifeSpanTicks = LIFE_SPAN_TICKS;     
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ExplodingShip::Do()
{
    int i;
  
    for( i = 0; i < MAX_SEGMENTS; i++ )
    {
       X1_List[i] += cos(AngleList[i] * PI/180) * SPEED;
       Y1_List[i] += sin(AngleList[i] * PI/180) * SPEED;
       X2_List[i] += cos(AngleList[i] * PI/180) * SPEED;
       Y2_List[i] += sin(AngleList[i] * PI/180) * SPEED;
    }

    if( LifeSpanTicks <= 0 )
    {
      Id = ID_NOTHING;  
      ScoreBar::GameState = ScoreBar::GAME_STATE_SHIP_DEAD;
    }
    else
      LifeSpanTicks--;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ExplodingShip::Draw()
{
    int i;
    World *WorldPtr = (World*)ItsWorld;
    
     for( i = 0; i < MAX_SEGMENTS; i++ )
        Bitmap_Dll_Loader::Bitmap_DrawLine( 0, X1_List[i], Y1_List[i], X2_List[i], Y2_List[i] );
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
/*
class Projectile : public GameObject
{
public:
    static const float SPEED = 5.0;
    static const int LIFE_SPAN_TICKS = 40;
    static const int RADIUS = 5;
    
    float X_Center, Y_Center;
    int Angle;
    
Projectile( float xcenter, float ycenter, int angle );
void Do();
void Draw();
int CheckCollide();        
};
*/
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
Projectile::Projectile( float xcenter, float ycenter, int angle )
{
   Id = ID_PROJECTILE;
   X_Center = xcenter; Y_Center = ycenter;
   Angle = angle;
   TickCount = LIFE_SPAN_TICKS;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Projectile::Do()
{
    X_Center += SPEED * cos(Angle * PI/180 ) + X_Speed_Plus;
    Y_Center += SPEED * -sin(Angle * PI/180 ) + Y_Speed_Plus;
    
    if( TickCount <= 0 )
        Id = ID_NOTHING;
    else
        TickCount--;
        
    CheckCollide();
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Projectile::Draw()
{
  Bitmap_Dll_Loader::Bitmap_DrawEllipse( 0, X_Center - RADIUS, Y_Center - RADIUS, RADIUS * 2, RADIUS * 2 );     
/*  
  char str[100];
  sprintf( str, "proj %d", ProjectileCount );
  Bitmap_Dll_Loader::Bitmap_DrawTextGDI( str, 10, 380, 0 );
*/  
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int Projectile::CheckCollide()
{
   World *WorldPtr = (World*)ItsWorld;
   GameObject *go;
   Asteroid *ast;
   int CollideFlag = 0;
   int distance;
   
  int i; 
  for( i = 0; i < World::MAX_GAME_OBJECTS; i++ )
  {
     go = WorldPtr->GameObjectList[i];
     
     if( go != NULL )
      if( go->Id == ID_ASTEROID )
      {
        ast = (Asteroid *)go;
        distance = Distance( X_Center, Y_Center, ast->X_Center, ast->Y_Center );
        if( distance <= ast->AverageRadius )
        {
            CollideFlag = 1;
            break;
        }
      }
  }   
  
  if( CollideFlag == 1 )
  {
    Id = ID_NOTHING;
    ast->BreakUp();
    ScoreBar::CurrentScore += 10;
    WorldPtr->PlaySound(1);
  }
  
  return CollideFlag;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void Projectile::AddSpeed( float x_sum, float y_sum )
{
    X_Speed_Plus = x_sum;  Y_Speed_Plus = y_sum;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
/*
class ScoreBar : public GameObject
{
public:
  static const int GAME_STATE_GAME_OVER = 0;
  static const int GAME_STATE_PLAYING = 1;
  static const int GAME_STATE_SHIP_DEAD = 2;
  static int GameState;
  
  static int CurrentLives, CurrentLevel, CurrentScore, HighScore;

ScoreBar();
ScoreBar::void Do();
ScoreBar::void Draw();  
};
*/ 
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
ScoreBar::ScoreBar()
{
  Id = ID_SCOREBAR;
  GameState = GAME_STATE_PLAYING;
  CurrentLives = 3; CurrentLevel = 1; CurrentScore = 0; HighScore = 0;
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ScoreBar::Do()
{
   World *WorldPtr = (World*)ItsWorld;
   
   if( GameState == GAME_STATE_SHIP_DEAD )
   {
     if( CurrentLives > 0 )
     {
         Ship *ship = new Ship();         
         WorldPtr->Add(ship);
         GameState = GAME_STATE_PLAYING;
         CurrentLives = CurrentLives - 1;
     }
     else
     {
        GameState = GAME_STATE_GAME_OVER;
        
        if( CurrentScore > HighScore )
            HighScore = CurrentScore;
     }
   }
   else
   if( GameState == GAME_STATE_PLAYING )
   {
     if( WorldPtr->GetCount(ID_ASTEROID) <= 0 )  
     {
        CurrentLevel++;
        WorldPtr->Init(CurrentLevel);
     }
   }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ScoreBar::Draw()
{ 
  World *WorldPtr = (World *)ItsWorld;
  
  char str[1000];
  sprintf(str,"SHIP x %2d  LEVEL %2d  SCORE %10d  HIGHSCORE %10d", CurrentLives, CurrentLevel,
      CurrentScore, HighScore );
      
  Bitmap_Dll_Loader::Bitmap_DrawTextGDI( str, 5, 10, 0 );
  
  if( GameState == GAME_STATE_GAME_OVER )
       Bitmap_Dll_Loader::Bitmap_DrawTextGDI( "Game Over", GameObject::SCREEN_WIDTH_PIXELS/2.2, GameObject::SCREEN_HEIGHT_PIXELS/2, 0 );          
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
void ScoreBar::InputKey( int pressflag, int vk_code )
{
    World *WorldPtr = (World*)ItsWorld;
    
    if( pressflag == 1 )
    {
       if( GameState == GAME_STATE_GAME_OVER )
       {
          CurrentLives = 3; CurrentLevel = 1; CurrentScore = 0;
          GameState = GAME_STATE_PLAYING;          
          WorldPtr->Init(1);
       }
    }
}
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
int ScoreBar::GameState = ScoreBar::GAME_STATE_PLAYING;
int ScoreBar::CurrentLives = 3;
int ScoreBar::CurrentLevel = 1;
int ScoreBar::CurrentScore = 0;
int ScoreBar::HighScore = 0;

//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
//########################################################################################
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
#endif
