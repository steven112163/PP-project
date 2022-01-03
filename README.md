# PP-project

Parallel Programming Final Project  
📌 Title: `Ripple Simulation Based on OpenGL`

## Prerequisites

### Install Packages

```shell=
sudo apt update
sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev libglm-dev cmake xorg-dev pkg-config
```

### Install GLFW

```shell=
cd ~
git clone https://github.com/glfw/glfw.git
cd glfw
cmake -S . -B build
cd build
make
sudo make install
```

### Install GLAD

1. Head on
   to [link](https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on)
   and click *Generate*.
2. Download `glad.zip`.
3. Execute following commands:

```shell=
cd ~/Downloads/
unzip glad.zip -d glad
rm glad.zip
sudo cp -R glad/include/* /usr/local/include/
```

### Run

```bash
./ripple_simulation -s <surface_size> -d <damp> -i <max_iter> -t <thread_num>
```