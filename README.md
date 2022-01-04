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
./ripple_simulation -s <surface_size> -i <max_iter> -t <thread_num>
```

## Experiment

### Different surface size & iterations?

- `./test_all.sh <surface_size> <iterations>`
- This will generate `report_<surface_size>_<iterations>.txt`, which is CSV format. 

### Use `for collapse` or not?

- `-s 800 -i 200 -t 4`
- for collapse(2)
    - Average execution time: 4.23319 ms
    - Minimum execution time: 3.41811 ms
    - Maximum execution time: 22.4012 ms
- for
    - Average execution time: 10.7506 ms
    - Minimum execution time: 10.2692 ms
    - Maximum execution time: 30.0684 ms

