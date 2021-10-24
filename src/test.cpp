/**
 * @author Clark
 * @email haixuanwoTxh@gmail.com
 * @date 2021-10-24
 */

#include <stdio.h>
#include <string>
#include "test.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libavutil/ffversion.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
}

Test::Test(std::string &fileName)
{
    int ret=0;

    AVFormatContext *fmt_ctx = avformat_alloc_context(); // 创建格式对象并初始化
    // const char* fileName="/home/txh/technical/nginx-rtmp/video/gaint1.mp4";

    do{
        // 打开输入文件
        ret = avformat_open_input(&fmt_ctx, fileName.c_str(), NULL, NULL);
        if (ret < 0)
        {
            printf("avformat_open_input fail\n");
            break;
        }

        // 查找流信息（音频流和视频流）
        if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
            printf("Cannot find stream information\n");
            break;
        }

        // 输出视频信息
        av_dump_format(fmt_ctx, 0, fileName.c_str(), 0);
    } while(0);

    // 关闭输入文件
    avformat_close_input(&fmt_ctx);
}

Test::~Test()
{

}
