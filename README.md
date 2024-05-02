# Technical Overview of 'Space-Wars'
1. [Technical Overview](#section-a)
2. [Simple Button Class](#section-b)
3. [Player Class](#section-c)
4. [Game Engine](#section-d)
4. [Game Controls](#section-e)

## Introduction

"Space-Wars" is a dynamic 2D game inspired by the classic title 'Spacewar!' developed in 1962. This project pays homage to the golden age of video games by skillfully fusing vintage components with cutting-edge game production methodologies. This technical documentation has been created to provide a thorough overview of the title by exploring its architecture and creative methods used during production.

# Technical Overview

### Main Menu<a name="section-a"></a>

The Main Menu serves as the entry point to the game, offering a user-friendly interface for navigation. It sets the tone for the game, combining aesthetic appeal with functionality.

### Simple Button Class<a name="section-b"></a>

The Simple Button Class is the fundamental component of the game's UI. This class handles different button states (idle, hover, and pressed) to provide visual feedback to the player. Each state is associated with distinct colors to display the button's current status. The detection method utilizes collision boundaries to determine if the mouse cursor is over the button and changes the button's state based on user input.

### Player Class<a name="section-c"></a>

The Player Class is a central component of the engine, responsible for creating and managing the user’s character within the game environment. It serves as the backbone for player interaction and character management in the game.

- **Initialization:** Sets up player properties such as health and score and initializes weapon states.
- **Movement Mechanics:** Implements dynamic player movement with acceleration features, responding to real-time user inputs.
- **Boundary Control:** Ensures the player remains within the gameplay area, repositioning them if they move off-screen.
- **Gameplay Integration:** Regularly updates player actions within the game's main loop, ensuring responsive and accurate gameplay.

### Game Engine<a name="section-d"></a>

The engine initializes critical components of the game such as the window, variables, and game states. This setup is crucial for the game's performance and visual rendering.

- **Window Management:** Creates and manages the game window, setting properties like size and frame rate limit.
- **State Management:** Handles various game states (such as the menu and gameplay states) using a stack structure.
- **Game Loop:** Runs the primary game loop, consisting of 'Think', 'RenderThink', and 'EventThink' methods. This loop continually updates and renders game elements, maintaining the flow of the game.
- **Delta Time Management:** Tracks the time elapsed between frames, ensuring smooth and consistent animations and movements, regardless of the hardware's performance.

## Game Controls<a name="section-e"></a>

The application offers a responsive control scheme designed to be simple yet effective, catering to both novice and experienced users.

- **Movement:** Navigate your spacecraft (Player Entity) using the following keys:
  - `W`: Move forward.
  - `S`: Move backward.
  - `A`: Steer left.
  - `D`: Steer right.
  
This setup allows for smooth and agile movements.

- **Primary Weapon:** Press the `Space` key to fire the primary weapon, ensuring quick and seamless interaction during gameplay.

- **Secondary Weapon:** Activate the secondary weapon by pressing the `Left Shift` key. This provides an alternative attack mode to enhance the gameplay dynamics.

- **Menu Access:** Pressing the `Escape` key allows players to access the main menu, enabling them to pause the game or adjust settings as needed.
