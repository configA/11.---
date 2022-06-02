#include "6050-DMP.h"

unsigned char ack;	//应答标志位 0:ack 1：nak
//以下的 firmware 及 config update 数据来自于 Jeff Jrowberg 公开的程序
//正常c编译器中将数据储存到ROM中为code如code unsigned char X[100] = {.....}; 在合泰中使用const将数据储存在ROM中
const unsigned char dmpmemorydata[1929]=
{
 // bank 0, 256 bytes
    0xFB, 0x00, 0x00, 0x3E, 0x00, 0x0B, 0x00, 0x36, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x65, 0x00, 0x54, 0xFF, 0xEF, 0x00, 0x00, 0xFA, 0x80, 0x00, 0x0B, 0x12, 0x82, 0x00, 0x01,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x28, 0x00, 0x00, 0xFF, 0xFF, 0x45, 0x81, 0xFF, 0xFF, 0xFA, 0x72, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0xE8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x7F, 0xFF, 0xFF, 0xFE, 0x80, 0x01,
    0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3E, 0x03, 0x30, 0x40, 0x00, 0x00, 0x00, 0x02, 0xCA, 0xE3, 0x09, 0x3E, 0x80, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
    0x41, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x2A, 0x00, 0x00, 0x16, 0x55, 0x00, 0x00, 0x21, 0x82,
    0xFD, 0x87, 0x26, 0x50, 0xFD, 0x80, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x05, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x6F, 0x00, 0x02, 0x65, 0x32, 0x00, 0x00, 0x5E, 0xC0,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFB, 0x8C, 0x6F, 0x5D, 0xFD, 0x5D, 0x08, 0xD9, 0x00, 0x7C, 0x73, 0x3B, 0x00, 0x6C, 0x12, 0xCC,
    0x32, 0x00, 0x13, 0x9D, 0x32, 0x00, 0xD0, 0xD6, 0x32, 0x00, 0x08, 0x00, 0x40, 0x00, 0x01, 0xF4,
    0xFF, 0xE6, 0x80, 0x79, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0xD6, 0x00, 0x00, 0x27, 0x10,
    // bank 1, 256 bytes
    0xFB, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFA, 0x36, 0xFF, 0xBC, 0x30, 0x8E, 0x00, 0x05, 0xFB, 0xF0, 0xFF, 0xD9, 0x5B, 0xC8,
    0xFF, 0xD0, 0x9A, 0xBE, 0x00, 0x00, 0x10, 0xA9, 0xFF, 0xF4, 0x1E, 0xB2, 0x00, 0xCE, 0xBB, 0xF7,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x02, 0x02, 0x00, 0x00, 0x0C,
    0xFF, 0xC2, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0xCF, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x14,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x3F, 0x68, 0xB6, 0x79, 0x35, 0x28, 0xBC, 0xC6, 0x7E, 0xD1, 0x6C,
    0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB2, 0x6A, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x00, 0x00, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x25, 0x4D, 0x00, 0x2F, 0x70, 0x6D, 0x00, 0x00, 0x05, 0xAE, 0x00, 0x0C, 0x02, 0xD0,
    // bank 2, 256 bytes
    0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x00, 0x54, 0xFF, 0xEF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0xFF, 0xEF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // bank 3, 256 bytes
    0xD8, 0xDC, 0xBA, 0xA2, 0xF1, 0xDE, 0xB2, 0xB8, 0xB4, 0xA8, 0x81, 0x91, 0xF7, 0x4A, 0x90, 0x7F,
    0x91, 0x6A, 0xF3, 0xF9, 0xDB, 0xA8, 0xF9, 0xB0, 0xBA, 0xA0, 0x80, 0xF2, 0xCE, 0x81, 0xF3, 0xC2,
    0xF1, 0xC1, 0xF2, 0xC3, 0xF3, 0xCC, 0xA2, 0xB2, 0x80, 0xF1, 0xC6, 0xD8, 0x80, 0xBA, 0xA7, 0xDF,
    0xDF, 0xDF, 0xF2, 0xA7, 0xC3, 0xCB, 0xC5, 0xB6, 0xF0, 0x87, 0xA2, 0x94, 0x24, 0x48, 0x70, 0x3C,
    0x95, 0x40, 0x68, 0x34, 0x58, 0x9B, 0x78, 0xA2, 0xF1, 0x83, 0x92, 0x2D, 0x55, 0x7D, 0xD8, 0xB1,
    0xB4, 0xB8, 0xA1, 0xD0, 0x91, 0x80, 0xF2, 0x70, 0xF3, 0x70, 0xF2, 0x7C, 0x80, 0xA8, 0xF1, 0x01,
    0xB0, 0x98, 0x87, 0xD9, 0x43, 0xD8, 0x86, 0xC9, 0x88, 0xBA, 0xA1, 0xF2, 0x0E, 0xB8, 0x97, 0x80,
    0xF1, 0xA9, 0xDF, 0xDF, 0xDF, 0xAA, 0xDF, 0xDF, 0xDF, 0xF2, 0xAA, 0xC5, 0xCD, 0xC7, 0xA9, 0x0C,
    0xC9, 0x2C, 0x97, 0x97, 0x97, 0x97, 0xF1, 0xA9, 0x89, 0x26, 0x46, 0x66, 0xB0, 0xB4, 0xBA, 0x80,
    0xAC, 0xDE, 0xF2, 0xCA, 0xF1, 0xB2, 0x8C, 0x02, 0xA9, 0xB6, 0x98, 0x00, 0x89, 0x0E, 0x16, 0x1E,
    0xB8, 0xA9, 0xB4, 0x99, 0x2C, 0x54, 0x7C, 0xB0, 0x8A, 0xA8, 0x96, 0x36, 0x56, 0x76, 0xF1, 0xB9,
    0xAF, 0xB4, 0xB0, 0x83, 0xC0, 0xB8, 0xA8, 0x97, 0x11, 0xB1, 0x8F, 0x98, 0xB9, 0xAF, 0xF0, 0x24,
    0x08, 0x44, 0x10, 0x64, 0x18, 0xF1, 0xA3, 0x29, 0x55, 0x7D, 0xAF, 0x83, 0xB5, 0x93, 0xAF, 0xF0,
    0x00, 0x28, 0x50, 0xF1, 0xA3, 0x86, 0x9F, 0x61, 0xA6, 0xDA, 0xDE, 0xDF, 0xD9, 0xFA, 0xA3, 0x86,
    0x96, 0xDB, 0x31, 0xA6, 0xD9, 0xF8, 0xDF, 0xBA, 0xA6, 0x8F, 0xC2, 0xC5, 0xC7, 0xB2, 0x8C, 0xC1,
    0xB8, 0xA2, 0xDF, 0xDF, 0xDF, 0xA3, 0xDF, 0xDF, 0xDF, 0xD8, 0xD8, 0xF1, 0xB8, 0xA8, 0xB2, 0x86,
    // bank 4, 256 bytes
    0xB4, 0x98, 0x0D, 0x35, 0x5D, 0xB8, 0xAA, 0x98, 0xB0, 0x87, 0x2D, 0x35, 0x3D, 0xB2, 0xB6, 0xBA,
    0xAF, 0x8C, 0x96, 0x19, 0x8F, 0x9F, 0xA7, 0x0E, 0x16, 0x1E, 0xB4, 0x9A, 0xB8, 0xAA, 0x87, 0x2C,
    0x54, 0x7C, 0xB9, 0xA3, 0xDE, 0xDF, 0xDF, 0xA3, 0xB1, 0x80, 0xF2, 0xC4, 0xCD, 0xC9, 0xF1, 0xB8,
    0xA9, 0xB4, 0x99, 0x83, 0x0D, 0x35, 0x5D, 0x89, 0xB9, 0xA3, 0x2D, 0x55, 0x7D, 0xB5, 0x93, 0xA3,
    0x0E, 0x16, 0x1E, 0xA9, 0x2C, 0x54, 0x7C, 0xB8, 0xB4, 0xB0, 0xF1, 0x97, 0x83, 0xA8, 0x11, 0x84,
    0xA5, 0x09, 0x98, 0xA3, 0x83, 0xF0, 0xDA, 0x24, 0x08, 0x44, 0x10, 0x64, 0x18, 0xD8, 0xF1, 0xA5,
    0x29, 0x55, 0x7D, 0xA5, 0x85, 0x95, 0x02, 0x1A, 0x2E, 0x3A, 0x56, 0x5A, 0x40, 0x48, 0xF9, 0xF3,
    0xA3, 0xD9, 0xF8, 0xF0, 0x98, 0x83, 0x24, 0x08, 0x44, 0x10, 0x64, 0x18, 0x97, 0x82, 0xA8, 0xF1,
    0x11, 0xF0, 0x98, 0xA2, 0x24, 0x08, 0x44, 0x10, 0x64, 0x18, 0xDA, 0xF3, 0xDE, 0xD8, 0x83, 0xA5,
    0x94, 0x01, 0xD9, 0xA3, 0x02, 0xF1, 0xA2, 0xC3, 0xC5, 0xC7, 0xD8, 0xF1, 0x84, 0x92, 0xA2, 0x4D,
    0xDA, 0x2A, 0xD8, 0x48, 0x69, 0xD9, 0x2A, 0xD8, 0x68, 0x55, 0xDA, 0x32, 0xD8, 0x50, 0x71, 0xD9,
    0x32, 0xD8, 0x70, 0x5D, 0xDA, 0x3A, 0xD8, 0x58, 0x79, 0xD9, 0x3A, 0xD8, 0x78, 0x93, 0xA3, 0x4D,
    0xDA, 0x2A, 0xD8, 0x48, 0x69, 0xD9, 0x2A, 0xD8, 0x68, 0x55, 0xDA, 0x32, 0xD8, 0x50, 0x71, 0xD9,
    0x32, 0xD8, 0x70, 0x5D, 0xDA, 0x3A, 0xD8, 0x58, 0x79, 0xD9, 0x3A, 0xD8, 0x78, 0xA8, 0x8A, 0x9A,
    0xF0, 0x28, 0x50, 0x78, 0x9E, 0xF3, 0x88, 0x18, 0xF1, 0x9F, 0x1D, 0x98, 0xA8, 0xD9, 0x08, 0xD8,
    0xC8, 0x9F, 0x12, 0x9E, 0xF3, 0x15, 0xA8, 0xDA, 0x12, 0x10, 0xD8, 0xF1, 0xAF, 0xC8, 0x97, 0x87,
    // bank 5, 256 bytes
    0x34, 0xB5, 0xB9, 0x94, 0xA4, 0x21, 0xF3, 0xD9, 0x22, 0xD8, 0xF2, 0x2D, 0xF3, 0xD9, 0x2A, 0xD8,
    0xF2, 0x35, 0xF3, 0xD9, 0x32, 0xD8, 0x81, 0xA4, 0x60, 0x60, 0x61, 0xD9, 0x61, 0xD8, 0x6C, 0x68,
    0x69, 0xD9, 0x69, 0xD8, 0x74, 0x70, 0x71, 0xD9, 0x71, 0xD8, 0xB1, 0xA3, 0x84, 0x19, 0x3D, 0x5D,
    0xA3, 0x83, 0x1A, 0x3E, 0x5E, 0x93, 0x10, 0x30, 0x81, 0x10, 0x11, 0xB8, 0xB0, 0xAF, 0x8F, 0x94,
    0xF2, 0xDA, 0x3E, 0xD8, 0xB4, 0x9A, 0xA8, 0x87, 0x29, 0xDA, 0xF8, 0xD8, 0x87, 0x9A, 0x35, 0xDA,
    0xF8, 0xD8, 0x87, 0x9A, 0x3D, 0xDA, 0xF8, 0xD8, 0xB1, 0xB9, 0xA4, 0x98, 0x85, 0x02, 0x2E, 0x56,
    0xA5, 0x81, 0x00, 0x0C, 0x14, 0xA3, 0x97, 0xB0, 0x8A, 0xF1, 0x2D, 0xD9, 0x28, 0xD8, 0x4D, 0xD9,
    0x48, 0xD8, 0x6D, 0xD9, 0x68, 0xD8, 0xB1, 0x84, 0x0D, 0xDA, 0x0E, 0xD8, 0xA3, 0x29, 0x83, 0xDA,
    0x2C, 0x0E, 0xD8, 0xA3, 0x84, 0x49, 0x83, 0xDA, 0x2C, 0x4C, 0x0E, 0xD8, 0xB8, 0xB0, 0xA8, 0x8A,
    0x9A, 0xF5, 0x20, 0xAA, 0xDA, 0xDF, 0xD8, 0xA8, 0x40, 0xAA, 0xD0, 0xDA, 0xDE, 0xD8, 0xA8, 0x60,
    0xAA, 0xDA, 0xD0, 0xDF, 0xD8, 0xF1, 0x97, 0x86, 0xA8, 0x31, 0x9B, 0x06, 0x99, 0x07, 0xAB, 0x97,
    0x28, 0x88, 0x9B, 0xF0, 0x0C, 0x20, 0x14, 0x40, 0xB8, 0xB0, 0xB4, 0xA8, 0x8C, 0x9C, 0xF0, 0x04,
    0x28, 0x51, 0x79, 0x1D, 0x30, 0x14, 0x38, 0xB2, 0x82, 0xAB, 0xD0, 0x98, 0x2C, 0x50, 0x50, 0x78,
    0x78, 0x9B, 0xF1, 0x1A, 0xB0, 0xF0, 0x8A, 0x9C, 0xA8, 0x29, 0x51, 0x79, 0x8B, 0x29, 0x51, 0x79,
    0x8A, 0x24, 0x70, 0x59, 0x8B, 0x20, 0x58, 0x71, 0x8A, 0x44, 0x69, 0x38, 0x8B, 0x39, 0x40, 0x68,
    0x8A, 0x64, 0x48, 0x31, 0x8B, 0x30, 0x49, 0x60, 0xA5, 0x88, 0x20, 0x09, 0x71, 0x58, 0x44, 0x68,
    // bank 6, 256 bytes
    0x11, 0x39, 0x64, 0x49, 0x30, 0x19, 0xF1, 0xAC, 0x00, 0x2C, 0x54, 0x7C, 0xF0, 0x8C, 0xA8, 0x04,
    0x28, 0x50, 0x78, 0xF1, 0x88, 0x97, 0x26, 0xA8, 0x59, 0x98, 0xAC, 0x8C, 0x02, 0x26, 0x46, 0x66,
    0xF0, 0x89, 0x9C, 0xA8, 0x29, 0x51, 0x79, 0x24, 0x70, 0x59, 0x44, 0x69, 0x38, 0x64, 0x48, 0x31,
    0xA9, 0x88, 0x09, 0x20, 0x59, 0x70, 0xAB, 0x11, 0x38, 0x40, 0x69, 0xA8, 0x19, 0x31, 0x48, 0x60,
    0x8C, 0xA8, 0x3C, 0x41, 0x5C, 0x20, 0x7C, 0x00, 0xF1, 0x87, 0x98, 0x19, 0x86, 0xA8, 0x6E, 0x76,
    0x7E, 0xA9, 0x99, 0x88, 0x2D, 0x55, 0x7D, 0x9E, 0xB9, 0xA3, 0x8A, 0x22, 0x8A, 0x6E, 0x8A, 0x56,
    0x8A, 0x5E, 0x9F, 0xB1, 0x83, 0x06, 0x26, 0x46, 0x66, 0x0E, 0x2E, 0x4E, 0x6E, 0x9D, 0xB8, 0xAD,
    0x00, 0x2C, 0x54, 0x7C, 0xF2, 0xB1, 0x8C, 0xB4, 0x99, 0xB9, 0xA3, 0x2D, 0x55, 0x7D, 0x81, 0x91,
    0xAC, 0x38, 0xAD, 0x3A, 0xB5, 0x83, 0x91, 0xAC, 0x2D, 0xD9, 0x28, 0xD8, 0x4D, 0xD9, 0x48, 0xD8,
    0x6D, 0xD9, 0x68, 0xD8, 0x8C, 0x9D, 0xAE, 0x29, 0xD9, 0x04, 0xAE, 0xD8, 0x51, 0xD9, 0x04, 0xAE,
    0xD8, 0x79, 0xD9, 0x04, 0xD8, 0x81, 0xF3, 0x9D, 0xAD, 0x00, 0x8D, 0xAE, 0x19, 0x81, 0xAD, 0xD9,
    0x01, 0xD8, 0xF2, 0xAE, 0xDA, 0x26, 0xD8, 0x8E, 0x91, 0x29, 0x83, 0xA7, 0xD9, 0xAD, 0xAD, 0xAD,
    0xAD, 0xF3, 0x2A, 0xD8, 0xD8, 0xF1, 0xB0, 0xAC, 0x89, 0x91, 0x3E, 0x5E, 0x76, 0xF3, 0xAC, 0x2E,
    0x2E, 0xF1, 0xB1, 0x8C, 0x5A, 0x9C, 0xAC, 0x2C, 0x28, 0x28, 0x28, 0x9C, 0xAC, 0x30, 0x18, 0xA8,
    0x98, 0x81, 0x28, 0x34, 0x3C, 0x97, 0x24, 0xA7, 0x28, 0x34, 0x3C, 0x9C, 0x24, 0xF2, 0xB0, 0x89,
    0xAC, 0x91, 0x2C, 0x4C, 0x6C, 0x8A, 0x9B, 0x2D, 0xD9, 0xD8, 0xD8, 0x51, 0xD9, 0xD8, 0xD8, 0x79,
    // bank 7, 138 bytes (remainder)
    0xD9, 0xD8, 0xD8, 0xF1, 0x9E, 0x88, 0xA3, 0x31, 0xDA, 0xD8, 0xD8, 0x91, 0x2D, 0xD9, 0x28, 0xD8,
    0x4D, 0xD9, 0x48, 0xD8, 0x6D, 0xD9, 0x68, 0xD8, 0xB1, 0x83, 0x93, 0x35, 0x3D, 0x80, 0x25, 0xDA,
    0xD8, 0xD8, 0x85, 0x69, 0xDA, 0xD8, 0xD8, 0xB4, 0x93, 0x81, 0xA3, 0x28, 0x34, 0x3C, 0xF3, 0xAB,
    0x8B, 0xF8, 0xA3, 0x91, 0xB6, 0x09, 0xB4, 0xD9, 0xAB, 0xDE, 0xFA, 0xB0, 0x87, 0x9C, 0xB9, 0xA3,
    0xDD, 0xF1, 0xA3, 0xA3, 0xA3, 0xA3, 0x95, 0xF1, 0xA3, 0xA3, 0xA3, 0x9D, 0xF1, 0xA3, 0xA3, 0xA3,
    0xA3, 0xF2, 0xA3, 0xB4, 0x90, 0x80, 0xF2, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3,
    0xA3, 0xB2, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xA3, 0xB0, 0x87, 0xB5, 0x99, 0xF1, 0xA3, 0xA3, 0xA3,
    0x98, 0xF1, 0xA3, 0xA3, 0xA3, 0xA3, 0x97, 0xA3, 0xA3, 0xA3, 0xA3, 0xF3, 0x9B, 0xA3, 0xA3, 0xDC,
    0xB9, 0xA7, 0xF1, 0x26, 0x26, 0x26, 0xD8, 0xD8, 0xFF
};


