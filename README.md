## [LFX Ffmpeg Plugin](https://github.com/WasmEdge/WasmEdge/issues/2689)

This repository is the solution to [Pretest #2703](https://github.com/WasmEdge/WasmEdge/discussions/2703). 

The solution is split into two repositories-
1. [WasmEdge-FFMPEG](https://github.com/Hrushi20/WasmEdge-FFMPEG) 
<br> Contains Ffmpeg Plugin that acts as a bridge between WasmEdge and Ffmpeg C API.

2. [ffmpeg-rust](https://github.com/Hrushi20/ffmpeg-rust)<br> Uses the WasmEdgeFfmpeg plugin to execute Ffmpeg C API functions.

The Ffmpeg plugin is compiled into a shared library and can then be used in wasmedge runtime.

The plugin uses two functions from FFMPEG C API ([libavformat/avformat.h](https://github.com/FFmpeg/FFmpeg/blob/master/libavformat/avformat.h))
- avformat_open_input 
- av_dump_format

Follow the below steps to compile and build ffmpeg shared library.

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
git clone https://github.com/Hrushi20/WasmEdge-FFMPEG.git
cmake -Bbuild -GNinja -DFFMPEG_INCLUDE=/usr/local/include -DFFMPEG_LIB=/usr/local/lib  .   
cmake --build build
```
The above command compiles and builds WasmEdge with the FFMPEG plugin. 

Check if `libwasmedgePluginWasmEdgeFfmpeg.so` (.dylib in MacOs) file is created at <br> `<path-to-WasmEdge-FFMPEG>/build/plugins/wasmedge_ffmpeg`. 
<br>If present, it means the plugin has been built successfully.

### 4. Testing the Plugin
To test the plugin, follow the steps in [ffmpeg-rust](https://github.com/Hrushi20/ffmpeg-rust) repository.

### Previous Work at WasmEdge
Created a POC to read Binlogs from MySql and Forward the logs to Kafka using WasmEdge <br>
[wasmedge-mysql-binlog-kafka](https://github.com/Hrushi20/wasmedge-mysql-binlog-kafka.git)