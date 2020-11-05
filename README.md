# Master's Degree in Video game programming at U-Tad
## Audio Programming

Practices for the subject Audio Programming.

* Practice 1: Buffer reproduction.
* Practice 2: Doppler effect.

Every practice is an improvement from the last one so a lot of the code is reused.
But you should look at it closely because sometimes although it's really similar it has a little change.

### Instructions to compile and run the code
* Folder structure must be:
  * data
  * lib
  * openal
  * project
  * src
* Lib folder outside the practices contains the glfw library so it must be **included and combined** within the lib folder in **every practice** (I've uploaded it this way not to upload the library twice). **stb_image.h**, **stb_truetype.h** and **litegfx.h** must be combined as well.
* The **openal** folder outside the practices has to be copied inside them as shown in the above structure.
* After compiling the code, you have to move the **OpenAL32.dll** inside the generated Debug or Release folder.
* To run the code, be sure to **compile it for x82**. Any other way it will fail.
