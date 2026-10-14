#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_DAMAGE_TEXTS 50


typedef enum GameState {
    STATE_IDLE,       
    STATE_WAITING,   
    STATE_FISHING,   
    STATE_SUCCESS,   
    STATE_FAILED   
} GameState;

typedef enum {
    SHARK_IDLE,
    SHARK_DAMAGED,
    SHARK_STUNNED,
    SHARK_TURNING
} SharkState;

typedef enum {
    ANIM_PHYSICS_FALL, 
    ANIM_FLOAT_FADE    
} AnimType;

typedef struct {
    char text[16];
    Vector2 position;
    Vector2 velocity;
    float scale;
    float alpha;
    float lifetime;
    float maxLifetime;
    AnimType type;
    bool active;
} DamageText;

DamageText damageTexts[MAX_DAMAGE_TEXTS] = { 0 };


//Dev reminder
//- Crtl + Shift + B to save the new code.
//- press any key in terminal to make it typable.
//- & "C:\Users\ASUS TUF A15\Desktop\Earth's CMU\dg111-036\wraylib\raylib_project.exe"
//- press "UP" to recall last command.

//MAIN VARIABLE INIT
    int isPlayerPullingLeft = 0;
    int shouldTension = 0;
    float defTensionIncreaseRate = 20.0f;
    float tensionIncreaseRate;
    float tensionDecreaseRate = 7.5f;
    float tensionProgress = 0.0f;

    float gameTimer;

    int isNormalAttacking = 0;
    float cdAttackTimer = 0;
    float cdBetweenNormalAttack = 1.0f;
    int baseDamage = 99;
    int whirlpoolDamage = 133;
    int score = 0;
    int highscore;
    float scoreMultiplier = 1.0f;

    float fishSize = 150.0f; //Also resolution target size
    float fishTimer = 0.0f;
    float fishVelocity = 0.0f;
    float fishX;
    float fishY;
    float fishSpeed = 6.0f;
    float fishStunTimer = 0;
    float fishTurningTimer = 0;
    int isFishStunnedThisTurn = 0; //Boolean to check if you press Space this turning session
    int isFishTurningLeft = 0;
    SharkState currentSharkState;

    int isOnWhirlpool = 0;
    int whirlSize;
    int whirlWidth;
    int whirlHeight;
    float whirlBaseX = 200;
    float whirlX = 0;
    float whirlpoolTimer = 0; //Timer to change POS
    bool whirlRequestAppear = false;
    float whirlpoolAlpha = 1; //Fading whirlpool

    



void initializeSharkSpeedBasedOnFacing(void);
void dealDamageToShark(int, int);
void stunSharkForThisSecond(float);
int UpdateScoreMultiplier(void);

    //popup
    float animTime = 0.0f;
    float maxDuration = 0.3f;
    bool triggerAnim = false; 

    //multiplier popup 
    int prevMultiplierTier = 1;
    float mulAnimTime = 0.0f;
    float mulMaxDuration = 0.3f;
    bool triggerMulAnim = false;
    float mulPopDirection = 1.0f; 

//Damage Text anim part.
void SpawnDamageText(const char* text, Vector2 pos, AnimType type);
void UpdateDamageTexts(float dt);
void DrawDamageTexts(Font font);
void ClearAllDamageTexts(void);


//Camera Shake part.
    float shakeTimer = 0.0f;
    float shakeIntensity = 0.0f;
void TriggerScreenShake(float duration, float intensity) {
    shakeTimer = duration;
    shakeIntensity = intensity;
}

