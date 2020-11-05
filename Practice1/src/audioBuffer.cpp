#include "../openal/AL/al.h"
#include <cstdint>
#include "audioBuffer.h"
#include <fstream>
#include <bitset>

AudioBuffer* AudioBuffer::load(const char* filename)
{
    char buffer[4];
    std::ifstream in(filename, std::ios::binary);
    in.read(buffer, 4); // ChunkID -> RIFF
    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        printf("ERROR: %s is not a valid WAVE file", filename);
        return nullptr;
    }
    in.read(buffer, 4); // size of the file
    in.read(buffer, 4); // format
    if (strncmp(buffer, "WAVE", 4) != 0)
    {
        printf("ERROR: could not read WAVE");
        return nullptr;
    }
    in.read(buffer, 4); // fmt
    in.read(buffer, 4); // chunk size
    bool hasExtraParams = convertToInt(buffer, 4) > 16;
    in.read(buffer, 2); // audioFormat
    in.read(buffer, 2); // channels
    int channels = convertToInt(buffer, 2);
    in.read(buffer, 4); // SampleRate
    int frequency = convertToInt(buffer, 4);
    in.read(buffer, 4); // ByteRate
    in.read(buffer, 2); // BlockAlign
    in.read(buffer, 2); // BitsPerSample
    int bitsPerSample = convertToInt(buffer, 2);

    // If there are extra params, skip them
    if (hasExtraParams)
    {
        in.read(buffer, 2); // ExtramParamSize
        int extraSize = convertToInt(buffer, 2);
        while (extraSize > 0)
        {
            in.read(buffer, 1); // ExtraParams
            extraSize -= 1;
        }
    }

    // Search for "data" block
    in.read(buffer, 4);
    while (strncmp(buffer, "data", 4) != 0)
    {
        in.read(buffer, 4); 
    }
    in.read(buffer, 4); // dataSize
    int dataSize = convertToInt(buffer, 4);
    char* data = new char[dataSize];
    in.read(data, dataSize); // The actual sound data


    // Generate buffer
    AudioBuffer* audioBuffer = new AudioBuffer();
    alGetError();
    alGenBuffers(1, &audioBuffer->m_buffer);
    ALenum error;
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        printf("alGenBuffers : %d", error);
        return nullptr;
    }

    // Determine format
    ALenum format;
    if (bitsPerSample == 8)
    {
        if (channels == 1)
        {
            format = AL_FORMAT_MONO8;
        }
        else
        {
            format = AL_FORMAT_STEREO8;
        }
    }
    else
    {
        if (channels == 1)
        {
            format = AL_FORMAT_MONO16;
        }
        else
        {
            format = AL_FORMAT_STEREO16;
        }
    }

    // Fill buffer information
    alBufferData(audioBuffer->m_buffer, format, data, dataSize, frequency);
    return audioBuffer;
}

uint32_t AudioBuffer::getAlBuffer() const
{
    return m_buffer;
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &m_buffer);
}

uint32_t AudioBuffer::convertToInt(char* buffer, size_t len)
{
    int32_t val = 0;
    memcpy(&val, buffer, len);
    return val;
}

AudioBuffer::AudioBuffer()
    : m_buffer(0)
{
}
