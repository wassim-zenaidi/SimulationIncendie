////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#ifndef FIRE_SIMULATOR_H
#define FIRE_SIMULATOR_H

#include <vector>
#include "Image.h"

////////////////////////////////////////////////////////////////////////////////
/// This is a fire simulator.
///
/// Given a pixel of forest in an image, it simulates a fire in the zone
/// of forest of the given pixel.
/// Étant donné un pixel de forêt dans une image, 
/// il simule un incendie dans la zone de forêt du pixel donné.
////////////////////////////////////////////////////////////////////////////////
class FireSimulator {
public:

//constructor
FireSimulator(const Image& img,int i, int j);

//destructor
~FireSimulator();

///Pass the time t of n periods
void TimeEvolution(int n);

///Change from time t to time t+1 by modifying the image
void TimeScrolling();

//method to reset the time and the forest
void TimeReboot();


int Access_At_The_Beginning_Of_The_Fire();


///Generates the image of the situation in real time
Image Image_Of_The_Moment();



private:

//time
int timeCounter;

//starting point
int beginning_of_fire;

int DrillSize;

std::vector<std::vector<int>> anteriority;


std::vector<int> vert,rouge,noir;

Color** Copy_of_Two_Dimensional_Table;
int copy_of_width;
int copy_of_height;

};

#endif
