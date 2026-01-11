# BlackFade


![](./res/original/256x256.png)

## :sparkles:Features

- Turns the screen black.
- The black screen will exit upon any key press or mouse movement.
- It functions similarly to the Windows screensaver "Blank". (but not screen saver)

## :egg:Requirement

- Windows
- Visual Studio Build Tools

## :hatching_chick:Installation

In PowerShell

```powershell
cd BlackFade
mkdir build
cd build

cmake ..
cmake --build . --config Release
# It will be output to .\Release\BlackFade.exe
```

## :hatched_chick:Getting started


### Command Line Option

You can use the `--keep-awake` option to prevent the PC from sleeping or turning off the display, and to keep the black window open even after fade-in.

Example:

```
BlackFade.exe --keep-awake
```

Without this option, the window will close as usual when you press any key or move the mouse after fade-in.

## :chicken:FAQ

 :thinking:

## License

[MIT License](LICENSE) :copyright: [sAbIz](https://github.com/sabiz):jp:

