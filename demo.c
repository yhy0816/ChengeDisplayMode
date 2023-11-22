#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <unistd.h>


int main(){
    FreeConsole();
    FILE* file = freopen("ChangeMode.log", "a", stdout);
    SYSTEM_POWER_STATUS power_status;

    while(GetSystemPowerStatus(&power_status)){

        if(power_status.ACLineStatus == 0) { // 如果是电池供电就尝试切换
            for (int i = 0; i < 3; i++) {
                if (system("DisplaySwitch.exe /internal") == 0) {

                    printf("切换成功\n");
                    break;

                } else {
                    printf("第%d次切换失败\n", i);

                }
            }
            break; // 三次切换失败退出程序
        }

        sleep(2);
    }
    fclose(file);
    return 0;



}
