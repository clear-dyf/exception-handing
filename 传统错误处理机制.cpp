#include <stdio.h>
#include <stdlib.h>

#define BUFSiZE  1024
//实现文件的二进制拷贝
int copyfile(const char* dest, const char* src) {
	FILE* fp1 = NULL, * fp2 = NULL;

	//rb 只读方式打开一个二进制文件, 只允许读取数据
	//fopen_s(&fp1, "src.txt", "rb");
	fopen_s(&fp1, src, "rb");

	if (fp1 == NULL) {
		return -1;
	}

	//wb 以只写的方式打开或新建一个二进制文件,只允许写数据.
	fopen_s(&fp2, dest, "wb");
	if (fp2 == NULL) {
		return -2;
	}

	char buffer[BUFSiZE];
	int readlen, writelen;

	//readlen = fread(buffer, 1, BUFSiZE, fp1);//读取文件中的数据,并且把数据长度(字节数)保存到readlen
	//while (readlen > 0) {//长度大于0时循环,与上一句搭配造成死循环

	while ((readlen = fread(buffer, 1, BUFSiZE, fp1)) > 0) {
		writelen = fwrite(buffer, 1, readlen, fp2);
		if (readlen != writelen) {
			return -3;
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

void main() {
	int ret = 0;
	ret = copyfile("c:/test/dest.txt", "c:/test/src.txt");

	if (ret != 0) {
		switch (ret) {
		case	-1:
			printf("打开源文件失败 ! \n");
			break;
		case -2:
			printf("打开目标文件失败 ! \n");
			break;
		case -3:
			printf("拷贝文件出错 ! \n");
			break;
		default:
			printf("出现未知的情况 ! \n");
			break;
		}
	}
	system("pause");
	return;
}