#include"opration.h"



int opration::help()
{
	cout << "*****************************************************************************" << endl;
	cout << "*                             �ļ�ϵͳ�����ֲ�                               *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                  1�� mkdir <dir>  --����Ŀ¼                               *" << endl;
	cout << "*                  2�� create <file>  --�����ļ�                             *" << endl;
	cout << "*                  3�� read <file>  --��ȡ�ļ�                               *" << endl;
	cout << "*                  4�� vi <file>   --�༭�ļ�                                *" << endl;
	cout << "*                  5�� rm <file>  --ɾ��Ŀ¼/�ļ�                            *" << endl;
	cout << "*                  6�� rename <src> <dest>  --������                         *" << endl;
	cout << "*                  7�� mv <file> <dir>  --�ƶ��ļ�                           *" << endl;
	cout << "*                  8�� cd <dir>  --��Ŀ¼                                  *" << endl;
	cout << "*                  9�� cd ..  --������һ��Ŀ¼                               *" << endl;
	cout << "*                  10��pwd  --�鿴��ǰ·��                                   *" << endl;
	cout << "*                  11��ls  --���ֵ�ǰĿ¼                                    *" << endl;
	cout << "*                  12��free  --��ʾ���̿��ÿռ�                              *" << endl;
	cout << "*                  13��writeout  --д�뵽����                                *" << endl;
	cout << "*                  14��readin  --�Ӵ��̶�ȡ�ļ�ϵͳ                          *" << endl;
	cout << "*                  15��format  --��ʽ������                                  *" << endl;
	cout << "*                  16��help  --��ʾ������Ϣ                                  *" << endl;
	cout << "*                  17��exit  --�˳��ļ�ϵͳ                                  *" << endl;
	cout << "*                  18��clear  --�����Ļ��ʾ                                  *" << endl;
	cout << "******************************************************************************" << endl;
	return 0;
}

