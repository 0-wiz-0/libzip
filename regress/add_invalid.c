#include "zip.h"
#include "error.h"

char *prg;
#define BUFSIZE 65536

int
main(int argc, char *argv[])
{
    struct zip *zf, *destzf;
    
    prg = argv[0];
    
    if (argc != 3) {
	myerror(ERRDEF, "call with two options: src dest\n");
	return 1;
    }

    seterrinfo(NULL, argv[1]);
    if ((zf=zip_open(argv[1], 0))==NULL) {
	myerror(ERRZIPSTR, "can't open file: %s", zip_err_str[zip_err]);
	return 1;
    }

    seterrinfo(NULL, argv[2]);
    if ((destzf=zip_open(argv[2], ZIP_CREATE))==NULL) {
	myerror(ERRZIPSTR, "can't open file: %s", zip_err_str[zip_err]);
	return 1;
    }

    if (zip_add_zip(destzf, NULL, NULL, zf, 1, 0, 0) == -1)
	myerror(ERRZIPSTR, "can't add file to zip-file: %s", zip_err_str[zip_err]);

    if (zip_close(destzf)!=0) {
	myerror(ERRZIPSTR, "can't close file: %s", zip_err_str[zip_err]);
	return 1;
    }

    seterrinfo(NULL, argv[1]);
    if (zip_close(zf)!=0) {
	myerror(ERRZIPSTR, "can't close file %s", zip_err_str[zip_err]);
	return 1;
    }
    
    return 0;
}
