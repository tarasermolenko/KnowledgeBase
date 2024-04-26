#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float player_x_val, player_y_val, player_delta_x, player_delta_y, player_angle; // player positions to rotate player (deltax, deltay, angle)

#define mapX 8  // map width
#define mapY 8  // map height
#define mapS 64 // map cube size
#define PI 3.14159265
#define P2 PI / 2     // pie over 2
#define P3 3 * PI / 2 // 3/2pie
#define DR 0.0174533  // one degree in radians


int All_Textures[]=               //all 32x32 textures
{
 //Checkerboard
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 //Brick
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 //Window
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,    
       
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 

 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,   
       
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
 //Door
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,     

 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  

 0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,1,1,1,1,0,1, 1,0,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,   
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 
 
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,     
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,   
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,         
};


typedef struct
{
    int w, a, d, s;

} ButtonKeys;

ButtonKeys Keys;

double roundToNearest64th(double value)
{
    return round(value * 64) / 64;
}

// Function returns distance between player and array endpoint (aka hypot)
float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

float degToRad(float a) { return a * PI / 180.0; }

float FixAng(float a)
{
    if (a < 0)
        a += 2 * PI;
    if (a >= 2 * PI)
        a -= 2 * PI;
    return a;
}

//-----------------------------PLAYER----------------------------------------------

void drawPlayer2D()
{
    glColor3f(1, 1, 0);                     // Set the color for drawing. Here, (1,1,0) corresponds to yellow (RGB).
    glPointSize(8);                         // Set the size of points to be drawn to 8 pixels.
    glBegin(GL_POINTS);                     // Begin drawing points.
    glVertex2i(player_x_val, player_y_val); // Specify the position of the point, which represents the player's position.
    glEnd();                                // End drawing.

    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2i(player_x_val, player_y_val);
    glVertex2i(player_x_val + player_delta_x * 5, player_y_val + player_delta_y * 5);
    glEnd();
}

//-----------------------------MAP----------------------------------------------
int map[]=          //walls
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};

void drawMap2D()
{
    int x, y, x_offset, yo;
    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map[y * mapX + x] == 1)
            {
                glColor3f(1, 1, 1); // color of walls
            }
            else
            {
                glColor3f(0, 0, 0); // color of empy spaces
            }

            x_offset = x * mapS;
            yo = y * mapS;
            glBegin(GL_QUADS);
            // add / subtract 1 pixel to outline cubes
            glVertex2i(0 + x_offset + 1, 0 + yo + 1);
            glVertex2i(0 + x_offset + 1, mapS + yo - 1);
            glVertex2i(mapS + x_offset - 1, mapS + yo - 1);
            glVertex2i(mapS + x_offset - 1, 0 + yo + 1);
            glEnd();
        }
    }
}
//-----------------------------MAP----------------------------------------------

//-----------------------------RAYS----------------------------------------------

