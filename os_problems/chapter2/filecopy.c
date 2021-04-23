/* filecopy.c */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>
#include <errno.h>
#define MODE 0666
#define BUF_SIZE 4096

int main(int argc, const char *argv[])
{
    char src_name[PATH_MAX], dst_name[PATH_MAX], buffer[BUF_SIZE];
    int src, dst, in, out;

    // Get user inputs
    printf("source file: ");
    scanf("%s", src_name);
    printf("destination file: ");
    scanf("%s", dst_name);

    // Open files
    src = open(src_name, O_RDONLY);
    if (src < 0)
    {
        perror("Failed");
        return 1;
    }
    dst = open(dst_name, O_WRONLY | O_CREAT | O_EXCL, MODE);
    if (dst < 0)
    {
        perror("Failed");
        return 1;
    }

    // Copy
    in = read(src, buffer, BUF_SIZE);
    while (in > 0)
    {
        out = write(dst, buffer, in);
        in = read(src, buffer, BUF_SIZE);
    }

    close(src);
    close(dst);
    return 0;
}