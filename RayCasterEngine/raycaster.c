#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float player_x_val, player_y_val, pdx, pdy, player_angle; // player positions to rotate player (deltax, deltay, angle)

#define mapX  8      //map width
#define mapY  8      //map height
#define mapS 64      //map cube size
#define PI 3.141592653589793238462643383279502884197
#define P2 PI/2       // pie over 2
#define P3 3*PI/2    // 3/2pie


double roundToNearest64th(double value) {
    return round(value * 64) / 64;
}

float degToRad(int a) { return a*PI/180.0;}

// Function returns distance between player and array endpoint (aka hypot)
float dist(float ax,float ay, float bx, float by,float ang)
{ 
    return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);
    
}


void drawPlayer2D()
{
    glColor3f(1,1,0);   // Set the color for drawing. Here, (1,1,0) corresponds to yellow (RGB).
    glPointSize(8);     // Set the size of points to be drawn to 8 pixels.
    glBegin(GL_POINTS); // Begin drawing points.
    glVertex2i(player_x_val,player_y_val);  // Specify the position of the point, which represents the player's position.
    glEnd();            // End drawing.

    glLineWidth(3);
    glBegin(GL_LINES); 
    glVertex2i(player_x_val,player_y_val);
    glVertex2i(player_x_val+pdx*5,player_y_val+pdy*5); 
    glEnd();
}


//-----------------------------MAP----------------------------------------------
int map[]=     
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};

void drawMap2D()
{
    int x,y,x_offset,yo;
        for(y=0; y<mapY; y++)
        {
            for(x=0; x<mapX ;x++)
            {
                if(map[y*mapX+x]==1)
                { 
                    glColor3f(1,1,1); // color of walls
                } 
                else
                { 
                    glColor3f(0,0,0); // color of empy spaces
                }

                x_offset=x*mapS; 
                yo=y*mapS;
                glBegin(GL_QUADS); 
                // add / subtract 1 pixel to outline cubes
                glVertex2i( 0 +x_offset+1, 0 +yo+1); 
                glVertex2i( 0 +x_offset+1, mapS+yo-1); 
                glVertex2i( mapS+x_offset-1, mapS+yo-1);  
                glVertex2i( mapS+x_offset-1, 0 +yo+1); 
                glEnd();
        } 
    } 
}
//-----------------------------MAP----------------------------------------------

//-----------------------------RAYS----------------------------------------------

