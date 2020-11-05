#include "../openal/AL/alc.h"


#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <glfw3.h>
#include <sstream>
#include <vector>

#include <fstream>     
#include <iterator>

#include "audioBuffer.h"
#include "audioSource.h"
#include "listener.h"

using namespace std;


int main() {
    int WIDTH = 800;
    int HEIGHT = 600;

    if (glfwInit())
    {
        // Leer tiempo transcurrido
        double previousTime = glfwGetTime();

        // Crear ventana
        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica1", NULL, NULL);
        if (window)
        {
            // Crear contexto
            glfwMakeContextCurrent(window);

            ///////////////// Datos //////////////////
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

            AudioBuffer* audio = AudioBuffer::load("data/music.wav");
            AudioSource* source = new AudioSource(audio);
            Listener::GetInstance().Init();

            source->play();
            ///////////////////////////////////////////

			double fElapsedSeconds;
			// Bucle de pintado
			while (!glfwWindowShouldClose(window))
			{
				// Actualizar tiempo
				double currentTime = glfwGetTime();
				fElapsedSeconds = currentTime - previousTime;
				previousTime = currentTime;

				// Leer input
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
				{
                    source->setPosition(source->getPosX() + 0.05f * fElapsedSeconds, source->getPosY(), source->getPostZ());
				}
				else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
				{
                    source->setPosition(source->getPosX() - 0.05f * fElapsedSeconds, source->getPosY(), source->getPostZ());
				}
				else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
				{
                    source->setPitch(source->getPitch() + 0.5 * fElapsedSeconds);
				}
                else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
                {
                    source->setPitch(source->getPitch() - 0.5 * fElapsedSeconds);
                }

                // Procesar eventos
                glfwPollEvents();
			}

            // Eliminar sistema de audio
            delete source;
            delete audio;
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(Context);
            alcCloseDevice(Device);

            // Finalizar ejecucion
            glfwTerminate();
        }
    }

    return 0;
}
