# Custom-2D-Physics-Engine
A Custom 2D Physics Engine written in C++, designed in a modular form such that the same code could be used to simulate in n-dimensions.

The engine seeks to demonstrate primarily physical properties of structurally static objects, although, in future projects, will be used to implement optical phenomena and dynamic object structures such as liquids, gasses, stress, tearing, and the like. Instances of this engine, however, will be able to simulate certain non-real properties, such as immobility (in particular regards to axles), or masslessness. A full list of engine functionalities can be found within its corresponding section.

## Visuals
![SoftBodySeptagon](https://user-images.githubusercontent.com/42471346/143506986-2c010932-3f43-4af1-811a-2f948a2f436b.gif)

## Installation

The graphics for this engine are handled using OpenGL, and the following instructions are for setting up the code in Windows. 

### Required packages:

* Minimalist GNU for Windows ([MinGW](https://sourceforge.net/projects/mingw/))

### Steps:

1. Install MinGW from the above link, and install the following packages from the installation tab labeled "Basic Setup". You can install all the packages listed there, as they only add MinGW support for Ada and Fortran.
   * mingw-developer-toolkit
   * mingw32-base
   * mingw32-gcc-g++
   * mingw32-gcc-objc
   * msys-base

2. Download this repository, and copy the files from the folders within the directory labeled "Dependencies" into their respective folders within your MinGW installation (e.g. files in the folder `/bin` are copied to `/MinGW/bin`). 

3. Add the path to your MinGW installation to your Path environment variable. To do so, open System Properties from the Control Panel and go to the Advanced tab, or search Path in the Windows search bar and select "Edit the system environment variables". Click "Environment Variables", and then select the Path variable. Click edit, then new, and then enter the path to the root directory of your MinGW installation.
   * You can verify that MinGW has been added to your Path environment variable by typing `path` into the command prompt, and confirming that the path has been added correctly

4. If launching via Visual Studio Code, edit the include path located in the file `/.vscode/c_cpp_properties.json`, and add the path to the include directory inside your MinGW installation (`/MinGW/include`).



## Future of the project


## License
[MIT](https://choosealicense.com/licenses/mit/)
