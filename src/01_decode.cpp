/**
 * @author Clark
 * @email haixuanwoTxh@gmail.com
 * @date 2021-10-24
 */

#include "common.h"
#include "fopen.h"

/**
 * @brief 读取编码视频数据，解码为yuv，保存到文件
 */
class Decode
{
public:
    Decode(std::string &inputFileName, std::string &outputFileName)
    {
        int ret=0;//默认返回值

        yuvFrame = av_frame_alloc();

        file = new File(outputFileName);

        std::cout<<"start decode:"<<inputFileName<<" "<<outputFileName<<std::endl;

        do {
            // 创建AVFormatContext结构体
            // 分配一个AVFormatContext，FFMPEG所有的操作都要通过这个AVFormatContext来进行
            fmtCtx = avformat_alloc_context();

            if ((ret=avformat_open_input(&fmtCtx, inputFileName.c_str(), NULL, NULL)) != 0) {
                printf("cannot open video file\n");
                break;
            }

            // 获取视频流信息
            if ((ret=avformat_find_stream_info(fmtCtx, NULL)) < 0) {
                printf("cannot retrive video info\n");
                break;
            }

            // 查找视频类型的流
            videoStreamIndex = -1;
            for (unsigned int i = 0; i < fmtCtx->nb_streams; i++) {
                if (fmtCtx->streams[ i ]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                    videoStreamIndex = i;
                    break;
                }
            }

            //如果videoStream为-1 说明没有找到视频流
            if (videoStreamIndex == -1) {
                printf("cannot find video stream\n");
                break;
            }

            //打印输入和输出信息：长度 比特率 流格式等
            av_dump_format(fmtCtx, 0, inputFileName.c_str(), 0);

            // 查找解码器
            avCodecPara = fmtCtx->streams[videoStreamIndex]->codecpar;
            const AVCodec *codec = avcodec_find_decoder(avCodecPara->codec_id);
            if (codec == NULL) {
                printf("cannot find decoder\n");
                break;
            }

            // 根据解码器参数来创建解码器内容
            codecCtx = avcodec_alloc_context3(codec);
            avcodec_parameters_to_context(codecCtx, avCodecPara);
            if (codecCtx == NULL) {
                printf("Cannot alloc context.");
                break;
            }

            // 打开解码器
            if ((ret=avcodec_open2(codecCtx, codec, NULL)) < 0) {
                printf("cannot open decoder\n");
                break;
            }

            width=codecCtx->width;
            height=codecCtx->height;

            pkt = av_packet_alloc();
            av_new_packet(pkt, codecCtx->width * codecCtx->height);

            //读取视频数据，解码为YUV，存入文件
            while (av_read_frame(fmtCtx, pkt) >= 0) {
                if (pkt->stream_index == videoStreamIndex){
                    if (avcodec_send_packet(codecCtx, pkt) == 0){
                        while (avcodec_receive_frame(codecCtx, yuvFrame) == 0){
                            // yuv420p
                            file->file_write(yuvFrame->data[0], width*height);      // y
                            file->file_write(yuvFrame->data[1], width*height/4);    // u
                            file->file_write(yuvFrame->data[2], width*height/4);    // v
                        }
                    }
                }
                av_packet_unref(pkt);
            }
        }while(0);
    }

    ~Decode()
    {
        av_packet_free(&pkt);
        avcodec_close(codecCtx);
        avcodec_parameters_free(&avCodecPara);
        //avformat_close_input(&fmtCtx);
        //avformat_free_context(fmtCtx);
        av_frame_free(&yuvFrame);

        delete file;
    }
private:
    AVFormatContext *fmtCtx;
    AVPacket *pkt;
    AVCodecContext *codecCtx;
    AVCodecParameters *avCodecPara;
    AVFrame *yuvFrame;

    int videoStreamIndex;   // 视频流所在流序列中的索引
    int width;
    int height;

    File *file;
};

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("please input infile and outfile\n");
        return -1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    Decode decode(inputFileName, outputFileName);

    return 0;
}
