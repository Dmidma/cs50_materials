//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of game's paddle
#define PHEIGHT 10
#define PWIDTH 60

// height and width of game's brick
#define BHEIGHT 10
#define BWIDTH 35

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// speed limit of the ball
#define SPLIMIT 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
GImage* initLives(GWindow window, int lives);
void socreEffect(GLabel label);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);    

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;


    // displays the lives and stocks it an array
    GImage* arrayLives = malloc(sizeof(GImage) * lives);
    arrayLives = initLives(window, lives);

    // number of points initially
    int points = 0;

    // adding image indicator, of how to start the game
    GImage start = newGImage("clickStart.png");
    setSize(start, 300, 100);       
    add(window, start);

    // coordinates of the indicator
    double x = (WIDTH - getWidth(start)) / 2;
    double y = (HEIGHT - getHeight(start)) / 2;
    setLocation(start, x, y);

    // wait for click before begining the game
    waitForClick();

    // removes the indicator once the game begin 
    removeGWindow(window, start);

    startOver:
    // randomizing the angle of the ball
    srand48((long int) time(NULL));

    double v = drand48() * SPLIMIT;
    while (v == 0.0)
    {
        v = drand48() * SPLIMIT;
    }

    double xVelocity = v;
    double yVelocity = SPLIMIT;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // moves the ball
        move(ball, xVelocity, yVelocity);
        pause(10);

        // redirects the path of ball when it hits the extremity of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xVelocity = -xVelocity;
        }
        else if (getX(ball) <= 0)
        {
            xVelocity = -xVelocity;
        }

        // looses a live when the ball hits the bottom of window
        if (getY(ball) + getWidth(ball) >= getHeight(window))
        {   
            // looses a live
            lives--;

            // removes a live from window
            removeGWindow(window, arrayLives[lives]);

            // game is over when no lives left
            if (lives == 0)
            {
                // printing game over when the user looses
                GImage over = newGImage("gameOver.png");
                setSize(over, 300, 100);
                add(window, over);

                // coordinates of the game over image
                double x = (WIDTH - getWidth(over)) / 2;
                double y = (HEIGHT - getHeight(over)) / 2;
                setLocation(over, x, y);
                
                // breaks from the loop
                break;
            }
            
            // wait until user click to start playing again
            waitForClick();

            // sets the ball to the center of window, then starts game
            double x = (WIDTH - (2 * RADIUS)) / 2;
            double y = (HEIGHT - (2 * RADIUS)) / 2;
            setLocation(ball, x, y);
            goto startOver;
        }
        else if (getY(ball) <= 0)
        {
            yVelocity = -yVelocity;
        }
        

        // detects collision and saves the collided object
        GObject obj = detectCollision(window, ball);

        // redirects the path of the ball when it collides to the paddle
        if (obj == paddle)
        {
            yVelocity = -yVelocity; 
        }
        else if (obj != NULL)
        {   
            // checks if the collided object is a brick
            if (strcmp(getType(obj), "GRect") == 0)
            {   
                // decrements the number of bricks and removes brick
                bricks--;
                removeGWindow(window, obj);

                // increments the score
                points++;
                updateScoreboard(window, label, points);

                // adding a little effect to the score
                socreEffect(label);
                
                // changes direction of ball
                yVelocity = -yVelocity;
            }
        }

        // checks for events
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // checks if the event is not NULL
        if (event != NULL)
        {
            // if the user close the window, it will break from loop
            if (getEventType(event) == WINDOW_CLOSED)
            {
                break;
            }

            // moves paddle
            if (getEventType(event) == MOUSE_MOVED)
            {
                // x of paddle will depend of the movement of the cursor
                double x = getX(event) - PWIDTH / 2;

                // y of paddle will be constant
                double y = HEIGHT - PWIDTH;

                // left and right extremities of paddle
                double lefExt = PWIDTH / 2;
                double rigExt = getWidth(window) - PWIDTH / 2;

                // making sure we do not go beyond the extremities
                if (getX(event) >= lefExt && getX(event) <= rigExt)
                {
                    setLocation(paddle, x, y);
                }
            }
        }
    }


    // checks if the user won the game
    if (lives != 0)
    {   
        // adds a winner sign image to window
        GImage winner = newGImage("winner.png");
        setSize(winner, 300, 100);         
        add(window, winner);

        // coordinates of the winner image
        double x = (WIDTH - getWidth(winner)) / 2;
        double y = (HEIGHT - getHeight(winner)) / 2;
        setLocation(winner, x, y);
    }

    // wait for click before exiting
    waitForClick();

    // frees the array of lives
    free(arrayLives);

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{   

    // colors of 5 rows of brick
    char* colors[] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};

    // coordinates of bricks in the window
    int x;
    int y = 50;

    // adding bricks to window
    for (int i = 0; i < ROWS; i++)
    {   
        x = 2;

        for (int j = 0; j < COLS; j++)
        {
            // creates a new brick
            GRect rect = newGRect(x, y, BWIDTH, BHEIGHT);
            
            // fills it with a color
            setFilled(rect, true);
            setColor(rect, colors[i]);
            
            // adds it to the window
            add(window, rect);

            // adds space after each brick
            x += 40;
        }

        // goes to a new row
        y += 15;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{   
    // coordinates of the centered ball
    double x = (WIDTH - (2 * RADIUS)) / 2;
    double y = (HEIGHT - (2 * RADIUS)) / 2;

    // creates a ball, fills with black, and adds it to window
    GOval circle = newGOval(x, y, (2 * RADIUS), (2 * RADIUS));
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);

    // returns the ball
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // coordinates of the bottom-middle paddle
    double x = (WIDTH - PWIDTH) / 2;
    double y = HEIGHT - PWIDTH;
   
    // creates paddle, fills it with black, and adds it to window
    GRect rect = newGRect(x, y, PWIDTH, PHEIGHT);
    setFilled(rect, true);
    setColor(rect, "BLACk");
    add(window, rect);

    // returns the paddle
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // creates the scoreboard
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-50");
    setColor(label, "LIGHT_GRAY");
    
    // coordinates of the label
    double x = (WIDTH - getWidth(label)) / 2;
    double y = (HEIGHT - getFontAscent(label)) / 2;

    // sets the scoreboard to its location and adds it to window
    setLocation(label, x, y);
    add(window, label);

    // returns the scoreboard
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

/**
 * Displaying little hearts at the bottom-right of the window.
 * The number of hearts depends of lives.
 * Returns an array of pointers to GImage, so we can remove hearts 
 * one at a time.
 */
GImage* initLives(GWindow window, int lives)
{
    
    // allocating an array of images according to the number of lives   
    GImage* arrayLives = malloc(sizeof(GImage) * lives);

    // coordinates of lives
    double x = 360;
    double y = 560;
    for (int i = 0; i < lives; i++)
    {
        GImage live = newGImage("live.png");
        arrayLives[i] = live;
        setSize(live, 30, 30);
        setLocation(live, x, y);
        add(window, live);

        // leaves space for the next live
        x -= 35;
    }

    // returns the arrays of lives
    return arrayLives;
}

/**
 * Adding a little effect to the score.
 */
void socreEffect(GLabel label)
{
    char* size[] = {"SansSerif-40", "SansSerif-42", "SansSerif-44", "SansSerif-46", "SansSerif-48","SansSerif-50"};

    // making the label bigger
    for (int i = 0; i < 6; i++)
    {
        setFont(label, size[i]);
        pause(5);
    }

    // returning the label to its normal size
    for (int i = 5; i >= 0; i--)
    {
        setFont(label, size[i]);
        pause(5);
    }
}