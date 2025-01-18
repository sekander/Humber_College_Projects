<h1>Graphics Programming</h1>

Introductory course to OpenGL and HLSL shader language. Accomplished loading 3D models using tinyOBJ, suceffully programmed models to retieve position, scale and oreintation from the cpu and compute on the shader code. Was able to load in multiple different type of shaders for OpenGL to accept.

<h2>Scene1</h2> 

Task for this assignment was to load in two lights into the scene using Phong Shading model. Required to create two light positions initialized on the cpu end and send the required information to the GPU as uniform variables. Stored all the light data (Diffuse, Specular and position) into a data structure, each light data was stored in an array which the shader code accepted.

<img src="images/FINAL-OpengGLFramework-Scene1.png" width="50%"></img> 


<h2>Scene2</h2>

In this assignment I would like you to place two eyes in the into the Skull.obj. The two eyes need to be parented to the skull such that when the head rotates the eyes move as well. You will need to implement the Trackball code to do the rotations or just use keyboard events. Be sure to scale the eyes to a reasonable size and translate them into the correct position.

<img src="images/FINAL-OpengGLFramework-Scene2.png" width="50%"></img> 

<h2>Scene3</h2>

The purpose of this assignment was to load in Skybox/environment map or cube map. A cube map can be loaded using all six faces of texture representing the scene's background image. The camera is placed in the origin, looking down the negative z-axis; as the camera changes its position, the cube map will follow and update its location.

<img src="images/FINAL-OpengGLFramework-Scene3.png" width="50%"></img> 


<h2>Scene4</h2>

The task for this assignment was to build reflection and refraction shaders loaded into a 3D model and have the correct behaviour implemented. 

<img src="images/FINAL-OpengGLFramework-Scene4.png" width="50%"></img> 

<h2>Scene5</h2>

For the final assignment, the 3D model is to manipulate all the vertices through time. The 3D model would continuously transform itself during runtime to produce a visual effect; this technique simulates specific environmental effects such as water currents or lava in the Scene. 

<img src="images/FINAL-OpengGLFramework-Scene5.png" width="50%"></img> 

