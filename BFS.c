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
void turn3();
void pulang();
void putar(int sdt);
void belokSkip(int sdt);
void FindBlue();
bool kunjungiLagi(ElTree titik);
void pulanglompat(ElTree *E);
ElTree El;
Tree T;
int it;
int lvl;
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
	Visited(El) = Alamat(T.Elm[1]);
	it = 1;
	int i=2;
	while(fire==0){
		BFS(i,&El,&fire);
		//displayTextLine()
		i++;
		it++;
		/*if(it>=4){
			turn1();
		}*/
		if(fire){
			pulanglompat(&El);
		}
		forward(1000,milliseconds,30);
		putar(60);
		forward(500,milliseconds,20);
		if(!fire){
			putar180();
		}
	}
	FindBlue();
	displayTextLine(9,"Pulang");
	/*
	if(fire==1){
		displayTextLine(9,"Pulang");
		pulang();
	}*/
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
	lvl++;
	displayTextLine(lvl+1,"%d",AnakKe(*E));
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
			JmlAnak(T.Elm[Bapak(*E)])--;

			FindPoint();
		}else if(isYellow()){
			*Fire = 1;
			putar180();
			displayTextLine(1,"Api telah dipadamkan");
			FindPoint();
			int cou;
			/*for(cou = 0; cou < 50; cou++){
				// bunuh semua anaknya
				Anak1(T.Elm[cou]) = 0;
				Anak2(T.Elm[cou]) = 0;
				Anak3(T.Elm[cou]) = 0;
			}*/
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

				if(a == 1){
					AddAnak(&T,E,1);

				}
				if(b == 1){
					AddAnak(&T,E,3);
				}
				if(c == 1){
					AddAnak(&T,E,2);
				}
				//sleep(3000);

				int j;
				for(j=1;j<=3;j++){
					// loop kunjungi semua anak anaknya
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
					GoToChild(T,E,j);	// go to child sepertinya tidak bekerja dengan baik dan benar sebagaimana mestinya

					putar(50);
					turn1();
					//sleep(3000);
					if(Alamat(*E) != altemp){
						//sleep(3000);
						BFS(Level,E,Fire);
						//Visited(*E);
						//Visited(T.Elm[Alamat(*E)])++;

						MoveToParent(T,E);
					}
				}
				Visited(*E)++;
				Visited(T.Elm[Alamat(*E)])++;
				putar(50);
				turn1();
				if(*Fire!=1){
					if(!kunjungiLagi(T.Elm[Bapak(*E)])){
						displayTextLine(8,"jgn kunjungi");
						sleep(1000);
						displayTextLine(8,"            ");
						return;
					}
				}
				//return;
				//Visited(*E)++;

				}else if(Visited(*E)==0){
					// jika cabang tersebut belum dikunjungi
					Visited(*E)++;
					Visited(T.Elm[Alamat(*E)])=Visited(*E);
					putar180();
					FindPoint();
				}else{
				int j;

				// kalau dia udh pernah diunjungi > 1 kali, maka gausah itung cabang anak anaknya
				for(j=1;j<=3;j++){
					int altemp = Alamat(*E);
					if(j==1){
						if(Anak1(*E)==0){
							putar(50);
							belokSkip(50);

							continue;
						}
					}else if(j==2){
						if(Anak2(*E)==0){
							if (Anak1(*E)!=0){
							putar(50);
						}
							belokSkip(50);

							continue;
						}
					}else if(j==3){
						if(Anak3(*E)==0){
							if ((Anak1(*E)==0)&&(Anak2(*E)==0)){
							putar(50);
						} else if (Anak2(*E)!=0){
						putar(50);
					}
							belokSkip(50);
							continue;
						}
					}
					if(j==1){
						putar(50);
					}else if(j==2){
						if(Anak1(*E)!=0){
							putar(50);
						}
					}else if(j==3){
						if(Anak2(*E)!=0){
							putar(50);
						}
					}
					GoToChild(T,E,j);


					turn1();
					if(Alamat(*E) != altemp){
						BFS(Level,E,Fire);

						/**** Eliminasi point ****/
						if(JmlAnak(*E)==0){
							if(AnakKe(*E)==1){
								Anak1(T.Elm[Bapak(*E)]) = 0;
							}else if(AnakKe(*E)==2){
								Anak2(T.Elm[Bapak(*E)]) = 0;
							}else if(AnakKe(*E)==3){
								Anak3(T.Elm[Bapak(*E)]) = 0;
							}
						}
						/**** END Eliminasi point ****/
						if(*Fire!=1){
							if(!kunjungiLagi(*E)){
								displayTextLine(8,"jgn kunjungi");
								displayTextLine(8,"            ");
								return;
							}
						}
						MoveToParent(T,E);
						FindPoint();
						backward(0.3);
						if(*Fire==1){
							if(j==1){
								Anak2(*E) = 0;
								Anak3(*E) = 0;
							}else if(j==2){
								Anak1(*E) = 0;
								Anak3(*E) = 0;
							}else if(j==3){
								Anak1(*E) = 0;
								Anak2(*E) = 0;
							}
						}
					}

				}
				//revisi baru

				//FindPoint();

				turn1();
				if(*Fire!=1){
					if(!kunjungiLagi(T.Elm[Bapak(*E)])){
						displayTextLine(8,"jgn kunjungi");
						return;
					}
				}

				//if ((Anak3(*E) == 0) && (Anak3(*E) == 0)){
					//turn3();
				//}
				/******* TAMBAHAN HARI INI *******/

			}
		}
	}
	//pulang
	displayTextLine((lvl+1),"  ");
	lvl--;
}