STATUS opration::mkdir(char *path, char *pname)
{
	int ino = getnode(path);
	if (ino == -1)
	{
		return ERR_PATH_FAIL;
	}
	int n_ino;
	int d_ino;
	// ������Ŀ¼
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (root->dir[i].size == 0)
		{
			root->dir[i].size = 1;
			d_ino = i;
			break;
			//root->dir[i].direct[0].d_ino = n_ino;
		}
	}
	//������finode�ڵ�
	for (int i = 0; i < NUM; i++)
		if (root->fnode[i].fi_nlink != 1)
		{
			n_ino = i;
			root->fnode[i].fi_mode = DIRMODE;
			root->fnode[i].fi_size = 0;
			root->fnode[i].dir_no = d_ino;
			root->fnode[i].fi_addr[0] = NULL;
			root->fnode[i].fi_nlink = 1;
			break;
		}
	// �ڸ��׽ڵ㽨��ָ��
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strlen(root->dir[root->fnode[ino].dir_no].direct[i].d_name) == 0)
		{
			root->dir[root->fnode[ino].dir_no].direct[i].d_ino = n_ino;
			root->dir[root->fnode[ino].dir_no].size++;
			strcpy(root->dir[root->fnode[ino].dir_no].direct[i].d_name, pname);
			break;
		}
	}
	return SUCCESS;
}
STATUS opration::create(char *path, char* fname)
{
	int ino = getnode(path);
	if (ino == -1)
	{
		return ERR_PATH_FAIL;
	}
	int n_ino;
	for (int i = 0; i < NUM; i++)
		if (root->fnode[i].fi_nlink != 1)
		{
			n_ino = i;
			root->fnode[i].fi_mode = FILEMODE;
			root->fnode[i].fi_size = 0;
			root->fnode[i].fi_addr[0] = NULL;
			root->fnode[i].fi_nlink = 1;
			break;
		}
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strlen(root->dir[root->fnode[ino].dir_no].direct[i].d_name) == 0)
		{
			root->dir[root->fnode[ino].dir_no].direct[i].d_ino = n_ino;
			strcpy(root->dir[root->fnode[ino].dir_no].direct[i].d_name, fname);
			break;
		}
	}
	return SUCCESS;
}
STATUS opration::read(char *path, char *file)
{
	int ino = getnode(path);
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strcmp(root->dir[root->fnode[ino].dir_no].direct[i].d_name, file) == 0)
		{
			if (root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_mode == DIRMODE)
			{
				cout << "����һ��Ŀ¼" << endl;
			}
			else
			{
				// ȷ���ж��ٿ�
				for (int j = 0; j < 1 + root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_size / BSIZE; j++)
				{
					//cout << (BSIZE *root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_addr[j]) << endl;
					//cout << ((root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_addr[j] * BSIZE) + (
					//	j>(root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_size / BSIZE) ? BSIZE :
					//	(root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_size%BSIZE)));
					//cout << (root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_size / BSIZE) << endl;;
					for (int k = (BSIZE *root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_addr[j]);
					k < ((root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_addr[j] * BSIZE) +
						(j >(root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_size / BSIZE) ? BSIZE :
							(root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_size%BSIZE))); k++)
					{
						//cout << k;
						cout << root->free[k];
					}
				}
			}
			break;
		}
	}
	cout << endl;
	return SUCCESS;
}
STATUS opration::vi(char *path, char *file, char *cont) 
{
	int ino = getnode(path);
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strcmp(root->dir[root->fnode[ino].dir_no].direct[i].d_name, file) == 0)
		{
			if (root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_mode == DIRMODE)
			{
				cout << "����һ��Ŀ¼" << endl;
			}
			else
			{

				root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_size = strlen(cont);
				// ȷ���ж��ٿ�
				for (int j = 0; j < 1 + strlen(cont) / BSIZE; j++)
				{
					// Ѱ�ҿ��п�
					for (int k = 0; k < BNUM; k++)
					{

						if (root->root.s_freeblock[k] != 1)
						{
							// д��ռ��
							int l, m;
							root->root.s_freeblock[k] = 1;
							root->root.s_freeblocksize--;
							root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_addr[j] = k;
							for (l = k*BSIZE, m = j*BSIZE; l < k*BSIZE + BSIZE; m++, l++)
							{
								root->free[l] = cont[m];

							}
							break;
						}
					}
				}
			}
			break;
		}

	}
	return SUCCESS;
}
int opration::rm(char *path, char *file)
{
	int ino = getnode(path);

	int n_ino;
	//��Ŀ¼���Ƴ��ڵ�
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strcmp(root->dir[root->fnode[ino].dir_no].direct[i].d_name, file) == 0)
		{
			strcpy(root->dir[root->fnode[ino].dir_no].direct[i].d_name, "");
			n_ino = root->dir[root->fnode[ino].dir_no].direct[i].d_ino;
			root->dir[root->fnode[ino].dir_no].size--;
		}
		else
		{
			cout << "�ļ�������" << endl;
			return ERR_FILE_NOT_EXIST;
		}
	}
	for (int i = 0; i < 1 + (root->fnode[n_ino].fi_size / BSIZE); i++)
	{
		root->root.s_freeblock[root->fnode[n_ino].fi_addr[i]] = 0;
		root->root.s_freeblocksize++;
	}
	root->fnode[n_ino].fi_nlink = 0;
	return SUCCESS;
}
STATUS opration::rename(char *path, char *cname, char *nname)
{
	int ino = getnode(path);
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strcmp(root->dir[root->fnode[ino].dir_no].direct[i].d_name, cname) == 0)
		{
			for (int j = 0; j < DIRSIZE; j++)
			{
				if (strcmp(root->dir[root->fnode[ino].dir_no].direct[j].d_name, nname) == 0)
				{
					cout << "�ļ����ظ�" << endl;
					return ERR_FILE_EXIST;
				}
			}
			strcpy(root->dir[root->fnode[ino].dir_no].direct[i].d_name, nname);
		}
	}
	return SUCCESS;
}
STATUS opration::mv(char *path, char *file, char *npath)
{
	int ino = getnode(path);
	//��Ŀ¼��ɾ���ڵ�
	int n_ino;
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strcmp(root->dir[root->fnode[ino].dir_no].direct[i].d_name, file) == 0)
		{
			strcpy(root->dir[root->fnode[ino].dir_no].direct[i].d_name, "");
			n_ino = root->dir[root->fnode[ino].dir_no].direct[i].d_ino;
			root->dir[root->fnode[ino].dir_no].size--;
		}
	}
	ino = getnode(npath);
	// �����½ڵ��
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strlen(root->dir[root->fnode[ino].dir_no].direct[i].d_name) == 0)
		{
			root->dir[root->fnode[ino].dir_no].direct[i].d_ino = n_ino;
			strcpy(root->dir[root->fnode[ino].dir_no].direct[i].d_name, file);
			break;
		}
	}

	return SUCCESS;
}
STATUS opration::cd(char *topath)
{
	char path[NAMESIZE*DIRNUM] = "";
	//������һ��Ŀ¼
	if (!strcmp(topath, ".."))
	{
		//
		int len;
		//cout << strlen(PATH);
		for (int i = strlen(PATH); i >= 0; i--)
		{
			if (PATH[i] == '/')
			{
				len = i;
				break;
			}
			//cout << len;
		}

		strncpy(path, PATH, len);
		strcpy(PATH, path);
	}
	// ����Ŀ¼
	else
	{
		strcpy(path, PATH);
		strcat(path, "/");
		strcat(path, topath);
		if (getnode(path) == -1 || getnode(path) == 0)
			cout << "Ŀ¼������󣬽���ʧ��" << endl;
		else
		{
			strcpy(PATH, path);
		}

		//cout << path;

	}
	//cout << p;
	return SUCCESS;
}

