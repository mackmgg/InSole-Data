#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

int main()
{
    FILE *in1;
    int i = 0;
    int index = 3;
    int pressIndex = 0;
    int pressureCount = 0;
    int pressures[47];
    char buff[1024];
    char tmp[1024];
    char pressurePoint[3];
    char accelX_msb[3];
    char accelX_lsb[3];
    char accelY_msb[3];
    char accelY_lsb[3];
    char accelZ_msb[3];
    char accelZ_lsb[3];
    char gyrX_msb[3];
    char gyrX_lsb[3];
    char gyrY_msb[3];
    char gyrY_lsb[3];
    char gyrZ_msb[3];
    char gyrZ_lsb[3];
    char magX_msb[3];
    char magX_lsb[3];
    char magY_msb[3];
    char magY_lsb[3];
    char magZ_msb[3];
    char magZ_lsb[3];
    char unknown[3];
    float accX = 0.0, accY = 0.0, accZ = 0.0, gyrX = 0.0, gyrY = 0.0, gyrZ = 0.0, magX = 0.0, magY = 0.0, magZ = 0.0, unknownx = 0.0;
    int timeStamp;
    char rawPressures[47];
    int lineCount = 1;
    //Initial Connect to bind transfer
    system("hcitool lecc B4:99:4C:67:B7:B4");
    sleep(3); 
    //Writing for gatt protocol to have registers transmit data
    //Change --value= 11 for Pressure, 12 for IMU, 13 for Pressure + IMU
    if(!(in1 = popen("gatttool -b B4:99:4C:67:B7:B4 --char-write-req --handle 0x0025 --value=13 --listen", "r")))
    {
        return -1;
    }
    int lasttime;
    lasttime=time(NULL);
    int downsample;
    downsample=0;
    int altYaw;
    altYaw=0;
    while(fgets(buff, sizeof(buff), in1)!=NULL)
    {
        //Deleting Unnecessary components of 
        string str(buff);
        str.erase (0,36);
        //Uncomment the following lines if you just want pure characters to be printed out.
        //You can access each character by tmp[i], i being the index of the character array.
        strcpy(tmp, str.c_str()); 
        //cout << tmp;
        
        index = 3;
    

        if(tmp[1] == '0' || tmp[1] == '1')
        {
           cout<<"Pressure Points: ";
           while(index < 60)
           {
            memcpy(pressurePoint, &tmp[index], 2);
            pressurePoint[2] = '\0';
            index = index + 3;
            cout<<(255 - (((unsigned int)strtol(pressurePoint, NULL, 16))))<<" ";
           }   
        }

        else if(tmp[1] == '2')
        {
            cout<<"Pressure Points: ";
            while(index < 33)
            {
                memcpy(pressurePoint, &tmp[index], 2);
                pressurePoint[2] = '\0';
                index = index + 3;
                cout<<(255 - (((unsigned int)strtol(pressurePoint, NULL, 16))))<<" ";
            }   
        }

        else if(tmp[1] == '3')
        {
            memcpy(accelX_msb, &tmp[3], 2);
            accelX_msb[2] = '\0';
            memcpy(accelX_lsb, &tmp[6], 2);
            accelX_lsb[2] = '\0';
            memcpy(accelY_msb, &tmp[9], 2);
            accelY_msb[2] = '\0';
            memcpy(accelY_lsb, &tmp[12], 2);
            accelY_lsb[2] = '\0';
            memcpy(accelZ_msb, &tmp[15], 2);
            accelZ_msb[2] = '\0';
            memcpy(accelZ_lsb, &tmp[18], 2);
            accelZ_lsb[2] = '\0';
            memcpy(gyrX_msb, &tmp[21], 2);
            gyrX_msb[2] = '\0';
            memcpy(gyrX_lsb, &tmp[24], 2);
            gyrX_lsb[2] = '\0';
            memcpy(gyrY_msb, &tmp[27], 2);
            gyrY_msb[2] = '\0';
            memcpy(gyrY_lsb, &tmp[30], 2);
            gyrY_lsb[2] = '\0';
            memcpy(gyrZ_msb, &tmp[33], 2);
            gyrZ_msb[2] = '\0';
            memcpy(gyrZ_lsb, &tmp[36], 2);
            gyrZ_lsb[2] = '\0';
            memcpy(magX_msb, &tmp[39], 2);
            magX_msb[2] = '\0';
            memcpy(magX_lsb, &tmp[42], 2);
            magX_lsb[2] = '\0';
            memcpy(magY_msb, &tmp[45], 2);
            magY_msb[2] = '\0';
            memcpy(magY_lsb, &tmp[48], 2);
            magY_lsb[2] = '\0';
            memcpy(magZ_msb, &tmp[51], 2);
            magZ_msb[2] = '\0';
            memcpy(magZ_lsb, &tmp[54], 2);
            magZ_lsb[2] = '\0';
            memcpy(unknown, &tmp[57], 2);
            unknown[2] = '\0';
            // accX = (((int)strtol(accelX_msb,NULL,16)) << 8 | ((int)strtol(accelX_lsb,NULL,16) ))/16056.0f;
            // accY = (((int)strtol(accelY_msb,NULL,16)) << 8 | ((int)strtol(accelY_lsb,NULL,16) ))/16056.0f;
            // accZ = (((int)strtol(accelZ_msb,NULL,16)) << 8 | ((int)strtol(accelZ_lsb,NULL,16) ))/16056.0f;

            accX = ((((int)strtol(accelX_msb,NULL,16)) << 8 | ((int)strtol(accelX_lsb,NULL,16))) ) ;
            accY = ((((int)strtol(accelY_msb,NULL,16)) << 8 | ((int)strtol(accelY_lsb,NULL,16))) ) ;
            accZ = ((((int)strtol(accelZ_msb,NULL,16)) << 8 | ((int)strtol(accelZ_lsb,NULL,16))) ) ;

            if(accX > 32767)
                accX = (-1 * (65536 - accX))/16056.0f;
            else
                accX = accX/16056.0f;
            if(accY > 32767)
                accY = (-1 * (65536 - accY))/16056.0f;
            else
                accY = accY/16056.0f;
            if(accZ > 32767)
                accZ = (-1 * (65536 - accZ))/16056.0f;
            else
                accZ = accZ/6056.0f;
            

            gyrX = (((int)strtol(gyrX_msb,NULL,16)) << 8 | ((int)strtol(gyrX_lsb,NULL,16))) ;
            gyrY = (((int)strtol(gyrY_msb,NULL,16)) << 8 | ((int)strtol(gyrY_lsb,NULL,16))) ;
            gyrZ = (((int)strtol(gyrZ_msb,NULL,16)) << 8 | ((int)strtol(gyrZ_lsb,NULL,16))) ;

            if(gyrX > 32767)
                gyrX = (-1 * (65536 - gyrX))/262.0f;
            else
                gyrX = gyrX/262.0f;
            if(gyrY > 32767)
                gyrY = (-1 * (65536 - gyrY))/262.0f;
            else
                gyrY = gyrY/262.0f;
            if(gyrZ > 32767)
                gyrZ = (-1 * (65536 - gyrZ))/262.0f;
            else
                gyrZ = gyrZ/262.0f;

            magX = (((unsigned int)strtol(magX_msb,NULL,16)) << 8 | ((unsigned int)strtol(magX_lsb,NULL,16)) );
            magY = (((unsigned int)strtol(magY_msb,NULL,16)) << 8 | ((unsigned int)strtol(magY_lsb,NULL,16)) );
            magZ = (((unsigned int)strtol(magZ_msb,NULL,16)) << 8 | ((unsigned int)strtol(magZ_lsb,NULL,16)) );

            if(magX > 32767)
                magX = -1 * (65536 - magX);
            if(magY > 32767)
                magY = -1 * (65536 - magY);
            if(magZ > 32767)
                magZ = -1 * (65536 - magZ);

            unknownx = (unsigned int)strtol(unknown,NULL,16) << 8; 

            //Bob code begins here
            int pitchAcc;
            pitchAcc=atan(accY/(sqrt(accX*accX+accZ*accZ)))*180/3.14;

            int pitchGyro;
            int timer;
            int dt;
            

            timer=time(NULL);
            dt=timer-lasttime;
            pitchGyro=pitchAcc+gyrX*(dt);
            lasttime=timer;

            int pitchComplement;
            pitchComplement=0.9*pitchGyro+0.1*pitchAcc;

            int rollAcc;
            rollAcc=atan(-accX/accZ)*180/3.14;

            int yaw;
            //yaw = atan (accZ/sqrt(accX*accX + accZ*accZ))*180/3.14;
            int mag_norm;
            mag_norm=sqrt(magX*magX+magY*magY+magZ*magZ);
            magX=magX/mag_norm;
            magY=magY/mag_norm;
            magZ=magZ/mag_norm;

            // yaw=atan2(-magY*cos(rollAcc)+magZ*sin(rollAcc),magX*cos(pitchComplement)+magY*sin(pitchComplement)*sin(rollAcc)+
            //     magZ*sin(pitchComplement)*cos(rollAcc))*180/3.14;
            if(abs(gyrZ)>1.75 ){
                altYaw+=gyrZ*3;
                // cout<<"NEGATIVE"<<endl;
            }
            else if(abs(gyrZ)>0.35){
                altYaw+=gyrZ*5.75;
            }
            
            if(downsample==0){
                // cout<<"downsample is false"<<endl;
                // yaw = 180 * atan (accZ/sqrt(accX*accX + accZ*accZ))/3.14159;
                yaw=(magX+magY)*180/3.14*2;
                downsample=3;
            }
            else{
                downsample--;
            }
            

            // cout<<"AccX: "<<accX<<" AccY: "<<accY<<" AccZ: "<<accZ<<endl;
            cout<<"raw yaw: "<<gyrZ<<" "<<endl;
            cout<<"Pitch: "<<pitchComplement<<" Roll: "<<rollAcc<< " Yaw: "<<int(altYaw)<<endl;
            // cout<<"Uknown: "<<unknownx<<endl;
            // cout<<"GyrX: "<<gyrX<<" GyrY: "<<gyrY<<" GyrZ: "<<gyrZ<<endl;
            // cout<<"MagX: "<<magX/1000<<" MagY: "<<magY/1000<<" MagZ: "<<magZ/1000<<endl;

            //sources: http://engineering.stackexchange.com/questions/3348/calculating-pitch-yaw-and-roll-from-mag-acc-and-gyro-data
            //sources: https://theccontinuum.com/2012/09/24/arduino-imu-pitch-roll-from-accelerometer/
            //source: https://sites.google.com/site/myimuestimationexperience/sensors/magnetometer
            //Bob code ends here 
        }
        cout<<endl;
    index = 0;
    }
    pclose(in1);
    return 0;
}