const unsigned char dmpcfgupddata[192] = {
//  dmp config 
//  BANK    OFFSET  LENGTH  [DATA]
    0x03,   0x7B,   0x03,   0x4C, 0xCD, 0x6C,         
    0x03,   0xAB,   0x03,   0x36, 0x56, 0x76,         
    0x00,   0x68,   0x04,   0x02, 0xCB, 0x47, 0xA2,   
    0x02,   0x18,   0x04,   0x00, 0x05, 0x8B, 0xC1,   
    0x01,   0x0C,   0x04,   0x00, 0x00, 0x00, 0x00,   
    0x03,   0x7F,   0x06,   0x0C, 0xC9, 0x2C, 0x97, 0x97, 0x97, 
    0x03,   0x89,   0x03,   0x26, 0x46, 0x66,         
    0x00,   0x6C,   0x02,   0x20, 0x00,               
    0x02,   0x40,   0x04,   0x00, 0x00, 0x00, 0x00,   
    0x02,   0x44,   0x04,   0x00, 0x00, 0x00, 0x00,   
    0x02,   0x48,   0x04,   0x00, 0x00, 0x00, 0x00,   
    0x02,   0x4C,   0x04,   0x00, 0x00, 0x00, 0x00,   
    0x02,   0x50,   0x04,   0x00, 0x00, 0x00, 0x00,   
    0x02,   0x54,   0x04,   0x00, 0x00, 0x00, 0x00,  
    0x02,   0x58,   0x04,   0x00, 0x00, 0x00, 0x00,  
    0x02,   0x5C,   0x04,   0x00, 0x00, 0x00, 0x00,  
    0x02,   0xBC,   0x04,   0x00, 0x00, 0x00, 0x00,   
    0x01,   0xEC,   0x04,   0x00, 0x00, 0x40, 0x00,  
    0x03,   0x7F,   0x06,   0x0C, 0xC9, 0x2C, 0x97, 0x97, 0x97,
    0x04,   0x02,   0x03,   0x0D, 0x35, 0x5D,         
    0x04,   0x09,   0x04,   0x87, 0x2D, 0x35, 0x3D,   
    0x00,   0xA3,   0x01,   0x00,                    
    0x00,   0x00,   0x00,   0x01, 	//这里是开启DMP的特殊中断的
    //原程序中此行代码为(这里不一定错)
    //0x00,   0x00,   0x00,   0x01,  即LENGTH=0x00，有错
        
    0x07,   0x86,   0x01,   0xFE,                     
    0x07,   0x41,   0x05,   0xF1, 0x20, 0x28, 0x30, 0x38, 
    0x07,   0x7E,   0x01,   0x30,                   
    0x07,   0x46,   0x01,   0x9A,                    
    0x07,   0x47,   0x04,   0xF1, 0x28, 0x30, 0x38,   
    0x07,   0x6C,   0x04,   0xF1, 0x28, 0x30, 0x38,  
    0x02,   0x16,   0x02,   0x00, 0x01              

    
};


