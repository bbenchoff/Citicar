#include "IS31FL3741.h"
#include "Arduino.h"
#include <Wire.h>
#include "Globals.h"

typedef struct {
  uint8_t x;
  uint8_t y;
  uint8_t Pixel;
} Lookup;

Lookup page0_Top[180] = {
  {0, 8, 0x00}, {1, 8, 0x01}, {2, 8, 0x02}, {3, 8, 0x03}, {4, 8, 0x04}, {5, 8, 0x05}, {6, 8, 0x06}, {7, 8, 0x07}, {8, 8, 0x08}, {9, 8, 0x09}, {10, 8, 0x0A}, {11, 8, 0x0B}, {12, 8, 0x0C}, {13, 8, 0x0D}, {14, 8, 0x0E}, {15, 8, 0x0F}, {16, 8, 0x10}, {17, 8, 0x11}, {18, 8, 0x12}, {19, 8, 0x13}, {20, 8, 0x14}, {21, 8, 0x15}, {22, 8, 0x16}, {23, 8, 0x17}, {24, 8, 0x18}, {25, 8, 0x19}, {26, 8, 0x1A}, {27, 8, 0x1B}, {28, 8, 0x1C}, {29, 8, 0x1D}, 
  {0, 7, 0x1E}, {1, 7, 0x1F}, {2, 7, 0x20}, {3, 7, 0x21}, {4, 7, 0x22}, {5, 7, 0x23}, {6, 7, 0x24}, {7, 7, 0x25}, {8, 7, 0x26}, {9, 7, 0x27}, {10, 7, 0x28}, {11, 7, 0x29}, {12, 7, 0x2A}, {13, 7, 0x2B}, {14, 7, 0x2C}, {15, 7, 0x2D}, {16, 7, 0x2E}, {17, 7, 0x2F}, {18, 7, 0x30}, {19, 7, 0x31}, {20, 7, 0x32}, {21, 7, 0x33}, {22, 7, 0x34}, {23, 7, 0x35}, {24, 7, 0x36}, {25, 7, 0x37}, {26, 7, 0x38}, {27, 7, 0x39}, {28, 7, 0x3A}, {29, 7, 0x3B},
  {0, 6, 0x3C}, {1, 6, 0x3D}, {2, 6, 0x3E}, {3, 6, 0x3F}, {4, 6, 0x40}, {5, 6, 0x41}, {6, 6, 0x42}, {7, 6, 0x43}, {8, 6, 0x44}, {9, 6, 0x45}, {10, 6, 0x46}, {11, 6, 0x47}, {12, 6, 0x48}, {13, 6, 0x49}, {14, 6, 0x4A}, {15, 6, 0x4B}, {16, 6, 0x4C}, {17, 6, 0x4D}, {18, 6, 0x4E}, {19, 6, 0x4F}, {20, 6, 0x50}, {21, 6, 0x51}, {22, 6, 0x52}, {23, 6, 0x53}, {24, 6, 0x54}, {25, 6, 0x55}, {26, 6, 0x56}, {27, 6, 0x57}, {28, 6, 0x58}, {29, 6, 0x59}, 
  {0, 5, 0x5A}, {1, 5, 0x5B}, {2, 5, 0x5C}, {3, 5, 0x5D}, {4, 5, 0x5E}, {5, 5, 0x5F}, {6, 5, 0x60}, {7, 5, 0x61}, {8, 5, 0x62}, {9, 5, 0x63}, {10, 5, 0x64}, {11, 5, 0x65}, {12, 5, 0x66}, {13, 5, 0x67}, {14, 5, 0x68}, {15, 5, 0x69}, {16, 5, 0x6A}, {17, 5, 0x6B}, {18, 5, 0x6C}, {19, 5, 0x6D}, {20, 5, 0x6E}, {21, 5, 0x6F}, {22, 5, 0x70}, {23, 5, 0x71}, {24, 5, 0x72}, {25, 5, 0x73}, {26, 5, 0x74}, {27, 5, 0x75}, {28, 5, 0x76}, {29, 5, 0x77},
  {0, 4, 0x78}, {1, 4, 0x79}, {2, 4, 0x7A}, {3, 4, 0x7B}, {4, 4, 0x7C}, {5, 4, 0x7D}, {6, 4, 0x7E}, {7, 4, 0x7F}, {8, 4, 0x80}, {9, 4, 0x81}, {10, 4, 0x82}, {11, 4, 0x83}, {12, 4, 0x84}, {13, 4, 0x85}, {14, 4, 0x86}, {15, 4, 0x87}, {16, 4, 0x88}, {17, 4, 0x89}, {18, 4, 0x8A}, {19, 4, 0x8B}, {20, 4, 0x8C}, {21, 4, 0x8D}, {22, 4, 0x8E}, {23, 4, 0x8F}, {24, 4, 0x90}, {25, 4, 0x91}, {26, 4, 0x92}, {27, 4, 0x93}, {28, 4, 0x94}, {29, 4, 0x95},
  {0, 3, 0x96}, {1, 3, 0x97}, {2, 3, 0x98}, {3, 3, 0x99}, {4, 3, 0x9A}, {5, 3, 0x9B}, {6, 3, 0x9C}, {7, 3, 0x9D}, {8, 3, 0x9E}, {9, 3, 0x9F}, {10, 3, 0xA0}, {11, 3, 0xA1}, {12, 3, 0xA2}, {13, 3, 0xA3}, {14, 3, 0xA4}, {15, 3, 0xA5}, {16, 3, 0xA6}, {17, 3, 0xA7}, {18, 3, 0xA8}, {19, 3, 0xA9}, {20, 3, 0xAA}, {21, 3, 0xAB}, {22, 3, 0xAC}, {23, 3, 0xAD}, {24, 3, 0xAE}, {25, 3, 0xAF}, {26, 3, 0xB0}, {27, 3, 0xB1}, {28, 3, 0xB2}, {29, 3, 0xB3}
};

