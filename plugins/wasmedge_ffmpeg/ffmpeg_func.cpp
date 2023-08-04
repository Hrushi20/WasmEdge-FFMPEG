// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2023 Second State INC

#include "ffmpeg_func.h"
#include "common/defines.h"
extern "C" {
    #include "libavformat/avformat.h"

}

#include <string>
#include <vector>


namespace WasmEdge {
namespace Host {

Expect<uint32_t>
WasmEdgeFfmpegAvFormatOpenInput::body(const Runtime::CallingFrame &Frame,uint32_t filePtr,uint32_t fileNameSize) {

        std::string TargetFileName;
        // Check memory instance from module.
        auto* MemInst = Frame.getMemoryByIndex(0);

        auto buf = MemInst->getPointer<char *>(filePtr);
        std::copy_n(buf,fileNameSize,std::back_inserter(TargetFileName));

        AVFormatContext* avFormatContext = Env.getCtx();
        if(avformat_open_input(&avFormatContext,TargetFileName.c_str(),0,0) < 0)
            return -1;

        av_dump_format(avFormatContext,0,TargetFileName.c_str(),0);
        return 1;
    }
} // Host
} // WasmEdge