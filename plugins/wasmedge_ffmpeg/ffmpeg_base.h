#pragma once

#include "ffmpeg_env.h"
#include "runtime/hostfunc.h"

namespace WasmEdge {
namespace Host{

template <typename T>
class WasmEdgeFfmpeg : public Runtime::HostFunction<T> {
public:
   WasmEdgeFfmpeg(WasmEdgeFfmpegEnvironmet &HostEnv)
        : Runtime::HostFunction<T>(0), Env(HostEnv) {}

    protected:
        WasmEdgeFfmpegEnvironmet &Env;
};
    
} // namespace Host
} // namespace WasmEdge