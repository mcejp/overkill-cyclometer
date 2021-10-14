#ifndef BIKECU_DRAW_HPP
#define BIKECU_DRAW_HPP

struct Font;

extern const Font font8x12;
extern const Font font16x20;
extern const Font font32x48;

void puttextat(Font const& font, int x_div_8, int y, const char* text);

#endif //BIKECU_DRAW_HPP
