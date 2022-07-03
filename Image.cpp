////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>

#include <fstream>

#include <sstream>

#include <stdexcept>

#include "Image.h"

Image::Image(int w, int h) {
  assert(0 < w && 0 < h); //precondition: h and w > 0

  m_height = h;
  m_width = w;

  Two_Dimensional_Table = new Color * [h]; //allocation of a two-dimensional array we create the columns of the array
  for (int i = 0; i < h; i++) {
    Two_Dimensional_Table[i] = new Color[w]; //create the rows of the table
  }
  for (int j = 0; j < h; j++) {
    for (int k = 0; k < w; k++) {
      Two_Dimensional_Table[j][k] = Color(); //target a cell of the table and color it in black
    }
  }
}

Image::~Image() /// Destructeur

{
  //unallocation of a two-dimensional array
  for (int i = 0; i < m_height; i++) {
    delete[] Two_Dimensional_Table[i]; //delete the cells of the table
  }

  delete[] Two_Dimensional_Table;
}

Image::Image(const Image & img) {
  m_height = img.height();
  m_width = img.width();
  Two_Dimensional_Table = new Color * [height()];
  for (int i = 0; i < height(); i++) {
    Two_Dimensional_Table[i] = new Color[width()];
  }
  for (int j = 0; j < height(); j++) {
    for (int k = 0; k < width(); k++) {
      Two_Dimensional_Table[j][k] = img.Two_Dimensional_Table[j][k];
    }
  }
}

int Image::width() const {
  return m_width; //recover the width of the table
}

int Image::height() const {
  return m_height; //recover the height of the table
}

int Image::size() const {
  return m_width * m_height; //recover the size of the table 
}

Color Image::getPixel(int i, int j) const {
  return Two_Dimensional_Table[i - 1][j - 1]; //we target a pixel of the array
}

void Image::setPixel(int i, int j, Color col) //modify the targeted pixel 
{
  Two_Dimensional_Table[i - 1][j - 1] = col;
}

int Image::toIndex(int i, int j) const {
  //coordinate of a pixel which gives the index of an array
  int index;
  index = (i - 1) * width() + (j - 1);
  return index;
}

std::pair < int, int > Image::toCoordinate(int k) const {
  // index of an array that gives the coordinates of a pixel
  std::pair < int, int > coordinate;
  coordinate.first = (k / width()) + 1;
  coordinate.second = (k % width()) + 1;
  return coordinate;
}

void Image::fill(Color c) {

  for (int i = 0; i < m_height; i++) {
    for (int j = 0; j < m_width; j++) {

      Two_Dimensional_Table[i][j] = c; //fill in all the boxes in the table 

    }

  }

}

void Image::fillRectangle(int i1, int j1, int i2, int j2, Color c) {
  for (int i = i1; i <= i2; i++) {
    for (int j = j1; j <= j2; j++) {
      Two_Dimensional_Table[i - 1][j - 1] = c; //fill in the boxes of the selected table
    }
  }
}

void Image::writeSVG(const std::string & filename, int pixelSize) const {
  assert(pixelSize > 0);

  std::ofstream file;
  file.open(filename + ".svg");

  if (!file) throw std::runtime_error("error open file (write SVG)");

  file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" <<
    std::endl <<
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" <<
    pixelSize * width() <<
    "\" height=\"" <<
    pixelSize * height() <<
    "\">" <<
    std::endl;

  for (int i = 1; i <= height(); ++i)
    for (int j = 1; j <= width(); ++j)
      file << "<rect width=\"" <<
      pixelSize <<
      "\" height=\"" <<
      pixelSize <<
      "\" x=\"" <<
      pixelSize * (j - 1) <<
      "\" y=\"" <<
      pixelSize * (i - 1) <<
      "\" fill=\"" <<
      getPixel(i, j) <<
      "\" />" <<
      std::endl;

  file << "</svg>" <<
    std::endl;

  file.close();
}

void Image::writeAIP(const std::string & filename) const {
  Color color;
  std::ofstream newFile; /// Declare an object of type ofstream allowing to write the file

  newFile.open(filename + ".aip");

  if (!newFile) throw std::runtime_error("error open file (write AIP)"); //If we can't open the file entered in parameter, we return an exception and an error message

  newFile << width() << " " << height() << std::endl; ///Write the width and height of the current object on the first line
  for (int i = 1; i <= height(); i++) {
    for (int j = 1; j <= width(); j++) {
      ///For each pixel of the current object we convert the color of this one in full, in order to transcribe it on our file 
      color = getPixel(i, j);
      newFile << color.toInt();
    }
    newFile << std::endl;
  }

  newFile.close();
}

Image Image::readAIP(const std::string & filename) //ok
{
  int height, width;

  std::string line;
  std::ifstream inputFile; /// Declare an object of type ifstream allowing to write the file 

  inputFile.open(filename + ".aip");

  if (!inputFile) throw std::runtime_error("error open file $$(filename) file filename"); //If we can't open the file entered in parameter, we return an exception and an error message

  /// Recover the width and height on the first line, then move to the next line using the getline method 
  inputFile >> width;
  inputFile >> height;
  getline(inputFile, line);

  Image newImage(width, height); /// create a black pixel image using the height and width 

  for (int i = 1; i <= height; i++) {
    getline(inputFile, line);
    for (int j = 1; j <= width; j++) {
      /// Recover an integer number from the characters of the file thanks to the ascii code
      ///Permits the modification of each pixel by converting the obtained numbers into a Color object
      int temporary = line[j - 1] - '0';
      newImage.setPixel(i, j, Color::makeColor(temporary));
    }
  }

  inputFile.close();
  return newImage;
}

bool Image::operator == (const Image & img) const {
  if ((img.height() == height()) && (width() == img.width())) {
    for (int i = 0; i < m_height; i++) {
      for (int j = 0; j < m_width; j++) {
        /// test for each pixel of each object if they are equal
        if (img.Two_Dimensional_Table[i][j].operator != (this -> Two_Dimensional_Table[i][j])) {

          return false;
        }

      }

    }
  } else {
    return false;
  }
  return true;
}

bool Image::operator != (const Image & img) const {
  if (!operator == (img)) {
    return true;
  }
  return false;
}

bool Image::areConsecutivePixels(int i1, int j1, int i2, int j2) {
  assert(isValidCoordinate(i1, j1) == true && isValidCoordinate(i2, j2) == true);
  /// If one of the two coordinates of each pair is identical and the difference between the other coordinates is only 1, the pixels are contiguous.     if (((j1==j2)&&(i1==i2-1||i1==i2+1))||((i2==i1)&&(j1==j2-1||j1==j2+1)))
  if (((j1==j2)&&(i1==i2-1||i1==i2+1))||((i2==i1)&&(j1==j2-1||j1==j2+1)))
  {
    return true;
  }
  return false;

}

bool Image::isValidCoordinate(int i, int j) const {

  return (j < m_width + 2 && i > 0 && j > 0 && i < m_height + 2);

}

Image makeRandomImage(int w, int h) {
  Image randomImage(w, h);
  int randomValue;
  for (int j = 0; j < h; j++) {
    for (int k = 0; k < w; k++) {

      ///Each pixel color is defined randomly between [0,4] which is then converted into a Color object 
      randomValue = rand() % 5;
      randomImage.setPixel(j + 1, k + 1, Color::makeColor(randomValue));
    }
  }
  return randomImage;
}