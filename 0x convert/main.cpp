#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp_read=NULL,*fp_write=NULL;
    errno_t err_read,err_write;
    err_read=fopen_s(&fp_read,"in.txt","r");
    if(err_read!=0)
    {
		printf("read file cannot open!\n");
		system("pause");
		return 0;
    }
	err_write=fopen_s(&fp_write,"out.txt","w");
    if(err_write!=0)
    {
		fclose(fp_read);
		printf("write file cannot create!\n");
		system("pause");
        return 0;
    }
	unsigned int num=0;
	char readchar=0;
	bool firsttime=true;
	bool pos=true;
	while(fscanf_s(fp_read,"%c",&readchar,sizeof(char))!=EOF)
	{
		if(((readchar>='a')&&(readchar<='f'))||((readchar>='A')&&(readchar<='F'))||((readchar>='0')&&(readchar<='9')))
		{
			if(firsttime==true&&pos==true)
			{
				fprintf_s(fp_write,"{0x%c",readchar);
				pos=false;
			}
			else if(firsttime==true&&pos==false)
			{
				fprintf_s(fp_write,"%c",readchar);
				pos=true;
				firsttime=false;
				num++;
			}
			else if(firsttime==false&&pos==true)
			{
				fprintf_s(fp_write,",0x%c",readchar);
				pos=false;
			}
			else if(firsttime==false&&pos==false)
			{
				fprintf_s(fp_write,"%c",readchar);
				pos=true;
				num++;
			}
		}
	}
	if(pos==true)
	{
		fprintf(fp_write,"};\nnum=%d\n",num);
		fclose(fp_read);
		fclose(fp_write);
		printf("convert success!\n");
		system("pause");
		return 0;
	}
	else if(pos==false)
	{
		fprintf(fp_write,"\nread file format error!\n");
		fclose(fp_read);
		fclose(fp_write);
		printf("read file format error!\n");
		system("pause");
		return 0;
	}
    system("pause");
    return 0;
}
