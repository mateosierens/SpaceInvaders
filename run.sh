mkdir build
cd build
cmake .. # Assuming cmakelist.txt is in parent directory
make
mv SpaceInvaders ../SpaceInvaders # Assuming spaceinvaders is the name of your executable
cd ../ # Move to your parent dir
./SpaceInvaders
