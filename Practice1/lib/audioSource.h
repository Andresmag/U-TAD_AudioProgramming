#pragma once

class AudioBuffer;

class AudioSource
{
public:
    AudioSource(AudioBuffer* buffer);
    ~AudioSource();

    void setPitch(float pitch);
    void setGain(float gain);
    void setLooping(bool loop);
    void setPosition(float x, float y, float z);
    void setVelocity(float x, float y, float z);

    void play();
    void stop();
    void pause();
    bool isPlaying() const;

    float getPitch() const { return m_pitch; }
    float getPosX() const { return m_x; }
    float getPosY() const { return m_y; }
    float getPostZ() const { return m_z; }

private:
    ALuint m_source;

    float m_pitch;
    float m_x, m_y, m_z;
};