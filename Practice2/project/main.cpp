#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"


#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#define _CRT_SECURE_NO_WARNINGS

#ifndef STB_IMAGE_H
#define STB_IMAGE_H
#include <stb_image.h>
#endif

#include <glfw3.h>
#include <sstream>
#include <iostream>
#include <vector>
 
#include <iterator>

#include "audioBuffer.h"
#include "audioSource.h"
#include "listener.h"

#include "vec2.h"
#include "font.h"
#include "sprite.h"
#ifndef LITE
#include "litegfx.h"
#endif // !LITE
#include "world.h"

using namespace std;

// Funcion para actualizar el tamaño de la ventana
void updateViewportSize(GLFWwindow* _Window, Vec2& _WindowSize_)
{
    int iNewWidth, iNewHeight;
    glfwGetWindowSize(_Window, &iNewWidth, &iNewHeight);
    if (iNewWidth != _WindowSize_.GetXCoor() || iNewHeight != _WindowSize_.GetYCoor())
    {
        _WindowSize_.SetXCoor(iNewWidth);
        _WindowSize_.SetYCoor(iNewHeight);
        lgfx_setviewport(0, 0, static_cast<int>(_WindowSize_.GetXCoor()), static_cast<int>(_WindowSize_.GetYCoor()));
        lgfx_setresolution(static_cast<int>(_WindowSize_.GetXCoor()), static_cast<int>(_WindowSize_.GetYCoor()));
    }
}

void updateCarSprite(Sprite& sprite, float deltaSeconds)
{
    Vec2 pivot = *static_cast<Vec2*>(sprite.getUserData());
    Vec2 currentPos = sprite.getPosition() - pivot;
    float angle = 30 * deltaSeconds;
    float newX = (currentPos.GetXCoor() * cos(angle * PI / 180) + currentPos.GetYCoor() * -sin(angle * PI / 180));
    float newY = (currentPos.GetXCoor() * sin(angle * PI / 180) + currentPos.GetYCoor() * cos(angle * PI / 180));
    sprite.setPosition(pivot + Vec2(newX, newY));
    sprite.setCollisionType(sprite.getCollisionType());
}

int main() {
    Vec2 vWindowSize(800.f, 800.f);

    if (glfwInit())
    {
        // Leer tiempo transcurrido
        double previousTime = glfwGetTime();

        // Crear ventana
        GLFWwindow* window = glfwCreateWindow(vWindowSize.GetXCoor(), vWindowSize.GetYCoor(), "Practica2", NULL, NULL);
        if (window)
        {
            // Crear contexto
            glfwMakeContextCurrent(window);

            // Inicializar sistema de audio
            ALCdevice* Device = alcOpenDevice(nullptr);
            ALCcontext* Context = nullptr;
            if (Device)
            {
                Context = alcCreateContext(Device, nullptr);
                alcMakeContextCurrent(Context);
            }
            else
            {
                printf("Error: No audio device detected");
                return -1;
            }

            ///////////////// Datos //////////////////
            // Sprite and sounds
            vector<ltex_t*> textures = { LoadTexture("data/circle.png"), LoadTexture("data/car.png") };
            AudioBuffer* audio = AudioBuffer::load("data/engine.wav");

            // Listener sprite
            Sprite* listenerSprite = new Sprite(textures[0]);
            listenerSprite->setScale(Vec2(2.f, 2.f));
            listenerSprite->setCollisionType(Sprite::COLLISION_CIRCLE);

            // Car sprite
            Sprite* carSprite = new Sprite(textures[1]);
            carSprite->setScale(Vec2(0.5f, 0.5f));
            carSprite->setPosition(Vec2(vWindowSize.GetXCoor() / 4.f, vWindowSize.GetXCoor() / 2.f));
            carSprite->setCollisionType(Sprite::COLLISION_PIXELS);
            carSprite->setAudioSource(audio);
            Vec2 pivot(vWindowSize.GetXCoor() / 2.f, vWindowSize.GetYCoor() / 2.f);
            carSprite->setUserData(static_cast<void*>(&pivot)); // rotation pivot
            carSprite->setCallback(updateCarSprite);

            // Create world
            World* world = new World(0.9f, 0.85f, 0.9f);
            // Add sprites
            world->addSprite(*listenerSprite);
            world->addSprite(*carSprite);
            
            Listener::GetInstance().Init();
            Listener::GetInstance().setListenerPosition(400.f, 750.f, 0.f);

            carSprite->getAudioSource()->setGain(150.f);
            carSprite->getAudioSource()->setLooping(true);
            carSprite->getAudioSource()->setVelocity(30.f, 30.f, 0.f);
            carSprite->getAudioSource()->play();
            ///////////////////////////////////////////

            // Iniciar para pintado
            lgfx_setup2d(static_cast<int>(vWindowSize.GetXCoor()), static_cast<int>(vWindowSize.GetYCoor()));


			double fElapsedSeconds;
			// Bucle de pintado
			while (!glfwWindowShouldClose(window))
			{
				// Actualizar tiempo
				double currentTime = glfwGetTime();
				fElapsedSeconds = currentTime - previousTime;
				previousTime = currentTime;

                Listener::GetInstance().setListenerVelocity(0.f, 0.f, 0.f);

				// Leer input
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
				{
                    //world->moveSprite(*listenerSprite, Vec2(80.f * static_cast<float>(fElapsedSeconds), 0));
                    Listener::GetInstance().setListenerPosition(Listener::GetInstance().getPosX() + 50.f * static_cast<float>(fElapsedSeconds), Listener::GetInstance().getPosY(), 0.f);
                    Listener::GetInstance().setListenerVelocity(50.f, 0.f, 0.f);
				}
				else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
				{
                    //world->moveSprite(*listenerSprite, Vec2(-80.f * static_cast<float>(fElapsedSeconds), 0.f));
                    Listener::GetInstance().setListenerPosition(Listener::GetInstance().getPosX() - 50.f * static_cast<float>(fElapsedSeconds), Listener::GetInstance().getPosY(), 0.f);
				    Listener::GetInstance().setListenerVelocity(-50.f, 0.f, 0.f);
				}

                ///////////////////////// Actualizar logica ///////////////////////////
                // Actualizar tamanio de pintada
                updateViewportSize(window, vWindowSize);

                // Actualizar world
                listenerSprite->setPosition(Vec2(Listener::GetInstance().getPosX(), Listener::GetInstance().getPosY()));
                world->update(static_cast<float>(fElapsedSeconds));

                //////////////////////// Actualizar pintada /////////////////////////////
                world->draw(vWindowSize);
                ///////////////////////////////////////////////////////////////////////

                // Intercambio de buffers
                glfwSwapBuffers(window);

                // Procesar eventos
                glfwPollEvents();
			}

            // Eliminamos la memoria reservada
            delete world;
            delete listenerSprite;
            delete carSprite;
            delete audio;

            for (ltex_t* tex : textures)
            {
                delete tex;
            }
            textures.clear();

            // Eliminar sistema de audio
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(Context);
            alcCloseDevice(Device);

            // Finalizar ejecucion
            glfwTerminate();
        }
    }

    return 0;
}
