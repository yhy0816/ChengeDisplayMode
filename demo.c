#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <unistd.h>


int main(){
    FreeConsole();
    FILE* file = freopen("ChangeMode.log", "a", stdout);
    SYSTEM_POWER_STATUS power_status;
    HANDLE hMutex = CreateMutex(NULL, TRUE, "MyProgramMutex"); //只允许程序运行一个实例

    if (hMutex == NULL) {
        printf("Failed to create mutex.\n");
        exit(1);
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        printf("Another instance of the program is already running.\n");
        exit(1);
    }

    while(GetSystemPowerStatus(&power_status)){
        if(power_status.ACLineStatus != 0){
            sleep(2);
            continue;
        }

        // 如果是电池供电就尝试切换
        for (int i = 0; i < 3; i++) {
            if (system("DisplaySwitch.exe /internal") == 0) {

                printf("切换成功\n");
                break;

            } else {
                printf("第%d次切换失败\n", i);

            }


        }
        break;



    }
    fclose(file);
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    return 0;



}
