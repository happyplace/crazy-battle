#pragma once

#include <memory>

#include <SDL.h>

struct KeyboardConfig
{
    KeyboardConfig()
        : attack(SDL_SCANCODE_UNKNOWN)
        , jump(SDL_SCANCODE_UNKNOWN)
        , back(SDL_SCANCODE_UNKNOWN)
        , start(SDL_SCANCODE_UNKNOWN)
        , btnB(SDL_SCANCODE_UNKNOWN)
        , btnLeftShoulder(SDL_SCANCODE_UNKNOWN)
        , btnY(SDL_SCANCODE_UNKNOWN)
        , moveX_pos(SDL_SCANCODE_UNKNOWN)
        , moveX_neg(SDL_SCANCODE_UNKNOWN)
    {}

    SDL_Scancode attack;
    SDL_Scancode jump;
    SDL_Scancode back;
    SDL_Scancode start;
    SDL_Scancode btnB;
    SDL_Scancode btnLeftShoulder;
    SDL_Scancode btnY;
    SDL_Scancode moveX_pos;
    SDL_Scancode moveX_neg;
};

class GamePad
{
public:
    int32_t GetId() const { return m_id; }

    bool Attack() const;
    bool Jump() const;
    bool Back() const;
    bool Start() const;
    bool BtnB() const;
    bool BtnLeftShoulder() const;
    bool BtnY() const;
    float MoveX() const;

private:
    enum class InputType { Keyboard, Joystick, };

    explicit GamePad(int32_t id, SDL_GameController* gameController);
    explicit GamePad(int32_t id, const KeyboardConfig& keyboardConfig);

    int32_t m_id;
    InputType m_inputType;
    SDL_GameController* m_gameController;
    KeyboardConfig m_keyboardConfig;

    friend class InputManager;
};

typedef std::shared_ptr<GamePad> GamePadPtr;