const unsigned  char dmpUpdates[47]={	
    0x01,   0xB2,   0x02,   0xFF, 0xFF,
    0x01,   0x90,   0x04,   0x09, 0x23, 0xA1, 0x35,
    0x01,   0x6A,   0x02,   0x06, 0x00,
    0x01,   0x60,   0x08,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,   0x60,   0x04,   0x40, 0x00, 0x00, 0x00,
    0x01,   0x62,   0x02,   0x00, 0x00,
    0x00,   0x60,   0x04,   0x00, 0x40, 0x00, 0x00    
};




void IIC_init()//IIC初始化
{

	SDA_set=0;//输出
	SCL_set=0;//输出
	SCL_pin=1;
	SDA_pin=1;
	SDA_up_set=1;
}


/*******************************************************************************
* 函数名         : Delay2us()
* 函数功能		   : 延时
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
//8个asm出错，4有39  指令周期为4个时钟周期 机器周期为8个时钟周期(0.125us)
//时钟周期0.125us
void IIC_delay2us()
{		
	asm("nop");//一个机器周期1us
	asm("nop");
}

void IIC_delay5us()
{		
	asm("nop");  	asm("nop");//一个机器周期1us
	asm("nop");		asm("nop");
	asm("nop");
}


/*******************************************************************************
* 函数名         : I2cStart()
* 函数功能		   : 起始信号：在SCL_pin时钟信号在高电平期间SDA_pin信号产生一个下降沿
* 输入           : 无
* 输出         	 : 无
* 备注           : 起始之后SDA_pin和SCL_pin都为0
*******************************************************************************/
void i2_qs()	//SCL 线是高电平时，SDA 线从高电平向低电平切换表示起始条件。
{
//	SDA_pin=1;
//	SCL_pin=1;
//	IIC_delay5us();//建立时间是SDA_pin保持时间>4.7us
//	SDA_pin=0;
//	IIC_delay5us();	
//	SCL_pin=0;		
	
	SDA_pin=1;
	IIC_delay2us();
	SCL_pin=1;
	IIC_delay5us();//建立时间是SDA_pin保持时间>4.7us
	IIC_delay2us();	
	SDA_pin=0;
	IIC_delay5us();//保持时间是>4us
	IIC_delay2us();
	SCL_pin=0;		
	IIC_delay2us();	
	
}