int main(void) {

    //Force working directory to ALWAYS be where the .exe file lives
    ChangeDirectory(GetApplicationDirectory());
    //To fix short Texture path doesn't work and need full path.

    //initialization, a must for raylib
    const int screenWidth = 800; // 800 600
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "COMPRO PROJECT");
    SetTargetFPS(60);

    //initialize variable.
    tensionIncreaseRate = defTensionIncreaseRate;
    fishX = (screenWidth/2)-50;
    fishY = (screenHeight/2)-(fishSize/2);
    GameState currentState = STATE_IDLE;
    currentSharkState = SHARK_IDLE;
    whirlSize = (float)screenWidth*0.25f;
    whirlWidth = screenWidth/2 - whirlSize/2;
    whirlpoolAlpha = 1;
    


    Font defaultFont = GetFontDefault();


    //init Camera2D
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    
    float waitTimer = 0.0f;
    float timeToBite = 0.0f;

    

    const int barWidth = screenWidth * 0.7f;
    const int barHeight = 30;
    const int barX = screenWidth / 2 - barWidth / 2;
    const int barY = screenHeight / 2 - barHeight / 2;

    

    

    
    

    ///IMAGEINIT
    /*Texture2D compro_shark = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/compro_shark.png");
    Texture2D compro_shark_stunned = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/compro_shark_stunned.png");
    Texture2D compro_shark_turn = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/compro_shark_turn.png");
    Texture2D space_skill = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/space_skill.png");
    Texture2D w_skill = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/w_skill.png");
    Texture2D whirlpool = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/whirlpool.png");
    Texture2D background = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/background.png");
    Texture2D main_menu = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/main_menu.png");
    Texture2D score_menu = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/score_menu.png");*/

   
    Texture2D compro_shark = LoadTexture("resources/compro_shark.png");
    Texture2D compro_shark_stunned = LoadTexture("resources/compro_shark_stunned.png");
    Texture2D compro_shark_turn = LoadTexture("resources/compro_shark_turn.png");


    Texture2D space_skill = LoadTexture("resources/space_skill.png");
    Texture2D w_skill = LoadTexture("resources/w_skill.png");



    Texture2D whirlpool = LoadTexture("resources/whirlpool.png");
    Texture2D background = LoadTexture("resources/background.png");
    Texture2D main_menu = LoadTexture("resources/main_menu.png");
    Texture2D score_menu = LoadTexture("resources/score_menu.png");

    
    while (!WindowShouldClose()) {
        if (currentState == STATE_IDLE) {
            if (IsKeyPressed(KEY_SPACE)) {
                currentSharkState = SHARK_IDLE;
                
                isFishTurningLeft = GetRandomValue(0, 1);

                score = 0;
                scoreMultiplier = 1;
                fishX = (screenWidth/2)-50;
                tensionProgress = 0;
                fishTimer = 0;
                gameTimer = 60;

                whirlpoolAlpha = 1;
                whirlX = whirlBaseX;
                whirlpoolTimer = 3;
                whirlRequestAppear = false;

                currentState = STATE_FISHING;

            
            }
        } 



        ///MAIN STATE
        else if (currentState == STATE_FISHING) {

            //KEY CONTROLLING
            if(IsKeyDown(KEY_A) && IsKeyUp(KEY_D)) {
                isPlayerPullingLeft = 1;
            } else if(IsKeyDown(KEY_D) && IsKeyUp(KEY_A)) {
                isPlayerPullingLeft = -1;
            } else if(IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
                isPlayerPullingLeft = 0;
            }

            if(IsKeyPressed(KEY_W) && fishStunTimer <= 0) {
                if(isOnWhirlpool == 1) {
                    dealDamageToShark(333, 1);
                    stunSharkForThisSecond(1.0f);
                    tensionProgress += 15;
                    if(tensionProgress >= 100) {
                        tensionProgress = 99;
                    }
                    TriggerScreenShake(0.3f, 6.0f);

                    //make the whirl goes faster.
                    whirlpoolTimer -= 1.5f;
                    if(whirlpoolTimer <= 1.0f) {
                        whirlpoolTimer = 1;
                    }
                } else {
                    dealDamageToShark(250, 0);
                    tensionProgress += 15;
                }   
            } 

            if(IsKeyPressed(KEY_SPACE)) {
                if(currentSharkState == SHARK_TURNING) {
                    dealDamageToShark(199, 1);
                    stunSharkForThisSecond(0.3f);
                    isFishStunnedThisTurn = 1;
                    TriggerScreenShake(0.15f, 3.0f);
                    
                } else {
                    dealDamageToShark(111, 0);
                    tensionProgress += 10;
                }
            }

            


    

            
            //Handle changing direction.
            if(fishStunTimer > 0) {
                fishStunTimer -= GetFrameTime();
                
            } else if (fishStunTimer <= 0) {
                currentSharkState = SHARK_IDLE;
                fishStunTimer = 0;

                fishTimer -= GetFrameTime(); //Facing direction timer
                if (fishTimer <= 0.4f) {
                    if(isFishStunnedThisTurn == 0) currentSharkState = SHARK_TURNING;
                    if(fishTimer <= 0) {
                        fishTimer = (float)GetRandomValue(5, 20) / 10.0f;
                        initializeSharkSpeedBasedOnFacing();
                        if(isFishTurningLeft == 0) {isFishTurningLeft = 1; fishVelocity = fishSpeed;} 
                        else{isFishTurningLeft = 0; fishVelocity = -fishSpeed;}
                        isFishStunnedThisTurn = 0; //reset.
                    }
                }
            }

            //Handle Whirlpool Changing POS
            if (!whirlRequestAppear) {
                whirlpoolTimer -= GetFrameTime();

                if (whirlpoolTimer <= 0.5f) {
                    whirlpoolAlpha -= 3.0f * GetFrameTime();
                    if (whirlpoolAlpha < 0.0f) whirlpoolAlpha = 0.0f; 
                }
                if (whirlpoolTimer <= 0.0f) {
                    whirlpoolAlpha = 0.0f;
                    int oldWhirlX = (int)whirlX;
                    for (int i = 0; i < 10; i++) {
                        whirlX = (float)GetRandomValue((int)whirlBaseX - 250, (int)whirlBaseX + 250);
                        if ( abs((int)whirlX - oldWhirlX) > 50 ) {
                            break;
                        }
                    }
                    whirlpoolTimer = 0.5f; //Wait for X long before appear again.
                    whirlRequestAppear = true;
                }
            } 
            else {
                if (whirlpoolTimer > 0.0f) {
                    whirlpoolTimer -= GetFrameTime();
                } else {
                    whirlpoolAlpha += 3.0f * GetFrameTime();
                    if (whirlpoolAlpha >= 1.0f) {
                        whirlpoolAlpha = 1.0f;
                        whirlRequestAppear = false;
                        whirlpoolTimer = (float)GetRandomValue(2, 5);
                    }
                }
            }
    


            //Init each frame.
            shouldTension = 0;
            isNormalAttacking = 0;
            tensionIncreaseRate = defTensionIncreaseRate;
            
            //Handle shark on wall
            int limitX = barX - (barWidth / 4);
            int limitY = barX + (int)((float)barWidth * 1.08f);
            float fishCentreX = fishX+(fishSize/2);
            if (fishX < limitX) {
                fishX = limitX;
                fishVelocity = 0;
            } else {initializeSharkSpeedBasedOnFacing();}
            if (fishX > limitY) {
                fishX = limitY;
                fishVelocity = 0;
            } else {initializeSharkSpeedBasedOnFacing();}

            if(fishX <= limitX + 5 || fishX >= limitY - 5) {
                shouldTension = 1;
                tensionIncreaseRate = (int)((float)tensionIncreaseRate * 1.5f);
            }

            //CHECK if on whirlpool
            float whirlCentreX = whirlX + 200.0f;
            float whirlLeftEdge = whirlCentreX - (whirlSize / 2.0f);
            float whirlRightEdge = whirlCentreX + (whirlSize / 2.0f);
            if (!whirlRequestAppear && whirlpoolAlpha > 0.3f &&
                fishCentreX > whirlLeftEdge && fishCentreX < whirlRightEdge) {
                isOnWhirlpool = 1;
                cdAttackTimer -= GetFrameTime() * 2.0f;
            } else {
                isOnWhirlpool = 0;
            }


            //Handle movement.
            if (currentSharkState == SHARK_STUNNED) {
    
                if (isPlayerPullingLeft == 1) {
                    fishX -= (fishSpeed * 1.2f);
                    isNormalAttacking = 1;
                } else if (isPlayerPullingLeft == -1) {
                    fishX += (fishSpeed * 1.2f); 
                    isNormalAttacking = 1;
                } else {

                    fishX += fishVelocity;
                }
                shouldTension = 0;
            } 
            else {
                
                if (isPlayerPullingLeft == 1 && isFishTurningLeft == 1) {
                    fishX += -(fishVelocity * 0.5f);
                    shouldTension = 1;
                    isNormalAttacking = 1;
                } else if (isPlayerPullingLeft == -1 && isFishTurningLeft == 0) {
                    fishX += -(fishVelocity * 0.5f);
                    shouldTension = 1;
                    isNormalAttacking = 1;
                } else if (isPlayerPullingLeft == 1 && isFishTurningLeft == 0) {
                    fishX += (fishVelocity * 1.75f);
                } else if (isPlayerPullingLeft == -1 && isFishTurningLeft == 1) {
                    fishX += (fishVelocity * 1.75f);
                } else {
                    fishX += fishVelocity;
                }
            }

            if (shouldTension == 1) {
                tensionProgress += tensionIncreaseRate * GetFrameTime();
            } else {
                if(currentSharkState == SHARK_STUNNED) {
                    tensionProgress -= (tensionDecreaseRate * 2.0f) * GetFrameTime();
                } else {
                    tensionProgress -= tensionDecreaseRate * GetFrameTime();
                }
            }



            //if(isOnWhirlpool) 
            if(isNormalAttacking == 1 || isOnWhirlpool) {
                if(cdAttackTimer > 0) {cdAttackTimer -= GetFrameTime();}
                else {
                    if(isOnWhirlpool == 0) {
                        dealDamageToShark(baseDamage, 0); 
                    } else {
                        dealDamageToShark(whirlpoolDamage, 0);
                    }
                    cdAttackTimer = cdBetweenNormalAttack;
                }
            }

            UpdateDamageTexts(GetFrameTime());


            






    
            
            UpdateScoreMultiplier();

            

            //Handle Losing
            if (tensionProgress >= 100.0f) {
                currentState = STATE_FAILED;
                ClearAllDamageTexts();
                
            } else if(tensionProgress < 0) {
                tensionProgress = 0;
            }

            if(gameTimer > 0) {
                gameTimer -= GetFrameTime();
            } else if(gameTimer <= 0) {
                gameTimer = 0;
                currentState = STATE_FAILED;
                
            }


            //Handle Camera Shake 
            if (shakeTimer > 0.0f) {
                shakeTimer -= GetFrameTime();
                camera.offset.x = (float)GetRandomValue(-100, 100) / 100.0f * shakeIntensity;
                camera.offset.y = (float)GetRandomValue(-100, 100) / 100.0f * shakeIntensity;
            } else {
                camera.offset = (Vector2){ 0.0f, 0.0f };
            }

        
        } 
        else if (currentState == STATE_SUCCESS || currentState == STATE_FAILED) {
            if (IsKeyPressed(KEY_SPACE)) {
                currentState = STATE_IDLE;
            }
        }


        //Score pop up animation.
        float scoreScale = 1.0f;
        if (triggerAnim) {
            animTime += GetFrameTime();
            if (animTime >= maxDuration) {
                triggerAnim = false;
                scoreScale = 1.0f; 
            } else {
                float progress = animTime / maxDuration;
                scoreScale = sinf(progress * PI * 1.5f) * (1.0f - progress) * 0.4f + 1.0f;
            }
        }

        //ScoreMultiplier pop up 
        int currentTier = UpdateScoreMultiplier(); 
        if (currentTier != prevMultiplierTier) {

            mulPopDirection = (currentTier > prevMultiplierTier) ? 1.0f : -1.0f;
            prevMultiplierTier = currentTier;
            mulAnimTime = 0.0f;
            triggerMulAnim = true;
        }

        float baseMulScale = 1.0f + 0.2f * (currentTier - 1);
        float mulBounce = 0.0f;
        if (triggerMulAnim) {
            mulAnimTime += GetFrameTime();
            if (mulAnimTime >= mulMaxDuration) {
                triggerMulAnim = false;
                mulBounce = 0.0f;
            } else {
                float progress = mulAnimTime / mulMaxDuration;
                float popStrength = 0.25f + (0.1f * currentTier);
                mulBounce = sinf(progress * PI) * (1.0f - progress) * popStrength * mulPopDirection;
            }
        }
        float scoreMultiplierScale = baseMulScale + mulBounce;

        
        #pragma region BeginDrawing()
        BeginDrawing();
            ClearBackground(DARKBLUE);
            BeginMode2D(camera);

            Rectangle backgroundSourceRec = { 0.0f, 0.0f, (float)background.width, (float)background.height };
            Rectangle backgroundDestRec = { 0.0f, 0.0f, (float)screenWidth, (float)screenHeight };
            
            Vector2 origin = { 0.0f, 0.0f }; //always 0
        
            
            //STATE_IDLE
            if (currentState == STATE_IDLE) {DrawTexture(main_menu, 0, 0, WHITE);} 

            //STATE_FISHING
            else if (currentState == STATE_FISHING) {
                //background.png
                DrawTexturePro(background, backgroundSourceRec, backgroundDestRec, origin, 0.0f, WHITE);
            
                //RENDER WHIRLPOOL
                Rectangle whirlpoolSourceRec = { 0.0f, 0.0f, (float)whirlpool.width, (float)whirlpool.height };
                Rectangle whirlpoolDestRec = { whirlX, 185, 400.0f, 300.0f }; //-50 -> 200 -> 450
                Color tintColor = WHITE;
                tintColor.a = (unsigned char)(whirlpoolAlpha * 255);
                DrawTexturePro(whirlpool, whirlpoolSourceRec, whirlpoolDestRec, origin, 0.0f, tintColor);
                /*Rectangle whirlpoolSourceRec = { 0.0f, 0.0f, (float)whirlpool.width, (float)whirlpool.height };
                Rectangle whirlpoolDestRec = { 450, 185, 400, 300 }; 
                DrawTexturePro(whirlpool, whirlpoolSourceRec, whirlpoolDestRec, origin, 0.0f, WHITE);
*/
                
                //RENDER SHARK
                float isFlipping = isFishTurningLeft == 0 ? (float)compro_shark.width : -(float)compro_shark.width;
                Rectangle compro_sharkSourceRec = { 0.0f, 0.0f, isFlipping, (float)compro_shark.height };
                Rectangle compro_sharkDestRec = { fishX, fishY, fishSize, fishSize };
                if(currentSharkState == SHARK_IDLE) {
                    DrawTexturePro(compro_shark, compro_sharkSourceRec, compro_sharkDestRec, origin, 0.0f, WHITE);
                } else if(currentSharkState == SHARK_STUNNED) {
                    DrawTexturePro(compro_shark_stunned, compro_sharkSourceRec, compro_sharkDestRec, origin, 0.0f, WHITE);
                } else if(currentSharkState == SHARK_TURNING) {
                    DrawTexturePro(compro_shark_turn, compro_sharkSourceRec, compro_sharkDestRec, origin, 0.0f, WHITE);
                }

                

                //RENDER Tension Bar
                int tensionBarY = barY - (screenHeight * 0.4f);
                DrawRectangle(barX - 4, tensionBarY - 4, barWidth + 8, barHeight + 8, DARKBLUE);
                int currentTensionWidth = (int)((tensionProgress / 100.0f) * barWidth);
                DrawRectangle(barX, tensionBarY, currentTensionWidth, barHeight, RED);   
                DrawText("TENSION", barX +5, tensionBarY +7, 20, BLACK);   

                //RENDER TWO SKILLS
                float defaultSkillSize = 240.0f;
                float w_skillSize;
                Color w_skillColor;
                if((isOnWhirlpool && currentSharkState != SHARK_STUNNED)) {w_skillSize = defaultSkillSize; w_skillColor = WHITE;}
                else {w_skillSize = defaultSkillSize * 0.9f; w_skillColor = GRAY;}
                Rectangle w_skillSourceRec = { 0.0f, 0.0f, (float)w_skill.width, (float)w_skill.height };
                Rectangle w_skillDestRec = { (screenWidth/2)-130, 500, w_skillSize, w_skillSize };
                Vector2 w_skillOrigin = {(float)w_skillDestRec.width / 2, (float)w_skillDestRec.height / 2};
                w_skillColor.a = (unsigned char)(1.0f * 255);
                DrawTexturePro(w_skill, w_skillSourceRec, w_skillDestRec, w_skillOrigin, 0.0f, w_skillColor);
                //
                float space_skillSize;
                Color space_skillColor;
                if(currentSharkState == SHARK_TURNING) {space_skillSize = defaultSkillSize; space_skillColor = WHITE;}
                else {space_skillSize = defaultSkillSize * 0.9f; space_skillColor = GRAY;}
                Rectangle space_skillSourceRec = { 0.0f, 0.0f, (float)space_skill.width, (float)space_skill.height };
                Rectangle space_skillDestRec = { (screenWidth/2)+130, 500, space_skillSize, space_skillSize };
                Vector2 space_skillOrigin = {(float)space_skillDestRec.width / 2, (float)space_skillDestRec.height / 2};
                space_skillColor.a = (unsigned char)(1.0f * 255);
                DrawTexturePro(space_skill, space_skillSourceRec, space_skillDestRec, space_skillOrigin, 0.0f, space_skillColor);

                
                //RENDER TEXT score
                float currentFontSize = 35.0f * scoreScale;
                Vector2 scoreTextPos = { screenWidth/2, tensionBarY + 60 }; 
                char scoreText[] = "Score: %d";
                Vector2 scoreTextSize = MeasureTextEx(GetFontDefault(), scoreText, currentFontSize, 2.0f);
                Vector2 scoreTextOrigin = { scoreTextSize.x / 2.0f, scoreTextSize.y / 2.0f };
                //DrawText(TextFormat(scoreText, score), barX, tensionBarY + 60, 40, BLACK);
                DrawTextPro(GetFontDefault(), TextFormat(scoreText, score), scoreTextPos, scoreTextOrigin, 0.0f, currentFontSize, 2.0f, BLACK);



                //RENDER TEXT Score Multiplier
                int shakeMultiIntensity = 0; 
                if(currentTier == 4) {
                    shakeMultiIntensity = 4;
                } else if(currentTier == 3) {
                    shakeMultiIntensity = 2;
                } else {
                    shakeMultiIntensity = 0;
                }
                float offsetMultiX = (float)GetRandomValue(-shakeMultiIntensity, shakeMultiIntensity);
                float offsetMultiY = (float)GetRandomValue(-shakeMultiIntensity, shakeMultiIntensity);
                float scoreMulFontSize = 40.0f * scoreMultiplierScale;
                Vector2 scoreMultiplierTextPos = { 640+offsetMultiX, 70+offsetMultiY }; 
                char scoreMultiplierText[] = "x%.2f";
                Vector2 scoreMulTextSizePOS = MeasureTextEx(GetFontDefault(), scoreMultiplierText, scoreMulFontSize, 2.0f);
                //Vector2 scoreMulTextOrigin = { scoreMulTextSizePOS.x / 2.0f, scoreMulTextSizePOS.y / 2.0f };
                DrawTextPro(GetFontDefault(), TextFormat(scoreMultiplierText, scoreMultiplier), scoreMultiplierTextPos, origin, 10.0f, scoreMulFontSize, 2.0f, ORANGE);

                //RENDER TEXT Game Timer
                float gameTimetSize = 35.0f;
                Vector2 gameTimerTextPos = { (screenWidth/2) - 7 , 500 }; 
                char gameTimerText[] = "%.2f";
                Vector2 gameTimerTextSize = MeasureTextEx(GetFontDefault(), gameTimerText, gameTimetSize, 2.0f);
                Vector2 gameTimerOrigin = { gameTimerTextSize.x / 2.0f, gameTimerTextSize.y / 2.0f };
                //DrawText(TextFormat(scoreText, score), barX, tensionBarY + 60, 40, BLACK);
                DrawTextPro(GetFontDefault(), TextFormat(gameTimerText, gameTimer), gameTimerTextPos, gameTimerOrigin, 0.0f, gameTimetSize, 2.0f, RED);

            
                //RENDER TEXT Highscore
                char highscoreText[] = "HIGHSCORE : %d";
                /*if(highscore != 0)*/ DrawText(TextFormat(highscoreText, highscore), 5,5, 20, YELLOW);
            
                



                //DrawTextPro(GetFontDefault(), text, position, origin, 0.0f, currentFontSize, 2.0f, GOLD);






                //Debug circle to find pos.
                //DrawCircle(fishX+(fishSize/2), (screenHeight/2)-(fishSize/2), 5.0f, RED);

                //Better visual
                /*if(isOnWhirlpool) {
                    DrawCircle(screenWidth/2, screenHeight - 100, 20.0f, GREEN);
                } else {
                    DrawCircle(screenWidth/2, screenHeight - 100, 20.0f, RED);
                }*/



                } 
            /*else if (currentState == STATE_SUCCESS) {
                DrawText("YOU CAUGHT A FISH! 🐟", 240, 220, 30, GREEN);
                DrawText("PRESS [SPACEBAR] TO FISH AGAIN", 240, 320, 20, RAYWHITE);
            }*/
            else if (currentState == STATE_FAILED) {
                ClearAllDamageTexts();
                DrawTexture(score_menu, 0, 0, WHITE);
                char gameDoneText[] = "You got %d score!!!";
                DrawText(TextFormat(gameDoneText, score), 425, 240, 30, ORANGE);
                DrawText("PRESS [SPACEBAR] TO TRY AGAIN", 400, 340, 20, RAYWHITE);
                if(highscore < score) {
                    highscore = score;
                }
            }

            DrawDamageTexts(defaultFont);

            //DEBUG X Y
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            //DrawCircle(mouseX, mouseY, 4.0f, RED);
            //DrawText(TextFormat("X: %d, Y: %d", mouseX, mouseY), mouseX + 12, mouseY - 10, 20, YELLOW);


            EndMode2D();


        EndDrawing();

        #pragma endregion
    }
    UnloadTexture(background);
    CloseWindow();
    return 0;
}



