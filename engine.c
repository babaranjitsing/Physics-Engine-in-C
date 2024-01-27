#include "headerFiles/engine.h"
#include "headerFiles/graphics.h"

float acceleration = 1.5;

void createCollisionMask(Object *object)
{
    drawRectangle(
        object->display,
        object->window,
        object->vector.x - object->width / 2,
        object->vector.y - object->height / 2,
        object->width,
        object->height,
        false);

    // upper left
    object->collisionMask.coord[0][0] = object->vector.x - object->width / 2;
    object->collisionMask.coord[0][1] = object->vector.y - object->height / 2;

    // upper right
    object->collisionMask.coord[1][0] = object->vector.x + object->width / 2;
    object->collisionMask.coord[1][1] = object->vector.y - object->height / 2;

    // lower right
    object->collisionMask.coord[2][0] = object->vector.x + object->width / 2;
    object->collisionMask.coord[2][1] = object->vector.y + object->height / 2;

    // lower left
    object->collisionMask.coord[3][0] = object->vector.x - object->width / 2;
    object->collisionMask.coord[3][1] = object->vector.y + object->height / 2;
}

void createObject(Object *object)
{

    if (object->type == CIRCLE)
    {
        object->width = object->radius * 2;
        object->height = object->radius * 2;

        drawCircle(
            object->display,
            object->window,
            object->vector.x,
            object->vector.y,
            object->radius,
            true,
            false);
    }
    else if (object->type == RECTANGLE)
    {

        object->radius = (object->width + object->height) / 4;

        drawRectangle(
            object->display,
            object->window,
            object->vector.x - object->width / 2,
            object->vector.y - object->height / 2,
            object->width,
            object->height,
            true);
    }

    createCollisionMask(object);
}

bool checkCollisionObjects(Object *obj, Object *objects[], int noOfObjects)
{
    for (int i = 0; i < noOfObjects; i++)
    {
        if (obj == objects[i])
        {
            continue;
        }

        bool xOverlap = (obj->collisionMask.coord[0][0] < objects[i]->collisionMask.coord[1][0] &&
                         obj->collisionMask.coord[1][0] > objects[i]->collisionMask.coord[0][0]);

        bool yOverlap = (obj->collisionMask.coord[0][1] < objects[i]->collisionMask.coord[3][1] &&
                         obj->collisionMask.coord[3][1] > objects[i]->collisionMask.coord[0][1]);

        if (xOverlap && yOverlap)
        {
            return true;
        }
    }

    return false;
}

void updateObject(Object *object[], int noOfObjects)
{

    for (int i = 0; i < noOfObjects; i++)
    {
        createObject(object[i]);

        // check wether the object is on the ground
        if (object[i]->vector.y + object[i]->radius >= WindowHeight)
        {
            object[i]->grounded = true;
        }
        else
        {
            object[i]->grounded = false;
        }

        // checks for the gravity and update accordingly
        if (object[i]->grv)
        {
            if (object[i]->vector.y + object[i]->radius + object[i]->grvValue < WindowHeight)
            {
                object[i]->grvValue += acceleration * object[i]->weight;
            }
            else
            {
                if (object[i]->elasticity)
                {
                    object[i]->grvValue *= -object[i]->elasticityFactor;
                }
                else
                {
                    object[i]->grvValue = 0;
                    object[i]->vector.y = WindowHeight - object[i]->radius;
                }
            }

            object[i]->vector.y += object[i]->grvValue;
        }

        // checks for the collision with any object and update accordingly
        for (int j = 0; j < noOfObjects; j++)
        {
            if (i == j)
            {
                continue;
            }

            if (checkCollisionObjects(object[i], object, noOfObjects))
            {
                if (object[i]->elasticity)
                {
                    object[i]->grvValue *= -object[i]->elasticityFactor;
                }
                else
                {
                    object[i]->grvValue = 0;
                    object[j]->grvValue = 0;
                }
                if (object[j]->elasticity)
                {
                    object[j]->grvValue *= -object[j]->elasticityFactor;
                }
                else
                {
                    object[i]->grvValue = 0;
                    object[j]->grvValue = 0;
                }
            }
        }

        // checks for the collision with the walls and update accordingly
        if (object[i]->x_offset != 0)
        {
            if (
                object[i]->vector.x + object[i]->radius + object[i]->x_offset > WindowWidth ||
                object[i]->vector.x - object[i]->radius + object[i]->x_offset < 0)
            {
                if (object[i]->elasticity)
                {
                    if (object[i]->friction)
                    {
                        object[i]->x_offset *= -object[i]->elasticityFactor;
                    }
                    else
                    {
                        object[i]->x_offset *= -1;
                    }
                }
                else
                {
                    object[i]->x_offset = 0;
                }
            }

            if (object[i]->friction && object[i]->grounded)
            {
                object[i]->x_offset *= (1 - object[i]->frictionFactor);
            }

            object[i]->vector.x += object[i]->x_offset;
        }

        if (object[i]->y_offset != 0)
        {
            object[i]->vector.y += object[i]->y_offset;
        }
    }
    delay(15);
}
