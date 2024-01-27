#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <X11/Xlib.h>

typedef enum
{
    CIRCLE,
    RECTANGLE,
} Types;

typedef struct
{
    float x, y;
} vector2D;

typedef struct
{
    float coord[4][2];
} collisionMaskCoordinates;

extern float acceleration;

typedef struct
{
    vector2D vector;
    float x_offset, y_offset;
    float grvValue;
    char *name;
    bool grv;
    Display *display;
    Window window;
    bool elasticity;
    float elasticityFactor;
    float weight;
    float width, height, radius;
    bool friction;
    float frictionFactor;
    Types type;
    collisionMaskCoordinates collisionMask;
    bool grounded;
    char* color;
} Object;

void updateObject(Object *object[], int noOfObjects);
bool checkCollisionObjects(Object *obj, Object *objects[], int noOfObjects);

#endif