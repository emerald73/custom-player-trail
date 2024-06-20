#ifndef _COLORCONVERSION_H_
#define _COLORCONVERSION_H_
#include <Geode/geode.hpp>
#include <Geode/cocos/include/ccTypes.h>
#include <Geode/loader/Mod.hpp>
#include <Geode/modify/CCMotionStreak.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

float hue_base = 0;

void computeHSVtoRGB(float &rgb_red,
  float &rgb_green,
  float &rgb_blue,
  float &hsv_hue,
  float &hsv_saturation,
  float &hsv_value) {

    float rgbRange = hsv_value * hsv_saturation;
    float maxRGB = hsv_value;
    float minRGB = hsv_value - rgbRange;
    float h_prime = fmod(hsv_hue / 60, 6);
    float gradient_pos = fmod(h_prime, 1.0);
    float gradient_neg = (1 - fmod(h_prime, 1.0));

    if (h_prime >= 0 && h_prime < 1) {
      rgb_red = maxRGB;
      rgb_green = ((gradient_pos * rgbRange) + minRGB);
      rgb_blue = minRGB;
    } else if (h_prime >= 1 && h_prime < 2) {
      rgb_red = ((gradient_neg * rgbRange) + minRGB);
      rgb_green = maxRGB;
      rgb_blue = minRGB;
    } else if (h_prime >= 2 && h_prime < 3) {
      rgb_red = minRGB;
      rgb_green = maxRGB;
      rgb_blue = ((gradient_pos * rgbRange) + minRGB);
    } else if (h_prime >= 3 && h_prime < 4) {
      rgb_red = minRGB;
      rgb_green = ((gradient_neg * rgbRange) + minRGB);
      rgb_blue = maxRGB;
    } else if (h_prime >= 4 && h_prime < 5) {
      rgb_red = ((gradient_pos * rgbRange) + minRGB);
      rgb_green = minRGB;
      rgb_blue = maxRGB;
    } else if (h_prime >= 5 && h_prime < 6) {
      rgb_red = maxRGB;
      rgb_green = minRGB;
      rgb_blue = ((gradient_neg * rgbRange) + minRGB);
    } else {
      rgb_red = 0;
      rgb_blue = 0;
      rgb_green = 0;
    }

    rgb_red = rgb_red * 255;
    rgb_green = rgb_green * 255;
    rgb_blue = rgb_blue * 255;
}

cocos2d::_ccColor3B getRGB(float offset, float saturation, float value) {
	float rgb_red;
	float rgb_green;
	float rgb_blue;

	float hue = fmod(hue_base + offset, 360);
	float sat = saturation / 100;
	float val = value / 100;

	computeHSVtoRGB(rgb_red, rgb_green, rgb_blue, hue, sat, val);

	cocos2d::_ccColor3B out;
	out.r = rgb_red;
	out.g = rgb_green;
	out.b = rgb_blue;

	return out;
}

#endif