Lookup page1_Top[171] = {
  {0, 2, 0x00}, {1, 2, 0x01}, {2, 2, 0x02}, {3, 2, 0x03}, {4, 2, 0x04}, {5, 2, 0x05}, {6, 2, 0x06}, {7, 2, 0x07}, {8, 2, 0x08}, {9, 2, 0x09}, {10, 2, 0x0A}, {11, 2, 0x0B}, {12, 2, 0x0C}, {13, 2, 0x0D}, {14, 2, 0x0E}, {15, 2, 0x0F}, {16, 2, 0x10}, {17, 2, 0x11}, {18, 2, 0x12}, {19, 2, 0x13}, {20, 2, 0x14}, {21, 2, 0x15}, {22, 2, 0x16}, {23, 2, 0x17}, {24, 2, 0x18}, {25, 2, 0x19}, {26, 2, 0x1A}, {27, 2, 0x1B}, {28, 2, 0x1C}, {29, 2, 0x1D},
  {0, 1, 0x1E}, {1, 1, 0x1F}, {2, 1, 0x20}, {3, 1, 0x21}, {4, 1, 0x22}, {5, 1, 0x23}, {6, 1, 0x24}, {7, 1, 0x25}, {8, 1, 0x26}, {9, 1, 0x27}, {10, 1, 0x28}, {11, 1, 0x29}, {12, 1, 0x2A}, {13, 1, 0x2B}, {14, 1, 0x2C}, {15, 1, 0x2D}, {16, 1, 0x2E}, {17, 1, 0x2F}, {18, 1, 0x30}, {19, 1, 0x31}, {20, 1, 0x32}, {21, 1, 0x33}, {22, 1, 0x34}, {23, 1, 0x35}, {24, 1, 0x36}, {25, 1, 0x37}, {26, 1, 0x38}, {27, 1, 0x39}, {28, 1, 0x3A}, {29, 1, 0x3B},
  {0, 0, 0x3C}, {1, 0, 0x3D}, {2, 0, 0x3E}, {3, 0, 0x3F}, {4, 0, 0x40}, {5, 0, 0x41}, {6, 0, 0x42}, {7, 0, 0x43}, {8, 0, 0x44}, {9, 0, 0x45}, {10, 0, 0x46}, {11, 0, 0x47}, {12, 0, 0x48}, {13, 0, 0x49}, {14, 0, 0x4A}, {15, 0, 0x4B}, {16, 0, 0x4C}, {17, 0, 0x4D}, {18, 0, 0x4E}, {19, 0, 0x4F}, {20, 0, 0x50}, {21, 0, 0x51}, {22, 0, 0x52}, {23, 0, 0x53}, {24, 0, 0x54}, {25, 0, 0x55}, {26, 0, 0x56}, {27, 0, 0x57}, {28, 0, 0x58}, {29, 0, 0x59},

  {30, 8, 0x5A}, {31, 8, 0x5B}, {32, 8, 0x5C}, {33, 8, 0x5D}, {34, 8, 0x5E}, {35, 8, 0x5F}, {36, 8, 0x60}, {37, 8, 0x61}, {38, 8, 0x62},
  {30, 7, 0x63}, {31, 7, 0x64}, {32, 7, 0x65}, {33, 7, 0x66}, {34, 7, 0x67}, {35, 7, 0x68}, {36, 7, 0x69}, {37, 7, 0x6A}, {38, 7, 0x6B},
  {30, 6, 0x6C}, {31, 6, 0x6D}, {32, 6, 0x6E}, {33, 6, 0x6F}, {34, 6, 0x70}, {35, 6, 0x71}, {36, 6, 0x72}, {37, 6, 0x73}, {38, 6, 0x74},
  {30, 5, 0x75}, {31, 5, 0x76}, {32, 5, 0x77}, {33, 5, 0x78}, {34, 5, 0x79}, {35, 5, 0x7A}, {36, 5, 0x7B}, {37, 5, 0x7C}, {38, 5, 0x7D},
  {30, 4, 0x7E}, {31, 4, 0x7F}, {32, 4, 0x80}, {33, 4, 0x81}, {34, 4, 0x82}, {35, 4, 0x83}, {36, 4, 0x84}, {37, 4, 0x85}, {38, 4, 0x86},
  {30, 3, 0x87}, {31, 3, 0x88}, {32, 3, 0x89}, {33, 3, 0x8A}, {34, 3, 0x8B}, {35, 3, 0x8C}, {36, 3, 0x8E}, {37, 3, 0x8F}, {38, 3, 0x90},
  {30, 2, 0x91}, {31, 2, 0x92}, {32, 2, 0x93}, {33, 2, 0x94}, {34, 2, 0x95}, {35, 2, 0x96}, {36, 2, 0x97}, {37, 2, 0x98}, {38, 2, 0x99},
  {30, 1, 0x9A}, {31, 1, 0x9B}, {32, 1, 0x9C}, {33, 1, 0x9D}, {34, 1, 0x9E}, {35, 1, 0x9F}, {36, 1, 0xA0}, {37, 1, 0xA1}, {38, 1, 0xA2},
  {30, 0, 0xA3}, {31, 0, 0xA4}, {32, 0, 0xA5}, {33, 0, 0xA6}, {34, 0, 0xA7}, {35, 0, 0xA8}, {36, 0, 0xA9}, {37, 0, 0xAA}, {38, 0, 0xAB},
};

