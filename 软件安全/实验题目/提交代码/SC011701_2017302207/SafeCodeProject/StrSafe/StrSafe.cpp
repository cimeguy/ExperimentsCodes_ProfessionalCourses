//���汾
//#include <StrSafe.h>
#include <iostream>
using namespace std;
int isUsernameOK(char* name) {
	/*���ܣ��ж� name �ַ����Ƿ����Ҫ��name ֻ�������ֻ���ĸ����С�� 8 ���ַ���
		������ 16 ���ַ�����Ҫ������ĸ��ͷ��*/
		/*����ֵ������Ҫ�󷵻� 0�����򷵻�-1. */
	if (!name)return -1;//Ϊ��
	size_t num = strlen(name);
	if (num < 8 || num>16)return -1;
	if (!isalpha(*name)) {//����ĸ�ǲ���Ӣ��
		return -1;
	}name++;
	while (*name) {//��while(*name!='\0')
		//���ÿ����ĸ�ǲ������ֻ�Ӣ��
		if (isalnum(*name)) {
			name++;
		}
		else return -1;
	}
	return 0;

}
int isPasswordOK(char* pwd) {
	
	/*���ܣ��ж� pwd �ַ����Ƿ����Ҫ���������ֻ���ĸ����С�� 8 ���ַ��������� 16
	���ַ������ٰ���һ�����ֺ�һ����ĸ��������һ����д��ĸ�� 

	����ֵ������Ҫ�󷵻� 0�����򷵻�-1. */
	if (!pwd)return -1;//Ϊ��
	size_t num = strlen(pwd);
	if (num < 8 || num>16)return -1;//�ж��ַ����� ��С�� 8 ���ַ��������� 16���ַ�
	int numdig = 0/*���ֵĸ���*/, numsupper = 0/*��д��ĸ�ĸ���*/;
	while (*pwd) {//����
		if (isalpha(*pwd)) {//�������ĸ
			if (isupper(*pwd))numsupper++;//�жϴ�д��ĸ
			pwd++;
		}
		else if (isdigit(*pwd)) {//���������
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
	if (n == 0) {//�������󣬻��Ƿ���0
		str[0] = '\0';
		return 0;
	}
	char c = '\0';//ʹ��δ��ʼ�����ڴ�c����
	rsize_t len = 0;
	while (c = getchar() != '\n' && c != EOF) {
		if (ferror(stdin)) {//��ȡ����
			str[0] = 0; //�����ȡ�г��ִ���getchar ���ش��󣩣��� str[0] ���㣨���ȷ�� str �ǿգ���
			return -2;//����-2
		}
		if (c == '\n')break;//�س�
		str[len++] = c;
		if (len >= n) {
			len = n - 1;
			while ((c = getchar()) != '\n' && c != EOF);//��ջ�����
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

	if (len_of_src >= destsz) {//���ȴ��ڵ���destsz
		//д��1
		//while ((*(dest+1))&&(*(src+1))) {//ֻ����ǰ (destsz-1) ���ַ�
		//	*dest = *src;
		//	dest++;
		//	src++;
		//}
		//*dest = '\0';
		//д��2
		while (n < destsz - 1) {//ֻ����ǰ (destsz-1) ���ַ�
			dest[n] = src[n];
			n++;
		}
		dest[n] = '\0';//Ŀ�Ļ��������һ���ַ�����
		return destsz - 1;
	}
	else {//����С��destsz
		while (n < len_of_src) {
			dest[n] = src[n];
			n++;
		}
		dest[len_of_src] = '\0';
		return len_of_src;
	}
}
