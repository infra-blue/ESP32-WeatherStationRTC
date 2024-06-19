#pragma once

#include <Font_Data.cpp>

/**
 * @brief Two types of fonts for the matrix display.
 * 
 * The first font is a small number font that is 3x5 pixels (only for seconds).
 * The second font is a pixel font that is 4x7 pixels for numbers and 5x7 for the letters (some of them are 6x7).
 */

MD_MAX72XX::fontType_t* font[] = {small_num, pixel_font};
