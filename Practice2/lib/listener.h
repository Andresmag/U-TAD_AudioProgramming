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

    float getPosX() const { return m_x; }
    float getPosY() const { return m_y; }
    float getPosZ() const { return m_z; }

private:
    Listener() = default;

    float m_x, m_y, m_z;
};