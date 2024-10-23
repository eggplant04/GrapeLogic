#pragma once
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 256



// Function to evaluate simple mathematical expressions
double EvaluateExpression(const char* expression) {
    // A simple implementation using `strtod` and basic operations
    // This is just a placeholder for more complex logic
    double result = 0.0;

    // You can expand this function to parse and evaluate expressions
    // For demonstration, we will just convert it to double directly
    // WARNING: This is not secure and not recommended for real code execution
    char* endptr;
    result = strtod(expression, &endptr);

    // Check if the entire string was converted
    if (*endptr != '\0') {
        // Handle error: the input was not a valid number
        return NAN; // Return NaN to indicate error
    }

    return result;
}

int main(int argc, char* argv[]) {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 600;
    int screenHeight = 150;
    InitWindow(screenWidth, screenHeight, "GrapeLogic - by EGGPLANT");

    SetTargetFPS(60);

    // Input variables
    char codeInput[MAX_INPUT_LENGTH] = { 0 };
    double result = 0.0;
    bool hasError = false;

    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER)) {
            // Evaluate the input code
            result = EvaluateExpression(codeInput);
            hasError = (result != result); // Check if the result is NaN
            // Clear the input after processing
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Rectangle textBoxRect = { 10, 10, screenWidth - 20, 50 };
        GuiTextBox(textBoxRect, codeInput, MAX_INPUT_LENGTH, true); // Input field

        if (hasError) {
            DrawText("Error: Invalid expression!", 10, 90, 20, RED);
        }
        else {
            char resultText[64];
            snprintf(resultText, sizeof(resultText), "Result: %.2f", result);
            DrawText(resultText, 10, 90, 20, DARKGREEN);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