void drawRays2D()
{
 	 	
    int r,map_x_value,map_y_vaue,map_position,depth_of_field; 
    float ray_x_val = 0.0;
    float ray_y_val = 0.0;
    float x_offset = 0.0;
    float y_offset= 0.0;
    
    float ray_angle = player_angle; // set ray angle to players angle

    for(r=0;r<1;r++) // cast ray
    {
        //---Check Horizontal Lines--- 
        depth_of_field=0;
        float distanceHorizontal = 1000000; // we want shortest distance so mak defualt very high
        float horizontal_x = player_x_val;
        float horizontal_y = player_y_val;

        float aTan = -1/tan(ray_angle); // negative inverse of tangent
        // need to know if a ray is looking up or down konw this by looking at a rays angle
        if(ray_angle > PI) // if greated than 180 deg then upwards 
        {
            // round rays y position to nearest 64 value
            ray_y_val = ((int)(player_y_val/64)*64)-0.0001;
            // rays x value is distance between player and rays y position * inverse Tan + players x position
            ray_x_val = (player_y_val-ray_y_val)*aTan + player_x_val;
            y_offset=-64;
            x_offset=-y_offset*aTan;

        }
        if(ray_angle < PI)
        {
            // round rays y position to nearest 64 value
            ray_y_val = ((int)(player_y_val/64)*64)+64;
            // rays x value is distance between player and rays y position * inverse Tan + players x position
            ray_x_val = (player_y_val-ray_y_val)*aTan + player_x_val;
            y_offset= 64;
            x_offset=-y_offset*aTan;

        }
        if(ray_angle == 0 || ray_angle == PI) // if looking straigt left or right impossible to hit horizontal line
        {
            // round rays y position to nearest 64 value
            ray_x_val = player_x_val;
            ray_y_val = player_y_val;
            depth_of_field = 8;

        }
        while(depth_of_field < 8) // dont want to get caught in inf loop set max depth of field
        {
            map_x_value = (int) (ray_x_val)/64;
            map_y_vaue = (int) (ray_y_val)/ 64;
            map_position = map_y_vaue * mapX +  map_x_value;
            // if map position less than array size
            // check inside the map
            if( (map_position)> 0 && map_position<mapX*mapY && map[map_position]==1) // hit wall if value is 1
            { 
                horizontal_x = ray_x_val;
                horizontal_y = ray_y_val;
                distanceHorizontal = dist(player_x_val, player_y_val, horizontal_x, horizontal_y, ray_angle);
                depth_of_field=8; // hit wall done shut it down

            }
            else // if didnt hit wall to check next horizontal line add the x and y offset
            {
                ray_x_val += x_offset; 
                ray_y_val += y_offset; 
                depth_of_field+=1;
            }

            glColor3f(0,1,0);
            glLineWidth(10);
            glBegin(GL_LINES);
            glVertex2i(player_x_val, player_y_val);
            glVertex2i(ray_x_val, ray_y_val);
            glEnd();


        }

        //---Check Vertical Lines--- 
        depth_of_field = 0;
        float negativeTan = -tan(ray_angle); // negative inverse of tangent
        float distanceVertical = 1000000; // we want shortest distance so mak defualt very high
        float vertical_x = player_x_val;
        float vertical_y = player_y_val;

        // need to know if a ray is looking up or down konw this by looking at a rays angle
        if(ray_angle > P2 && ray_angle < P3) // if left
        {
            // round rays y position to nearest 64 value
            ray_x_val = ((int)(player_x_val/64)*64)-0.0001;
            // rays x value is distance between player and rays y position * inverse Tan + players x position
            ray_y_val = (player_x_val-ray_x_val)*negativeTan + player_y_val;
            x_offset=-64;
            y_offset=-x_offset*negativeTan;

        }
        if(ray_angle < P2 || ray_angle > P3) // if right
        {
            // round rays y position to nearest 64 value
            ray_x_val = ((int)(player_x_val/64)*64)+64;
            // rays x value is distance between player and rays y position * inverse Tan + players x position
            ray_y_val = (player_x_val-ray_x_val)*negativeTan + player_y_val;
            x_offset= 64;
            y_offset=-x_offset*negativeTan;

        }
        if(ray_angle == 0 || ray_angle == PI) // if up or down
        {
            // round rays y position to nearest 64 value
            ray_x_val = player_x_val;
            ray_y_val = player_y_val;
            depth_of_field = 8;

        }


        while(depth_of_field < 8) // dont want to get caught in inf loop set max depth of field
        {
            map_x_value = (int) (ray_x_val)/64;
            map_y_vaue = (int) ray_y_val / 64;
            map_position = map_y_vaue * mapX +  map_x_value;
            // if map position less than array size
            // check inside the map
            if( (map_position)> 0 && map_position<mapX*mapY && map[map_position]==1) // hit wall if value is 1
            { 
                vertical_x = ray_x_val;
                vertical_y = ray_y_val;
                distanceVertical = dist(player_x_val, player_y_val, vertical_x, vertical_y, ray_angle);
                depth_of_field=8; // hit wall done shut it down
            }
            else // if didnt hit wall to check next horizaontal line add the x and y offset
            {
                ray_x_val += x_offset; 
                ray_y_val += y_offset; 
                depth_of_field+=1;
            }
            
            // draw array
            glColor3f(1,0,0);
            glLineWidth(2);
            glBegin(GL_LINES);
            glVertex2i(player_x_val, player_y_val);
            glVertex2i(ray_x_val, ray_y_val);
            glEnd();

        }

    }
}

//-----------------------------------------------------------------------------


void display()
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer and depth buffer.
    drawMap2D(); // call before drawing player
    drawPlayer2D();  // Call the function to draw the player as a point on the screen.
    drawRays2D();
    glutSwapBuffers();  // Swap the front and back buffers to update the displayed image.
}

void init()
{
    glClearColor(0.3,0.3,0.3,0); // Set the clear color for the window (background color) to a grey tone.
    gluOrtho2D(0,1024,510,0);    // Define a 2D orthographic projection matrix. Coordinates for the display.
    // Initialize player's position to the center of the window (approximately).
    player_x_val=300; 
    player_y_val=300;   
    pdx=cos(player_angle)*5; 
    pdy=sin(player_angle)*5;          
}

void buttons(unsigned char key, int x, int y)
{
    // sin and cos will use radian values 0 - 6.28
    if(key=='a')
    {
        player_angle-=0.1; // subtract small amount from players angle
        if (player_angle < 0 ) // if we go less than zero reset to 2 PI
        {
            player_angle+=2*PI;
        }
        // multp by 5 bc value by cos and sin very small
        pdx = cos(player_angle)*5;
        pdy = sin(player_angle)*5;
    } 
    if(key=='d')
    {
        player_angle+=0.1; 
        if (player_angle > 2*PI ) 
        {
            player_angle-=2*PI;
        }
        pdx = cos(player_angle)*5;
        pdy = sin(player_angle)*5;
    } 
    if(key=='w')
    { 
        player_x_val += pdx; 
        player_y_val += pdy;
    }
    if(key=='s')
    { 
        player_x_val -= pdx; 
        player_y_val -= pdy;
    }

    glutPostRedisplay();
}


int main(int argc, char* argv[])
{ 
    glutInit(&argc, argv);                        // Initialize GLUT library.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Set the initial display mode. Double buffered and RGB color.
    glutInitWindowSize(1024,510);                 // Set the initial window size to 1024x510 pixels.
    glutCreateWindow("RayCaster Engine");         // Create a window with the title "RayCaster Engine".
    init();                                       // Call the initialization function to setup OpenGL state.
    glutDisplayFunc(display);                     // Register the display function that gets called every time the window needs to be updated.
    glutKeyboardFunc(buttons);
    glutMainLoop();                               // Enter the GLUT event processing loop. This will keep the application active until it's closed.
}