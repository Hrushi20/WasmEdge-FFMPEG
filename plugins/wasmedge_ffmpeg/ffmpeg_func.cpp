// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2023 Second State INC

#include "ffmpeg_func.h"
#include "common/defines.h"
extern "C" {
    #include "libavcodec/avcodec.h"
}

#include <string>
#include <vector>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"


namespace WasmEdge {
namespace Host {


// Using 100 as error code for now.

Expect<uint32_t> WasmEdgeFfmpegAvformatAllocContext::body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtx) {
    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* avFormatCtxPtr =  MemInst->getPointer<uint32_t *>(avFormatCtx);
    AVFormatContext* avFormatContext; 

    avFormatContext = avformat_alloc_context();
    Env.avFormatContextArr.push_back(avFormatContext);

    *avFormatCtxPtr = Env.avFormatContextArr.size() - 1;
    return !avFormatContext ? 100 : 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvformatOpenInput::body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtx, uint32_t file,uint32_t fileSize) {

    std::string targetFileName;
    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* avFormatCtxPtr =  MemInst->getPointer<uint32_t *>(avFormatCtx);
    char* buf = MemInst->getPointer<char*>(file);

    AVFormatContext* avFormatContext = Env.avFormatContextArr.at(*avFormatCtxPtr);
    
    std::copy_n(buf,fileSize,std::back_inserter(targetFileName));

    if(avformat_open_input(&avFormatContext,targetFileName.c_str(),NULL,NULL) != 0)
        return 100;

    return 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvformatFindStreamInfo::body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtx) {

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* avFormatCtxPtr =  MemInst->getPointer<uint32_t *>(avFormatCtx);

    AVFormatContext* avFormatContext = Env.avFormatContextArr.at(*avFormatCtxPtr);
    if(avformat_find_stream_info(avFormatContext,NULL)){
        return 100;
    }

    // For sake of example returing the number of stream.
    return avFormatContext->nb_streams;
}

Expect<uint32_t> WasmEdgeFfmpegAvCodecParameters::body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtx,uint32_t idx,uint32_t codecParameter) {

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* avFormatCtxPtr =  MemInst->getPointer<uint32_t *>(avFormatCtx);
    uint32_t* codecParameterPtr =  MemInst->getPointer<uint32_t *>(codecParameter);

    AVFormatContext* avFormatContext = Env.avFormatContextArr.at(*avFormatCtxPtr);

    AVCodecParameters* pLocalCodecParameters = avFormatContext->streams[idx]->codecpar;

    Env.avCodecParameters.push_back(pLocalCodecParameters);
    *codecParameterPtr = Env.avCodecParameters.size() - 1;


    printf("AVStream -> time_base before open coded %d/%d\n",avFormatContext->streams[idx]->time_base.num,avFormatContext->streams[idx]->time_base.den);
    printf("AVStream -> start_time %lld\n",avFormatContext->streams[idx]->start_time);
    printf("AVStream -> duration %lld\n",avFormatContext->streams[idx]->duration);

    if(pLocalCodecParameters == NULL)
        return 100;

    return 0; 
}
Expect<uint32_t> WasmEdgeFfmpegAvcodecFindDecoder::body(const Runtime::CallingFrame &Frame,uint32_t codecParamter,uint32_t avCodecInput){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* avCodecPtr =  MemInst->getPointer<uint32_t *>(avCodecInput);
    uint32_t* codecParameterPtr =  MemInst->getPointer<uint32_t *>(codecParamter);

    AVCodecParameters* pLocalCodecParameters = Env.avCodecParameters.at(*codecParameterPtr);
    const AVCodec* pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);
    Env.avCodec.push_back(pLocalCodec);

    *avCodecPtr = Env.avCodec.size() - 1;

    if(pLocalCodec == NULL)
        return 100;

    // Could be audio as well. Neglicting it. 
    return pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO ? 0 : 
    pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO ? 1: 100;
}