#pragma region FUNCTIONS

void initializeSharkSpeedBasedOnFacing() {
    float currentSpeed = (currentSharkState == SHARK_STUNNED) ? (fishSpeed * 0.3f) : fishSpeed;
    if (isFishTurningLeft == 0) {
        fishVelocity = -currentSpeed;
    } else {
        fishVelocity = currentSpeed;
    }
}

void dealDamageToShark(int damage, int animationMode) {
    damage = (int)((float)damage * scoreMultiplier);
    score += damage;
    Vector2 pos = { fishX+(fishSize/2),fishY};
    char dmgStr[8];
    sprintf(dmgStr, "%d", damage);
    if(isOnWhirlpool || animationMode == 1) {
        SpawnDamageText(dmgStr, pos, ANIM_PHYSICS_FALL);
    } else if(isOnWhirlpool == 0 || animationMode == 0) {
        SpawnDamageText(dmgStr, pos, ANIM_FLOAT_FADE);
    }
    /*if(isOnWhirlpool) {
        char dmgStr[8];
        sprintf(dmgStr, "%d", damage);
        SpawnDamageText(dmgStr, pos, ANIM_PHYSICS_FALL);
    } else {
        char dmgStr[8];
        sprintf(dmgStr, "%d", damage);
        SpawnDamageText(dmgStr, pos, ANIM_FLOAT_FADE);
    }*/
    animTime = 0.0f;
    triggerAnim = true;
}

