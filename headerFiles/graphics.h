#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define CRD 100

extern int WindowHeight;
extern int WindowWidth;
extern int frameRate;
extern int frameCounter;

extern int clickCoordinates[CRD][2];
extern int clickCounter;

extern struct timeval startTime;

void clearScreen(Display *display, Window window);

void createWindow(Display **display, Window *window);

void destroyWindow(Display *display, Window window);

void delay(int milliseconds);

void updateFrame(Display* display, Window window, bool showFrameRate);

void drawLine(Display* display, Window window, int x1, int y1, int x2,int y2);

void drawCircle(Display* display, Window window, int x, int y, int radius, bool fill, bool draw);

void drawRectangle(Display* display, Window window, int x, int y, int width, int height, bool fill);

void getMousePosition(Display *display, Window window, int *x, int *y);

void drawMessage(Display *display, Window window, char *message, int x, int y);

void getMouseClickCoordinates(Display *display, Window window, int *x, int *y);

#endif
