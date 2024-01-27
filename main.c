#include "headerFiles/graphics.h"
#include "headerFiles/engine.h"

#define TLOBJ 2

int main(){

    Display *gameDisplay, *infoDisplay;
    Window gameWindow, infoWindow;

    createWindow(&infoDisplay, &infoWindow);
    createWindow(&gameDisplay, &gameWindow);

    Object ball ={
        .name = "Ball",
        .color = "red",
        .type = CIRCLE,
        .vector = {
            .x = 100,
            .y = 0,
        },
        .radius = 20,
        .grv = true,
        .elasticity = true,
        .friction = true,
        .elasticityFactor = 0.9,
        .frictionFactor = 0.3,
        .weight = 1,
        .display = gameDisplay,
        .window = gameWindow,
        .x_offset = 10
    };
    
    Object ball2 ={
        .name = "Ball",
        .color = "red",
        .type = CIRCLE,
        .vector = {
            .x = 300,
            .y = 0,
        },
        .radius = 20,
        .grv = true,
        .elasticity = true,
        .friction = true,
        .elasticityFactor = 0.9,
        .frictionFactor = 0.3,
        .weight = 1,
        .display = gameDisplay,
        .window = gameWindow,
        .x_offset = -10
    };

    char text[CRD*2];
    Object *objects[TLOBJ] = {&ball, &ball2};
    acceleration = 1.5;

    while(true){

        updateFrame(infoDisplay, infoWindow, false, false);
        updateFrame(gameDisplay, gameWindow, false, false);

        updateObject(objects, TLOBJ);

        sprintf(
            text,
            "Name Object1: %s\n"
            "X: %f\n"
            "Y: %f\n"
            "X_offset: %f\n"
            "Friction Factor: %f\n"
            "Elasticity Factor: %lf\n"
            "Weight: %f\n"
            "Grounded: %s\n",
            ball.name,
            ball.vector.x,
            ball.vector.y,
            ball.x_offset,
            ball.frictionFactor,
            (double)ball.elasticityFactor,
            ball.weight,
            ball.grounded ? "true" : "false"
        );

        drawMessage(infoDisplay, infoWindow, text, 10, 10);

        sprintf(
            text,
            "Name Object2: %s\n"
            "X: %f\n"
            "Y: %f\n"
            "X_offset: %f\n"
            "Friction Factor: %f\n"
            "Elasticity Factor: %lf\n"
            "Weight: %f\n"
            "Grounded: %s\n",
            ball2.name,
            ball2.vector.x,
            ball2.vector.y,
            ball2.x_offset,
            ball2.frictionFactor,
            (double)ball2.elasticityFactor,
            ball2.weight,
            ball2.grounded ? "true" : "false"
        );

        drawMessage(infoDisplay, infoWindow, text, 220, 10);

        sprintf(text, "collision: %s", checkCollisionObjects(&ball, objects, TLOBJ) ? "true" : "false");
        drawMessage(infoDisplay, infoWindow, text, 125, 125);

    }

    destroyWindow(gameDisplay, gameWindow);

}
