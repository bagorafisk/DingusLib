#ifndef INPUT_H
#define INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

    enum Key {
        // Letters
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Å, Ä, Ö,

        // Numbers and symbols (top row keys)
        Num1, ExclamationMark,   // 1 and !
        Num2, QuotationMark,     // 2 and "
        Num3, Hash,              // 3 and #
        Num4, Dollar,            // 4 and $
        Num5, Percent,           // 5 and %
        Num6, Ampersand,         // 6 and &
        Num7, Slash,             // 7 and /
        Num8, LeftParenthesis,   // 8 and (
        Num9, RightParenthesis,  // 9 and )
        Num0, Equals,            // 0 and =
        Plus, QuestionMark,      // + and ?

        // Other symbol keys
        Apostrophe, Asterisk,    // ' and *
        Caret, Backtick,         // ^ and `
        At, Pound,               // @ and £
        SectionSign,             // §
        GreaterThan, LessThan,   // > and <
        Semicolon, Colon,        // ; and :
        Underscore, Hyphen,      // _ and -
        LeftBracket, RightBracket, // [ and ]

        // Special keys
        Enter, Space, Tab,
        Backspace, Escape,
        LeftShift, RightShift,
        LeftControl, RightControl,
        Alt, AltGr,
        CapsLock,

        // Function keys
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        // Arrow keys
        ArrowUp, ArrowDown, ArrowLeft, ArrowRight,

        // Other keys
        Insert, Delete, Home, End, PageUp, PageDown,
        PrintScreen, ScrollLock, PauseBreak
    };

class Keyboard {
public:
	GLFWwindow* window;


    Keyboard(GLFWwindow* window);

    Keyboard();

    bool isKeyDown(Key key);
    bool isKeyPressed(Key key);

    void updateKeyStates();

private:
    std::unordered_map<Key, bool> keyStates;
};

#endif