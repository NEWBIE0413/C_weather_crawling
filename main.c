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
		printf("날씨 조회 프로그램에 오신걸 환영합니다 !\n1. 오늘 날씨 정보 불러오기\n2. 프로그램 종료하기\n원하시는 작업 번호를 입력해주세요  : ");
		scanf("%s", &answer);
		if(strcmp(answer, "1") == 0) {
			printf("날씨정보를 불러옵니다."); 
			popen("curl -o weather.html https://weather.naver.com/", "r"); //네이버 날씨에서 html파일 다운로드 
			system("cls");
			printf("날씨 정보를 다운로드중입니다.\n\n\n\n\n");
            sleep(3000);
            system("cls");
			_wsetlocale(LC_ALL, L"Korean"); //UTF-8인코딩을 위한 로케일 설정 
			wchar_t buff[10000];
			wchar_t* location_string = L"<strong class=\"location_name\">"; //크롤링을 위한 html 엘리먼트 
			wchar_t* degree_string = L"<span class=\"degree\">";  //2
			wchar_t* weather_string = L"<span class=\"weather\">";  //3 
			wchar_t* update_string = L"<span class=\"offer_update\">"; //4
			FILE *fp = fopen("weather.html", "rt+,ccs=UTF-8"); //5
            if (fp == NULL) {
               printf("날씨파일을 열 수 없습니다.");
               return 1;
            }
		    int count = 1;
            while (fgetws(buff, 1000, fp)) {
                if (count == 1000) {
                   printf("일치하는 결과가 없습니다.");
                   sleep(5000);
                   return 0;
                } 
                if (wcsstr(buff, location_string) != 0) { // strstr 및 strtok을 활용한 크롤링 구현 
                   char *ptr = wcstok(buff, ">");
                   ptr = wcstok(NULL, ">");
                   printf("날씨정보 다운에 성공했습니다.");
                   wprintf(L"\n",ptr);
                   ptr = wcstok(ptr, "<");
                   printf("현재 위치 : "); 
                   wprintf(L"%ls\n",ptr);
                }
                if (wcsstr(buff, degree_string) != 0) {
                   char *ptr2 = wcstok(buff, ">");
                   ptr2 = wcstok(NULL, ">");
                   wprintf(L"",ptr2);
                   ptr2 = wcstok(NULL, ">");
                   wprintf(L"",ptr2);
                   ptr2 = wcstok(ptr2, "<");
                   printf("현재 온도 : "); 
                   wprintf(L"%ls",ptr2);
                   printf("°\n");
                }
                if (wcsstr(buff, weather_string) != 0) {
                   char *ptr = wcstok(buff, ">");
                   ptr = wcstok(NULL, ">");
                   wprintf(L"",ptr);
                   ptr = wcstok(ptr, "<");
                   printf("현재 날씨 : "); 
                   wprintf(L"%ls\n",ptr);
                }
                if (wcsstr(buff, update_string) != 0) {
                   char *ptr = wcstok(buff, ">");
                   int i;
                   printf("업데이트 시간 : ");
                   for(i=0;i<4;i++){
                           if (i!=0){
                              wprintf(L"%ls.",ptr);
                           }
                           ptr = wcstok(NULL, ">");
                   }
                   ptr = wcstok(ptr, "<");
                   wprintf(L"%ls\n",ptr);
                   printf("\n아무 키나 입력하여 종료하기");
                }
			}
			free(buff);
			char *c = _getch(); //키입력 
			system("cls");
			return 0;
			
		}
		if(strcmp(answer, "2") == 0) {
            system("cls");
			printf("프로그램이 종료됩니다.\n");
			sleep(3000); 
			return 0;
		}
        else {
            system("cls");
			printf("\n잘못된 답변을 입력하셨습니다.\n3초 뒤 메인화면으로 돌아갑니다.");
			sleep(3000);
		}
	}
}

void main() {
	webcrawling();
}
