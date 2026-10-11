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

    int isNormalAttacking = 0;
    float cdAttackTimer = 0;
    float cdBetweenNormalAttack = 1.0f;
    int baseDamage = 99;
    int whirlpoolDamage = 133;
    int score = 0;

    float fishSize = 150.0f; //Also resolution target size
    float fishTimer = 0.0f;
    float fishVelocity = 0.0f;
    float fishX;
    float fishY;
    float fishSpeed = 6.0f;
    float fishStunTimer = 0;
    float fishTurningTimer = 0;
    int isFishTurningLeft = 0;
    SharkState currentSharkState;

    int isOnWhirlpool = 0;
    int whirlSize;
    int whirlWidth;
    int whirlHeight;

    float animTime = 0.0f;
    float maxDuration = 0.3f; // แอนิเมชันยาว 0.6 วินาที
    bool triggerAnim = false;   // เปิดมาให้เล่นเลย



void initializeSharkSpeedBasedOnFacing(void);
void dealDamageToShark(int);
void stunSharkForThisSecond(float);

void SpawnDamageText(const char* text, Vector2 pos, AnimType type);
void UpdateDamageTexts(float dt);
void DrawDamageTexts(Font font);

int main(void) {
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
    whirlSize = (float)screenWidth*0.2f;
    whirlWidth = screenWidth/2 - whirlSize/2;
    Font defaultFont = GetFontDefault();
    //whirlHeight = screenHeight/2 - whirlSize 

    
    float waitTimer = 0.0f;
    float timeToBite = 0.0f;

    

    const int barWidth = screenWidth * 0.7f;
    const int barHeight = 30;
    const int barX = screenWidth / 2 - barWidth / 2;
    const int barY = screenHeight / 2 - barHeight / 2;

    

    

    
    


    Texture2D compro_shark = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/compro_shark.png");
    Texture2D compro_shark_stunned = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/compro_shark_stunned.png");
    Texture2D compro_shark_turn = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/compro_shark_turn.png");



    Texture2D background = LoadTexture("C:/Users/ASUS TUF A15/Desktop/Earth's CMU/dg111-036/wraylib/resources/background.png");

   
    while (!WindowShouldClose()) {
        if (currentState == STATE_IDLE) {
            if (IsKeyPressed(KEY_SPACE)) {
                currentState = STATE_WAITING;
                currentSharkState = SHARK_IDLE;
                waitTimer = 0.0f;
                timeToBite = (float)GetRandomValue(0, 1);
                isFishTurningLeft = GetRandomValue(0, 1);

                score = 0;
                fishX = (screenWidth/2)-50;
                tensionProgress = 0;
            }
        } 
        else if (currentState == STATE_WAITING) {
            waitTimer += GetFrameTime();
            if (waitTimer >= timeToBite) {
                currentState = STATE_FISHING;
                tensionProgress = 0.0f;
                fishTimer = 0.0f;
            }
        } 
        else if (currentState == STATE_FISHING) {

            //KEY CONTROLLING
            if(IsKeyDown(KEY_A) && IsKeyUp(KEY_D)) {
                isPlayerPullingLeft = 1;
            } else if(IsKeyDown(KEY_D) && IsKeyUp(KEY_A)) {
                isPlayerPullingLeft = -1;
            } else if(IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
                isPlayerPullingLeft = 0;
            }

            if(IsKeyPressed(KEY_SPACE) && fishStunTimer <= 0) {
                if(isOnWhirlpool == 1) {
                    dealDamageToShark(333);
                    stunSharkForThisSecond(1.0f);
                    tensionProgress += 15;
                } else {
                    dealDamageToShark(250);
                    tensionProgress += 15;
                }   
            } 

            if(IsKeyPressed(KEY_W)) {
                if(currentSharkState == SHARK_TURNING) {
                    dealDamageToShark(199);
                    stunSharkForThisSecond(0.3f);
                    
                } else {
                    dealDamageToShark(111);
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
                    currentSharkState = SHARK_TURNING;
                    if(fishTimer <= 0) {
                        fishTimer = (float)GetRandomValue(5, 20) / 10.0f;
                        initializeSharkSpeedBasedOnFacing();
                        if(isFishTurningLeft == 0) {isFishTurningLeft = 1; fishVelocity = fishSpeed;} 
                        else{isFishTurningLeft = 0; fishVelocity = -fishSpeed;}
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

            //check if on whirlpool
            if(fishCentreX > whirlWidth && fishCentreX < whirlWidth + whirlSize) {
                isOnWhirlpool = 1;
                cdAttackTimer -= GetFrameTime();
                cdAttackTimer -= GetFrameTime();
            } else {isOnWhirlpool = 0;}


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




            if(isNormalAttacking == 1) {
                if(cdAttackTimer > 0) {cdAttackTimer -= GetFrameTime();}
                else {
                    if(isOnWhirlpool == 0) {
                        dealDamageToShark(baseDamage); 
                    } else {
                        dealDamageToShark(whirlpoolDamage);
                    }
                    cdAttackTimer = cdBetweenNormalAttack;
                }
            }

            UpdateDamageTexts(GetFrameTime());


            






    
            



            if (tensionProgress >= 100.0f) {
                currentState = STATE_FAILED;
            } else if(tensionProgress < 0) {
                tensionProgress = 0;
            }

        
        } 
        else if (currentState == STATE_SUCCESS || currentState == STATE_FAILED) {
            if (IsKeyPressed(KEY_SPACE)) {
                currentState = STATE_IDLE;
            }
        }


        //Score pop up animation.
        float scale = 1.0f;
        if (triggerAnim) {
            animTime += GetFrameTime();
            if (animTime >= maxDuration) {
                triggerAnim = false;
                scale = 1.0f; 
            } else {
                float progress = animTime / maxDuration;
                scale = sinf(progress * PI * 1.5f) * (1.0f - progress) * 0.4f + 1.0f;
            }
        }

        
        #pragma region BeginDrawing()
        BeginDrawing();
            ClearBackground(DARKBLUE);

            //background.png
            Rectangle backgroundSourceRec = { 0.0f, 0.0f, (float)background.width, (float)background.height };
            Rectangle backgroundDestRec = { 0.0f, 0.0f, (float)screenWidth, (float)screenHeight };
            Vector2 origin = { 0.0f, 0.0f }; //always 0
            DrawTexturePro(background, backgroundSourceRec, backgroundDestRec, origin, 0.0f, WHITE);
            
            //compro_shark.png
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

            
            if (currentState == STATE_IDLE) {
                DrawText("THE SHARK WANT TO PLAY WITH YOU!", 240, 150, 30, RAYWHITE);
                DrawText("PRESS [SPACEBAR] TO CAST YOUR LINE", 210, 300, 20, LIGHTGRAY);
            } 
            else if (currentState == STATE_WAITING) {
                DrawText("READY...", 290, 250, 20, GOLD);
                DrawCircle(screenWidth / 2, screenHeight / 2 + 100, 10 + sinf(GetTime() * 5) * 4, RED); // ทุ่นลอยกระเพื่อมน้ำ
            } 
            else if (currentState == STATE_FISHING) {


                int tensionBarY = barY - (screenHeight * 0.4f);
                DrawRectangle(barX - 4, tensionBarY - 4, barWidth + 8, barHeight + 8, DARKBLUE);
                int currentTensionWidth = (int)((tensionProgress / 100.0f) * barWidth);
                DrawRectangle(barX, tensionBarY, currentTensionWidth, barHeight, RED);      


                
                
                float currentFontSize = 35.0f * scale;
                Vector2 scoreTextPos = { barX, tensionBarY + 60 }; 
                char scoreText[] = "Score: %d";
                Vector2 scoreTextSize = MeasureTextEx(GetFontDefault(), scoreText, currentFontSize, 2.0f);
                Vector2 scoreTextOrigin = { scoreTextSize.x / 2.0f, scoreTextSize.y / 2.0f };
                Vector2 sss = { 0,0 };
                //DrawText(TextFormat(scoreText, score), barX, tensionBarY + 60, 40, BLACK);
                DrawTextPro(GetFontDefault(), TextFormat(scoreText, score), scoreTextPos, sss, 0.0f, currentFontSize, 2.0f, BLACK);


            
                



                //DrawTextPro(GetFontDefault(), text, position, origin, 0.0f, currentFontSize, 2.0f, GOLD);






                //Debug circle to find pos.
                //DrawCircle(fishX+(fishSize/2), (screenHeight/2)-(fishSize/2), 5.0f, RED);

                //Better visual
                if(isOnWhirlpool) {
                    DrawCircle(screenWidth/2, screenHeight - 100, 20.0f, GREEN);
                } else {
                    DrawCircle(screenWidth/2, screenHeight - 100, 20.0f, RED);
                }



                } 
            else if (currentState == STATE_SUCCESS) {
                DrawText("YOU CAUGHT A FISH! 🐟", 240, 220, 30, GREEN);
                DrawText("PRESS [SPACEBAR] TO FISH AGAIN", 240, 320, 20, RAYWHITE);
            } 
            else if (currentState == STATE_FAILED) {
                char gameDoneText[] = "You got %d score!!!";
                DrawText(TextFormat(gameDoneText, score), 245, 220, 30, RED);
                DrawText("PRESS [SPACEBAR] TO TRY AGAIN", 240, 320, 20, RAYWHITE);
            }

            DrawDamageTexts(defaultFont);

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

void dealDamageToShark(int damage) {
    score += damage;
    Vector2 pos = { fishX+(fishSize/2),fishY};
    if(isOnWhirlpool) {
        char dmgStr[8];
        sprintf(dmgStr, "%d", damage);
        SpawnDamageText(dmgStr, pos, ANIM_PHYSICS_FALL);
    } else {
        char dmgStr[8];
        sprintf(dmgStr, "%d", damage);
        SpawnDamageText(dmgStr, pos, ANIM_FLOAT_FADE);
    }
    animTime = 0.0f;
    triggerAnim = true;
}

void stunSharkForThisSecond(float seconds) {
    currentSharkState = SHARK_STUNNED;
    fishStunTimer = seconds;
}


#pragma endregion












#pragma region DamageText


// Function to spawn a new damage popup
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

#pragma endregion