#pragma once

#include <memory>

#include <SDL.h>

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

    int32_t m_id;
    InputType m_inputType;
    SDL_GameController* m_gameController;

    friend class InputManager;
};

typedef std::shared_ptr<GamePad> GamePadPtr;
