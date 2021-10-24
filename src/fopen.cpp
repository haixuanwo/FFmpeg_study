/**
 * @author Clark
 * @email haixuanwoTxh@gmail.com
 * @date 2021-10-24
 */

#include "fopen.h"
#include <stdlib.h>
#include <unistd.h>

File::File(std::string &name)
{
    std::string mode;
    if (0 == access(name.c_str(), F_OK))
    {
        mode = "r+";
    }
    else
    {
        mode = "w+";
    }

    fp = fopen(name.c_str(), mode.c_str());
    if (nullptr == fp)
    {
        perror("fopen fail");
        exit(-1);
    }
}

int File::file_read(unsigned char *buf, int len)
{
    return fread(buf, len, 1, fp);
}

int File::file_write(const unsigned char *buf, int len)
{
    return fwrite(buf, len, 1, fp);
}

int File::file_seek(int offset, int whence)
{
    return fseek(fp, offset, whence);
}

File::~File()
{
    fclose(fp);
}