void stunSharkForThisSecond(float seconds) {
    currentSharkState = SHARK_STUNNED;
    fishStunTimer = seconds;
}

int UpdateScoreMultiplier() {
    if(tensionProgress >= 75) {
        scoreMultiplier = 2.22;
        return 4;
    } else if(tensionProgress >= 50) {
        scoreMultiplier = 1.67f;
        return 3;
    } else if(tensionProgress >= 25) {
        scoreMultiplier = 1.33f;
        return 2;
    } else if(tensionProgress < 25) {
        scoreMultiplier = 1.00f;
        return 1;
    }
    return 0;
}


#pragma endregion












#pragma region DamageText


void SpawnDamageText(const char* text, Vector2 pos, AnimType type) {
    for (int i = 0; i < MAX_DAMAGE_TEXTS; i++) {
        if (!damageTexts[i].active) {
            snprintf(damageTexts[i].text, sizeof(damageTexts[i].text), "%s", text);
            damageTexts[i].position = pos;
            damageTexts[i].active = true;
            damageTexts[i].type = type;
            
            if (type == ANIM_PHYSICS_FALL) {
                damageTexts[i].velocity.x = (float)GetRandomValue(-100, 100); 
                damageTexts[i].velocity.y = (float)GetRandomValue(-300, -200); 
                damageTexts[i].scale = 0.1f; 
                damageTexts[i].alpha = 1.0f;
                damageTexts[i].lifetime = 0.8f; 
                damageTexts[i].maxLifetime = 0.8f;
            } 
            else if (type == ANIM_FLOAT_FADE) {
    
                damageTexts[i].velocity.x = 0;
                damageTexts[i].velocity.y = -60.0f; 
                damageTexts[i].scale = 1.0f;
                damageTexts[i].alpha = 1.0f;
                damageTexts[i].lifetime = 1.2f;
                damageTexts[i].maxLifetime = 1.2f;
            }
            break;
        }
    }
}


