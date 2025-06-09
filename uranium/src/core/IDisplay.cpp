#include "uranium/core/IDisplay.hpp"

using namespace uranium::core;

const IDisplay::Properties IDisplay::DEFAULT = {
    "Default",              // title
    "",                     // icon_path
    800,                    // width
    600,                    // height
    100,                    // opacity
    Mode::WINDOWED,         // mode
    Resolution::R_800x600,  // resolution
    0,                      // xposition
    0,                      // yposition
    1,                      // antialiasing level
    true,                   // vsync
    true,                   // visible
    true                    // resizable
};

IDisplay::IDisplay(const Properties& properties,
                   const IMonitor& smonitor) noexcept
    : properties(properties), initialized(false) {}

uint32_t IDisplay::getWidth() const {
  // Width
  return properties.width;
}

uint32_t IDisplay::getHeight() const {
  // Height
  return properties.height;
}

float IDisplay::getAspectRatio() const {
  return (float)properties.width / (float)properties.height;
}

void IDisplay::getPosition(int32_t* xpos, int32_t* ypos) const {
  *xpos = xpos != nullptr ? properties.xposition : 0;
  *ypos = ypos != nullptr ? properties.yposition : 0;
}

IDisplay::Mode IDisplay::getMode() const {
  // Current mode
  return properties.mode;
}

IDisplay::Resolution IDisplay::getResolution() const {
  return properties.resolution;
}

bool IDisplay::hasInitialized() const { return initialized; }