Lookup page0_Bottom[180] = {
  {38, 9, 0x00}, {37, 9, 0x01}, {36, 9, 0x02}, {35, 9, 0x03}, {34, 9, 0x04}, {33, 9, 0x05}, {32, 9, 0x06}, {31, 9, 0x07}, {30, 9, 0x08}, {29, 9, 0x09}, {28, 9, 0x0A}, {27, 9, 0x0B}, {26, 9, 0x0C}, {25, 9, 0x0D}, {24, 9, 0x0E}, {23, 9, 0x0F}, {22, 9, 0x10}, {21, 9, 0x11}, {20, 9, 0x12}, {19, 9, 0x13}, {18, 9, 0x14}, {17, 9, 0x15}, {16, 9, 0x16}, {15, 9, 0x17}, {14, 9, 0x18}, {13, 9, 0x19}, {12, 9, 0x1A}, {11, 9, 0x1B}, {10, 9, 0x1C}, {9, 9, 0x1D}, 
  {38, 10, 0x1E}, {37, 10, 0x1F}, {36, 10, 0x20}, {35, 10, 0x21}, {34, 10, 0x22}, {33, 10, 0x23}, {32, 10, 0x24}, {31, 10, 0x25}, {30, 10, 0x26}, {29, 10, 0x27}, {28, 10, 0x28}, {27, 10, 0x29}, {26, 10, 0x2A}, {25, 10, 0x2B}, {24, 10, 0x2C}, {23, 10, 0x2D}, {22, 10, 0x2E}, {21, 10, 0x2F}, {20, 10, 0x30}, {19, 10, 0x31}, {18, 10, 0x32}, {17, 10, 0x33}, {16, 10, 0x34}, {15, 10, 0x35}, {14, 10, 0x36}, {13, 10, 0x37}, {12, 10, 0x38}, {11, 10, 0x39}, {10, 10, 0x3A}, {9, 10, 0x3B},
  {38, 11, 0x3C}, {37, 11, 0x3D}, {36, 11, 0x3E}, {35, 11, 0x3F}, {34, 11, 0x40}, {33, 11, 0x41}, {32, 11, 0x42}, {31, 11, 0x43}, {30, 11, 0x44}, {29, 11, 0x45}, {28, 11, 0x46}, {27, 11, 0x47}, {26, 11, 0x48}, {25, 11, 0x49}, {24, 11, 0x4A}, {23, 11, 0x4B}, {22, 11, 0x4C}, {21, 11, 0x4D}, {20, 11, 0x4E}, {19, 11, 0x4F}, {18, 11, 0x50}, {17, 11, 0x51}, {16, 11, 0x52}, {15, 11, 0x53}, {14, 11, 0x54}, {13, 11, 0x55}, {12, 11, 0x56}, {11, 11, 0x57}, {10, 11, 0x58}, {9, 11, 0x59}, 
  {38, 12, 0x5A}, {37, 12, 0x5B}, {36, 12, 0x5C}, {35, 12, 0x5D}, {34, 12, 0x5E}, {33, 12, 0x5F}, {32, 12, 0x60}, {31, 12, 0x61}, {30, 12, 0x62}, {29, 12, 0x63}, {28, 12, 0x64}, {27, 12, 0x65}, {26, 12, 0x66}, {25, 12, 0x67}, {24, 12, 0x68}, {23, 12, 0x69}, {22, 12, 0x6A}, {21, 12, 0x6B}, {20, 12, 0x6C}, {19, 12, 0x6D}, {18, 12, 0x6E}, {17, 12, 0x6F}, {16, 12, 0x70}, {15, 12, 0x71}, {14, 12, 0x72}, {13, 12, 0x73}, {12, 12, 0x74}, {11, 12, 0x75}, {10, 12, 0x76}, {9, 12, 0x77},
  {38, 13, 0x78}, {37, 13, 0x79}, {36, 13, 0x7A}, {35, 13, 0x7B}, {34, 13, 0x7C}, {33, 13, 0x7D}, {32, 13, 0x7E}, {31, 13, 0x7F}, {30, 13, 0x80}, {29, 13, 0x81}, {28, 13, 0x82}, {27, 13, 0x83}, {26, 13, 0x84}, {25, 13, 0x85}, {24, 13, 0x86}, {23, 13, 0x87}, {22, 13, 0x88}, {21, 13, 0x89}, {20, 13, 0x8A}, {19, 13, 0x8B}, {18, 13, 0x8C}, {17, 13, 0x8D}, {16, 13, 0x8E}, {15, 13, 0x8F}, {14, 13, 0x90}, {13, 13, 0x91}, {12, 13, 0x92}, {11, 13, 0x93}, {10, 13, 0x94}, {9, 13, 0x95},
  {38, 14, 0x96}, {37, 14, 0x97}, {36, 14, 0x98}, {35, 14, 0x99}, {34, 14, 0x9A}, {33, 14, 0x9B}, {32, 14, 0x9C}, {31, 14, 0x9D}, {30, 14, 0x9E}, {29, 14, 0x9F}, {28, 14, 0xA0}, {27, 14, 0xA1}, {26, 14, 0xA2}, {25, 14, 0xA3}, {24, 14, 0xA4}, {23, 14, 0xA5}, {22, 14, 0xA6}, {21, 14, 0xA7}, {20, 14, 0xA8}, {19, 14, 0xA9}, {18, 14, 0xAA}, {17, 14, 0xAB}, {16, 14, 0xAC}, {15, 14, 0xAD}, {14, 14, 0xAE}, {13, 14, 0xAF}, {12, 14, 0xB0}, {11, 14, 0xB1}, {10, 14, 0xB2}, {9, 14, 0xB3}
};