void UpdateDamageTexts(float dt) {
    float gravity = 600.0f;

    for (int i = 0; i < MAX_DAMAGE_TEXTS; i++) {
        if (!damageTexts[i].active) continue;

        damageTexts[i].lifetime -= dt;

        if (damageTexts[i].lifetime <= 0) {
            damageTexts[i].active = false;
            continue;
        }

        if (damageTexts[i].type == ANIM_PHYSICS_FALL) {
        
            damageTexts[i].velocity.y += gravity * dt;
            damageTexts[i].position.x += damageTexts[i].velocity.x * dt;
            damageTexts[i].position.y += damageTexts[i].velocity.y * dt;
            
            float elapsed = damageTexts[i].maxLifetime - damageTexts[i].lifetime;
            float progress = elapsed / (damageTexts[i].maxLifetime * 0.25f);
            if (progress < 1.0f) {
                damageTexts[i].scale = 0.1f + (1.4f * progress); 
            } else {
                damageTexts[i].scale = 1.5f;
            }

       
            if (damageTexts[i].lifetime < 0.2f) {
                damageTexts[i].alpha = damageTexts[i].lifetime / 0.2f;
            }
        } 
        else if (damageTexts[i].type == ANIM_FLOAT_FADE) {
            
            damageTexts[i].position.y += damageTexts[i].velocity.y * dt;

           
            damageTexts[i].alpha = damageTexts[i].lifetime / damageTexts[i].maxLifetime;
        }
    }
}


void DrawDamageTexts(Font font) {
    for (int i = 0; i < MAX_DAMAGE_TEXTS; i++) {
        if (!damageTexts[i].active) continue;

        
        Color textColor = (damageTexts[i].type == ANIM_PHYSICS_FALL) ? RED : ORANGE;
        textColor.a = (unsigned char)(damageTexts[i].alpha * 255);

        float baseFontSize = 24.0f;
        float currentFontSize = baseFontSize * damageTexts[i].scale;

       
        Vector2 textSize = MeasureTextEx(font, damageTexts[i].text, currentFontSize, 2.0f);
        Vector2 origin = { textSize.x / 2.0f, textSize.y / 2.0f };

       
        DrawTextPro(
            font, 
            damageTexts[i].text, 
            damageTexts[i].position, 
            origin, 
            0.0f, 
            currentFontSize, 
            2.0f,
            textColor
        );
    }
}

void ClearAllDamageTexts(void) {
    for (int i = 0; i < MAX_DAMAGE_TEXTS; i++) {
        damageTexts[i].active = false;
    }
}

#pragma endregion