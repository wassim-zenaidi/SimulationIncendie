////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "Color.h"


////////////////////////////////////////////////////////////////////////////////
/// This a rectangular colored image.
////////////////////////////////////////////////////////////////////////////////
class Image {
public:
  /// Creates a black rectangular image with w*h pixels
  /// w is the width of this image, h is its height
  Image(int w, int h);//ok

  /// Destructor
  ~Image();//ok

  /// Copy constructor
  Image(const Image& img);

  /// No assignment (sans affectation)
  Image& operator=(const Image& img) = delete;

  /// Returns the width of this
  int width() const;//ok

  /// Returns the height of this
  int height() const;//ok

  /// Returns the number of pixels of this
  int size() const;//ok

  /// Gets the pixel in the i-th row and j-th column
  /// 1 <= i <= height(), 1 <= j <= width()
  Color getPixel(int i, int j) const;//ok

  /// Sets the pixel in the i-th row and j-th column
  /// 1 <= i <= height(), 1 <= j <= width()
  /// col is the new color
  void setPixel(int i, int j, Color col);//ok

  /// Maps a coordinate (i, j) to a unique identifier
  /// Associe une coordonnée (i, j) à un identifiant unique
  int toIndex(int i, int j) const;//ok

  /// Maps an identifier to the corresponding coordinates
  /// Given the result p, p.first is the row and p.second is the column 
  /// Associe un identifiant au coordonnées correspondantes 
  /// donnant le résultat p, p.first est la ligne et p.second la colonne
  std::pair<int, int> toCoordinate(int k) const;//ok

  /// Fills this with a given color
  /// Remplit this avec une couleur donnée
  void fill(Color c);//ok

  /// Fills a rectangle in this with a given color
  /// (i2, j2) is the lower right corner(en bas à droite)
  /// (i1, j1) is the upper left corner (en haut à gauche)
  void fillRectangle(int i1, int j1, int i2, int j2, Color c);//ok
  
  /// Generates a SVG image given a filename without the extension
  /// The file name is of this image is filename.svg
  /// Each pixel is represented by a square of side pixelSize
  /// Throws an exception std::runtime_error if an error occurs
  void writeSVG(const std::string& filename, int pixelSize) const;//ok

  /// Enregistre this dans un fichier texte en utilisant un format spécifique :
  /// - largeur et hauteur de this sur la première ligne ;
  /// - suivi des lignes de this de sorte que chaque chiffre
  /// correspond à la couleur du pixel correspondant.
  /// Le fichier de sortie est nommé filename.aip
  /// Lève une exception std::runtime_error si une erreur se produit
  /// Saves this in a text file using a specific format:
  ///   - width and height of this on the first line;
  ///   - followed by the lines of this such that each digit
  ///     corresponds to the color of the corresponding pixel.
  /// Að×Û÷¡|n example of output file follows:
  ///   5 3m
  ///   10014
  ///   01233
  ///   23101
  /// The output file is named filename.aip
  /// Throws an exception std::runtime_error if an error occurs
  void writeAIP(const std::string& filename) const;//ok

  /// Creates an image from an AIP file
  /// The file name must be given without the extension
  /// Throws an exception std::runtime_error if an error occurs
  /// Create an image from an AIP file
  /// The file name must be given without the extension
  /// Lifts an exception std::runtime_error if an error occurs
  static Image readAIP(const std::string& filename);//ok

  /// Returns true if this and img are equal
  bool operator==(const Image& img) const;//ok

  /// Returns true if this and img are different
  bool operator!=(const Image& img) const;//ok

  /// Returns true if (i1, j1) and (i2, j2) are two consecutive pixels of this
  bool areConsecutivePixels(int i1, int j1, int i2, int j2);//ok

  /// Tests if (i,j) is the coordinates of some pixel of this
  bool isValidCoordinate(int i, int j) const;//ok

 
 

private:

  int m_height;
  int m_width;
  Color** Two_Dimensional_Table; ///Two-Dimensional Table
  
};

  /// Generates an image of width w and height h such that each pixel is
  /// selected randomly.
  Image makeRandomImage(int w, int h);//ok

#endif
