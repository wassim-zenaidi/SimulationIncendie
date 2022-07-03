////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT A std::cout<<"nb pixel to color " << h+1 <<"/"<<o<< std::endl;
#include <sstream>
#include "FireSimulator.h"
#include "Image.h"
#include "Analyst.h"

using namespace std;

int main(void)
{

  //FIRESIMULATOR TEST GAME

  Image ExempleImage=Image::readAIP("amazonie_0");
  ExempleImage.writeSVG("Mon Image en Exemple",100);

  
  FireSimulator fs(ExempleImage,1267/50,1267%50);
  Image fs119=fs.Image_Of_The_Moment();
  fs119.writeSVG("Firetest0",100);
  cout <<fs.Access_At_The_Beginning_Of_The_Fire();

  fs.TimeScrolling();
  Image fs1=fs.Image_Of_The_Moment();
  fs1.writeSVG("Firetest1",100);

  fs.TimeScrolling();
  Image fs12=fs.Image_Of_The_Moment();
  fs12.writeSVG("Firetest2",100);

  fs.TimeScrolling();
  Image fs13=fs.Image_Of_The_Moment();
  fs13.writeSVG("Firetest3",100);

  fs.TimeScrolling();
  Image fs14=fs.Image_Of_The_Moment();
  fs14.writeSVG("Firetest4",100);

  fs.TimeScrolling();
  Image fs15=fs.Image_Of_The_Moment();
  fs15.writeSVG("Firetest5",100);

  fs.TimeScrolling();
  Image fs16=fs.Image_Of_The_Moment();
  fs16.writeSVG("Firetest6",100);

  fs.TimeScrolling();
  Image fs17=fs.Image_Of_The_Moment();
  fs17.writeSVG("Firetest7",100);

  fs.TimeScrolling();
  Image fs18=fs.Image_Of_The_Moment();
  fs18.writeSVG("Firetest8",100);

  fs.TimeScrolling();
  Image fs19=fs.Image_Of_The_Moment();
  fs19.writeSVG("Firetest9",100);

  fs.TimeScrolling();
  Image fs110=fs.Image_Of_The_Moment();
  fs110.writeSVG("Firetest10",100);

  fs.TimeScrolling();
  Image fs2=fs.Image_Of_The_Moment();
  fs2.writeSVG("Firetest11",100);

  fs.TimeScrolling();
  Image fs3=fs.Image_Of_The_Moment();
  fs3.writeSVG("Firetest12",100);

  fs.TimeScrolling();
  Image fs4=fs.Image_Of_The_Moment();
  fs4.writeSVG("Firetest13",100);

  fs.TimeScrolling();
  Image fs5=fs.Image_Of_The_Moment();
  fs5.writeSVG("Firetest14",100);

  fs.TimeScrolling();
  Image fs6=fs.Image_Of_The_Moment();
  fs6.writeSVG("Firetest15",100);

  fs.TimeScrolling();
  Image fs7=fs.Image_Of_The_Moment();
  fs7.writeSVG("Firetest16",100);

  fs.TimeScrolling();
  Image fs8=fs.Image_Of_The_Moment();
  fs8.writeSVG("Firetest17",100);

  fs.TimeScrolling();
  Image fs9=fs.Image_Of_The_Moment();
  fs9.writeSVG("Firetest18",100);

  fs.TimeScrolling();
  Image fs10=fs.Image_Of_The_Moment();
  fs10.writeSVG("Firetest19",100);

  fs.TimeScrolling();
  Image fs112=fs.Image_Of_The_Moment();
  fs112.writeSVG("Firetest20",100);

  fs.TimeScrolling();
  Image fs113=fs.Image_Of_The_Moment();
  fs113.writeSVG("Firetest21",100);

  fs.TimeScrolling();
  Image fs114=fs.Image_Of_The_Moment();
  fs114.writeSVG("Firetest22",100);

  
  

  return 0;
}