Lookup page1_Bottom[171] = {
  {38, 15, 0x00}, {37, 15, 0x01}, {36, 15, 0x02}, {35, 15, 0x03}, {34, 15, 0x04}, {33, 15, 0x05}, {32, 15, 0x06}, {31, 15, 0x07}, {30, 15, 0x08}, {29, 15, 0x09}, {28, 15, 0x0A}, {27, 15, 0x0B}, {26, 15, 0x0C}, {25, 15, 0x0D}, {24, 15, 0x0E}, {23, 15, 0x0F}, {22, 15, 0x10}, {21, 15, 0x11}, {20, 15, 0x12}, {19, 15, 0x13}, {18, 15, 0x14}, {17, 15, 0x15}, {16, 15, 0x16}, {15, 15, 0x17}, {14, 15, 0x18}, {13, 15, 0x19}, {12, 15, 0x1A}, {11, 15, 0x1B}, {10, 15, 0x1C}, {9, 15, 0x1D},
  {38, 16, 0x1E}, {37, 16, 0x1F}, {36, 16, 0x20}, {35, 16, 0x21}, {34, 16, 0x22}, {33, 16, 0x23}, {32, 16, 0x24}, {31, 16, 0x25}, {30, 16, 0x26}, {29, 16, 0x27}, {28, 16, 0x28}, {27, 16, 0x29}, {26, 16, 0x2A}, {25, 16, 0x2B}, {24, 16, 0x2C}, {23, 16, 0x2D}, {22, 16, 0x2E}, {21, 16, 0x2F}, {20, 16, 0x30}, {19, 16, 0x31}, {18, 16, 0x32}, {17, 16, 0x33}, {16, 16, 0x34}, {15, 16, 0x35}, {14, 16, 0x36}, {13, 16, 0x37}, {12, 16, 0x38}, {11, 16, 0x39}, {10, 16, 0x3A}, {9, 16, 0x3B},
  {38, 17, 0x3C}, {37, 17, 0x3D}, {36, 17, 0x3E}, {35, 17, 0x3F}, {34, 17, 0x40}, {33, 17, 0x41}, {32, 17, 0x42}, {31, 17, 0x43}, {30, 17, 0x44}, {29, 17, 0x45}, {28, 17, 0x46}, {27, 17, 0x47}, {26, 17, 0x48}, {25, 17, 0x49}, {24, 17, 0x4A}, {23, 17, 0x4B}, {22, 17, 0x4C}, {21, 17, 0x4D}, {20, 17, 0x4E}, {19, 17, 0x4F}, {18, 17, 0x50}, {17, 17, 0x51}, {16, 17, 0x52}, {15, 17, 0x53}, {14, 17, 0x54}, {13, 17, 0x55}, {12, 17, 0x56}, {11, 17, 0x57}, {10, 17, 0x58}, {9, 17, 0x59},

  {8, 9, 0x5A}, {7, 9, 0x5B}, {6, 9, 0x5C}, {5, 9, 0x5D}, {4, 9, 0x5E}, {3, 9, 0x5F}, {2, 9, 0x60}, {1, 9, 0x61}, {0, 9, 0x62},
  {8, 10, 0x63}, {7, 10, 0x64}, {6, 10, 0x65}, {5, 10, 0x66}, {4, 10, 0x67}, {3, 10, 0x68}, {2, 10, 0x69}, {1, 10, 0x6A}, {0, 10, 0x6B},
  {8, 11, 0x6C}, {7, 11, 0x6D}, {6, 11, 0x6E}, {5, 11, 0x6F}, {4, 11, 0x70}, {3, 11, 0x71}, {2, 11, 0x72}, {1, 11, 0x73}, {0, 11, 0x74},
  {8, 12, 0x75}, {7, 12, 0x76}, {6, 12, 0x77}, {5, 12, 0x78}, {4, 12, 0x79}, {3, 12, 0x7A}, {2, 12, 0x7B}, {1, 12, 0x7C}, {0, 12, 0x7D},
  {8, 13, 0x7E}, {7, 13, 0x7F}, {6, 13, 0x80}, {5, 13, 0x81}, {4, 13, 0x82}, {3, 13, 0x83}, {2, 13, 0x84}, {1, 13, 0x85}, {0, 13, 0x86},
  {8, 14, 0x87}, {7, 14, 0x88}, {6, 14, 0x89}, {5, 14, 0x8A}, {4, 14, 0x8B}, {3, 14, 0x8C}, {2, 14, 0x8E}, {1, 14, 0x8F}, {0, 14, 0x90},
  {8, 15, 0x91}, {7, 15, 0x92}, {6, 15, 0x93}, {5, 15, 0x94}, {4, 15, 0x95}, {3, 15, 0x96}, {2, 15, 0x97}, {1, 15, 0x98}, {0, 15, 0x99},
  {8, 16, 0x9A}, {7, 16, 0x9B}, {6, 16, 0x9C}, {5, 16, 0x9D}, {4, 16, 0x9E}, {3, 16, 0x9F}, {2, 16, 0xA0}, {1, 16, 0xA1}, {0, 16, 0xA2},
  {8, 17, 0xA3}, {7, 17, 0xA4}, {6, 17, 0xA5}, {5, 17, 0xA6}, {4, 17, 0xA7}, {3, 17, 0xA8}, {2, 17, 0xA9}, {1, 17, 0xAA}, {0, 17, 0xAB},
};


