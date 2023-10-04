#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <unistd.h>


int main(){

    SYSTEM_POWER_STATUS power_status;
    while(1){

        if (GetSystemPowerStatus(&power_status)) {

            if (power_status.ACLineStatus == 1) {
                printf("电源供电\n");

            } else if (power_status.ACLineStatus == 0) {
                printf("电池供电\n");
                if(system("DisplaySwitch.exe /internal") == 0){

                    printf("切换成功\n");
                    return 0;

                }else{
                    printf("切换失败\n");
                    return -1;
                }
            } else {
                printf("error\n");
                return -1;
            }




        } else {
            printf("error\n");
            return 0;
        }
        sleep(2);

    }

    return 0;



}