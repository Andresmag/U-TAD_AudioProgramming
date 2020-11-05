#pragma once

class Listener
{
public:
    static Listener& GetInstance();
    Listener(Listener const&) = delete;
    void operator=(Listener const&) = delete;

    void Init();

    void setListenerPosition(float x, float y, float z);
    void setListenerVelocity(float x, float y, float z);
    void setListenerOrientation(float x, float y, float z);

private:
    Listener() = default;

};