MyIS41::MyIS41(uint8_t address) {
  chipAddress = address;
}

void MyIS41::clearDisplay()
{
  //Clear the display
  //This is done by seeting PWM value to 0x00
  writeByte(chipAddress,0xfe,0xc5);//unlock
  writeByte(chipAddress,0xfD,0x00);//write page 0
  for(int i=0;i<0xB4;i++){
    writeByte(chipAddress,i,0x00);//write all PWM set 0x00
  }

  writeByte(chipAddress,0xfe,0xc5);//unlock
  writeByte(chipAddress,0xfD,0x01);//write page 1
  for(int i=0;i<0xAB;i++){
    writeByte(chipAddress,i,0x00);//write all PWM set 0x00
  } //init all the PWM data to 0x00
}

void MyIS41::setGlobalCurrent(uint8_t brightness)
{
  writeByte(chipAddress,0xfe,0xc5);//unlock
  writeByte(chipAddress,0xfD,0x04);//write page 4
  writeByte(chipAddress,0x01, brightness);//write global current
  writeByte(chipAddress,0x00, 0x01);//normal operation
}

void MyIS41::begin()
{
  //unlock the chip and set scaling for all LEDs to 0xFF
  writeByte(chipAddress,0xfe,0xc5); //unlock
  writeByte(chipAddress, 0xfd,0x02); //write page 2
  for(int i=0;i<0xB4;i++){
    writeByte(chipAddress, i,255);
  }

  //unlock the chip and set scaling for all LEDs to 0xFF
  writeByte(chipAddress,0xfe,0xc5);//unlock
  writeByte(chipAddress,0xfD,0x03);//write page 3
  for(int i=0;i<0xAB;i++){
    writeByte(chipAddress, i,255);
  }

  //Clear the display
  //This is done by seeting PWM value to 0x00
  writeByte(chipAddress,0xfe,0xc5);//unlock
  writeByte(chipAddress,0xfD,0x00);//write page 0
  for(int i=0;i<0xB4;i++){
    writeByte(chipAddress,i,0x00);//write all PWM set 0x00
  }

  writeByte(chipAddress,0xfe,0xc5);//unlock
  writeByte(chipAddress,0xfD,0x01);//write page 1
  for(int i=0;i<0xAB;i++){
    writeByte(chipAddress,i,0x00);//write all PWM set 0x00
  } //init all the PWM data to 0x00

  writeByte(chipAddress,0xfe,0xc5);//unlock
  writeByte(chipAddress,0xfD,0x04);//write page 4
  writeByte(chipAddress,0x01, 0x0F);//write global current
  writeByte(chipAddress,0x00, 0x01);//normal operation

  /* This was code for testing
  //try to write a pixel here
    for(int i = 0; i < 0xB4 ; i++)
    {
        writeByte(chipAddress,0xfe,0xc5);//unlock
        writeByte(chipAddress,0xfD,0x00);//write page 0
        writeByte(chipAddress,i,0xFF);//write all PWM set 0x00
        
        delay(0);

        writeByte(chipAddress,0xfe,0xc5);//unlock
        writeByte(chipAddress,0xfD,0x00);//write page 0
        writeByte(chipAddress,i,0x00);//write all PWM set 0x00
    }

        for(int i = 0; i < 0xAB ; i++)
    {
        writeByte(chipAddress,0xfe,0xc5);//unlock
        writeByte(chipAddress,0xfD,0x01);//write page 0
        writeByte(chipAddress,i,0xFF);//write all PWM set 0x00
        
        delay(0);

        writeByte(chipAddress,0xfe,0xc5);//unlock
        writeByte(chipAddress,0xfD,0x01);//write page 0
        writeByte(chipAddress,i,0x00);//write all PWM set 0x00
    }*/
}

