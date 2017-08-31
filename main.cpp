/**
* ������Ա����־�����ϼ����ΰ��
*
* ���񣺽��������ڴ���ļ�ϵͳ
* Ŀ�ģ������˽��ļ�ϵͳ�ṹ
* Ҫ�����ȷ���һ���������ڴ棬����������̣�
*	   �ڸô����Ͻ�����Ӧ���ļ��ļ�ϵͳ��
*	   Ϊ���ļ�ϵͳ�����Ӧ�����ݽṹ������Ŀ¼��������̵Ŀ��пռ䣬�ѷ���ռ�ȣ�
*	   �ṩ�ļ��Ĵ�����ɾ������λ�������ȹ��ܣ�
*	   �ṩ���õĽ��棬������ʾ�����ļ���״̬�Ϳռ��ʹ�������
*	   �ṩ�������ת�����ܣ��ɽ���Ϣ������̣����ɴӴ��̶����ڴ档
*
* ����������VS2015��windows 10
*
*/


#include<iostream>
#include"defines.h"
#include"opration.h"
#include<map>

using namespace std;
//ȫ�ִ��̱���
struct storage *root = new storage;
// ȫ��·��
char PATH[NAMESIZE*DIRNUM] = "";
void init()
{

	memset(root->fnode, '\0', FREEBYTE);
	root->dir[0].direct[0].d_ino = 0;
	root->dir[0].size = 1;
	strcpy(root->dir[0].direct[0].d_name, "C"); //���ø�Ŀ¼��
	root->fnode[0].fi_mode = DIRMODE;
	root->fnode[0].fi_nlink = 1;
	root->fnode[0].dir_no = 1;
	root->dir[1].size = 1;
	root->root.s_freeblocksize = BNUM;
	strcpy(PATH, "/C");
}

int main()
{
	map<string, int> command = {
		{"mkdir",1},
		{"create",2},
		{"read",3},
		{"vi",4},
		{"rm",5},
		{"rename",6},
		{"mv",7},
		{"cd",8},
		{"pwd",9},
		{"ls",10},
		{"free",11},
		{"writeout",12},
		{"readin",13},
		{"formate",14},
		{"help",15},
		{"exit",16},
		{"clear",17},
	};

	opration oprate;
	oprate.help();

	string s;
	char arg1[NAMESIZE] = "";
	char arg2[NAMESIZE] = "";
	char content[BSIZE*BNUM] = "";
	init();
	cout << "FileSystem>";
	bool flag = true;
	int commandNum;
	while (flag) {
		cout << PATH << ">";
		cin >> s;
		if (command.count(s) > 0) {
			commandNum = command.find(s)->second;
		}
		else {
			commandNum = 0;
		}
		switch (commandNum) 
		{
		case 1:cin >> arg1;
			oprate.mkdir(PATH, arg1);
			break;
		case 2:cin >> arg1;
			oprate.create(PATH, arg1);
			break;
		case 3:cin >> arg1;
			oprate.read(PATH, arg1);
			break;
		case 4:cin >> arg1;
			cout << endl << "������Ҫд���ļ������ݣ�" << endl;
			cin >> content;
			oprate.vi(PATH, arg1, content);
			break;
		case 5:cin >> arg1;
			oprate.rm(PATH, arg1);
			break;
		case 6:cin >> arg1 >> arg2;
			oprate.rename(PATH, arg1, arg2);
			break;
		case 7:cin >> arg1 >> arg2;
			oprate.mv(PATH, arg1, arg2);
			break;
		case 8:cin >> arg1;
			oprate.cd(arg1);
			break;
		case 9:cout << PATH << endl;
			break;
		case 10:oprate.ls(PATH);
			break;
		case 11:oprate.free();
			break;
		case 12:oprate.writeout();
			cout << "��д���� filesystem.dat" << endl;
			break;
		case 13:oprate.readin();
			cout << "�Ѵ� filesystem.dat �ж����ļ�ϵͳ" << endl;
			break;
		case 14:memset(root, '\0', sizeof(struct storage));
			init();
			break;
		case 15:oprate.help();
			break;
		case 16:flag = false;
			break;
		case 17:system("cls");
			break;
		default:cout << "�����������������������" << endl;
			break;
		}
	}

	return 0;
	
}


