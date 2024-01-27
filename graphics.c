#include "headerFiles/graphics.h"

int WindowHeight = 300;
int WindowWidth = 400;
int frameRate;
int frameCounter;
int clickCoordinates[CRD][2];
int clickCounter = 0;
struct timeval startTime;

void createWindow(Display **display, Window *window)
{
    *display = XOpenDisplay(NULL);
    if (!*display)
    {
        perror("XopenDisplay");
        exit(EXIT_FAILURE);
    }

    Window root = DefaultRootWindow(*display);

    *window = XCreateSimpleWindow(
        *display,
        root,
        0,
        0,
        WindowWidth,
        WindowHeight,
        1,
        BlackPixel(*display, 0),
        WhitePixel(*display, 0));

    XMapWindow(*display, *window);

    XSelectInput(*display, *window, ExposureMask);
}

void destroyWindow(Display *display, Window window)
{
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

void delay(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000)
        ;
}

void updateFrame(Display *display, Window window, bool showFrameRate, bool slomo)
{

    if (showFrameRate)
    {
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);

        long long elapsedTime = (currentTime.tv_sec - startTime.tv_sec) * 1000 +
                                (currentTime.tv_usec - startTime.tv_usec) / 1000;

        if (elapsedTime >= 1000)
        {
            frameRate = frameCounter;
            frameCounter = 0;
            gettimeofday(&startTime, NULL);
            return;
        }
        frameCounter++;
    }

    XWindowAttributes windowAttributes;

    XGetWindowAttributes(display, window, &windowAttributes);

    WindowHeight = windowAttributes.height;
    WindowWidth = windowAttributes.width;

    if (slomo)
    {
        delay(300);
    }

    clearScreen(display, window);
}

void clearScreen(Display *display, Window window)
{
    XClearWindow(display, window);
}

void drawLine(Display *display, Window window, int x1, int y1, int x2, int y2)
{
    XDrawLine(display, window, DefaultGC(display, 0), x1, y1, x2, y2);
}

void drawRectangle(Display *display, Window window, int x, int y, int width, int height, bool fill)
{
    if (fill)
    {
        XFillRectangle(display, window, DefaultGC(display, 0), x, y, width, height);
        return;
    }
    XDrawRectangle(display, window, DefaultGC(display, 0), x, y, width, height);
}

void drawCircle(Display *display, Window window, int x, int y, int radius, bool fill, bool pen)
{
    if (pen)
    {
        for (int i = 0; i < clickCounter; i++)
        {
            if (fill)
            {
                XFillArc(display, window, DefaultGC(display, 0), clickCoordinates[i][0] - radius, clickCoordinates[i][1] - radius, 2 * radius, 2 * radius, 0, 360 * 64);
                continue;
            }
            XDrawArc(display, window, DefaultGC(display, 0), clickCoordinates[i][0] - radius, clickCoordinates[i][1] - radius, 2 * radius, 2 * radius, 0, 360 * 64);
        }
    }
    else
    {
        if (fill)
        {
            XFillArc(display, window, DefaultGC(display, 0), x - radius, y - radius, 2 * radius, 2 * radius, 0, 360 * 64);
            return;
        }
        XDrawArc(display, window, DefaultGC(display, 0), x - radius, y - radius, 2 * radius, 2 * radius, 0, 360 * 64);
    }
}

void drawPolygon(Display *display, Window window, float coord[][2])
{
    for (int i = 1; i <= coord[0][1]; i++)
    {
        if (coord[i + 1][0] == __FLT_MAX__)
        {

            drawLine(
                display,
                window,
                coord[i][0],
                coord[i][1],
                coord[1][0],
                coord[1][1]);
            return;
        }

        drawLine(
            display,
            window,
            coord[i][0],
            coord[i][1],
            coord[i + 1][0],
            coord[i + 1][1]);
    }
}

void getMousePosition(Display *display, Window window, int *x, int *y)
{
    Window root, child;
    int root_x, root_y, win_x, win_y;
    unsigned int mask;

    XQueryPointer(display, window, &root, &child, &root_x, &root_y, &win_x, &win_y, &mask);

    *x = win_x;
    *y = win_y;
}

void drawMessage(Display *display, Window window, char *message, int x, int y)
{
    char *token = strtok(message, "\n");

    while (token != NULL)
    {
        XDrawString(display, window, DefaultGC(display, 0), x, y, token, strlen(token));
        y += 13;
        token = strtok(NULL, "\n");
    }
}

void getMouseClickCoordinates(Display *display, Window window, int *x, int *y)
{
    static clock_t lastClickTime = 0;
    const int clickDelay = 5;

    Window root, child;
    int root_x, root_y, win_x, win_y;
    unsigned int mask;

    XQueryPointer(display, window, &root, &child, &root_x, &root_y, &win_x, &win_y, &mask);

    if (mask & Button1Mask && win_x != clickCoordinates[clickCounter - 1][0] && win_y != clickCoordinates[clickCounter - 1][1])
    {
        *x = win_x;
        *y = win_y;

        if (clickCounter < CRD && (clock() - lastClickTime) > clickDelay * CLOCKS_PER_SEC / 1000)
        {
            clickCoordinates[clickCounter][0] = *x;
            clickCoordinates[clickCounter][1] = *y;

            clickCounter++;
            lastClickTime = clock();
        }
        else if (clickCounter >= CRD && (clock() - lastClickTime) > clickDelay * CLOCKS_PER_SEC / 1000)
        {
            for (int i = 0; i < CRD - 1; i++)
            {
                clickCoordinates[i][0] = clickCoordinates[i + 1][0];
                clickCoordinates[i][1] = clickCoordinates[i + 1][1];
            }

            clickCoordinates[CRD - 1][0] = *x;
            clickCoordinates[CRD - 1][1] = *y;

            lastClickTime = clock();
        }
    }
}
