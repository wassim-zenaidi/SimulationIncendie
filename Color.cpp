////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Color.h"

// Creates the static const colors at the begininng of the execution
const Color Color::Black = Color(_black);
const Color Color::White = Color(_white);
const Color Color::Red   = Color(_red);
const Color Color::Blue  = Color(_blue);;
const Color Color::Green = Color(_green);;

Color::Color()
{
  val_ = _black;
}

int Color::toInt() const
{
  return static_cast<int>(val_);
}

int Color::nbColors()
{
  return _size;
}

Color Color::makeColor(int n)
{
  assert(n >= 0 && n < nbColors());

  Value val = static_cast<Value>(n);
  return Color(val);
}

Color::Color(Value val)
{
  val_ = val;
}

bool Color::operator==(const Color& c) const
{
  return val_ == c.val_;
}

bool Color::operator!=(const Color& c) const
{
  return val_ != c.val_;
}

std::ostream& operator<<(std::ostream& os, const Color& c)
{
  switch(c.val_)
  {
    case Color::_black: { os << "black"; break; }
    case Color::_white: { os << "white"; break; }
    case Color::_red:   { os << "red";   break; }
    case Color::_blue : { os << "blue";  break; }
    case Color::_green: { os << "green"; break; }
    case Color::_size:  {}
  }
  return os;
}
