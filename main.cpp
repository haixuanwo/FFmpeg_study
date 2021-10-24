/**
 * @author Clark
 * @email haixuanwoTxh@gmail.com
 * @date 2021-10-24
 */

#include <stdio.h>
#include <iostream>
#include "test.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("please input a file name\n");
        return -1;
    }

    std::string fileName = argv[1];
    Test T(fileName);

	return 0;
}
