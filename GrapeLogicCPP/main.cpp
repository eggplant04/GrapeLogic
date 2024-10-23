#pragma once
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using std::vector;

#define MAX_INPUT_LENGTH 256



bool IsValidExpression(const std::string& input, const std::vector<char>& allowedCharacters) {
    for (char ch : input) {
        if (std::find(allowedCharacters.begin(), allowedCharacters.end(), ch) == allowedCharacters.end()) {
            return false; // Invalid character found
        }
    }
    return true; // All characters are valid
}

double EvaluateExpression(std::string input, double lastResult) {
    // Replace 'r' with the last result
    size_t pos;
    while ((pos = input.find('r')) != std::string::npos) {
        input.replace(pos, 1, std::to_string(lastResult));
    }

    std::istringstream stream(input);
    double result = 0.0;
    double currentNumber;
    char operation = '+'; // Start with addition

    while (stream >> currentNumber) {
        // Determine the operation to apply
        if (operation == '+') {
            result += currentNumber;
        }
        else if (operation == '-') {
            result -= currentNumber;
        }
        else if (operation == '*') {
            result *= currentNumber;
        }
        else if (operation == '/') {
            if (currentNumber != 0) {
                result /= currentNumber;
            }
            else {
                return 0; // Handle division by zero
            }
        }

        // Read the next operation
        stream >> operation;
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

    vector<char> allowedCharacters = { '+', '-', '/', '*', '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9', '0' , ' ', 'r', '.'};

    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER)) {
            std::string inputString(codeInput);

            // Check if the input string is valid
            if (IsValidExpression(inputString, allowedCharacters)) {
                result = EvaluateExpression(inputString, result);
                hasError = false; // No error
            }
            else {
                hasError = true; // Invalid characters in the input
            }

            // Clear the input after processing
            //memset(codeInput, 0, MAX_INPUT_LENGTH);
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
            snprintf(resultText, sizeof(resultText), "Result: %.7f", result);
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