/*******************************************************************************
* 函数名         : I2cStop()
* 函数功能		   : 终止信号：在SCL_pin时钟信号高电平期间SDA_pin信号产生一个上升沿
* 输入           : 无
* 输出         	 : 无
* 备注           : 结束之后保持SDA_pin和SCL_pin都为1；表示总线空闲
*******************************************************************************/

void i2_tz()
{
//	SDA_pin=0;
//	SCL_pin=1;
//	IIC_delay5us();//建立时间大于4.7us
//	SDA_pin=1;
//	IIC_delay5us();
//	SCL_pin=0;
//	IIC_delay2us();

	SDA_pin=0;
	IIC_delay5us();
	SCL_pin=1;
	IIC_delay5us();//建立时间大于4.7us
	SDA_pin=1;
	IIC_delay5us();
	IIC_delay2us();	
	SCL_pin=0;
	IIC_delay2us();
}

/*******************************************************************************
* 函数名         : I2cSendByte(unsigned char num)
* 函数功能		   : 通过I2C发送一个字节。在SCL_pin时钟信号高电平期间，保持发送信号SDA_pin保持稳定
* 输入           : num
* 输出         	 : 0或1。发送成功返回1，发送失败返回0
* 备注           : 发送完一个字节SCL_pin=0,SDA_pin=1
*******************************************************************************/

