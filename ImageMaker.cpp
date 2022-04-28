#include <sstream>
#include "ImageMaker.h"
#include "fstream"
#include <cmath>
#include "iostream"
#include <bits/stdc++.h>
using namespace std;


// default constructor
ImageMaker::ImageMaker() {
    //initialising private variables
    height = 0;
    width = 0;

    //setting initial pen color to black
    pen_red = 0;
    pen_green = 0;
    pen_blue = 0;

    //image variable initialised to white
    initialiseImageVariable();
}

void ImageMaker::initialiseImageVariable() {
    for(int row=0; row<MAX_HEIGHT; row++) {
        for(int cols=0; cols<MAX_WIDTH; cols++) {
            image[cols][row][RED] = 255;
            image[cols][row][GREEN] = 255;
            image[cols][row][BLUE] = 255;
        }
    }
}

ImageMaker::ImageMaker(string filename) {
    //initialise image variable to white
    initialiseImageVariable();

    //load ppm image to image matrix
    LoadImage(filename);

    //setting initial pen color to black
    pen_red = 0;
    pen_green = 0;
    pen_blue = 0;
}

//do error checking without opening the file again
void ImageMaker::errorChecking(string filename) {
    //retrieving header values from ppm file
    ifstream file;
    file.open (filename);
    if (!file)
    {
        throw "File failed to open";
    }
    string word, magic_number;
    int width, height, max_value;

    //retrieving magic_number
    file >> word;
    magic_number = word;
    cout<<"\n Magic"<<magic_number;
    if(magic_number!= "P3") throw "Bad magic number";

    //retrieving width
    file >> word;
    width = stoi(word);
    if(width<0 || width>MAX_WIDTH) throw "Width out of bounds";
    this->width = width;

    //retrieving height
    file >> word;
    height = stoi(word);
    if(height<0 || height>MAX_HEIGHT) throw "Height out of bounds";
    this->height = height;

    //retrieving max value from header
    file >> word;
    max_value = stoi(word);
    if(max_value != MAX_COLOR) throw "Max color range not 255";

    //error checking if pixel contains bad value
    while (file >> word)
    {
        stringstream convertedWord(word);
        int x = 0;
        convertedWord >> x;
        if(x>255) {
            throw "Color value invalid";
        }
    }
    //closing file
    file.close();
}


void ImageMaker::LoadImage(string filename) {
    cout<<"inside loadImage for file"<< filename << "width"<< width;
    //error checking
    errorChecking(filename);

    ifstream file;
    file.open (filename);

    //checking if file exists
    if (!file)
    {
        cout << "File not found." << endl;
        exit(2);
    }
    string word;

    //skipping header information
    file >> word;
    file >> word;
    file >> word;

    //reading through rest of ppm file and updating pixel values on image variable
    while (file >> word)
    {
        for(int row=0; row<height; row++) {
            for(int cols=0; cols<width; cols++) {
                file >> image[cols][row][RED];
                file >> image[cols][row][GREEN];
                file >> image[cols][row][BLUE];
            }
        }
    }
    file.close();
}

void ImageMaker::SaveImage(string filename) {
    cout<<"Inside save image for file" << filename << "width" << width;

    //error checking if width or height is 0
    if( width==0 || height==0) {
        throw "Image must have non-zero dimensions";
    }

    ofstream file(filename);

    //checking if file exists
    if(!file) {
        cout << "In save image, unable to locate file"<<endl;
        throw "File failed to open";
    } else {
        //writing header information into file
        file <<"P3"<<endl;
        file <<width<<" "<<height<<endl;
        file <<"255"<<endl;

        //writing image information into file
        for(int y=0; y<height; y++) {
            for(int x=0; x<width; x++) {
                file << image[x][y][RED]   << " ";
                file << image[x][y][GREEN] << " ";
                file << image[x][y][BLUE]  << " ";
            }
            file<<endl;
        }

        //closing file
        file.close();

        //error checking header values
        errorChecking(filename);
    }
}

