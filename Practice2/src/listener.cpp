#include "listener.h"
#include "AL/al.h"

Listener& Listener::GetInstance()
{
    static Listener listener;
    return listener;
}

void Listener::Init()
{
    m_x = m_y = m_z = 0;
    setListenerPosition(0.f, 0.f, 0.f);
    setListenerVelocity(0.f, 0.f, 0.f);
    setListenerOrientation(0.f, 0.f, 0.f);
}

void Listener::setListenerPosition(float x, float y, float z)
{
    alListener3f(AL_POSITION, x, y, z);
    m_x = x;
    m_y = y;
    m_z = z;
}

void Listener::setListenerVelocity(float x, float y, float z)
{
    alListener3f(AL_VELOCITY, x, y, z);
}

void Listener::setListenerOrientation(float x, float y, float z)
{
    alListener3f(AL_ORIENTATION, x, y, z);
}