void i2_fs(unsigned char dat)
{
	unsigned char a=0;//最大255，一个机器周期为1us，最大延时255us。		
	for(a=0;a<8;a++)//要发送8位，从最高位开始
	{
		SDA_pin=dat>>7;	 //起始信号之后SCL_pin=0，所以可以直接改变SDA_pin信号
		dat=dat<<1;
		IIC_delay2us();
		SCL_pin=1;
		IIC_delay5us();//建立时间>4.7us
		SCL_pin=0;
		IIC_delay5us();//时间大于4us		
	}
	SDA_pin=1;
	SDA_set=1;
	SCL_pin=1;
	IIC_delay5us();
	ack = SDA_pin;
	SCL_pin=0;
	IIC_delay2us();
	SDA_set=0;//模式改为输出		
}

/*******************************************************************************
* 函数名         : I2cReadByte()
* 函数功能		   : 使用I2c读取一个字节
* 输入           : 无
* 输出         	 : dat
* 备注           : 接收完一个字节SCL_pin=0,SDA_pin=1.
*******************************************************************************/

unsigned char i2_js(unsigned char aack)
{
	unsigned char a=0,dat=0;
	SDA_pin=1;			//起始和发送一个字节之后SCL_pin都是0
	IIC_delay2us();
	SDA_set=1;
	for(a=0;a<8;a++)//接收8个字节
	{
		SCL_pin=1;
		IIC_delay2us();
		dat<<=1;
		dat|=SDA_pin;
		IIC_delay5us();
		SCL_pin=0;
		IIC_delay5us();
	}
	SDA_set=0;
	
	SDA_pin = aack;                    //应答信号或不应答信号
	SCL_pin = 1;                   
	IIC_delay5us();              
	SCL_pin = 0;  
//	SDA_pin = 1; //释放总线(不确定要不要)                 
	IIC_delay2us();  
	return dat;		
}


/*写入8位寄存器一个字节
  参数 addr 寄存器地址
  参数 Data 写入数据
  返回值 (1=成功,0=失败)
*/
unsigned char i2cwrite(unsigned char addr,unsigned char Data)	//写入8位有效数据
{
	i2_qs();	//起始信号
	i2_fs(SlaveAddress);	//设备地址+写信号
	if(ack) return 0;	//判断是否是ACK如果不是返回0
	i2_fs(addr);	//设备内部地址
	if(ack) return 0;
	i2_fs(Data);	//写入的数据
	if(ack) return 0;
	i2_tz();	//停止信号
	return 1;                //发送停止信号
}

