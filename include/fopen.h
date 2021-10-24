/**
 * @author Clark
 * @email haixuanwoTxh@gmail.com
 * @date 2021-10-24
 */

#ifndef FOPEN_H
#define FOPEN_H

#include <stdio.h>
#include <string>

class File
{
public:
    File(std::string &name);
    int file_read(unsigned char *buf, int len);
    int file_write(const unsigned char *buf, int len);
    int file_seek(int offset, int whence);
    ~File();
private:
    FILE *fp;
};

#endif

