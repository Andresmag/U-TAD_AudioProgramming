#include "../openal/AL/al.h"
#include "audioSource.h"
#include "audioBuffer.h"
#include <cstdio>

AudioSource::AudioSource(AudioBuffer* buffer)
    : m_source(0)
{
    // Generate source
    alGenSources(1, &m_source);
    ALenum error;
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        printf("alGenSources 1: %d", error);
        m_source = 0;
    }

    // Set default parameters
    setLooping(false);
    setPitch(1.f);
    setGain(1.f);
    setPosition(0.f, 0.f, 0.f);
    setVelocity(0.f, 0.f, 0.f);

    // Attach buffer to the generated source
    alSourcei(m_source, AL_BUFFER, buffer->getAlBuffer());
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        printf("alSourcei AL_BUFFER 0: %d", error);
    }
}

AudioSource::~AudioSource()
{
    alDeleteSources(1, &m_source);
}

void AudioSource::setPitch(float pitch)
{
    alSourcef(m_source, AL_PITCH, pitch);
    m_pitch = pitch;
}

void AudioSource::setGain(float gain)
{
    alSourcef(m_source, AL_GAIN, gain);
}

void AudioSource::setLooping(bool loop)
{
    alSourcei(m_source, AL_LOOPING, loop);
}

void AudioSource::setPosition(float x, float y, float z)
{
    alSource3f(m_source, AL_POSITION, x, y, z);
    m_x = x;
    m_y = y;
    m_z = z;
}

void AudioSource::setVelocity(float x, float y, float z)
{
    alSource3f(m_source, AL_VELOCITY, x, y, z);
}

void AudioSource::play()
{
    alSourcePlay(m_source);
}

void AudioSource::stop()
{
    alSourceStop(m_source);
}

void AudioSource::pause()
{
    alSourcePause(m_source);
}

bool AudioSource::isPlaying() const
{
    ALint value;
    alGetSourcei(m_source, AL_SOURCE_STATE, &value);
    return value == AL_PLAYING;
}
