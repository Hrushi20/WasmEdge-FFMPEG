## [LFX Ffmpeg Plugin](https://github.com/WasmEdge/WasmEdge/issues/2689)

This repository is the solution to [Pretest #2703](https://github.com/WasmEdge/WasmEdge/discussions/2703). 

The solution is split into two repositories-
1. [WasmEdge-FFMPEG](https://github.com/Hrushi20/WasmEdge-FFMPEG) 
<br> Contains Ffmpeg Plugin that acts as a bridge between WasmEdge and Ffmpeg C API.

2. [ffmpeg-rust](https://github.com/Hrushi20/ffmpeg-rust)<br> Uses the WasmEdgeFfmpeg Plugin and executes Ffmpeg C API functions.

The Ffmpeg plugin is compiled into a shared library and can then be used in wasmedge runtime.

The plugin contains few `libavcodec/avcodec.h`` functions from FFMPEG C API ([libavformat/avformat.h](https://github.com/FFmpeg/FFmpeg/blob/master/libavcodec/avcodec.h))
The test uses these functions to convert a YUV420P video into grayscale image frames.  

Follow the below steps to compile and build Ffmpeg shared library.

### 1. Install the dependencies-<br>

Ubuntu 20.04
```
sudo apt install -y \
   software-properties-common \
   cmake \
   libboost-all-dev

sudo apt install -y \
   llvm-12-dev \
   liblld-12-dev

sudo apt install -y gcc g++
sudo apt install -y clang-12
sudo apt-get install -y ninja-build
``` 
MacOs
```
brew install cmake ninja llvm
export LLVM_DIR="$(brew --prefix)/opt/llvm/lib/cmake"
export CC=clang
export CXX=clang++
```

### 2. Clone and Install FFMPEG Shared library
Ubuntu/MacOs
```
git clone https://git.ffmpeg.org/ffmpeg.git ffmpeg
cd ffmpeg
./configure --prefix=/usr/local --enable-gpl --enable-nonfree --enable-shared --disable-static
sudo make install
```

### 3. Clone WasmEdge-FFMPEG
```
git clone https://github.com/Hrushi20/WasmEdge-FFMPEG.git WasmEdgeFfmpeg
cd WasmEdgeFfmpeg
mkdir build && cd build 
cmake -DCMAKE_BUILD_TYPE=Release -GNinja -DFFMPEG_INCLUDE=/usr/local/include -DFFMPEG_LIB=/usr/local/lib  ..
ninja
sudo ninja install 
```
The above command compiles, builds and installs WasmEdge with the FFMPEG plugin. 

Check if `libwasmedgePluginWasmEdgeFfmpeg.so` (.dylib in MacOs) file is created at <br> `/usr/local/lib/wasmedge`. 
<br>If present, it means the plugin has been built successfully.

### 4. Testing the Plugin
To test the plugin, follow the steps in [ffmpeg-rust](https://github.com/Hrushi20/ffmpeg-rust) repository.

## Previous Work at WasmEdge
Created a POC to read Binlogs from MySql and Forward the logs to Kafka using WasmEdge <br>
[wasmedge-mysql-binlog-kafka](https://github.com/Hrushi20/wasmedge-mysql-binlog-kafka.git)

## Contact Me
Feel free to contact me-

- [LinkedIn](https://www.linkedin.com/in/hrushikesh-rao-7741311b0/)
- [Twitter](https://twitter.com/Hrushi2020)
- [Gmail](mailto:hrushikesh20thegreat@gmail.com)
