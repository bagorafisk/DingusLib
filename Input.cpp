#include "Input.h"

Keyboard::Keyboard(GLFWwindow* window): window(window){
    for (int key = static_cast<int>(A); key <= static_cast<int>(PauseBreak); ++key) {
        keyStates[static_cast<Key>(key)] = false;
    }
}

Keyboard::Keyboard(){}

bool Keyboard::isKeyDown(Key key) {
    switch (key)
    {
    case A:
        return glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    case B:
        return glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS;
    case C:
        return glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
    case D:
        return glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    case E:
        return glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
    case F:
        return glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS;
    case G:
        return glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS;
    case H:
        return glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS;
    case I:
        return glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS;
    case J:
        return glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS;
    case K:
        return glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;
    case L:
        return glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
    case M:
        return glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS;
    case N:
        return glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS;
    case O:
        return glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
    case P:
        return glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;
    case Q:
        return glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;
    case R:
        return glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;
    case S:
        return glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    case T:
        return glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
    case U:
        return glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS;
    case V:
        return glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS;
    case W:
        return glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    case X:
        return glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS;
    case Y:
        return glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS;
    case Z:
        return glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS;
    case Å:
        return glfwGetKey(window, GLFW_KEY_WORLD_1) == GLFW_PRESS; // Adjust if needed
    case Ä:
        return glfwGetKey(window, GLFW_KEY_APOSTROPHE) == GLFW_PRESS; // Adjust if needed
    case Ö:
        return glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS; // Adjust if needed
    case Num1:
        return glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS;
    case ExclamationMark:
        return glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
        // Add similar cases for other shifted symbols if needed...
    case Space:
        return glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    case Enter:
        return glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
    case Tab:
        return glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;
    case Backspace:
        return glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS;
    case Escape:
        return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
    case ArrowUp:
        return glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
    case ArrowDown:
        return glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
    case ArrowLeft:
        return glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    case ArrowRight:
        return glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    default:
        return false;
    }
}

