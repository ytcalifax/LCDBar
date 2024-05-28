#ifndef LCDBARGRAPH_H
#define LCDBARGRAPH_H

#include "Arduino.h"
#include "Waveshare_LCD1602_RGB.h"

// Define a character to be used for filling the bar graph if built-in characters are not used
#define USE_BUILTIN_FILLED_CHAR  0xFF

/**
 * @brief Library for displaying a horizontal bar graph on an LCD screen.
 *
 * This class provides methods to draw a horizontal bar graph on an LCD screen.
 */
class LCDBar {
public:
    /**
     * @brief Constructs a new LCDBar object.
     *
     * @param lcd Pointer to the LCD object.
     * @param numCols Number of columns for the bar graph.
     * @param startX Starting X position for the bar graph.
     * @param startY Starting Y position for the bar graph.
     */
    LCDBar(Waveshare_LCD1602_RGB* lcd, byte numCols, byte startX = 0, byte startY = 0);

    /**
     * @brief Draws the bar graph representing the given value.
     *
     * @param value The value to be represented by the bar graph.
     * @param maxValue The maximum value that can be represented.
     */
    void drawValue(int value, int maxValue);

    /**
     * @brief Initializes the bar graph.
     *
     * This function should be called before using other functions of this class.
     */
    void begin();

private:
    Waveshare_LCD1602_RGB* _lcd; // Pointer to the LCD object
    byte _numCols; // Number of columns for the bar graph
    byte _startX; // Starting X position for the bar graph
    byte _startY; // Starting Y position for the bar graph
    int _prevValue; // Previous value of the bar graph
    byte _lastFullChars; // Number of last full characters
    bool _initialized = false; // Flag indicating whether the object is initialized

#ifndef USE_BUILTIN_FILLED_CHAR
    static byte _level0[8]; // Custom character for level 0
#endif
    static byte _level1[8]; // Custom character for level 1
    static byte _level2[8]; // Custom character for level 2
    static byte _level3[8]; // Custom character for level 3
    static byte _level4[8]; // Custom character for level 4
};

#endif