Expect<uint32_t> WasmEdgeFfmpegAvcodecAllocContext3::body(const Runtime::CallingFrame &Frame,uint32_t avCodec,uint32_t avCodecContext){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* avCodecPtr =  MemInst->getPointer<uint32_t *>(avCodec);
    uint32_t* avCodecContextPtr =  MemInst->getPointer<uint32_t *>(avCodecContext);
    const AVCodec* codec = Env.avCodec.at(*avCodecPtr);


    AVCodecContext* pCodecContext = avcodec_alloc_context3(codec);
    // Add to array. Return.
    Env.codecCtx.push_back(pCodecContext);
    *avCodecContextPtr = Env.codecCtx.size() - 1; 

    return !pCodecContext ? 100 : 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvcodecParametersToContext::body(const Runtime::CallingFrame &Frame,uint32_t codecParamter,uint32_t avCodecContext){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* codecParamterPtr =  MemInst->getPointer<uint32_t *>(codecParamter);
    uint32_t* avCodecContextPtr =  MemInst->getPointer<uint32_t *>(avCodecContext);
    AVCodecContext* codec = Env.codecCtx.at(*avCodecContextPtr);
    AVCodecParameters* parameters = Env.avCodecParameters.at(*codecParamterPtr);

    return avcodec_parameters_to_context(codec,parameters) < 0 ? 100 : 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvcodecOpen2::body(const Runtime::CallingFrame &Frame,uint32_t avCodec,uint32_t avCodecContext){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* codecParameterPtr =  MemInst->getPointer<uint32_t *>(avCodec);
    uint32_t* avCodecContextPtr =  MemInst->getPointer<uint32_t *>(avCodecContext);

    AVCodecContext* ctx = Env.codecCtx.at(*avCodecContextPtr);
    const AVCodec* codec = Env.avCodec.at(*codecParameterPtr);

    return avcodec_open2(ctx,codec,NULL) < 0 ? 100 : 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvFrameAlloc::body(const Runtime::CallingFrame &Frame,uint32_t frame){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* framePtr =  MemInst->getPointer<uint32_t *>(frame);

    AVFrame* pFrame = av_frame_alloc();
    Env.frame.push_back(pFrame);
    *framePtr = Env.frame.size() - 1;

    return !pFrame ? 100 : 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvPacketAlloc::body(const Runtime::CallingFrame &Frame,uint32_t packet){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* packetPtr =  MemInst->getPointer<uint32_t *>(packet);

    AVPacket* pPacket = av_packet_alloc();
    Env.packet.push_back(pPacket);
    *packetPtr = Env.packet.size() - 1;

    return !pPacket ? 100 : 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvReadFrame::body(const Runtime::CallingFrame &Frame,uint32_t packet,uint32_t avFormatCtx){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* packetPtr =  MemInst->getPointer<uint32_t *>(packet);
    uint32_t* avFormatCtxPtr = MemInst->getPointer<uint32_t *>(avFormatCtx);

    return av_read_frame(Env.avFormatContextArr.at(*avFormatCtxPtr),Env.packet.at(*packetPtr));
}

Expect<uint32_t> WasmEdgeFfmpegGetStreamIndex::body(const Runtime::CallingFrame &Frame,uint32_t packet){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* packetPtr =  MemInst->getPointer<uint32_t *>(packet);

    AVPacket* pkt = Env.packet.at(*packetPtr);
    return pkt->stream_index;
}

Expect<uint32_t> WasmEdgeFfmpegAvcodecSendPacket::body(const Runtime::CallingFrame &Frame,uint32_t packet,uint32_t avCodecContext){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* packetPtr =  MemInst->getPointer<uint32_t *>(packet);
    uint32_t* avCodecContextPtr = MemInst->getPointer<uint32_t *>(avCodecContext);

    const AVPacket* pkt = Env.packet.at(*packetPtr);
    int res = avcodec_send_packet(Env.codecCtx.at(*avCodecContextPtr),pkt);
    if (res < 0) return 100;
    return res;
}

Expect<uint32_t> WasmEdgeFfmpegAvcodecReceiveFrame::body(const Runtime::CallingFrame &Frame,uint32_t frame,uint32_t avCodecContext){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* framePtr =  MemInst->getPointer<uint32_t *>(frame);
    uint32_t* avCodecContextPtr = MemInst->getPointer<uint32_t *>(avCodecContext);

    int res = avcodec_receive_frame(Env.codecCtx.at(*avCodecContextPtr),Env.frame.at(*framePtr));
    if(res == AVERROR(EAGAIN) || res == AVERROR(AVERROR_EOF))
        return 20;
    if(res < 0)
        return 100;
    return 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvPacketUnref::body(const Runtime::CallingFrame &Frame,uint32_t packet){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* packetPtr =  MemInst->getPointer<uint32_t *>(packet);

    AVPacket* pkt = Env.packet.at(*packetPtr);
    av_packet_unref(pkt);
    return 0;
}

Expect<uint32_t> WasmEdgeFfmpegFrameData::body(const Runtime::CallingFrame &Frame,uint32_t frame,uint32_t data,uint32_t size){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* framePtr =  MemInst->getPointer<uint32_t *>(frame);
    auto buffer =  MemInst->getSpan<uint8_t>(data,size);

    AVFrame* f = Env.frame.at(*framePtr);
    uint8_t* buf = f->data[0];

    memmove(buffer.data(),buf,size);

    // Setting the rust value to the data.
    return 0;
}

// // Just for the sake of example. So such API is present in ffmpeg.
Expect<uint32_t> WasmEdgeFfmpegFrameDimension::body(const Runtime::CallingFrame &Frame,uint32_t frame,uint32_t dimensions,uint32_t size){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* framePtr =  MemInst->getPointer<uint32_t *>(frame);
    // uint32_t* dimensionPtr =  MemInst-<uint32_t *>(dimensions);
    uint32_t* dataSizePtr =  MemInst->getPointer<uint32_t *>(size);

    AVFrame* f = Env.frame.at(*framePtr);

    // First is size of row, 2nd is no.of columns, 3rd is no.of rows.
    int dim[] = {f->linesize[0],f->width,f->height};
    auto dimemsionPtr = MemInst->getSpan<int>(dimensions,3);

    memmove(dimemsionPtr.data(),dim,3 * sizeof(int));

    if(dataSizePtr)
        return 0;

    return 100;
}
Expect<uint32_t> WasmEdgeFfmpegAvformatCloseInput::body(const Runtime::CallingFrame &Frame,uint32_t avFormatId){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* avFormatPtr =  MemInst->getPointer<uint32_t *>(avFormatId);

    AVFormatContext* avFormatCtx = Env.avFormatContextArr.at(*avFormatPtr);
    Env.avFormatContextArr.erase(Env.avFormatContextArr.begin() + *avFormatPtr);
    avformat_free_context(avFormatCtx);
    return 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvPacketFree::body(const Runtime::CallingFrame &Frame,uint32_t packetId){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* packetPtr =  MemInst->getPointer<uint32_t *>(packetId);

    AVPacket* packet = Env.packet.at(*packetPtr);
    Env.packet.erase(Env.packet.begin() + *packetPtr);
    av_packet_free(&packet);
    return 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvFrameFree::body(const Runtime::CallingFrame &Frame,uint32_t frameId){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* framePtr =  MemInst->getPointer<uint32_t *>(frameId);

    AVFrame* frame = Env.frame.at(*framePtr);
    Env.frame.erase(Env.frame.begin() + *framePtr);
    av_frame_free(&frame);
    return 0;
}

Expect<uint32_t> WasmEdgeFfmpegAvcodecFreeContext::body(const Runtime::CallingFrame &Frame,uint32_t codecCtxId){

    auto MemInst = Frame.getMemoryByIndex(0);
    uint32_t* codecCtxPtr =  MemInst->getPointer<uint32_t *>(codecCtxId);

    AVCodecContext* ctx = Env.codecCtx.at(*codecCtxPtr);
    Env.avCodec.erase(Env.avCodec.begin() + *codecCtxPtr);
    avcodec_free_context(&ctx);
    return 0;
}

} // Host
} // WasmEdge