/*读取8位寄存器一个字节
  参数 addr 寄存器地址
  参数 *Data 数据存储地址
  返回值 (1=成功,0=失败)
*/
unsigned char i2cread(unsigned char addr,unsigned char *Data)	
{
	return i2creads(addr,1,Data);
}

/*读取8位寄存器多个字节
 * @参数 addr    I2C从器件内部地址
 * @参数 length  写入数据长度    
 * @参数 Data    保存数据的地址      
 * @返回值 返回状态 (1=成功)
 */
unsigned char i2creads(unsigned char addr,unsigned char length,unsigned char *Data)
{
		unsigned char i;
		length --;
		i2_qs();	//起始信号
		i2_fs(SlaveAddress);	//设备地址+写信号
		if(ack) return 0;
		i2_fs(addr);	//设备内部地址
		if(ack) return 0;
		i2_qs();	//起始信号
		i2_fs(SlaveAddress+1);	//设备地址+读信号
		if(ack) return 0;
		for(i=0;i<length;i++)
		{
			Data[i]= i2_js(0);	//读取数据,发送ACK
		}
		Data[length] = i2_js(1);//读取数据,发送NAK
		i2_tz();	//停止信号
		return 1;
}

/**写入8位寄存器的一个位。
 * @参数 addr    I2C从器件内部地址
 * @参数 bitNum  写入的比特位(0-7)     
 * @参数 data    写入数据      
 * @返回值 返回状态 (1=成功)
 */
unsigned char writeBit(unsigned char addr,unsigned char bitNum,unsigned char Data)
{
	unsigned char b;
	if (i2cread(addr,&b))
		{
			b = (Data != 0) ? (b | (1 << bitNum)):(b & ~(1 << bitNum)); 
			return i2cwrite(addr,b);	//写入数据
		}
	else
		return 0;
}

/**写入8位寄存器的多个位。  
 * @参数 addr     I2C从器件内部地址
 * @参数 bitStart 第一位的写入位置（0-7）
 * @参数 length   写的比特数(不超过8)
 * @参数 Data     写入数据
 * @返回值 返回状态 (1=成功)
 */
unsigned char writeBits(unsigned char addr,unsigned char bitStart,unsigned char length,unsigned char Data)
{
		//      010 要写入的值
    // 76543210 比特位
    //    xxx   args: bitStart=4, length=3
    // 00011100 掩码字节
    // 10101111 原始值（样本）
    // 10100011 原始值 & ~掩码
    // 10101011 掩码 | 原始值
	unsigned char b,mask=0;
	if (i2cread(addr,&b))
	{
		mask = (((1<<length) - 1) << (bitStart-length + 1));	//掩码
		Data <<=(bitStart - length + 1);	//把写入的数据移动到位
		Data &= mask;
		b &= ~(mask);
		b |= Data;
		i2cwrite(addr,b);	//写入数据
		return 1;
	}
	else
		return 0;
}

/**读取一个位从8位器件的寄存器。  
* @参数 addr    I2C从器件内部地址
* @参数 bitNum  位的位置来读取（0-7） 
* @参数 *data   数据存储地址  
* @返回值（1=成功） 
*/
unsigned char readBit(unsigned char addr,unsigned char bitNum,unsigned char *Data)
{
	unsigned char b;
	if(i2cread(addr,&b))
	{
		*Data = b & (1 << bitNum);
		return 1;
	}
	else
	{
		return 0;
	}
}

/**读取8位寄存器的多个位。 
* @参数 addr    I2C从器件内部地址 
* @参数 bitStart第一位的位置读取（0-7） 
* @参数 length  位读取@参数长度数（不超过8） 
* @参数 *data   数据存储地址（即'101'任何bitStart位置读取将等于0X05） 
* @返回值（1=成功） 
*/
unsigned char readBits(unsigned char addr,unsigned char bitStart,unsigned char length,unsigned char *Data)
{
		// 01101001 读取字节
    // 76543210 比特位
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
	unsigned char b,mask=0;
	if(i2cread(addr,&b))
	{
		
		mask = ((1 << length) - 1) << (bitStart - length + 1);
		b &= mask;
		b >>= (bitStart - length + 1);
		*Data = b;
		return 1;
	}
	else
		return 0;
}



 /*
   加载 DMP代码到
   返回值  (1=成功,0=失败)
 */
unsigned char loadfirmware(void)	
{
  unsigned int datanum=0;	//DMP固件写入标志位
  unsigned char ye,i,j;
  unsigned char bank=0;	//段（256个数据一段）
  unsigned char addr=0;	

	for(;bank<8;bank++)//循环8次
	{
		if(bank == 7)	//这里的作用就是区分最后一段数据
			i = 8;
		else
			i = 16;
		for(ye=0;ye<i;ye++)//循环8次 一共执行 8*8+8=72次
		{
			i2cwrite(0x6d,bank);
			i2cwrite(0x6e,addr);
			i2_qs();	//起始信号
			i2_fs(SlaveAddress);	//设备地址+写信号
			i2_fs(0x6f);	//设备内部地址
			for(j=0;j<16;j++)//72*16
			{
				i2_fs(dmpmemorydata[datanum++]);	//写入DMP的数据
				if(ack) return 0; 
			}
			addr += 16;
			i2_tz();	//停止信号
		}
	}
	i2cwrite(0x6d,7);
	i2cwrite(0x6e,addr);
	i2_qs();	//起始信号
	i2_fs(SlaveAddress);	//设备地址+写信号
	i2_fs(0x6f);	//设备内部地址
	for(i=0;i<9;i++)
	{
		i2_fs(dmpmemorydata[datanum++]);	//写入DMP的数据
		if(ack) return 0;
	}
	i2_tz();	//停止信号
	return 1;
}



