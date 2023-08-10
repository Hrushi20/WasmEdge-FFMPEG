#pragma once

#include "ffmpeg_base.h"
#include "runtime/callingframe.h"


namespace WasmEdge {
namespace Host {

    class WasmEdgeFfmpegAvformatAllocContext 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvformatAllocContext> {
    public:
    WasmEdgeFfmpegAvformatAllocContext(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtx);
    };

    class WasmEdgeFfmpegAvformatOpenInput
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvformatOpenInput> {
    public:
    WasmEdgeFfmpegAvformatOpenInput(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtx,uint32_t buf,uint32_t buflen);
    };

    class WasmEdgeFfmpegAvformatFindStreamInfo
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvformatFindStreamInfo> {
    public:
    WasmEdgeFfmpegAvformatFindStreamInfo(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtx);
    };
 
    class WasmEdgeFfmpegAvCodecParameters
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvCodecParameters> {
    public:
    WasmEdgeFfmpegAvCodecParameters(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtx,uint32_t idx,uint32_t codexParamterPtr);
    };

    class WasmEdgeFfmpegAvcodecFindDecoder 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvcodecFindDecoder> {
    public:
    WasmEdgeFfmpegAvcodecFindDecoder(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t codecParamter,uint32_t avCodec);
    };

    class WasmEdgeFfmpegAvcodecAllocContext3
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvcodecAllocContext3> {
    public:
    WasmEdgeFfmpegAvcodecAllocContext3(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t avCodec,uint32_t avCodecContext);
    };

    class WasmEdgeFfmpegAvcodecParametersToContext 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvcodecParametersToContext> {
    public:
    WasmEdgeFfmpegAvcodecParametersToContext(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t codecParamter,uint32_t avCodecContext);
    };

    class WasmEdgeFfmpegAvcodecOpen2 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvcodecOpen2> {
    public:
    WasmEdgeFfmpegAvcodecOpen2(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t avCodec,uint32_t avCodecContext);
    };

    class WasmEdgeFfmpegAvFrameAlloc 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvFrameAlloc> {
    public:
    WasmEdgeFfmpegAvFrameAlloc(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t frame);
    };

    class WasmEdgeFfmpegAvPacketAlloc 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvPacketAlloc> {
    public:
    WasmEdgeFfmpegAvPacketAlloc(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t  packet);
    };

    class WasmEdgeFfmpegAvReadFrame 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvReadFrame> {
    public:
    WasmEdgeFfmpegAvReadFrame(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t  packet,uint32_t avFormatCtx);
    };

    class WasmEdgeFfmpegGetStreamIndex 
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegGetStreamIndex> {
    public:
    WasmEdgeFfmpegGetStreamIndex(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t  packet);
    };

    class WasmEdgeFfmpegAvcodecSendPacket
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvcodecSendPacket> {
    public:
    WasmEdgeFfmpegAvcodecSendPacket(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t  packet, uint32_t avCodecContext);
    };

    class WasmEdgeFfmpegAvcodecReceiveFrame
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvcodecReceiveFrame> {
    public:
    WasmEdgeFfmpegAvcodecReceiveFrame(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t packet, uint32_t avCodecContext);
    };

    class WasmEdgeFfmpegAvPacketUnref
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegAvPacketUnref> {
    public:
    WasmEdgeFfmpegAvPacketUnref(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t packet);
    };

    class WasmEdgeFfmpegFrameData
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegFrameData> {
    public:
    WasmEdgeFfmpegFrameData(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t frame,uint32_t data,uint32_t size);
    };

    class WasmEdgeFfmpegFrameDimension
        : public WasmEdgeFfmpeg<WasmEdgeFfmpegFrameDimension> {
    public:
    WasmEdgeFfmpegFrameDimension(WasmEdgeFfmpegEnvironmet &HostEnv)
        : WasmEdgeFfmpeg(HostEnv) {}
    Expect<uint32_t> body(const Runtime::CallingFrame &Frame,uint32_t frame,uint32_t data,uint32_t dataSize);
    };


} // Host   
} // WasmEdge 