void drawRays2D()
{

    int r, map_x_value, map_y_vaue, map_position, depth_of_field;
    float ray_x_val = 0.0;
    float ray_y_val = 0.0;
    float x_offset = 0.0;
    float y_offset = 0.0;
    float final_distance = 0.0;

    float ray_angle = player_angle - DR * 30; // set ray angle to players angle

    if (ray_angle < 0)
    {
        ray_angle += 2 * PI;
    }
    else if (ray_angle > 2 * PI)
    {
        ray_angle -= 2 * PI;
    }

    for (r = 0; r < 60; r++) // cast ray
    {
        //---Check Horizontal Lines---
        ray_angle = ray_angle;
        depth_of_field = 0;
        float distanceHorizontal = 1000000; // we want shortest distance so mak defualt very high
        float horizontal_x = player_x_val;
        float horizontal_y = player_y_val;

        float aTan = -1 / tan(ray_angle); // negative inverse of tangent
        // need to know if a ray is looking up or down konw this by looking at a rays angle
        if (ray_angle > PI) // if greated than 180 deg then upwards
        {
            // round rays y position to nearest 64 value
            ray_y_val = ((int)(player_y_val / 64) * 64) - 0.0001;
            // rays x value is distance between player and rays y position * inverse Tan + players x position
            ray_x_val = (player_y_val - ray_y_val) * aTan + player_x_val;
            y_offset = -64;
            x_offset = -y_offset * aTan;
        }
        if (ray_angle < PI)
        {
            // round rays y position to nearest 64 value
            ray_y_val = ((int)(player_y_val / 64) * 64) + 64;
            // rays x value is distance between player and rays y position * inverse Tan + players x position
            ray_x_val = (player_y_val - ray_y_val) * aTan + player_x_val;
            y_offset = 64;
            x_offset = -y_offset * aTan;
        }
        if (ray_angle == 0 || ray_angle == PI) // if looking straigt left or right impossible to hit horizontal line
        {
            // round rays y position to nearest 64 value
            ray_x_val = player_x_val;
            ray_y_val = player_y_val;
            depth_of_field = 8;
        }
        while (depth_of_field < 8) // dont want to get caught in inf loop set max depth of field
        {
            map_x_value = (int)(ray_x_val) / 64;
            map_y_vaue = (int)(ray_y_val) / 64;
            map_position = map_y_vaue * mapX + map_x_value;
            // if map position less than array size
            // check inside the map
            if ((map_position) > 0 && map_position < mapX * mapY && map[map_position] == 1) // hit wall if value is 1
            {
                horizontal_x = ray_x_val;
                horizontal_y = ray_y_val;
                distanceHorizontal = dist(player_x_val, player_y_val, horizontal_x, horizontal_y, ray_angle);
                depth_of_field = 8; // hit wall done shut it down
            }
            else // if didnt hit wall to check next horizontal line add the x and y offset
            {
                ray_x_val += x_offset;
                ray_y_val += y_offset;
                depth_of_field += 1;
            }
        }

        //---Check Vertical Lines---
        depth_of_field = 0;
        float negativeTan = -tan(ray_angle); // negative inverse of tangent
        float distanceVertical = 1000000;    // we want shortest distance so mak defualt very high
        float vertical_x = player_x_val;
        float vertical_y = player_y_val;

        // need to know if a ray is looking up or down konw this by looking at a rays angle
        if (ray_angle > P2 && ray_angle < P3) // if left
        {
            // round rays y position to nearest 64 value
            ray_x_val = ((int)(player_x_val / 64) * 64) - 0.0001;
            // rays x value is distance between player and rays y position * inverse Tan + players x position
            ray_y_val = (player_x_val - ray_x_val) * negativeTan + player_y_val;
            x_offset = -64;
            y_offset = -x_offset * negativeTan;
        }
        if (ray_angle < P2 || ray_angle > P3) // if right
        {
            // round rays y position to nearest 64 value
            ray_x_val = ((int)(player_x_val / 64) * 64) + 64;
            // rays x value is distance between player and rays y position * inverse Tan + players x position
            ray_y_val = (player_x_val - ray_x_val) * negativeTan + player_y_val;
            x_offset = 64;
            y_offset = -x_offset * negativeTan;
        }
        if (ray_angle == 0 || ray_angle == PI) // if up or down
        {
            // round rays y position to nearest 64 value
            ray_x_val = player_x_val;
            ray_y_val = player_y_val;
            depth_of_field = 8;
        }

        while (depth_of_field < 8) // dont want to get caught in inf loop set max depth of field
        {
            map_x_value = (int)(ray_x_val) / 64;
            map_y_vaue = (int)ray_y_val / 64;
            map_position = map_y_vaue * mapX + map_x_value;
            // if map position less than array size
            // check inside the map
            if ((map_position) > 0 && map_position < mapX * mapY && map[map_position] == 1) // hit wall if value is 1
            {
                vertical_x = ray_x_val;
                vertical_y = ray_y_val;
                distanceVertical = dist(player_x_val, player_y_val, vertical_x, vertical_y, ray_angle);
                depth_of_field = 8; // hit wall done shut it down
            }
            else // if didnt hit wall to check next horizaontal line add the x and y offset
            {
                ray_x_val += x_offset;
                ray_y_val += y_offset;
                depth_of_field += 1;
            }
        }

        float shade = 1;

        if (distanceHorizontal < distanceVertical)
        {
            ray_x_val = horizontal_x;
            ray_y_val = horizontal_y;
            final_distance = distanceHorizontal;
            glColor3f(0.8, 0, 0); // horizontal wall color
        }
        else
        {
            ray_x_val = vertical_x;
            ray_y_val = vertical_y;
            final_distance = distanceVertical;
            glColor3f(0.6, 0, 0); // vertical wall color
            shade = 0.5;
        }

        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(player_x_val, player_y_val);
        glVertex2i(ray_x_val, ray_y_val);
        glEnd();

        // --- Draw 3D Walls --- //

        // fix fish eye effect, ( further rays need to be equal to center rays instead of longer )
        float angle_diff = player_angle - ray_angle;
        if (angle_diff < 0)
        {
            angle_diff += 2 * PI;
        }

        if (angle_diff > 2 * PI)
        {
            angle_diff -= 2 * PI;
        }

        final_distance = final_distance * cos(angle_diff);

        // window is 320X160px so ( cube size * screen hieght/final ray distance)
        // so the further away the smaller the wall height
        float line_height = (mapS * 320) / final_distance;

        if (line_height > 320)
        {
            line_height = 320;
        }

        //---draw walls---
        // order of this step formula before lineH clipping important to avoid wall getting to close smudge
        int lineH = (mapS * 320) / final_distance;
        float ty_step = 32.0 / (float)lineH;
        float texture_y_offset = 0;

        if (lineH > 320)
        {
            // half difference screen height and line height
            texture_y_offset = (lineH - 320) / 2.0; // line height and limit
            lineH = 320;
        }
        int lineOff = 160 - (lineH >> 1);

        int y;
        float ty = texture_y_offset * ty_step;
        // value of 0-32 we can look up in texture

        float tx = 0.0;


        // Flip textures to all face same direction
        if(shade == 1)
        {
            tx = (int)(ray_x_val / 2.0) % 32; // divided by 2 bc textures are half the size
            // up/down
            //  four south/down textures need to flip for them to be right way
            if (ray_angle < degToRad(180))
            {
               tx = 31 - tx;
            }
        }
        else
        {

            tx = (int)(ray_y_val / 2.0) % 32; // divided by 2 bc textures are half the size
            // left right
            // for left walls need to flip

            if (ray_angle > degToRad(90) && ray_angle < degToRad(270))
            {
                tx = 31 - tx; // flip
            }
        }

        for (y = 0; y < lineH; y++)
        {
            float c = All_Textures[(int)(ty) * 32 + (int)(tx)] * shade;
            glColor3f(c, c, c);
            glPointSize(8);
            glBegin(GL_POINTS);
            glVertex2i(r * 8 + 530, y + lineOff);
            glEnd(); // draw vertical wall
            ty += ty_step;
        }

        ray_angle += DR;

        if (ray_angle < 0)
        {
            ray_angle += 2 * PI;
        }
        else if (ray_angle > 2 * PI)
        {
            ray_angle -= 2 * PI;
        }
    }
}