void writeByte(uint8_t Dev_Add, uint8_t Reg_Add, uint8_t Reg_Dat)
{
  Wire.beginTransmission(Dev_Add);
  Wire.write(Reg_Add);
  Wire.write(Reg_Dat);
  Wire.endTransmission();
}

void MyIS41::printFramebuffer(uint8_t buffer[18][39])
{
  uint8_t localFramebuffer[18][39];
  uint8_t currentX;
  uint8_t currentY;

  //create a local buffer object
  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 39; j++) {
      localFramebuffer[i][j] = buffer[i][j];
    }
  }

  if(this->chipAddress == 0x30) // THIS IS THE BOTTOM HALF OF THE DISPLAY
  {
    //do the stuff for page 0:
    writeByte(chipAddress,0xfe,0xc5);//unlock
    writeByte(chipAddress,0xfD,0x00);//write page 0
    //begin buffer dump
    Wire.beginTransmission(0x30);
    Wire.write(0xFE);
    Wire.write(0xC5);
    Wire.write(0x80);//I have no idea why this is necessary
    for(int i = 0 ; i < 0xB4 ; i++)
    {
      currentX = page0_Bottom[i].x;
      currentY = page0_Bottom[i].y;
      Wire.write(localFramebuffer[currentY][currentX]);
    }
    Wire.endTransmission();

    //do the stuff for page 1:
    writeByte(chipAddress,0xfe,0xc5);//unlock
    writeByte(chipAddress,0xfD,0x01);//write page 1
    //begin buffer dump
    Wire.beginTransmission(0x30);
    Wire.write(0xFE);
    Wire.write(0xC5);
    Wire.write(0x80);
    for(int i = 0 ; i < 0xAB ; i++)
    {
      currentX = page1_Bottom[i].x;
      currentY = page1_Bottom[i].y;
      Wire.write(localFramebuffer[currentY][currentX]);
    }
    Wire.endTransmission();

  }
  else  // THIS IS THE TOP HALF OF THE DISPLAY
  {
    //do the stuff for page 0:
    writeByte(chipAddress,0xfe,0xc5);//unlock
    writeByte(chipAddress,0xfD,0x00);//write page 0
    //begin buffer dump
    Wire.beginTransmission(0x33);
    Wire.write(0xFE);
    Wire.write(0xC5);
    Wire.write(0x80);
    for(int i = 0 ; i < 0xB4 ; i++)
    {
      currentX = page0_Top[i].x;
      currentY = page0_Top[i].y;
      Wire.write(localFramebuffer[currentY][currentX]);
    }
    Wire.endTransmission();

   //do the stuff for page 1:
    writeByte(chipAddress,0xfe,0xc5);//unlock
    writeByte(chipAddress,0xfD,0x01);//write page 1
    //begin buffer dump
    Wire.beginTransmission(0x33);
    Wire.write(0xFE);
    Wire.write(0xC5);
    Wire.write(0x80);
    for(int i = 0 ; i < 0xAB ; i++)
    {
      currentX = page1_Top[i].x;
      currentY = page1_Top[i].y;
      Wire.write(localFramebuffer[currentY][currentX]);
    }
    Wire.endTransmission();

  }
}

