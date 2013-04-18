#include <lcdapi/api/LCDBar.h>
#include <cstdlib>
#include <sstream>

namespace lcdapi {

using namespace std;

LCDBar::LCDBar(const string &widgetType, const string &id, LCDElement *parent) : LCDWidget(id, parent, widgetType), _length(0), _max(100)
{
}

LCDBar::LCDBar(const string &widgetType, int length, int x, int y, const string &id, LCDElement *parent) : LCDWidget(id, parent, widgetType), _length(length), _max(100)
{
  set(length, x, y);
}

void LCDBar::notifyChanged()
{
  ostringstream params;

  params << _x
         << " "
         << _y
         << " "
         << _length;

  setWidgetParameters(params.str());
}

void LCDBar::set(int length, int x, int y)
{
  if (_length != length || _x != x || _y != y) {
    _length = length;
    _x = x;
    _y =y;
    notifyChanged();
  }
}

void LCDBar::setPercentage(int value)
{
  const int new_length = (value * _max) / 100;
  set(new_length, _x, _y);
}

int LCDBar::getPercentage() const
{
  return ((_length * 100) / _max);

}

void LCDBar::setPercentageMax(int max)
{
  _max = max;
}

void LCDBar::valueCallback(const string& value)
{
  /// \todo Use strtol(), and handle parse errors
  const int parsed_value = atoi(value.c_str());
  setPercentage(parsed_value);
}

} // end of lcdapi namespace