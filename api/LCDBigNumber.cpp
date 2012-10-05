#include "LCDBigNumber.h"
#include <cstdlib>
#include <sstream>

namespace lcdapi {

using namespace std;

const int LCDBigNumber::LCD_COLON = 10;

LCDBigNumber::LCDBigNumber(LCDElement *parent, const string &id) : LCDWidget(id, parent, "num"), _number(0), _position(1)
{
}

LCDBigNumber::LCDBigNumber(int number, int x, LCDElement *parent, const string &id) : LCDWidget(id, parent, "num"), _number(number), _position(1)
{
  set(number, x);
}

void LCDBigNumber::setNumberPosition(int position)
{
  _position = position;
}

void LCDBigNumber::notifyChanged()
{
  ostringstream params;

  params << _x
         << " "
         << _number;

  setWidgetParameters(params.str());
}

void LCDBigNumber::set(int number, int x)
{
  if (_number != number || _x != x) {
    _number = number;
    _x = x;
    notifyChanged();
  }
}

void LCDBigNumber::setNumber(int number)
{
  set(number, _x);
}

int LCDBigNumber::getNumber() const
{
  return _number;
}

void LCDBigNumber::valueCallback(const string& value)
{
  const int max = value.size();
  const int position = max - _position;
  if (position < 0)
  {
    _number = 0;
  }
  else
  {
    /// \todo Use strtol(), and handle parse errors
    const int parsed_value = atoi(value.substr(position,1).c_str());
    _number = parsed_value;
  }
  notifyChanged();
}

} // end of lcdapi namespace
