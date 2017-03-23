#pragma config(StandardModel, "EV3_REMBOT")
#pragma DebuggerWindows("EV3LCDScreen")
#include "tree.h"
#include "stack.h"

//lain-lain
bool isRed();
bool isGreen();
bool isBlue();
bool isBlack();
bool isYellow();
void intro();
void putar(int *adakiri, int *adakanan, int *adatengah, int *jmlCabang);//no inter : nomor cabang, arr inter : array penyimpan cabang
void putar180();//putar di tempat
void FindPoint();
void BFS(int Level, ElTree *E, int *Fire);
void turn1();
Tree T;
ElTree El;
int it;
task main()
{

	int fire = 0;
	Stack branch;
	CreateEmpty(branch);

	CreateTree(&T);
	displayTextLine(1,"Cari Start");
	intro();
	Bapak(El) = Bapak(T.Elm[1]);
	Anak1(El) = Anak1(T.Elm[1]);
	Anak2(El) = Anak2(T.Elm[1]);
	Anak3(El) = Anak3(T.Elm[1]);
	AnakKe(El) = AnakKe(T.Elm[1]);
	JmlAnak(El) = JmlAnak(T.Elm[1]);
	Alamat(El) = Alamat(T.Elm[1]);
	it = 1;
	int i=1;
	while(fire==0){
		BFS(i,&El,&fire);
	  //displayTextLine()
		i++;
		it++;
	}
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
bool isYellow(){
	return(getColorName(colorSensor) == colorYellow);
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

void putar(int *adakiri, int *adakanan, int *adatengah, int *jmlCabang){
	int kiri, kanan, tengah;
	kiri = 0;
  tengah = 0;
  kanan = 0;

  int jumlahcabang = 0;
  // asumsi semua 90 derajat
	backward(0.3);
	int g1 = getGyroDegrees(gyroSensor);
	while (getGyroDegrees(gyroSensor) < (g1 + 90)){
		setMotorSpeed(leftMotor,20);
		setMotorSpeed(rightMotor,-20);
	}
	g1 = getGyroDegrees(gyroSensor);
	int g2 = g1;
	while(g2 > (g1-360)){
		// tambahin range pencarian
		g2 = getGyroDegrees(gyroSensor);
		if((getGyroDegrees(gyroSensor) < (g1 - 40))&&(getGyroDegrees(gyroSensor) > (g1 - 90))){
			if(getColorName(colorSensor) == colorBlack){
				kanan = 1;
			}
		}
		if((getGyroDegrees(gyroSensor) < (g1 - 140))&&(getGyroDegrees(gyroSensor) > (g1 - 180))){
			if(getColorName(colorSensor) == colorBlack){
				tengah = 1;
			}
		}
		if((getGyroDegrees(gyroSensor) < (g1 - 200))&&(getGyroDegrees(gyroSensor) > (g1 - 280))){
			if(getColorName(colorSensor) == colorBlack){
				kiri = 1;
			}
		}
		setMotorSpeed(leftMotor,20);
		setMotorSpeed(rightMotor,50);
	}
	g1 = getGyroDegrees(gyroSensor);
	jumlahcabang = kiri + kanan + tengah;
	*adakiri = kiri;
	*adakanan = kanan;
	*adatengah = tengah;
	while (getGyroDegrees(gyroSensor) > (g1 - 90)){
		setMotorSpeed(leftMotor,-20);
		setMotorSpeed(rightMotor,20);
	}
	*jmlCabang = kiri + tengah + kanan;
}

//putar di tempat
void putar180(){
	int g1 = getGyroDegrees(gyroSensor);
	while (getGyroDegrees(gyroSensor) > (g1 - 180)){
		setMotorSpeed(leftMotor,-50);
		setMotorSpeed(rightMotor,50);
	}
}

void BFS(int Level, ElTree *E, int *Fire){
	//maju
	FindPoint();
	displayTextLine(1,"Cari Intersection");
	Level--;

	if(Level>=0){
		if(isRed()){
			if(AnakKe(*E)==1){ // ini apaan rol
				Anak1(T.Elm[Bapak(*E)]) = 0;
			}else if(AnakKe(*E)==2){
				Anak2(T.Elm[Bapak(*E)]) = 0;
			}else if(AnakKe(*E)==3){
				Anak3(T.Elm[Bapak(*E)]) = 0;
			}
			putar180();
			displayTextLine(1,"Cari Intersection");
			FindPoint();
		}else if(isYellow()){
			*Fire = 1;
			putar180();
			displayTextLine(1,"Cari Intersection");
			FindPoint();
		}else if(isBlue()){
			setMotorSpeed(leftMotor,0);
			setMotorSpeed(rightMotor,0);
		}else if(isGreen()){
			int a=0;
		  int b=0;
		  int c=0;
		  int cbg=0;
		  if(Visited(*E)==1){
				putar(&a,&b,&c,&cbg);
				JmlAnak(*E) = cbg;
				JmlAnak(T.Elm[Alamat(*E)]) = cbg;
				displayTextLine(1,"%d  ",cbg);
				if(a == 1){
					AddAnak(&T,E,1);
				}
				if(b == 1){
				  AddAnak(&T,E,2);
				}
				if(c == 1){
				  AddAnak(&T,E,3);
				}
				//sleep(3000);
				displayTextLine(1,"%d  ",Anak1(T.Elm[Alamat(*E)]));
				int j;
				for(j=1;j<=3;j++){

					int altemp = Alamat(*E);
					displayTextLine(1,"%d  ",j);
					displayTextLine(2,"%d  ",Anak1(*E));
					displayTextLine(3,"%d  ",Alamat(*E));
					if(j==1){
						if(Anak1(*E)==0){
							continue;
						}
					}else if(j==2){
						if(Anak2(*E)==0){
							continue;
						}
					}else if(j==3){
						if(Anak3(*E)==0){
							continue;
						}
					}
					GoToChild(T,E,j);	// go to child sepertinya tidak bekerja dengan baik dan benar sebagaimana mestinya
					displayTextLine(4,"%d  ",Alamat(*E));
					turn1();
					//sleep(3000);
					if(Alamat(*E) != altemp){
						//sleep(3000);
						BFS(Level,E,Fire);
						MoveToParent(T,E);
					}
				}
				turn1();
				//return;
				Visited(*E)++;
			}else if(Visited(*E)==0){
			  Visited(*E)++;
			  Visited(T.Elm[Alamat(*E)])=Visited(*E);
			  putar180();
				FindPoint();
			}else{
				int j;
				for(j=1;j<=JmlAnak(*E);j++){
					int altemp = Alamat(*E);
					if(j==1){
						if(Anak1(*E)==0){
							continue;
						}
					}else if(j==2){
						if(Anak2(*E)==0){
							continue;
						}
					}else if(j==3){
						if(Anak3(*E)==0){
							continue;
						}
					}
					GoToChild(T,E,j);
					displayTextLine(1,"%d",Alamat(*E));
					turn1();
					if(Alamat(*E) == altemp){
						BFS(Level,E,Fire);
						MoveToParent(T,E);
					}
				}
			}
		}
	}
	//pulang
}

void turn1(){
	// posisi sudah di backward
	int g1 = getGyroDegrees(gyroSensor);
	while (getGyroDegrees(gyroSensor) > (g1 - 50)){
		setMotorSpeed(leftMotor,-20);
		setMotorSpeed(rightMotor,20);
	}
	while (getColorName(colorSensor) != colorWhite){
		setMotorSpeed(leftMotor,50);
		setMotorSpeed(rightMotor,25);
	}
	// warna putih
	while (getColorName(colorSensor) != colorBlack){
		setMotorSpeed(leftMotor,50);
		setMotorSpeed(rightMotor,25);
	}
	while (getColorName(colorSensor) != colorWhite){
		setMotorSpeed(leftMotor,50);
		setMotorSpeed(rightMotor,25);
	}
	// set break
	setMotorSpeed(leftMotor,0);
	setMotorSpeed(rightMotor,0);
}
