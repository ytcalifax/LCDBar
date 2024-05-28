#include "Arduino.h"
#include "LCDBar.h"

#ifndef USE_BUILTIN_FILLED_CHAR
byte LCDBar::_level0[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};
#endif

byte LCDBar::_level1[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
};

byte LCDBar::_level2[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000
};

byte LCDBar::_level3[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100
};

byte LCDBar::_level4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
};

LCDBar::LCDBar(Waveshare_LCD1602_RGB* lcd, byte numCols, byte startX, byte startY)
    : _lcd(lcd), _numCols(numCols), _startX(startX), _startY(startY) {}

void LCDBar::begin() {
#ifndef USE_BUILTIN_FILLED_CHAR
    _lcd->customSymbol(0, _level0);
#endif
    _lcd->customSymbol(1, _level1);
    _lcd->customSymbol(2, _level2);
    _lcd->customSymbol(3, _level3);
    _lcd->customSymbol(4, _level4);
    _lcd->clear();
    _prevValue = 0;
    _lastFullChars = 0;
    _initialized = true;
}

void LCDBar::drawValue(int value, int maxValue) {
    if (!_initialized) {
        begin();
    }

    if(value > maxValue) {
      return;
    }

    byte fullChars = (long)value * _numCols / maxValue;
    byte mod = ((long)value * _numCols * 5 / maxValue) % 5;

    int normalizedValue = (int)fullChars * 5 + mod;
    if (_prevValue != normalizedValue) {
        _lcd->setCursor(_startX, _startY);

        for (byte i = 0; i < fullChars; i++) {
#ifdef USE_BUILTIN_FILLED_CHAR
            _lcd->write_char((byte)USE_BUILTIN_FILLED_CHAR);
#else
            _lcd->write_char((byte)0);
#endif
        }

        if (mod > 0) {
            _lcd->write_char(mod);
            ++fullChars;
        }

        for (byte i = fullChars; i < _lastFullChars; i++) {
            _lcd->write_char(' ');
        }

        _lastFullChars = fullChars;
        _prevValue = normalizedValue;
    }
}
