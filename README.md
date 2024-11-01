## Parallel Programming Class Project 🔍
<h2> Animation Project with ICBYTES </h2>
<p> For this project I used the ICBYTES library. The ICBYTES library is a simplified C++ library for developing GUI interfaces and graphics compatible with Visual Studio 2022, developed by the instructor of the parallel programming course.  It includes examples and various utilities for graphics programming that can be ideal for projects involving animations, interactive graphics, game development or diagnostic tools.</p>


## Requirements
To run this project, make sure the following requirements are met:

- **C++ compiler** (ex: Visual Studio 2022)
- **ICBYTES Library**: The project requires the ICBYTES library. [You can download it here](https://github.com/cembaykal/ICBYTES)

## Purpose of the Project
<p> - In the project, a dynamic environment is created, complete with a running animation of a character, a background scene and sound effects. The project aims to present an interactive animation by synchronizing both visual and auditory elements.</p>
<p> - The project aims to demonstrate the basic principles of animation, especially in game development, simulations and media projects.</p>

## Technical Details

- **Programming Language**: C++
- **Library**: ICBYTES - Used for image and sound processing.
- **Animation Structure**: Separate motion algorithms were defined for each character. Running speed and direction were adjusted according to the character's animation flow.
- **Background Layering**: The order of precedence between objects is set and the agent and dog characters move in front of the cow.

## Library and Tools

The **ICBYTES** library was used to manage the different elements of the animation:

- **Image Processing**: The movement animations of the characters are defined in terms of specific coordinates and frames.
- **Sound Playback**: UFO and cow sounds are played simultaneously in the background during the animation. This process aims to provide a more realistic experience to the user.

**Animation Flow and Speed Settings**: The movement speed of the characters and scene transition times are dynamically adjusted in the code. For example, while the agent character waits at the beginning, when the UFO reaches the middle of the average distance, it accelerates and starts running. Such flows are sensitive to events in the scene.

*Sound Effects**: Sound effects were played in parallel using the `ICBYTES` library. UFO and cow sounds played during the animation add atmosphere to the scene.

## Project video 

https://github.com/user-attachments/assets/cfd675c8-f6f7-48bd-ae51-f80f7d41c980