unsigned char loadcfgupd(void)	//DMP设置
{
  unsigned char line;	//一共需要写入30条设置数据
  unsigned char bank;	//页
  unsigned char datacounts=0;	//DMP设置数据标志位
  unsigned char bytes2write;	//数据长度。
  unsigned char offset;	//偏移地址
  unsigned char writingcounts;	//数据写入标志与bytes2write一同使用
  unsigned char special;
     
  for (line=0;line<30;line++)
  {
  	bank=dmpcfgupddata[datacounts++];
  	offset=dmpcfgupddata[datacounts++];
  	bytes2write=dmpcfgupddata[datacounts++];
  	i2cwrite(0x6d,bank);
  	i2cwrite(0x6e,offset);
  	i2_qs();	//起始信号
		i2_fs(SlaveAddress);	//设备地址+写信号
		i2_fs(0x6f);	//设备内部地址
  	for(writingcounts=0;writingcounts<bytes2write;writingcounts++)
  	{
  		i2_fs(dmpcfgupddata[datacounts++]);	//写入DMP配置数据
			if(ack) return 0;
  	}
  	if(0 == bytes2write)
  	{
  		special=dmpcfgupddata[datacounts++];
  		if(0x01 == special)
  			{
  				//设置零运动中断启用（真）;
          //设置FIFO缓冲区溢出启用（真）;
          //设置DMP启用（真）;
  				i2cwrite(0x38,0x32);
  			}
  		else
  			return 0;
  	}
  }
  i2_tz();	//停止信号
	return 1;
}

/*最后更新DMP*/
unsigned char xdmpUpdates(unsigned char datacounts)
{
	unsigned char writingcounts,bank,offset,bytes2write;
	bank=dmpUpdates[datacounts++];
  offset=dmpUpdates[datacounts++];
  bytes2write=dmpUpdates[datacounts++];
  i2cwrite(0x6d,bank);
  i2cwrite(0x6e,offset);
  i2_qs();	//起始信号
	i2_fs(SlaveAddress);	//设备地址+写信号
	i2_fs(0x6f);	//设备内部地址
	for(writingcounts=0;writingcounts<bytes2write;writingcounts++)
  	{
  		i2_fs(dmpUpdates[datacounts++]);	//写入DMP配置数据
			if(ack) return 0;
  	}
  	i2_tz();	//停止信号
  	return 0;
}



/*读取 FIFO 计数*/
unsigned int getFIFOCount()
{
	unsigned char i[2];
	i2creads(0x72,2,i);
	return ((i[0]<<8)+i[1]);
}
/*FIFO数据读取
参数 *Data	存储数据的地址
返回值 (1=读取成功,0读取失败)
*/
unsigned char readdmp(unsigned char *Data)
{
  return i2creads(0x74,42,Data);
}
	
//加载并配置 DMP 数字运动处理引擎
unsigned char dmpInitialize(void)
{
	unsigned char hwRevision,otpValid,mpuIntStatus/*fifoBuffer[128]*/;
	unsigned char xgOffsetTC,ygOffsetTC,zgOffsetTC;
	unsigned int fifoCount;
	writeBit(0x6B,7,1);	//复位 MPU6050
	delay_ms(30);
	writeBit(0x6B,6,0);	//禁止睡眠模式
	i2cwrite(0x6D,0x70);	//写入一个字节数据到0x6d寄存器(选择用户 bank)
	i2cwrite(0x6E,0x06);	//写入一个字节数据到0x6e寄存器(选择存储字节)
	i2cread(0x6F,&hwRevision);	//读取
	i2cwrite(0x6D,0);	//重置内存 bank 选择
	readBit(0x00,0,&otpValid);	//读取 OTP bank 有效标志
	readBits(0x00,6,6,&xgOffsetTC);	//读陀螺偏置TC值 X
	readBits(0x01,6,6,&ygOffsetTC);	//读陀螺偏置TC值 Y)
	readBits(0x02,6,6,&zgOffsetTC);	//读陀螺偏置TC值 Z
	i2cwrite(0x25,0x7f);	//设置从0地址 0x7
	writeBit(0x6A,5,0);	//禁用I2C主模式
	i2cwrite(0x25,0x68);	//这里可能要改。还没有弄明白这里
	writeBit(0x6A,1,1);	//I2C总线主控复位
	delay_ms(20);
	if((loadfirmware()) == 0 ) return 0;	//加载 DMP代码到内存
	if((loadcfgupd()) == 0 ) return 0;	//配制DMP
	writeBits(0x6B,2,3,0x03);	//设置时钟脉冲源Z陀螺
	i2cwrite(0x38,0x12);	//设置DMP和FIFO_OFLOW启用中断
	i2cwrite(0x19,4);	//设置采样率为200 hz  (1khz / (1 + 4) = 200 Hz)
	writeBits(0x1A,5,3,0x1);	//设置外部帧同步TEMP_OUT_L[0]
	writeBits(0x1A,2,3,0x03);	//设置DLPF带宽42赫兹
	writeBits(0x1B,4,2,0x03);	//陀螺灵敏度设置为+ / - 2000 deg/sec    0 +/-250  1+/-500 2 +/-1000  3+/-2000(/16.4)
	i2cwrite(0x70,0x03);	//设置DMP配置字节（功能未知）
	i2cwrite(0x71,0x00);	//设置DMP配置字节（功能未知）
	writeBit(0x00,0,0);	//清除OTP Bank 标志
	writeBits(0x00,6,6,xgOffsetTC);	//设置X 陀螺抵消TCs之前的值
	writeBits(0x01,6,6,ygOffsetTC);	//设置Y 陀螺抵消TCs之前的值
	writeBits(0x02,6,6,zgOffsetTC);	//设置Z 陀螺抵消TCs之前的值
	xdmpUpdates(0);	//最后更新1/7(函数未知)dmpUpdates数组第一行
	xdmpUpdates(5);	//最后更新2/7(函数未知)dmpUpdates数组第二行
	writeBit(0x6A,2,1);	//复位 FIFO
	fifoCount = getFIFOCount();	//读取 FIFO 计数
	//readdmp(fifoCount,fifoBuffer);	//读取FIFO里的数据
	writeBit(0x6A,2,1);	//复位 FIFO
	
	i2cwrite(0x1F,2);	//运动检测阈值设置为2
	i2cwrite(0x21,156);	//零运动检测阈值为156
	i2cwrite(0x20,80);	//设置运动检测持续时间至80
	i2cwrite(0x22,0);	//设置零运动检测时间0
	writeBit(0x6A,2,1);	//复位 FIFO
	writeBit(0x6A,6,1);	//使能 FIFO
	writeBit(0x6A,7,1);	//使能 DMP
	writeBit(0x6A,3,1);	//复位 DMP
	xdmpUpdates(12);	//最后更新3/7(函数未知)dmpUpdates数组第三行
	xdmpUpdates(17);	//最后更新4/7(函数未知)dmpUpdates数组第四行
	xdmpUpdates(28);	//最后更新5/7(函数未知)dmpUpdates数组第五行
	while((fifoCount = getFIFOCount()) < 3);	//等待 FIFO 计数 > 2
	writeBit(0x6A,2,1);	//复位 FIFO
	//readdmp(fifoCount,fifoBuffer);	//读取FIFO里的数据
	i2cread(0x3A,&mpuIntStatus);	//读取中断状态
	xdmpUpdates(35);	//最后更新6/7(函数未知)dmpUpdates数组第六行
	while((fifoCount = getFIFOCount()) < 3);	//等待 FIFO 计数 > 2
	writeBit(0x6A,2,1);	//复位 FIFO
	//readdmp(fifoCount,fifoBuffer);	//读取FIFO里的数据
	i2cread(0x3A,&mpuIntStatus);	//读取中断状态
	xdmpUpdates(40);	//最后更新7/7(函数未知)dmpUpdates数组第七行
	writeBit(0x6A,7,0);	//禁用DMP(稍后您打开它)
	writeBit(0x6A,2,1);	//复位 FIFO
	i2cread(0x3A,&mpuIntStatus);
	//星期六 (2014/06/28)
	return 1;
}

