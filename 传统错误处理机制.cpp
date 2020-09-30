#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define BUFSiZE  1024
//实现文件的二进制拷贝
int copyfile2(const char* dest, const char* src) {
	FILE* fp1 = NULL, * fp2 = NULL;

	//通过throw操作创建一个异常对象并抛掷
	//throw 0.01f;
	//rb 只读方式打开一个二进制文件, 只允许读取数据
	//fopen_s(&fp1, "src.txt", "rb");
	fopen_s(&fp1, src, "rb");

	if (fp1 == NULL) {
		throw new string("文件不存在:");
	}

	//wb 以只写的方式打开或新建一个二进制文件,只允许写数据.
	fopen_s(&fp2, dest, "wb");
	if (fp2 == NULL) {
		throw -2;
	}

	char buffer[BUFSiZE];
	int readlen, writelen;

	//readlen = fread(buffer, 1, BUFSiZE, fp1);//读取文件中的数据,并且把数据长度(字节数)保存到readlen
	//while (readlen > 0) {//长度大于0时循环,与上一句搭配造成死循环

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

	//在需要捕捉异常的地方,将可能抛出异常的程序段嵌在try块之中
	//按正常的程序顺序执行到达try语句,然后执行try块{}内的保护段
	//如果在保护段执行期间没有引起异常,那么跟在try块后的catch子句就不执行,
	//程序从try块后跟随的最后一个catch子句后面的语句继续执行下去
	try {  //保护段
		printf("开始执行 copyfile1...\n");
		ret = copyfile1("c:/test/dest.txt", "c:/test/src.txt");
		printf("执行 copyfile1  完毕\n");

		//catch子句按其在try块后出现的顺序被检查,
		//匹配的catch子句将捕获并按catch子句中的代码处理异常(或继续抛掷异常)
	}catch (int error) {
		printf("出现异常啦: %d\n", error);
	}
	catch (string* error) {
		printf("捕捉到字符串异常: %s\n", error->c_str());
		delete error;
	}catch (float error) {
		printf("出现异常啦 ! %f\n", error);
	}catch (...) {//通杀类型
		printf("catch ...\n");
	}

	//如果没有找到匹配,则缺少功能调用abort终止程序.

	system("pause");
	return;
}