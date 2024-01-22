#include "headerFiles/engine.h"
#include "headerFiles/graphics.h"

void createCollisionMask(Object* object){
    drawRectangle(
        object->display,
        object->window,
        object->x - object->width/2,
        object->y - object->height/2,
        object->width,
        object->height,
        false
    );

    //upper left
    object->collisionMask.coord[0][0] = object->x - object->width/2;
    object->collisionMask.coord[0][1] = object->y - object->height/2;

    //upper right
    object->collisionMask.coord[1][0] = object->x + object->width/2;
    object->collisionMask.coord[1][1] = object->y - object->height/2;

    //lower right
    object->collisionMask.coord[2][0] = object->x + object->width/2;
    object->collisionMask.coord[2][1] = object->y + object->height/2;

    //lower left
    object->collisionMask.coord[3][0] = object->x - object->width/2;
    object->collisionMask.coord[3][1] = object->y + object->height/2;

}

void createObject(Object* object){

    if(object->type == CIRCLE){
        object->width = object->radius * 2;
        object->height = object->radius * 2;

        drawCircle(
            object->display,
            object->window,
            object->x,
            object->y,
            object->radius,
            true,
            false
        );
    }else if(object->type == RECTANGLE){
        
        object->radius = (object->width + object->height)/4;
        
        drawRectangle(
            object->display,
            object->window,
            object->x - object->width/2,
            object->y - object->height/2,
            object->width,
            object->height,
            true
        );
    }

    createCollisionMask(object);
}

bool checkCollisionObjects(Object* obj1, Object* obj2){

    if(
        obj1->collisionMask.coord[0][0] < obj2->collisionMask.coord[1][0] &&
        obj1->collisionMask.coord[1][0] > obj2->collisionMask.coord[0][0] &&
        obj1->collisionMask.coord[0][1] < obj2->collisionMask.coord[3][1] &&
        obj1->collisionMask.coord[3][1] > obj2->collisionMask.coord[0][1]
    ){
        return true;
    }

    return false;
}

void updateObject(Object* object, float *x_offset, float y_offset, float acceleration) {

    createObject(object);

    if(
        object->x + object->width/2 + (*x_offset) > WindowWidth ||
        object->x - object->width/2 + (*x_offset) < 0
    ){
        (*x_offset) *= -object->elasticityFactor;
    }
    

    if(object->grv){
        if(object->y + object->radius + object->grvValue < WindowHeight){
            object->grvValue += acceleration * object->weight;
        } else {
            if (object->elasticity) {
                object->grvValue = -object->elasticityFactor * object->grvValue;
                (*x_offset) *= -object->elasticityFactor;
            } else {
                object->grvValue = 0;
                object->y = WindowHeight;
            }
        }

        object->y += object->grvValue;
    }

    if((*x_offset) != 0){
        object->x += (*x_offset);
    }

    if(y_offset != 0){
        object->y += y_offset;
    }

    delay(15);
}
