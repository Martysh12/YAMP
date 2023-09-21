<div align="center">

# YAMP
YAMP is a yam amp.

</div>

## History
YAMP (or "modplay") was originally made on my phone to test [libmodplug](https://github.com/Konstanty/libmodplug).  
After succeeding, I started adding more and more features (like argument parsing using argp, song information, UIs and [libopenmpt](https://lib.openmpt.org/libopenmpt/)).  
Eventually I realized that this is a pretty cool project, so I converted the folder to a git repo and uploaded it to GitHub.

## Building
To build YAMP, create a directory named `build` inside the repository, and enter it:
```sh
mkdir build
cd build
```
Create a Makefile using `cmake`:
```sh
cmake ..
```
And now compile it:
```sh
make
```

## Usage
To play a file, just execute `yamp module_file.mod`.
For help with different arguments, run `yamp --help`.

## Screenshots
<img
    src = 'doc/images/screenshot_termux.png'
    width = 250
/>
<img
    src = 'doc/images/screenshot_pc.png'
    width = 512
/>
<br>
