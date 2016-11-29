# Linux Process Launcher
A program to run Linux programs and run again if they crashed.
This software re-run programs after they crash or closed. This program insure a program re-run immediately or after a desired delay.

# Build
mkdir build
cd build
cmake ..
make

# How To Use
If you want to launch program X, just pass using this command:

./ProcessLauncher -p X

If there is some parameters for program X, use like this:

./ProcessLauncher -p "X -a -b -c d"

If you want to re-run program after a delay, pass the delay time in Milli-second using this command:

./ProcessLauncher -p X -t 1000

If you want to run multiple programs, pass them to ProcessLauncher like this:

./ProcessLauncher -p X1 -t T1 -p X2 -t T2 -p X3 -p X4 -t T4
