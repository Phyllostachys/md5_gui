#include <windows.h>
#include <cstdio>

#include <openssl/md5.h>

struct filedata {
    char filename[1024];
    unsigned char md5sum[MD5_DIGEST_LENGTH];
};

char *relativePath(char *filepath, int length) {
    char *temppath = &filepath[length - 1];
    while (temppath > filepath && *temppath != '\\') {
        temppath--;
    }
    if (*temppath == '\\') temppath++;
    return temppath;
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        return -1;
    }

    filedata filelist[10];
    int idx = 0;
    int max = argc - 1;
    for (int i = 1; i < argc; i++) {
        strncpy(filelist[idx].filename, argv[i], 1024);

        FILE *f = fopen(filelist[idx].filename, "rb");
        if (!f) {
            printf("Failed to open '%s'\n", filelist[idx++].filename);
            return -1;
        }

        size_t filelength;
        unsigned char *filebytes;

        fseek(f, 0, SEEK_END);  // seek to end
        filelength = ftell(f);
        filebytes = (unsigned char *)malloc(filelength);
        fseek(f, 0, SEEK_SET);  // seek to start
        fread(filebytes, sizeof(unsigned char), filelength, f);
        fclose(f);

        MD5((const unsigned char *)filebytes, filelength, filelist[idx].md5sum);
        free(filebytes);

        idx++;
    }

    char strbuf[2048];
    for (int i = 0; i < max; i++) {
        strncat(strbuf, relativePath(filelist[i].filename, strlen(filelist[i].filename)), 1024);
        strncat(strbuf, " -- ", 4);
        {
            char tempbuf[1024];
            snprintf(tempbuf, 1024, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                     filelist[i].md5sum[0], filelist[i].md5sum[1], filelist[i].md5sum[2], filelist[i].md5sum[3],
                     filelist[i].md5sum[4], filelist[i].md5sum[5], filelist[i].md5sum[6], filelist[i].md5sum[7],
                     filelist[i].md5sum[8], filelist[i].md5sum[9], filelist[i].md5sum[10], filelist[i].md5sum[11],
                     filelist[i].md5sum[12], filelist[i].md5sum[13], filelist[i].md5sum[14], filelist[i].md5sum[15]);
            strncat(strbuf, tempbuf, 1024);
        }
        strncat(strbuf, "\n", 1);
    }
    MessageBoxA(nullptr, strbuf, "MD5 Sum", MB_OK);

    return 0;
}