STATUS opration::ls(char *path)
{
	int ino = getnode(path);
	cout << setw(10) << "NAME" << setw(5) << "type" << setw(6) << "size" << endl;
	for (int i = 0; i < DIRSIZE; i++)
	{
		if (strlen(root->dir[root->fnode[ino].dir_no].direct[i].d_name) != 0)
		{
			cout << setw(10) << root->dir[root->fnode[ino].dir_no].direct[i].d_name;
			if (root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_mode == DIRMODE)
			{
				cout << setw(5) << "DIR" << setw(6) << "-";

			}
			else
			{
				cout << setw(5) << "FILE" << setw(6) << root->fnode[root->dir[root->fnode[ino].dir_no].direct[i].d_ino].fi_size;
			}
			cout << endl;
		}
	}
	return SUCCESS;
}
STATUS opration::free()
{
	cout << "[";
	int l = (int)40.0*(1.0*root->root.s_freeblocksize / BNUM);
	//cout << l;

	for (int i = 0; i < 40 - l; i++)
	{
		cout << "=";
	}
	for (int i = 0; i < l; i++)
	{
		cout << " ";
	}
	cout << "] ";
	cout << (int)(100.0*root->root.s_freeblocksize / BNUM) << "% free" << endl;
	return SUCCESS;
}
STATUS opration::writeout()
{
	FILE *fp;
	if ((fp = fopen("filesystem", "w")) == NULL)
	{
		cout << "д���ļ�ʧ�ܣ�" << endl;
		return ERR_FILE_FAIL;
	}

	if (fwrite(root, sizeof(struct storage), 1, fp) != 1)
	{
		cout << "�ļ�д��ʧ��" << endl;
	}

	fclose(fp);
	return SUCCESS;
}
STATUS opration::readin()
{
	FILE *fp;
	if ((fp = fopen("filesystem", "r")) == NULL)
	{
		cout << "�����ļ�ʧ��" << endl;
		return ERR_FILE_FAIL;
	}
	if (fread(root, sizeof(struct storage), 1, fp))
	{
		fclose(fp);
		return SUCCESS;
	}
	return SUCCESS;
}

int opration::getnode(char *path)
{
	if (path[0] != '/')
	{
		return -1;	//·���Ƿ�
	}
	else
	{
		struct dire cdir = root->dir[0];
		int ino = 0;
		char tpath[NAMESIZE*DIRNUM] = "";
		strcpy(tpath, path);
		char *fpath = strtok(tpath, "/");
		//cout << fpath;
		int match = 0;
		while (fpath != NULL)
		{
			match = 0;
			//cout << fpath;
			for (int i = 0; i < DIRNUM; i++)
			{
				if (!strncmp(fpath, cdir.direct[i].d_name, strlen(fpath)))
				{

					//cout << cdir.direct[i].d_name;
					if (root->fnode[cdir.direct[i].d_ino].fi_mode == DIRMODE)
					{
						ino = cdir.direct[i].d_ino;
						cdir = root->dir[root->fnode[cdir.direct[i].d_ino].dir_no];

						match = 1;
						break;
					}
					else
					{
						return -1;	//���ļ��������ļ���
					}
				}

			}
			fpath = strtok(NULL, "/");
		}

		return ino;	//Ϊ���ڵ㡰/��
	}
	return -1;	//����
}