//-----------------------------------------------------------------------------

// Function to check if a map position is walkable with buffer zones
int isWalkable(float x, float y, float buffer)
{
    int directions[8][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}}; // Check surrounding positions including diagonal
    for (int i = 0; i < 8; i++)
    {
        int mapGridX = (int)((x + directions[i][0] * buffer) / mapS);
        int mapGridY = (int)((y + directions[i][1] * buffer) / mapS);
        int mapPos = mapGridY * mapX + mapGridX;
        if (mapPos < 0 || mapPos >= mapX * mapY || map[mapPos] == 1)
        {             // Check map boundaries and wall presence
            return 0; // Not walkable
        }
    }
    return 1; // Walkable
}
float frame1, frame2, fps;

void display()
{

    frame2 = glutGet(GLUT_ELAPSED_TIME);
    if (frame1 == 0)
    {
        frame1 = frame2;
        return;
    }

    float frameTime = (frame2 - frame1) / 1000.0;
    float rotationSpeed = 1.57;
    float movementSpeed = 200.0;

    if (Keys.d == 1)
    {
        player_angle += rotationSpeed * frameTime;
        player_angle = FixAng(player_angle);
    }
    if (Keys.a == 1)
    {
        player_angle -= rotationSpeed * frameTime;
        player_angle = FixAng(player_angle);
    }

    player_delta_x = cos(player_angle);
    player_delta_y = sin(player_angle);

    float nextX, nextY;
    // Assuming a buffer size of 5 units to prevent clipping
    float buffer = 5.0f;

    if (Keys.w == 1)
    {
        nextX = player_x_val + player_delta_x * movementSpeed * frameTime;
        nextY = player_y_val + player_delta_y * movementSpeed * frameTime;
        if (isWalkable(nextX, nextY, buffer))
        {
            player_x_val = nextX;
            player_y_val = nextY;
        }
    }
    if (Keys.s == 1)
    {
        nextX = player_x_val - player_delta_x * movementSpeed * frameTime;
        nextY = player_y_val - player_delta_y * movementSpeed * frameTime;
        if (isWalkable(nextX, nextY, buffer))
        {
            player_x_val = nextX;
            player_y_val = nextY;
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawRays2D();
    drawPlayer2D();
    glutSwapBuffers();

    frame1 = frame2;
}

void init()
{
    glClearColor(0.3, 0.3, 0.3, 0); // Set the clear color for the window (background color) to a grey tone.
    gluOrtho2D(0, 1024, 510, 0);    // Define a 2D orthographic projection matrix. Coordinates for the display.
    // Initialize player's position to the center of the window (approximately).
    player_x_val = 300;
    player_y_val = 300;
    player_angle = 0; // Initialize player angle to 0 radians.
    player_delta_x = player_angle;
    player_delta_y = player_angle;
}

void resize()
{
    glutReshapeWindow(1024, 512);
}

void ButtonDown(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        Keys.a = 1;
    }
    if (key == 'd')
    {
        Keys.d = 1;
    }
    if (key == 'w')
    {
        Keys.w = 1;
    }
    if (key == 's')
    {
        Keys.s = 1;
    }
    glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        Keys.a = 0;
    }
    if (key == 'd')
    {
        Keys.d = 0;
    }
    if (key == 'w')
    {
        Keys.w = 0;
    }
    if (key == 's')
    {
        Keys.s = 0;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                       // Initialize GLUT library.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set the initial display mode. Double buffered and RGB color.
    glutInitWindowSize(1024, 510);               // Set the initial window size to 1024x510 pixels.
    glutInitWindowPosition(200, 200);
    glutCreateWindow("RayCaster Engine"); // Create a window with the title "RayCaster Engine".
    init();                               // Call the initialization function to setup OpenGL state.
    glutDisplayFunc(display);             // Register the display function that gets called every time the window needs to be updated.
    glutReshapeFunc(resize);
    glutKeyboardFunc(ButtonDown); // button pressed
    glutKeyboardUpFunc(ButtonUp); // button not pressed
    glutMainLoop();               // Enter the GLUT event processing loop. This will keep the application active until it's closed.
}