int ImageMaker::GetWidth() {
    return width;
}

int ImageMaker::GetHeight() {
    return height;
}

void ImageMaker::SetWidth(int width) {
    if (width<0 || width>MAX_WIDTH) throw "Width out of bounds";
    this->width = width;
}

void ImageMaker::SetHeight(int height) {
    if (height<0 || height>MAX_WIDTH) throw "Height out of bounds";
    this->height = height;
}

int ImageMaker::GetPenRed() {
    return pen_red;
}

int ImageMaker::GetPenGreen() {
    return pen_green;
}

int ImageMaker::GetPenBlue() {
    return pen_blue;
}

void ImageMaker::SetPenRed(int newR) {
    if(newR < 0 || newR > 255) throw "Color value invalid";
    pen_red = newR;
}

void ImageMaker::SetPenGreen(int newG) {
    if(newG < 0 || newG > 255) throw "Color value invalid";
    pen_green = newG;
}

void ImageMaker::SetPenBlue(int newB) {
    if(newB < 0 || newB > 255) throw "Color value invalid";
    pen_blue = newB;
}

void ImageMaker::DrawPixel(int x, int y) {
    cout<<"\n Inside draw pixel for"<<x<<","<<y;
    //returns true if point is in bounds
    //else returns false
    if(!PointInBounds(x, y)) {
        throw "Point out of bounds";
    }

    //setting respective pen colors
    image[x][y][RED] = pen_red;
    image[x][y][GREEN] = pen_green;
    image[x][y][BLUE] = pen_blue;
}

void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2) {
    if(x1<0 || y1<0 || x2<0 || y2<0) throw "Point out of bounds";

    //top line
    DrawLine(x1, y1, x2, y1);
    //right line
    DrawLine(x2, y1, x2, y2);
    //bottom line
    DrawLine(x2, y2, x1, y2);
    //left line
    DrawLine(x1, y2, x1, y1);
}

void ImageMaker::DrawLine(int x1, int y1, int x2, int y2) {
    cout<<"\n inside draw line";
    if(x1<0 || y1<0 || x2<0 || y2<0) throw "Point out of bounds";
    cout<<"\n x1,y1 "<<x1<<" "<<y1;
    cout<<"\n x2,y2 "<<x2<<" "<<y2;

    //if both points are same, drawing a pixel
    if(x1==x2 && y1==y2) {
        cout<<"Both points are same";
        DrawPixel(x1, y1);
        return;
    }

    int startX = min(x1, x2);
    int endX = max(x1, x2);
    int startY = min(y1, y2);
    int endY = max(y1, y2);

    //rendering vertical lines
    for(int y=startY; y<=endY && x1==x2; y++) {
        cout<<"drawing pixel when x1 x2 equal"<<x1<<y;
        DrawPixel(x1, y);
        if(y==endY) return;
    }

    float m = slope(x1, y1, x2, y2);
    cout<<"\nslope value"<<m;
    float b = yintercept(x1, y1, m);
    cout<<"\nb value"<<b;

    //rendering pixels between 2 points
    for(int xcoord = startX; xcoord<=endX; xcoord++) {
        int ycoord = round(m*xcoord + b);
        cout<<"\nx coordinate"<<xcoord;
        cout<<"\ny coordinate"<<ycoord;

        DrawPixel(xcoord, ycoord);
    }
}

//calculates y intercept
float ImageMaker::yintercept(int x1, int y1, float m) {
    return y1-m*x1;
}

//calculates slope
float ImageMaker::slope(int x1, int y1, int x2, int y2) {
    if (x1 == x2)
        return INT_MAX;
    return (float)(y2 - y1) / (x2 - x1);
}

bool ImageMaker::PointInBounds(int x, int y) {
    if(x<0 || x>MAX_WIDTH || y<0 || y>MAX_HEIGHT || (width==0 && x==0) || (height==0 && y==0)) {
        return false;
    } else {
        return true;
    }
}
