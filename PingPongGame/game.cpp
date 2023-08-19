#define is_down(b) input->btn[b].is_down
#define pressed(b) (input->btn[b].is_down && input->btn[b].changed)
#define released(b) (!input->btn[b].is_down && input->btn[b].changed)

float playerP1, playerDP1, playerP2, playerDP2;
float arenaHalfX = .85, arenaHalfY = .45;
float playerHalfX = 0.025, playerHalfY = .12;
float ballX, ballY, ballDPX = 1.3, ballDPY, ballHalf = .01;
int player1Score = 0;
int player2Score = 0;

static void simulatePlayer(float* playerP, float* playerDP, float playerDDP, float deltaTime) {
    playerDDP -= *playerDP * 10; // Remove the '*' before playerDDP

    *playerP = *playerP + *playerDP * deltaTime + playerDDP * deltaTime * deltaTime * 5;
    *playerDP = *playerDP + playerDDP * deltaTime;

    //ping pong padel collision detection
    if (*playerP + playerHalfY > arenaHalfY) {
        //moving the padel back after it hit the arena
        *playerP = arenaHalfY - playerHalfY;
        *playerDP = 0;//velocity of the impact
    }
    else if (*playerP - playerHalfY < -arenaHalfY) {
        //moving the padel back after it hit the arena bottom floor
        *playerP = -arenaHalfY + playerHalfY;
        *playerDP = 0;//velocity of the impact
    }
}

enum gameMode {
    menu,
    gamePlay,
};

gameMode currentMode;
int option;
bool enemyAi;

static void simulateGame(Input* input, float deltaTime) {
    clearScreen(0x926BCC);
    drawRec(0, 0, arenaHalfX, arenaHalfY, 0xC36BCC);


    if (currentMode == gamePlay) {

        float playerDDP1 = 0;
        if (enemyAi) {
            if (is_down(btn_up)) playerDDP1 += 20;
            if (is_down(btn_down)) playerDDP1 -= 20;
        }
        else {
            if (ballY > playerP1) playerDDP1 += 12;
            if (ballY < playerP1) playerDDP1 -= 12;
        }
        // player 2
        float playerDDP2 = 0;
        if (is_down(btn_W)) playerDDP2 += 20;
        if (is_down(btn_S)) playerDDP2 -= 20;

        simulatePlayer(&playerP1, &playerDP1, playerDDP1, deltaTime);
        simulatePlayer(&playerP2, &playerDP2, playerDDP2, deltaTime);

        //simulate ball
        {

            ballX += ballDPX * deltaTime;
            ballY += ballDPY * deltaTime;

            //ball collition
            if (ballX + ballHalf > .80 - playerHalfX &&
                ballX - ballHalf < .80 + playerHalfX &&
                ballY + ballHalf > playerP1 - playerHalfY &&
                ballY + ballHalf < playerP1 + playerHalfY) { // only bounces off when hitting padel
                ballX = .80 - playerHalfX - ballHalf;
                ballDPX *= -1;
                //ballDPY = playerDP1 *.75; // direction of ball based on pedals direction, Y direction
                ballDPY = (ballY - playerP1) * 2 + playerDP1 * .75; // direction of the ball changes based on what area of the pedal is hit
            }
            // other padel
            else if (ballX + ballHalf > -.80 - playerHalfX &&
                ballX - ballHalf < -.80 + playerHalfX &&
                ballY + ballHalf > playerP2 - playerHalfY &&
                ballY + ballHalf < playerP2 + playerHalfY) { // only bounces off when hitting padel
                ballX = -.80 + playerHalfX + ballHalf;
                ballDPX *= -1;
                ballDPY = (ballY - playerP2) * 2 + playerDP2 * .75;
            }
            // ball when it hits the arena, bouncing of the walls
            if (ballY + ballHalf > arenaHalfY) {
                ballY = arenaHalfY - ballHalf;
                ballDPY *= -1;

            }
            else if (ballY - ballHalf < -arenaHalfY) {
                ballY = -arenaHalfY + ballHalf;
                ballDPY *= -1;
            }
            //resetting the ball after it goes out of bound
            if (ballX + ballHalf > arenaHalfX) {
                ballDPX *= -1;
                ballDPY = 0;
                ballX = 0;
                ballY = 0;
                player1Score++;
            }
            else if (ballX - ballHalf < -arenaHalfX) {
                ballDPX *= -1;
                ballDPY = 0;
                ballX = 0;
                ballY = 0;
                player2Score++;

            }
        }

        drawScore(player1Score, -0.10, 0.40, 0.01, 0x000000);
        drawScore(player2Score, 0.10, 0.40, 0.01, 0x000000);


        drawRec(ballX, ballY, ballHalf, ballHalf, 0x00ff22);
        drawRec(.80, playerP1, playerHalfX, playerHalfY, 0xffff22);
        drawRec(-.80, playerP2, playerHalfX, playerHalfY, 0xffff22);
    }
    else {

        if (pressed(btn_left) || pressed(btn_right)) {
            option = !option;
        }

        if (pressed(btn_enter)) {
            currentMode = gamePlay;
            if (option) {
                enemyAi = 0;
            }
            else {
                enemyAi = 1;
            }
        }




        if (option == 0) {

            displayText("SINGLE PLAYER", -.80, -.10, 0.01, 0xF20808);
            displayText("MULTIPLAYER", .20, -.10, 0.01, 0xcccccc);

        }
        else {
            displayText("SINGLE PLAYER", -.80, -.10, 0.01, 0xcccccc);
            displayText("MULTIPLAYER", .20, -.10, 0.01, 0xF20808);
        }

        displayText("PING PONG", -.53, .40, 0.02, 0x2926AC);
        
    }
}