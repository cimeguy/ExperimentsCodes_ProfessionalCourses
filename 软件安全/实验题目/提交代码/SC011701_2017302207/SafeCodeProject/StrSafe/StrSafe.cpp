//最后版本
//#include <StrSafe.h>
#include <iostream>
using namespace std;
int isUsernameOK(char* name) {
	/*功能：判断 name 字符串是否符合要求：name 只允许数字或字母，不小于 8 个字符，
		不超过 16 个字符，且要求以字母开头。*/
		/*返回值：符合要求返回 0，否则返回-1. */
	if (!name)return -1;//为空
	size_t num = strlen(name);
	if (num < 8 || num>16)return -1;
	if (!isalpha(*name)) {//首字母是不是英文
		return -1;
	}name++;
	while (*name) {//即while(*name!='\0')
		//检查每个字母是不是数字或英文
		if (isalnum(*name)) {
			name++;
		}
		else return -1;
	}
	return 0;

}
int isPasswordOK(char* pwd) {
	
	/*功能：判断 pwd 字符串是否符合要求：允许数字或字母，不小于 8 个字符，不超过 16
	个字符，至少包含一个数字和一个字母，且至少一个大写字母。 

	返回值：符合要求返回 0，否则返回-1. */
	if (!pwd)return -1;//为空
	size_t num = strlen(pwd);
	if (num < 8 || num>16)return -1;//判断字符长度 不小于 8 个字符，不超过 16个字符
	int numdig = 0/*数字的个数*/, numsupper = 0/*大写字母的个数*/;
	while (*pwd) {//计数
		if (isalpha(*pwd)) {//如果是字母
			if (isupper(*pwd))numsupper++;//判断大写字母
			pwd++;
		}
		else if (isdigit(*pwd)) {//如果是数字
			numdig++;
			pwd++;
		}
		else return -1;
		
	}
	if (numdig < 1 || numsupper < 1 )return -1;
	return 0;
}
int gets_safe(char* str, rsize_t n) {	
	if (!str) return -1;
	if (n == 0) {//参数错误，还是返回0
		str[0] = '\0';
		return 0;
	}
	char c = '\0';//使用未初始化的内存c报错
	rsize_t len = 0;
	while (c = getchar() != '\n' && c != EOF) {
		if (ferror(stdin)) {//读取错误
			str[0] = 0; //如果读取中出现错误（getchar 返回错误），则 str[0] 置零（如果确定 str 非空），
			return -2;//返回-2
		}
		if (c == '\n')break;//回车
		str[len++] = c;
		if (len >= n) {
			len = n - 1;
			while ((c = getchar()) != '\n' && c != EOF);//清空缓冲区
			break;
		}
	}
	str[len] = '\0';
	return len;
}
int strcpy_safe(char* dest, rsize_t destsz, const char* src) {
	if (destsz == 0 || src == NULL)return 0;
	if (dest == NULL)return -1;

	rsize_t n = 0;
	rsize_t len_of_src = strlen(src);

	if (len_of_src >= destsz) {//长度大于等于destsz
		//写法1
		//while ((*(dest+1))&&(*(src+1))) {//只复制前 (destsz-1) 个字符
		//	*dest = *src;
		//	dest++;
		//	src++;
		//}
		//*dest = '\0';
		//写法2
		while (n < destsz - 1) {//只复制前 (destsz-1) 个字符
			dest[n] = src[n];
			n++;
		}
		dest[n] = '\0';//目的缓冲区最后一个字符置零
		return destsz - 1;
	}
	else {//长度小于destsz
		while (n < len_of_src) {
			dest[n] = src[n];
			n++;
		}
		dest[len_of_src] = '\0';
		return len_of_src;
	}
}
