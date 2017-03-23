#pragma config(StandardModel, "EV3_REMBOT")
#pragma DebuggerWindows("EV3LCDScreen")
#include "tree.h"
#include "stack.h"

//lain-lain
bool isRed();
bool isGreen();
bool isBlue();
bool isBlack();
void intro();
void putar(int no_inter, int jml_cabang, int *arr_inter);//no inter : nomor cabang, arr inter : array penyimpan cabang
void putar180();//putar di tempat
void FindPoint();
void BFS(int Level, );
task main()
{
	Stack branch;
	CreateEmpty(branch);

	displayTextLine(1,"Cari Start");
	intro();

	displayTextLine(1,"Cari Intersection");
	FindPoint();


}

//lain-lain
bool isRed(){
	return(getColorName(colorSensor) == colorRed);
}

bool isBlue(){
	return(getColorName(colorSensor) == colorBlue);
}

bool isGreen(){
	return(getColorName(colorSensor) == colorGreen);
}
bool isBlack(){
	return(getColorName(colorSensor) == colorBlack);
}

void FindPoint(){
	while(true)
  {
  	 // sensor sees light:
    if (getColorName(colorSensor) == colorBlack){
    	motor[leftMotor]  = 55;
    	motor[rightMotor] = -15;
  	}
    else{
    	if(getColorName(colorSensor) == colorWhite){
      // counter-steer right:
      	motor[leftMotor]  = -15;
     		motor[rightMotor] = 55;
			}
			else if((getColorName(colorSensor) == colorGreen)||(getColorName(colorSensor) == colorYellow)||(getColorName(colorSensor) == colorRed)){
    		motor[leftMotor] = 0;
    		motor[rightMotor] = 0;
    		break;
    	}
    }
  }
}

void intro()
{
	int i, j;
	// inisialisasi array kosong
/*	for(i=1;i<=10;i++){
		for(j=1;j<=10;j++){
			adjMatriks[i][j] = 0;
		}
		rem[i] = 99;
	}*/
	// maju cari biru
	setMotorSpeed(leftMotor,50);
  setMotorSpeed(rightMotor,50);
  while(true)
  {
  	if(isBlue())
  	{
  		break;
  	}
	}
  while(true)
  {
  	if(isBlack())
  	{
  		break;
  	}
	}
}

void putar(int no_inter, int jml_cabang, int *arr_inter){

}

//putar di tempat
void putar180(){
	int g1 = getGyroDegrees(gyroSensor);
	while (getGyroDegrees(gyroSensor) > (g1 - 180)){
		setMotorSpeed(leftMotor,-50);
		setMotorSpeed(rightMotor,50);
	}
}
