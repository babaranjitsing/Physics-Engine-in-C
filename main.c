#include "headerFiles/graphics.h"
#include "headerFiles/engine.h"

int main(){
    
    Display *display;
    Window window;
    int x, y;
    char text[CRD];

    createWindow(&display, &window);

    Object player = {
        .x = 200,
        .y = 0,
        .grv = true,
        .elasticity = true,
        .elasticityFactor = 0.9,
        .weight = 1,
        .type = CIRCLE,
        .radius = 20,
        .display = display,
        .window = window,
        .name = "Player 1",
    };

    Object player2 = {
        .x = 200,
        .y = 100,
        .grv = true,
        .elasticity = true,
        .elasticityFactor = 0.9,
        .weight = 5,
        .type = CIRCLE,
        .radius = 20,
        .display = display,
        .window = window,
        .name = "Player 2",
    };

    float x_offset = 5;

    while(true){

        getMousePosition(display, window, &x, &y);

        updateFrame(display, window, true);
        
        updateObject(&player, &x_offset, 0, 1.5);
        updateObject(&player2, &x_offset, 0, 1.5);

        sprintf(text, "x: %d, y: %d", x, y);
        drawMessage(display, window, text, 10, 10);
        
        drawMessage(display, window, player.name, 10, 20);
        
        sprintf(text, "x: %f, y: %f", player.x, player.y);
        drawMessage(display, window, text, 10, 30);
        
        sprintf(text, "Frame Rate: %d", frameRate);
        drawMessage(display, window, text, 10, 40);

        // if(checkCollisionObjects(&player, &player2)){
        //     sprintf(text, "Collision: true");
        // }else{
        //     sprintf(text, "Collision: false");
        // }
        // drawMessage(display, window, text, 10, 50);
    }

    destroyWindow(display, window);

    exit(EXIT_SUCCESS);
}