bool Keyboard::isKeyPressed(Key key) {
    int glfwKey = -1;

    switch (key)
    {
    case A:
        glfwKey = GLFW_KEY_A;
        break;
    case B:
        glfwKey = GLFW_KEY_B;
        break;
    case C:
        glfwKey = GLFW_KEY_C;
        break;
    case D:
        glfwKey = GLFW_KEY_D;
        break;
    case E:
        glfwKey = GLFW_KEY_E;
        break;
    case F:
        glfwKey = GLFW_KEY_F;
        break;
    case G:
        glfwKey = GLFW_KEY_G;
        break;
    case H:
        glfwKey = GLFW_KEY_H;
        break;
    case I:
        glfwKey = GLFW_KEY_I;
        break;
    case J:
        glfwKey = GLFW_KEY_J;
        break;
    case K:
        glfwKey = GLFW_KEY_K;
        break;
    case L:
        glfwKey = GLFW_KEY_L;
        break;
    case M:
        glfwKey = GLFW_KEY_M;
        break;
    case N:
        glfwKey = GLFW_KEY_N;
        break;
    case O:
        glfwKey = GLFW_KEY_O;
        break;
    case P:
        glfwKey = GLFW_KEY_P;
        break;
    case Q:
        glfwKey = GLFW_KEY_Q;
        break;
    case R:
        glfwKey = GLFW_KEY_R;
        break;
    case S:
        glfwKey = GLFW_KEY_S;
        break;
    case T:
        glfwKey = GLFW_KEY_T;
        break;
    case U:
        glfwKey = GLFW_KEY_U;
        break;
    case V:
        glfwKey = GLFW_KEY_V;
        break;
    case W:
        glfwKey = GLFW_KEY_W;
        break;
    case X:
        glfwKey = GLFW_KEY_X;
        break;
    case Y:
        glfwKey = GLFW_KEY_Y;
        break;
    case Z:
        glfwKey = GLFW_KEY_Z;
        break;
    case Å:
        glfwKey = GLFW_KEY_WORLD_1; // Adjust if needed
        break;
    case Ä:
        glfwKey = GLFW_KEY_APOSTROPHE; // Adjust if needed
        break;
    case Ö:
        glfwKey = GLFW_KEY_SEMICOLON; // Adjust if needed
        break;
    case Num1:
        glfwKey = GLFW_KEY_1;
        break;
    case ExclamationMark:
        glfwKey = GLFW_KEY_1; // Requires Shift, check in isKeyPressed
        break;
    case Num2:
        glfwKey = GLFW_KEY_2;
        break;
    case QuotationMark:
        glfwKey = GLFW_KEY_2; // Requires Shift
        break;
    case Num3:
        glfwKey = GLFW_KEY_3;
        break;
    case Hash:
        glfwKey = GLFW_KEY_3; // Requires Shift
        break;
    case Num4:
        glfwKey = GLFW_KEY_4;
        break;
    case Dollar:
        glfwKey = GLFW_KEY_4; // Requires Shift
        break;
    case Num5:
        glfwKey = GLFW_KEY_5;
        break;
    case Percent:
        glfwKey = GLFW_KEY_5; // Requires Shift
        break;
    case Num6:
        glfwKey = GLFW_KEY_6;
        break;
    case Ampersand:
        glfwKey = GLFW_KEY_6; // Requires Shift
        break;
    case Num7:
        glfwKey = GLFW_KEY_7;
        break;
    case Slash:
        glfwKey = GLFW_KEY_7; // Requires Shift
        break;
    case Num8:
        glfwKey = GLFW_KEY_8;
        break;
    case LeftParenthesis:
        glfwKey = GLFW_KEY_8; // Requires Shift
        break;
    case Num9:
        glfwKey = GLFW_KEY_9;
        break;
    case RightParenthesis:
        glfwKey = GLFW_KEY_9; // Requires Shift
        break;
    case Num0:
        glfwKey = GLFW_KEY_0;
        break;
    case Equals:
        glfwKey = GLFW_KEY_0; // Requires Shift
        break;
    case Plus:
        glfwKey = GLFW_KEY_EQUAL; // Requires Shift
        break;
    case QuestionMark:
        glfwKey = GLFW_KEY_SLASH; // Requires Shift
        break;
    case Apostrophe:
        glfwKey = GLFW_KEY_APOSTROPHE;
        break;
    //case Asterisk:
    //    glfwKey = GLFW_KEY_ASTERISK; // Requires Shift
    //    break;
    //case Caret:
    //    glfwKey = GLFW_KEY_CARET; // Requires Shift
    //    break;
    case Backtick:
        glfwKey = GLFW_KEY_GRAVE_ACCENT; // Backtick (`) key
        break;
    case At:
        glfwKey = GLFW_KEY_2; // Requires Shift
        break;
    case Pound:
        glfwKey = GLFW_KEY_3; // Requires Shift
        break;
    case SectionSign:
        glfwKey = GLFW_KEY_WORLD_1; // Adjust if needed
        break;
    case GreaterThan:
        glfwKey = GLFW_KEY_PERIOD; // Requires Shift
        break;
    case LessThan:
        glfwKey = GLFW_KEY_COMMA; // Requires Shift
        break;
    case Semicolon:
        glfwKey = GLFW_KEY_SEMICOLON;
        break;
    case Colon:
        glfwKey = GLFW_KEY_SEMICOLON; // Requires Shift
        break;
    case Underscore:
        glfwKey = GLFW_KEY_MINUS; // Requires Shift
        break;
    case Hyphen:
        glfwKey = GLFW_KEY_MINUS;
        break;
    case LeftBracket:
        glfwKey = GLFW_KEY_LEFT_BRACKET;
        break;
    case RightBracket:
        glfwKey = GLFW_KEY_RIGHT_BRACKET;
        break;
    case Enter:
        glfwKey = GLFW_KEY_ENTER;
        break;
    case Space:
        glfwKey = GLFW_KEY_SPACE;
        break;
    case Tab:
        glfwKey = GLFW_KEY_TAB;
        break;
    case Backspace:
        glfwKey = GLFW_KEY_BACKSPACE;
        break;
    case Escape:
        glfwKey = GLFW_KEY_ESCAPE;
        break;
    case LeftShift:
        glfwKey = GLFW_KEY_LEFT_SHIFT;
        break;
    case RightShift:
        glfwKey = GLFW_KEY_RIGHT_SHIFT;
        break;
    case LeftControl:
        glfwKey = GLFW_KEY_LEFT_CONTROL;
        break;
    case RightControl:
        glfwKey = GLFW_KEY_RIGHT_CONTROL;
        break;
    case Alt:
        glfwKey = GLFW_KEY_LEFT_ALT;
        break;
    case AltGr:
        glfwKey = GLFW_KEY_RIGHT_ALT;
        break;
    case CapsLock:
        glfwKey = GLFW_KEY_CAPS_LOCK;
        break;
    case F1:
        glfwKey = GLFW_KEY_F1;
        break;
    case F2:
        glfwKey = GLFW_KEY_F2;
        break;
    case F3:
        glfwKey = GLFW_KEY_F3;
        break;
    case F4:
        glfwKey = GLFW_KEY_F4;
        break;
    case F5:
        glfwKey = GLFW_KEY_F5;
        break;
    case F6:
        glfwKey = GLFW_KEY_F6;
        break;
    case F7:
        glfwKey = GLFW_KEY_F7;
        break;
    case F8:
        glfwKey = GLFW_KEY_F8;
        break;
    case F9:
        glfwKey = GLFW_KEY_F9;
        break;
    case F10:
        glfwKey = GLFW_KEY_F10;
        break;
    case F11:
        glfwKey = GLFW_KEY_F11;
        break;
    case F12:
        glfwKey = GLFW_KEY_F12;
        break;
    case ArrowUp:
        glfwKey = GLFW_KEY_UP;
        break;
    case ArrowDown:
        glfwKey = GLFW_KEY_DOWN;
        break;
    case ArrowLeft:
        glfwKey = GLFW_KEY_LEFT;
        break;
    case ArrowRight:
        glfwKey = GLFW_KEY_RIGHT;
        break;
    case Insert:
        glfwKey = GLFW_KEY_INSERT;
        break;
    case Delete:
        glfwKey = GLFW_KEY_DELETE;
        break;
    case Home:
        glfwKey = GLFW_KEY_HOME;
        break;
    case End:
        glfwKey = GLFW_KEY_END;
        break;
    case PageUp:
        glfwKey = GLFW_KEY_PAGE_UP;
        break;
    case PageDown:
        glfwKey = GLFW_KEY_PAGE_DOWN;
        break;
    case PrintScreen:
        glfwKey = GLFW_KEY_PRINT_SCREEN;
        break;
    case ScrollLock:
        glfwKey = GLFW_KEY_SCROLL_LOCK;
        break;
    case PauseBreak:
        glfwKey = GLFW_KEY_PAUSE;
        break;
    default:
        glfwKey = -1; // Unknown key
        return false;
    }

    bool isCurrentlyPressed = glfwGetKey(window, glfwKey);
    bool wasPreviouslyPressed = keyStates[key];

    bool singlePress = isCurrentlyPressed && !wasPreviouslyPressed;

    keyStates[key] = isCurrentlyPressed;

    return singlePress;
}

void Keyboard::updateKeyStates() {
    for (auto& pair : keyStates) {
        int glfwKey = -1;

        // Map the Keyboard::Key enum to the corresponding GLFW key
        switch (pair.first) {
        case A: glfwKey = GLFW_KEY_A; break;
        case B: glfwKey = GLFW_KEY_B; break;
        case C: glfwKey = GLFW_KEY_C; break;
            // ... continue mapping other keys
        case Space: glfwKey = GLFW_KEY_SPACE; break;
        default: continue;
        }

        pair.second = glfwGetKey(window, glfwKey) == GLFW_PRESS;
    }
}
