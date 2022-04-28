//
// Assignment Created by Varick Erickson
//

#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <cmath>
#include <fstream>

const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 800;
const int MAX_COLOR = 255;
enum COLOR { RED, GREEN, BLUE };

using namespace std;

//  Please put your pre and post comments in this file. See page 139 in the textbook.

class ImageMaker
{
public:
    //Default Constructor
    ImageMaker();

    //Parameterized constructor
    ImageMaker(string filename);

    // Function: Opens the ppm file and stores the pixel values into the image private variable
    // Pre: Image variable values are initialized to 255
    // Post: Image variable values are assigned with pixel values from the loaded ppm file
    void LoadImage(string filename);

    // Function: Saves the header information and current pixel values in the image variable to the specified ppm file
    // Pre: ppm file contains initialized values (255 - white)
    // Post: ppm file contains pixel values from image variable
    void SaveImage(string filename);

    // Size functions
    // Function: To retrieve the width of the image pixel matrix from width variable
    // Pre: width is initially set to 0 in the constructor
    // Post: returns the updated width with the value read from the loaded header information
    int GetWidth();

    // Function: To retrieve the height of the image pixel matrix from height variable
    // Pre: height is initially set to 0 in the constructor
    // Post: returns the updated height with the value read from the loaded header information
    int GetHeight();

    // Function: To set width of the image pixel matrix in the width variable
    // Pre: width is initially set to 0 in the constructor
    // Post: sets the width variable to the width value read from the header information
    void SetWidth(int width);

    // Function: To set height of the image pixel matrix in the height variable
    // Pre: height is initially set to 0 in the constructor
    // Post: sets the height variable to the height value read from the header information
    void SetHeight(int height);

    // Color functions
    // Function: To get the color of pen_red variable
    // Pre: pen_red is initialised to 0 in the constructor
    // Post: gets the current value of pen_red
    int GetPenRed();

    // Function: To get the color of pen_green variable
    // Pre: pen_green is initialised to 0 in the constructor
    // Post: gets the current value of pen_green
    int GetPenGreen();

    // Function: To get the color of pen_blue variable
    // Pre: pen_blue is initialised to 0 in the constructor
    // Post: gets the current value of pen_blue
    int GetPenBlue();

    // Function: To set the color of pen_red variable
    // Pre: pen_red is initialised to 0 in the constructor
    // Post: sets the color of pen_red variable to given value passed as parameter
    void SetPenRed(int newR);

    // Function: To set the color of pen_green variable
    // Pre: pen_green is initialised to 0 in the constructor
    // Post: sets the color of pen_green variable to given value passed as parameter
    void SetPenGreen(int newG);

    // Function: To set the color of pen_blue variable
    // Pre: pen_blue is initialised to 0 in the constructor
    // Post: sets the color of pen_blue variable to given value passed as parameter
    void SetPenBlue(int newB);

    // Drawing methods
    // Function: To update the pixel colors for the given x,y co-ordinate
    // Pre: pixel colors are initially set to 255 (white) in the constructor
    // Post: updates the pixel values for the given x,y co-ordinates using current values of red,green and blue values of the pen
    void DrawPixel(int x, int y);

    // Function: To draw a line using the DrawPixel methods
    // Pre: DrawPixel is implemented
    // Post: constructs a line using existing DrawPixel methods with the current values of pen colors.
    void DrawLine(int x1, int y1, int x2, int y2);

    // Function: To draw a rectangle using the DrawLine methods
    // Pre: DrawLine is implemented
    // Post: constructs a rectangle using existing DrawLine methods with the current values of pen colors.
    void DrawRectangle(int x1, int y1, int x2, int y2);


private:
    string magic;
    int width;
    int height;
    int pen_red;    // Used by draw functions
    int pen_green;  // Used by draw functions
    int pen_blue;   // Used by draw functions

    // Function: returns a boolean determining if the point given is in bounds or not
    // Pre: pass x and y coordinates as parameters
    // Post: returns true if point is within the given width and height
    bool PointInBounds(int x, int y);  // Not a bad idea to implement

               //   x          y
    short image[MAX_WIDTH][MAX_HEIGHT][3];

    // Function: To initialise the values in the matrix of private image variable
    // Pre: image variables and enum values must be declared
    // Post: initialises the pixel values to white (255)
    void initialiseImageVariable();

    // Function: To calculate the slop of a line
    // Pre: the 2 points between whose slope is to be calculated is to be passed as parameter
    // Post: returns the calculated slope of the line as a float
    float slope(int x1, int y1, int x2, int y2);

    // Function: To validate if header information and pixel values are conforming.
    // Pre: the filename is to be passed as a parameter
    // Post: checks if the header and pixel values are as expected and assigns to their corresponding private variables
    void errorChecking(string basicString);

    // Function: To calculate the y-intercept of a line
    // Pre: the points and slope are passed as parameter
    // Post: returns the calculated y-intercept value as a float.
    float yintercept(int x1, int y1, float m);
};

#endif //IMAGEMAKER_H
