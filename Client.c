//standard header files
#include<stdio.h>
#include<signal.h>
//standard header file for getting timestamp
#include<sys/time.h>
//standard header file for integrating Raspberry pi with the i2c bus
#include "i2c-dev.h"
//standard header file for integrating accelerometer
#include "ADXL345.h"
#define I2C_FILE_NAME "/dev/i2c-1" // 	predefining filename for Raspberry pi
void INThandler(int sig);
int main(int argc, char **argv)
{
//Open the connection to the I2C control file
int i2c_fd = open(I2C_FILE_NAME,O_RDWR);
//Checking for errors in opening the file
if(i2c_fd <0)
{
printf("Unable to open i2c control file, err=%d\n",i2c_fd);
        exit(1);
}
//print successful opening of file
printf("Opened i2c control file, id=%d\n", i2c_fd);
//Open the connection to access the ADXL345 control file
ADXL345 myAcc(i2c_fd);
int ret = myAcc.init();
//Checking for errors in opening the file
if (ret)
{
        printf("failed init ADXL345, ret=%d\n", ret);
        exit(1);
}
usleep(100 * 1000);
signal(SIGINT, INThandler);
short ax, ay, az;
//create and open the output file- output.txt
FILE *fp;
fp = fopen("./output.txt","w+");
char TimeString[128];
timeval curTime;
while(1)
{
        // printing the current time and date
        gettimeofday(&curTime, NULL);
        strftime(TimeString, 80, "%Y-%m-%d %H:%M:%S",localtime(&curTime.tv_sec));
        printf(TimeString);
        printf(": ");
        // fetching the co-ordinates of the sensor
        myAcc.readXYZ(ax, ay, az);
        // print the output co-ordinates on the monitor
        printf("Ax : %hi \t Ay : %hi \t Az : %hi \n",ax,ay,az);
        printf("----------------------\n");
        // save the timestamp on the output file
        fprintf(fp,TimeString);
        fprintf(fp, ": ");
        fprintf(fp, "Ax : %hi \t Ay : %hi \t Az : %hi \n",ax,ay,az);
        fprintf(fp, "----------------------\n");
        //when q is entered exit the loop
        if (getchar() == 'q') break;
}
//close the output file
fclose(fp);
return 0;
}
void INThandler(int sig)
{
signal(sig, SIG_IGN);
exit(0);
}