void MyIS41::printTestPattern()
{
  uint8_t currentX;
  uint8_t currentY;

  if(this->chipAddress == 0x30) // THIS IS THE BOTTOM HALF OF THE DISPLAY
  {
    //do the stuff for page 0:
    writeByte(chipAddress,0xfe,0xc5);//unlock
    writeByte(chipAddress,0xfD,0x00);//write page 0
    //begin buffer dump
    Wire.beginTransmission(0x30);
    Wire.write(0xFE);
    Wire.write(0xC5);
    Wire.write(0x80);//I have no idea why this is necessary
    for(int i = 0 ; i < 0xB4 ; i++)
    {
      currentX = page0_Bottom[i].x;
      currentY = page0_Bottom[i].y;
      Wire.write(testPattern[currentY][currentX]);
    }
    Wire.endTransmission();

    //do the stuff for page 1:
    writeByte(chipAddress,0xfe,0xc5);//unlock
    writeByte(chipAddress,0xfD,0x01);//write page 1
    //begin buffer dump
    Wire.beginTransmission(0x30);
    Wire.write(0xFE);
    Wire.write(0xC5);
    Wire.write(0x80);
    for(int i = 0 ; i < 0xAB ; i++)
    {
      currentX = page1_Bottom[i].x;
      currentY = page1_Bottom[i].y;
      Wire.write(testPattern[currentY][currentX]);
    }
    Wire.endTransmission();

  }
  else  // THIS IS THE TOP HALF OF THE DISPLAY
  {
    //do the stuff for page 0:
    writeByte(chipAddress,0xfe,0xc5);//unlock
    writeByte(chipAddress,0xfD,0x00);//write page 0
    //begin buffer dump
    Wire.beginTransmission(0x33);
    Wire.write(0xFE);
    Wire.write(0xC5);
    Wire.write(0x80);
    for(int i = 0 ; i < 0xB4 ; i++)
    {
      currentX = page0_Top[i].x;
      currentY = page0_Top[i].y;
      Wire.write(testPattern[currentY][currentX]);
    }
    Wire.endTransmission();

    //do the stuff for page 1:
    writeByte(chipAddress,0xfe,0xc5);//unlock
    writeByte(chipAddress,0xfD,0x01);//write page 1
    //begin buffer dump
    Wire.beginTransmission(0x33);
    Wire.write(0xFE);
    Wire.write(0xC5);
    Wire.write(0x80);
    for(int i = 0 ; i < 0xAB ; i++)
    {
      currentX = page1_Top[i].x;
      currentY = page1_Top[i].y;
      Wire.write(testPattern[currentY][currentX]);
    }
    Wire.endTransmission();

  }
}