void turn3(){
	// posisi sudah di backward
	int g1 = getGyroDegrees(gyroSensor);
	while (getGyroDegrees(gyroSensor) < (g1 + 90)){
		setMotorSpeed(leftMotor,20);
		setMotorSpeed(rightMotor,-20);
	}
	while (getColorName(colorSensor) != colorWhite){
		setMotorSpeed(leftMotor,25);
		setMotorSpeed(rightMotor,50);
	}
	// warna putih
	while (getColorName(colorSensor) != colorBlack){
		setMotorSpeed(leftMotor,25);
		setMotorSpeed(rightMotor,50);
	}
	// set break
	setMotorSpeed(leftMotor,0);
	setMotorSpeed(rightMotor,0);
}

void turn1(){
	// posisi sudah di backward

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

void pulang(){
	FindPoint();
	backward(0.3);
	turn1();
	FindPoint();
	turn1();
	while (getColorName(colorSensor) != colorBlack){
		setMotorSpeed(leftMotor,50);
		setMotorSpeed(rightMotor,25);
	}
	// set break
	while (getColorName(colorSensor) != colorWhite){
		setMotorSpeed(leftMotor,50);
		setMotorSpeed(rightMotor,25);
	}
	while (getColorName(colorSensor) != colorBlack){
		setMotorSpeed(leftMotor,50);
		setMotorSpeed(rightMotor,25);
	}
	while (getColorName(colorSensor) != colorWhite){
		setMotorSpeed(leftMotor,25);
		setMotorSpeed(rightMotor,25);
	}
	setMotorSpeed(leftMotor,0);
	setMotorSpeed(rightMotor,0);

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
			else if(getColorName(colorSensor) == colorBlue){
				motor[leftMotor] = 0;
				motor[rightMotor] = 0;
				break;
			}
		}
	}
}

void putar(int sdt){
	int sudut;
	sudut = getGyroDegrees(gyroSensor);
	while((sudut - getGyroDegrees(gyroSensor))<=sdt){
		setMotorSpeed(leftMotor,-20);
		setMotorSpeed(rightMotor,20);
	}

}

void belokSkip(int sdt){
	int sudut = getGyroDegrees(gyroSensor);
	while ((getGyroDegrees(gyroSensor)-sudut)<=sdt){
		setMotorSpeed(leftMotor,50);
		setMotorSpeed(rightMotor,25);
	}
}

void FindBlue(){
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
			else if(getColorName(colorSensor) == colorBlue){
				motor[leftMotor] = 0;
				motor[rightMotor] = 0;
				break;
			}
		}
	}
}

bool kunjungiLagi(ElTree titik){
	bool ret;
	if(Alamat(titik)== 0){
		ret = false;
	}else if(Alamat(titik)==1){//cek akar
		ret = (!(JmlAnak(titik)==1));
	}else if(Alamat(titik)>1){//rekurens
		if(JmlAnak(titik)==1){
			ret = kunjungiLagi(T.Elm[Bapak(titik)]);
		}else{
			ret = true;
		}
	}
	return ret;
}

void pulanglompat(ElTree *E){
	int j;
	if(Alamat(*E)>1){
		FindPoint();
		backward(0.3);
//		turn1();//disini
			if(AnakKe(*E)==1){
				Anak2(T.Elm[Bapak(*E)]) = 0;
				Anak3(T.Elm[Bapak(*E)]) = 0;
			}else if(AnakKe(*E)==2){
				Anak1(T.Elm[Bapak(*E)]) = 0;
				Anak3(T.Elm[Bapak(*E)]) = 0;
			}else if(AnakKe(*E)==3){
				Anak1(T.Elm[Bapak(*E)]) = 0;
				Anak2(T.Elm[Bapak(*E)]) = 0;
			}

		// kalau dia udh pernah diunjungi > 1 kali, maka gausah itung cabang anak anaknya
		for(j=AnakKe(*E)+1;j<=3;j++){
			int altemp = Alamat(*E);
			if(j==1){
				if(Anak1(T.Elm[Bapak(*E)])==0){
					putar(50);
					belokSkip(50);
				}
			}else if(j==2){
				if(Anak2(T.Elm[Bapak(*E)])==0){
					if (Anak1(T.Elm[Bapak(*E)])!=0){
						putar(50);
					}

					belokSkip(50);
				}
			}else if(j==3){
				if(Anak3(T.Elm[Bapak(*E)])==0){
					if ((Anak1(T.Elm[Bapak(*E)])==0)&&(Anak2(T.Elm[Bapak(*E)])==0)){
						putar(50);
					} else if (Anak2(T.Elm[Bapak(*E)])!=0){
						putar(50);
					}
					displayTextLine(9,"Masuk sini");
					sleep(500);
					displayTextLine(9,"          ");
					belokSkip(50);
				}
			}
		}
		turn1();
		MoveToParent(T,E);
		pulanglompat(E);
	}
}
