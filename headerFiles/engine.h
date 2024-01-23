#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <X11/Xlib.h>

typedef enum{
    CIRCLE,
    RECTANGLE,
} Types;

typedef struct{
    float x, y;
}vector2D;

typedef struct{
    float coord[4][2];
}collisionMaskCoordinates;

typedef struct{
    vector2D vector;
    float grvValue;
    char* name;
    bool grv;
    Display* display;
    Window window;
    bool elasticity;
    float elasticityFactor;
    float weight;
    float width, height, radius;
    Types type;
    double angle;
    collisionMaskCoordinates collisionMask;
} Object;

void updateObject(Object* object, float *x_offset, float y_offset, float acceleration);
bool checkCollisionObjects(Object* object1, Object* object2);

#endif