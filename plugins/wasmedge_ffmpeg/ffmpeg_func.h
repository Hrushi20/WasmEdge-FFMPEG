#pragma once

#include "ffmpeg_base.h"
#include "runtime/callingframe.h"

namespace WasmEdge {
namespace Host {
    class WasmEdgeFfmpegAvFormatOpenInput 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvFormatOpenInput> {
    public:
        WasmEdgeFfmpegAvFormatOpenInput(WasmEdgeFfmpegEnvironmet &HostEnv)
            : WasmEdgeFfmpeg(HostEnv) {}
        Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t filePtr,uint32_t fileNameSize);
};
 
} // Host   
} // WasmEdge 