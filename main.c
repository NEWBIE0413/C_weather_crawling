#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <locale.h>

int webcrawling() {
	char filename[] = "weather.html";
	FILE *fp;
    char ch;
	
	while (1) {
        char answer[1];
        system("cls");
		printf("���� ��ȸ ���α׷��� ���Ű� ȯ���մϴ� !\n1. ���� ���� ���� �ҷ�����\n2. ���α׷� �����ϱ�\n���Ͻô� �۾� ��ȣ�� �Է����ּ���  : ");
		scanf("%s", &answer);
		if(strcmp(answer, "1") == 0) {
			printf("���������� �ҷ��ɴϴ�."); 
			popen("curl -o weather.html (���� �ּ��Է�)", "r"); //���̹� �������� html���� �ٿ�ε� 
			system("cls");
			printf("���� ������ �ٿ�ε����Դϴ�.\n\n\n\n\n");
            sleep(3000);
            system("cls");
			_wsetlocale(LC_ALL, L"Korean"); //UTF-8���ڵ��� ���� ������ ���� 
			wchar_t buff[10000];
			wchar_t* location_string = L"<strong class=\"location_name\">"; //ũ�Ѹ��� ���� html ������Ʈ 
			wchar_t* degree_string = L"<span class=\"degree\">";  //2
			wchar_t* weather_string = L"<span class=\"weather\">";  //3 
			wchar_t* update_string = L"<span class=\"offer_update\">"; //4
			FILE *fp = fopen("weather.html", "rt+,ccs=UTF-8"); //5
            if (fp == NULL) {
               printf("���������� �� �� �����ϴ�.");
               return 1;
            }
		    int count = 1;
            while (fgetws(buff, 1000, fp)) {
                if (count == 1000) {
                   printf("��ġ�ϴ� ����� �����ϴ�.");
                   sleep(5000);
                   return 0;
                } 
                if (wcsstr(buff, location_string) != 0) { // strstr �� strtok�� Ȱ���� ũ�Ѹ� ���� 
                   char *ptr = wcstok(buff, ">");
                   ptr = wcstok(NULL, ">");
                   printf("�������� �ٿ �����߽��ϴ�.");
                   wprintf(L"\n",ptr);
                   ptr = wcstok(ptr, "<");
                   printf("���� ��ġ : "); 
                   wprintf(L"%ls\n",ptr);
                }
                if (wcsstr(buff, degree_string) != 0) {
                   char *ptr2 = wcstok(buff, ">");
                   ptr2 = wcstok(NULL, ">");
                   wprintf(L"",ptr2);
                   ptr2 = wcstok(NULL, ">");
                   wprintf(L"",ptr2);
                   ptr2 = wcstok(ptr2, "<");
                   printf("���� �µ� : "); 
                   wprintf(L"%ls",ptr2);
                   printf("��\n");
                }
                if (wcsstr(buff, weather_string) != 0) {
                   char *ptr = wcstok(buff, ">");
                   ptr = wcstok(NULL, ">");
                   wprintf(L"",ptr);
                   ptr = wcstok(ptr, "<");
                   printf("���� ���� : "); 
                   wprintf(L"%ls\n",ptr);
                }
                if (wcsstr(buff, update_string) != 0) {
                   char *ptr = wcstok(buff, ">");
                   int i;
                   printf("������Ʈ �ð� : ");
                   for(i=0;i<4;i++){
                           if (i!=0){
                              wprintf(L"%ls.",ptr);
                           }
                           ptr = wcstok(NULL, ">");
                   }
                   ptr = wcstok(ptr, "<");
                   wprintf(L"%ls\n",ptr);
                   printf("\n�ƹ� Ű�� �Է��Ͽ� �����ϱ�");
                }
			}
			free(buff);
			char *c = _getch(); //Ű�Է� 
			system("cls");
			return 0;
			
		}
		if(strcmp(answer, "2") == 0) {
            system("cls");
			printf("���α׷��� ����˴ϴ�.\n");
			sleep(3000); 
			return 0;
		}
        else {
            system("cls");
			printf("\n�߸��� �亯�� �Է��ϼ̽��ϴ�.\n3�� �� ����ȭ������ ���ư��ϴ�.");
			sleep(3000);
		}
	}
}

void main() {
	webcrawling();
}