int GetData(unsigned char REG_Address)//读取寄存器的初始数值
{
	unsigned char dat[2];
	i2creads(REG_Address,2,dat);
	return ((dat[1]<<8)+dat[0]);   //合成数据
}


/*初始化MPU6050*/
void initMPU6050(void)
{
	writeBits (0x6B,2,3,0x01);	//电源管理
	writeBits (0x1B,4,2,0x00);	//设置陀螺仪量程 250/s
	writeBits (0x1C,4,2,0x00);	//设置加速度量程 2G   0 +/- 2g  1+/- 4g  2+/- 8g  3+/- 16g
	writeBit (0x6B,6,1);	//电源管理MUP进入睡眠模式
}
/*验证MPU6050连接*/
unsigned char getDeviceID(void)
{
	unsigned char b=0;	//临时变量
	readBits(0x75,6,6,&b);	//读取i2c固定地址，去掉最高位和最低位这两位数据
	return b == 0x34;	//判断B是否等于0x34，如果等于返回1，不等于返回0(库的是0x38)
	
}


//传送数据给匿名四轴上位机软件(V2.6版本)
//fun:功能字. 0XA0~0XAF
//data:数据缓存区,最多28字节!!
//len:data区有效数据个数
//                          0xAF    tbuf    28
void usart1_niming_report(u8 fun,u8*data,u8 len)
{	// 0x88+0xAF+0x1C+ACC DATA+GYRO DATA+MAG DATA+ANGLE DATA + 0x00 0x00 + 0x00 0x00+SUM      飞控显示对应的帧FUN为0xAF

	u8 send_buf[33];
	u8 i;
	if(len>28)return;	//最多28字节数据 
	send_buf[len+3]=0;	//校验数置零
	send_buf[len+4]='\0';	//加上结束符
	send_buf[0]=0X88;	//帧头
	send_buf[1]=fun;	//功能字
	send_buf[2]=len;	//数据长度
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//复制数据
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//计算校验和	
	for(i=0;i<len+5;i++)send_char_unsigned(send_buf[i]);	//发送数据到串口0 
}


//发送加速度传感器数据和陀螺仪数据
//aacx,aacy,aacz:x,y,z三个方向上面的加速度值
//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)
{
	u8 tbuf[12]; 
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;
	usart1_niming_report(0XA1,tbuf,12);//自定义帧,0XA1
}	




//通过串口1上报结算后的姿态数据给电脑
//aacx,aacy,aacz:x,y,z三个方向上面的加速度值
//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值
//roll:横滚角.单位0.01度。 -18000 -> 18000 对应 -180.00  ->  180.00度
//pitch:俯仰角.单位 0.01度。-9000 - 9000 对应 -90.00 -> 90.00 度
//yaw:航向角.单位为0.1度 0 -> 3600  对应 0 -> 360.0度
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//清0
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;	
	tbuf[18]=(roll>>8)&0XFF;
	tbuf[19]=roll&0XFF;
	tbuf[20]=(pitch>>8)&0XFF;
	tbuf[21]=pitch&0XFF;
	tbuf[22]=(yaw>>8)&0XFF;
	tbuf[23]=yaw&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//飞控显示帧,0XAF
} 







