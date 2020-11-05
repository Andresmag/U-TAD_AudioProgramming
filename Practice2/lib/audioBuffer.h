#pragma once

typedef unsigned int ALuint;
typedef unsigned int uint32_t;

class AudioBuffer
{
public:
    static AudioBuffer* load(const char* filename);
    uint32_t getAlBuffer() const;
    ~AudioBuffer();

private:
    static uint32_t convertToInt(char* buffer, size_t len);
    AudioBuffer();

    ALuint m_buffer;
};
