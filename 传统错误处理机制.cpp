#include <stdio.h>
#include <stdlib.h>

#define BUFSiZE  1024
//ʵ���ļ��Ķ����ƿ���
int copyfile(const char* dest, const char* src) {
	FILE* fp1 = NULL, * fp2 = NULL;

	//rb ֻ����ʽ��һ���������ļ�, ֻ�����ȡ����
	//fopen_s(&fp1, "src.txt", "rb");
	fopen_s(&fp1, src, "rb");

	if (fp1 == NULL) {
		return -1;
	}

	//wb ��ֻд�ķ�ʽ�򿪻��½�һ���������ļ�,ֻ����д����.
	fopen_s(&fp2, dest, "wb");
	if (fp2 == NULL) {
		return -2;
	}

	char buffer[BUFSiZE];
	int readlen, writelen;

	//readlen = fread(buffer, 1, BUFSiZE, fp1);//��ȡ�ļ��е�����,���Ұ����ݳ���(�ֽ���)���浽readlen
	//while (readlen > 0) {//���ȴ���0ʱѭ��,����һ����������ѭ��

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
			printf("��Դ�ļ�ʧ�� ! \n");
			break;
		case -2:
			printf("��Ŀ���ļ�ʧ�� ! \n");
			break;
		case -3:
			printf("�����ļ����� ! \n");
			break;
		default:
			printf("����δ֪����� ! \n");
			break;
		}
	}
	system("pause");
	return;
}