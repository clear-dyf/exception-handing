#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define BUFSiZE  1024
//ʵ���ļ��Ķ����ƿ���
int copyfile2(const char* dest, const char* src) {
	FILE* fp1 = NULL, * fp2 = NULL;

	//ͨ��throw��������һ���쳣��������
	//throw 0.01f;
	//rb ֻ����ʽ��һ���������ļ�, ֻ�����ȡ����
	//fopen_s(&fp1, "src.txt", "rb");
	fopen_s(&fp1, src, "rb");

	if (fp1 == NULL) {
		throw new string("�ļ�������:");
	}

	//wb ��ֻд�ķ�ʽ�򿪻��½�һ���������ļ�,ֻ����д����.
	fopen_s(&fp2, dest, "wb");
	if (fp2 == NULL) {
		throw -2;
	}

	char buffer[BUFSiZE];
	int readlen, writelen;

	//readlen = fread(buffer, 1, BUFSiZE, fp1);//��ȡ�ļ��е�����,���Ұ����ݳ���(�ֽ���)���浽readlen
	//while (readlen > 0) {//���ȴ���0ʱѭ��,����һ����������ѭ��

	while ((readlen = fread(buffer, 1, BUFSiZE, fp1)) > 0) {
		writelen = fwrite(buffer, 1, readlen, fp2);
		if (readlen != writelen) {
			throw -3;
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

int copyfile1(const char* dest, const char* src) {
	try {
		copyfile2(dest, src);
	}catch (float e) {
		//throw;
		printf("copyfile1 - catch ...\n");
		throw;
	}

	return 0;
}

void main() {
	int ret = 0;

	//����Ҫ��׽�쳣�ĵط�,�������׳��쳣�ĳ����Ƕ��try��֮��
	//�������ĳ���˳��ִ�е���try���,Ȼ��ִ��try��{}�ڵı�����
	//����ڱ�����ִ���ڼ�û�������쳣,��ô����try����catch�Ӿ�Ͳ�ִ��,
	//�����try����������һ��catch�Ӿ�����������ִ����ȥ
	try {  //������
		printf("��ʼִ�� copyfile1...\n");
		ret = copyfile1("c:/test/dest.txt", "c:/test/src.txt");
		printf("ִ�� copyfile1  ���\n");

		//catch�Ӿ䰴����try�����ֵ�˳�򱻼��,
		//ƥ���catch�Ӿ佫���񲢰�catch�Ӿ��еĴ��봦���쳣(����������쳣)
	}catch (int error) {
		printf("�����쳣��: %d\n", error);
	}
	catch (string* error) {
		printf("��׽���ַ����쳣: %s\n", error->c_str());
		delete error;
	}catch (float error) {
		printf("�����쳣�� ! %f\n", error);
	}catch (...) {//ͨɱ����
		printf("catch ...\n");
	}

	//���û���ҵ�ƥ��,��ȱ�ٹ��ܵ���abort��ֹ����.

	system("pause");
	return;
}