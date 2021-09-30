/**************************************************************************
Algorithm to check  MaxKernel in Polygon,
 
	-By Panagiotis Tzivaras 
	
	-University Of Ioanina, Dep of Computer Sciense & Engineering

**************************************************************************/
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <list>
#include <vector>


#if defined (__WIN32__)
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* C++ */
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <ostream>
#include <iomanip>


	using namespace std;


int VerticesNum;//plithos korifon poligonou

int **Vertex = new int *[2];//edo oi korifes poligonou
int *Edge = new int[VerticesNum]; //edo oi akmes tou poligonou

int LowExtremEast,LowExtremWest,LowExtremSouth,LowExtremNorth;
int HighSE, HighSW, HighNE, HighNW;
int LowSE, LowSW, LowNE, LowNW;

int EastExtrNum, WestExtrNum, NorthExtrNum ,SouthExtrNum;//plithos Extremities gia na ftiakso pinaka na tis apothikeuso me sosto megethos meta


int **EastExtr = new int *[2];//pinakas Anatolika Extremities
int **WestExtr = new int *[2];//pinakas Ditika Extremities   
int **NorthExtr= new int *[2];//pinakas Voreia Extremities  
int **SouthExtr= new int *[2];//pinakas Notia Extremities

int chainCounterNW, chainCounterNE, chainCounterSE, chainCounterSW;//plithos stoixeion alisidas/perivlima
int **chainSE= new int *[2];//pinakas alisidas/perivlima
int **chainSW= new int *[2];//ppinakas alisidas/ perivlima  
int **chainNW= new int *[2];//pinakas alisidas/perivlima
int **chainNE= new int *[2];//pinakas alisidas/perivlima


int tangent1SeNw[2][2];//tangents/efaptomenes pinakas pou na tis periexei gia x=0,y=1 kai exei kai tis 2 akres tis
int tangent2SeNw[2][2];
int tangent1NeSw[2][2];
int tangent2NeSw[2][2];

double thetaMin1;
double thetaMax1;
double thetaMin2;
double thetaMax2;
double thetaMin;
double thetaMax;
int Unwbx, Unwby;
int Unwtx, Unwty; 
int Uswbx, Uswby;
int Uswtx, Uswty;


double * AnglesSW;
double * AnglesSE;
double * AnglesNW;
double * AnglesNE;
double * Angles;

int *edgeInAnglesSW;
int *edgeInAnglesSE;
int *edgeInAnglesNW;
int *edgeInAnglesNE;
int *edgeInAngles;

int *anglesCategory; //An i gonia anikei stin alisida SW"0" SE"1" NW"2" NE"3"
	
int totali;//kai sto erotima 5(plithos ton gonion mou sto pinaka Angles)
int uswbPosition, usebPosition, unwbPosition, unebPosition;
int uswtPosition, usetPosition, unwtPosition, unetPosition;

int badz=0;
int nextTimesClicked = 0;

double GLMaxLines[30][8];//apothikeuo simeia tomis gia kathe treksimo
//Telos!
double GlMaxLine1_Point1X, GlMaxLine1_Point1Y, GlMaxLine1_Point2X, GlMaxLine1_Point2Y, GlMaxLine2_Point1X, GlMaxLine2_Point1Y, GlMaxLine2_Point2X, GlMaxLine2_Point2Y;//ta simeia tomis tis akmis me to poligono sta opoia emfanizete megisto emvadon tou trigonou

//==============================================================================
//				FUNCTIONS
//==============================================================================
/*
* Give number of points and allocate rows+columns
* allocate memory Points,Edge
* give coordinates for points and print them
*/
void initialise() {
	int i, j;
	
	//cout << "How many Vertex(x,y) do you want.?.: ";
	//cin  >> VerticesNum;

	//cout << "Number of Vertex:";
	//cout << VerticesNum;
	//cout << endl;
	VerticesNum=30;
	//Use function New to allocate dynamic memory, points and Edge
	for (int i = 0; i < 2; i++){
		Vertex[i] = new int[VerticesNum];
	}

	//Give Coordinates of Vertex(x,y), print the coordinates in screen
	//for (i = 0; i < VerticesNum; i++){
		//cout << "enter X.. :\n";
		//cin >> Vertex[0][i];
		//cout << "enter Y.. :\n";
		//cin >> Vertex[1][i];
	//}
	Vertex[0][0]=3;
	Vertex[1][0]=2;
	
	Vertex[0][1]=6;
	Vertex[1][1]=2;
	
	Vertex[0][2]=6;
	Vertex[1][2]=3;
	
	Vertex[0][3]=7;
	Vertex[1][3]=3;
	
	Vertex[0][4]=7;
	Vertex[1][4]=1;
	
	Vertex[0][5]=8;
	Vertex[1][5]=1;
	
	Vertex[0][6]=8;
	Vertex[1][6]=4;
	
	Vertex[0][7]=9;
	Vertex[1][7]=4;
	
	Vertex[0][8]=9;
	Vertex[1][8]=1;
	
	Vertex[0][9]=10;
	Vertex[1][9]=1;
	
	Vertex[0][10]=10;
	Vertex[1][10]=2;
	
	Vertex[0][11]=13;
	Vertex[1][11]=2;
	
	Vertex[0][12]=13;
	Vertex[1][12]=4;
	
	Vertex[0][13]=12;
	Vertex[1][13]=4;
	
	Vertex[0][14]=12;
	Vertex[1][14]=5;
	
	Vertex[0][15]=13;
	Vertex[1][15]=5;
	
	Vertex[0][16]=13;
	Vertex[1][16]=11;
	
	Vertex[0][17]=9;
	Vertex[1][17]=11;
	
	Vertex[0][18]=9;
	Vertex[1][18]=10;
	
	Vertex[0][19]=8;
	Vertex[1][19]=10;
	
	Vertex[0][20]=8;
	Vertex[1][20]=7;
	
	Vertex[0][21]=7;
	Vertex[1][21]=7;
	
	Vertex[0][22]=7;
	Vertex[1][22]=8;
	
	Vertex[0][23]=6;
	Vertex[1][23]=8;
	
	Vertex[0][24]=6;
	Vertex[1][24]=9;
	
	Vertex[0][25]=3;
	Vertex[1][25]=9;
	
	Vertex[0][26]=3;
	Vertex[1][26]=6;
	
	Vertex[0][27]=5;
	Vertex[1][27]=6;
	
	Vertex[0][28]=5;
	Vertex[1][28]=4;
	
	Vertex[0][29]=3;
	Vertex[1][29]=4;
}









/*    Vertex with coordinates {float x, y;}, So i ll have 2 Variables for X, Y
* isLeft(): test if a Vector is Left|On|Right of an infinite line.
*    Input:  three Vertex P0, P1, and P2
*    Return: >0 for P2 left of the line through P0 and P1
*            =0 for P2 on the line
*            <0 for P2 right of the line
*/
int isLeft( int P0X, int P0Y, int P1X, int P1Y, int P2X, int P2Y )
{
    return (P1X - P0X)*(P2Y - P0Y) - (P2X - P0X)*(P1Y - P0Y);
}











/*
* Check if Polygon is orthogon by checking if next Vector has either x or y the same and again the next point must have the other one the same
* Parameters: 
* Return: Null
*/
void isOrthogon() {
	int i, j;
	int checkXYflag;//an 1 idio Y, an 0 idio X se 2 sinexomena zeugi Vertex
	int orthogonflag=0;//an einai orthogonio
	//edo tha koitakso VerticesNum-1 me arxiko simeio
	if( (Vertex[1][0])==(Vertex[1][VerticesNum-1]) ){//tote tora prepei idio Y
		checkXYflag=1;
	}
	if( (Vertex[0][0])==(Vertex[0][VerticesNum-1]) ){//tote tora prepei idio Y
		checkXYflag=0;
	}
	i=1;	
	
	//edo tha koitakso ola ta  Vertex ektos apo mia periptosi pou tin koitaksa pio pano
	while(i < VerticesNum ){

		if(checkXYflag==0){//an prin idio X
			if( (Vertex[1][i])==(Vertex[1][i-1]) ){//tote tora prepei idio Y
				checkXYflag=1;//idio Y
			}else{
				orthogonflag=1;
			}
		}else if(checkXYflag==1){//an prin idio Y
           	 	if( (Vertex[0][i])==(Vertex[0][i-1]) ){//tote tora prepei idio X
            	    		checkXYflag=0;//idio X
           	 	}else{
            			orthogonflag=1;
			}
        	}else{
        		orthogonflag=1;
        	}                       
		i=i+1;
    	}
//edo tha tiposo an einai orthogonio
	if(orthogonflag==0){
                cout << "\n";
                cout << "Polygon is Orthogon..\n";
              
	}else{
		cout << "Polygon is not Orthogon..\n";
	}
	
}









/*
*1# Find North-South-East-West Edge
*2# Find Extremities in polygon,e.g check if an north edge is also an Extremity
*3# Find how many Extremities there are
*4# Find lowest Extremity
*5# Initialise 4 arrays of extermies
*/
void extremityEdge() {
	//This code will find all the extremities of the orthogon polygon,in order to do so i will find first the N S E W Edge.    
	//pigaino aristerostrofa
	//0 -> Anatoliki
	//1 -> Ditiki
	//2 -> Boreia
	//3 -> Notia
	
	int i, j;
	for (j = 0; j < (VerticesNum-1); j++){  //gia na mi diavasei to teleuteo simeia gt seg fault
        
		for (i = 0; i < 2; i++){
			if( (Vertex[0][j+1]) == (Vertex[0][j]) ){//epomeno stoixeio exei idio X
			
                		if( (Vertex[1][j+1]) > (Vertex[1][j]) ){//epomeno stoixeio megalitero Y
                   			Edge[j]=0;//anatoliki akmi
                		}
                		
                		if( (Vertex[1][j+1]) < (Vertex[1][j]) ){//epomeno stoixeio mikrotero Y
					Edge[j]=1;//ditiki akmi
                		}
			}
            
			if( (Vertex[1][j+1]) == (Vertex[1][j]) ){//epomeno stoixeio exei idio Y
			
				if( (Vertex[0][j+1]) > (Vertex[0][j]) ){//epomeno stoixeio megalitero X
               	     			Edge[j]=3;//notia akmi
               	 		}
               	 		
                		if( (Vertex[0][j+1]) < (Vertex[0][j]) ){//epomeno stoixeio mikrotero X
                	   		 Edge[j]=2;//Boreia akmi
                		}
			}
	               
		}
	} 
   
//edo tha elekso ti teleutea
	for (i = 0; i < 2; i++){
		if( (Vertex[0][0]) == (Vertex[0][VerticesNum-1]) ){//epomeno stoixeio exei idio X
		
			if( (Vertex[1][0]) > (Vertex[1][VerticesNum-1]) ){//epomeno stoixeio megalitero Y
				Edge[j]=0;//anatoliki akmi
			}
			
			if( (Vertex[1][0]) < (Vertex[1][VerticesNum-1]) ){//epomeno stoixeio mikrotero Y
				Edge[j]=1;//ditiki akmi
			}
		}
            
		if( (Vertex[1][0]) == (Vertex[1][VerticesNum-1]) ){//epomeno stoixeio exei idio Y
			
			if( (Vertex[0][0]) > (Vertex[0][VerticesNum-1]) ){//epomeno stoixeio megalitero X
				Edge[j]=3;//notia akmi
			}
			
			if( (Vertex[0][0]) < (Vertex[0][VerticesNum-1]) ){//epomeno stoixeio mikrotero X
				Edge[j]=2;//Boreia akmi
			}
		}
	}
   
	

//Gia melontiko skopo tha vro plithos extremeties.................................
int EastExtrNum, WestExtrNum, NorthExtrNum ,SouthExtrNum;
EastExtrNum=WestExtrNum=NorthExtrNum=SouthExtrNum=0;
//................................................................................
//Tora tha vro ta extremities genika ektos apo 3 akmes,2 prin kai 1 meta to arxiko simeio
	for (i = 1; i < VerticesNum-2; i++){// den tis pairno oles tis akmes tora
        	if( (Edge[i])==(0) ){
        	
         		if( ( (Vertex[0][i-1])<(Vertex[0][i]) )  && ( (Vertex[0][i+2])<(Vertex[0][i]) ) ){
                		Edge[i]=4;//anatoliko Extremity
                		EastExtrNum=EastExtrNum+1;
            		}
            		
        	}
        	
       		if( (Edge[i])==(1) ){
       		
            		if( ( (Vertex[0][i-1])>(Vertex[0][i]) )  && ( (Vertex[0][i+2])>(Vertex[0][i]) ) ){
                		Edge[i]=5;//ditiko Extremity
               			WestExtrNum=WestExtrNum+1;
            		}
            		
        	}
        	
        	if( (Edge[i])==(2) ){
        	
            		if( ( (Vertex[1][i-1])<(Vertex[1][i]) )  && ( (Vertex[1][i+2])<(Vertex[1][i]) ) ){
               			//Voreia_Extremity
                		Edge[i]=6;
                		NorthExtrNum=NorthExtrNum+1;
           		}
           		
        	}
        	
       		if( (Edge[i])==(3) ){
       		
			if( ( (Vertex[1][i-1])>(Vertex[1][i]) )  && ( (Vertex[1][i+2])>(Vertex[1][i]) ) ){
				//Notia_Extremity
       	         		Edge[i]=7;
        	       	 SouthExtrNum=SouthExtrNum+1;
         	   	}
        	}
	}
//edo tha kano tis alles 3 petiproseis
    
//-2 akmi prin tin arxi
	if( (Edge[VerticesNum-2])==(0) ){
		if( ( (Vertex[0][VerticesNum-3])<(Vertex[0][VerticesNum-2]) )  && ( (Vertex[0][0])<(Vertex[0][VerticesNum-2]) ) ){
			//Anatoliki_Extremity
			Edge[VerticesNum-2]=4;
			EastExtrNum=EastExtrNum+1;
       		}
	}
	
	if( (Edge[VerticesNum-2])==(1) ){
		if( ( (Vertex[0][VerticesNum-3])>(Vertex[0][VerticesNum-2]) )  && ( (Vertex[0][0])>(Vertex[0][VerticesNum-2]) ) ){
            		//Ditiki Extremetie
            		Edge[VerticesNum-2]=5;
            		WestExtrNum=WestExtrNum+1;
        	}
    	}
    	
	if( (Edge[VerticesNum-2])==(2) ){
		if( ( (Vertex[1][VerticesNum-3])<(Vertex[1][VerticesNum-2]) )  && ( (Vertex[1][0])<(Vertex[1][VerticesNum-2]) ) ){
			//Voreia_Extremity
            		Edge[VerticesNum-2]=6;
            		NorthExtrNum=NorthExtrNum+1;
        	}
   	 }
   	 
	if( (Edge[VerticesNum-2])==(3) ){
		if( ( (Vertex[1][VerticesNum-3])>(Vertex[1][VerticesNum-2]) )  && ( (Vertex[1][0])>(Vertex[1][VerticesNum-2]) ) ){
              		//Notia_Extremity
           		 Edge[VerticesNum-2]=7;
            		SouthExtrNum=SouthExtrNum+1;
       	 	}
    	}
        
//1 akmi prin tin arxi
	if( (Edge[VerticesNum-1])==(0) ){
		if( ( (Vertex[0][VerticesNum-2])<(Vertex[0][VerticesNum-1]) )  && ( (Vertex[0][1])<(Vertex[0][0]) ) ){
			//Anatoliki_Extremity
                	Edge[VerticesNum-1]=4;
               	 	EastExtrNum=EastExtrNum+1;
            	}
        }
        
        if( (Edge[VerticesNum-1])==(1) ){
        	if( ( (Vertex[0][VerticesNum-2])>(Vertex[0][VerticesNum-1]) )  && ( (Vertex[0][1])>(Vertex[0][0]) ) ){
            		//ditiki_Extremity
			Edge[VerticesNum-1]=5;
               	 	WestExtrNum=WestExtrNum+1;
            	}
        }
        
        if( (Edge[VerticesNum-1])==(2) ){
            	if( ( (Vertex[1][VerticesNum-2])<(Vertex[1][VerticesNum-1]) )  && ( (Vertex[1][1])<(Vertex[1][0]) ) ){
              		//Voreia_Extremity
               		Edge[VerticesNum-1]=6;
               		NorthExtrNum=NorthExtrNum+1;
            	}
        }
        
       	if( (Edge[VerticesNum-1])==(3) ){
            if( ( (Vertex[1][VerticesNum-2])>(Vertex[1][VerticesNum-1]) )  && ( (Vertex[1][1])>(Vertex[1][0]) ) ){
             		//Notia_Extremity
                	Edge[VerticesNum-1]=7;
                	SouthExtrNum=SouthExtrNum+1;
            	}
        }
        
//kai i arxi diladi i 1 akmi meta tin arxi
	if( (Edge[0])==(0) ){
        	if( ( (Vertex[0][VerticesNum-1])<(Vertex[0][0]) )  && ( (Vertex[0][2])<(Vertex[0][1]) ) ){
              		//Anatoliki_Extremity
                	Edge[0]=4;
                	EastExtrNum=EastExtrNum+1;
            	}
        }
        
        if( (Edge[0])==(1) ){
            	if( ( (Vertex[0][VerticesNum-1])>(Vertex[0][0]) )  && ( (Vertex[0][2])>(Vertex[0][1]) ) ){
              		//ditiki_Extremity
              		Edge[0]=5;
              		WestExtrNum=WestExtrNum+1;
            	}
        }
        
        if( (Edge[0])==(2) ){
            	if( ( (Vertex[1][VerticesNum-1])<(Vertex[1][0]) )  && ( (Vertex[1][2])<(Vertex[1][1]) ) ){
            		//Voreia_Extremity
               	 	Edge[0]=6;
               	 	NorthExtrNum=NorthExtrNum+1;
            	}
        }
        
	if( (Edge[0])==(3) ){
		if( ( (Vertex[1][VerticesNum-1])>(Vertex[1][0]) )  && ( (Vertex[1][2])>(Vertex[1][1]) ) ){
			//South_Extremity";
			Edge[0]=7;
			SouthExtrNum=SouthExtrNum+1;
		}
	}
//as ektiposo ton pinaka Edge na do ti exei mesa gia elenxo lathon sto programa
//0 -> Anatoliki
//1 -> Ditiki
//2 -> Boreia
//3 -> Notia
//px mia Anatoliki akmi ginetai Anatoliki Extremitie
//4 -> Anatoliko Extremities
//5 -> Ditiko Extremities
//6 -> Boreio Extremities
//7 -> Notio Extremities
	


//tora thelo na vro  ti thesi tou xamiloterou anatolikou extremetie
int LowExtremEast=-1;
	for (i = 0; i < VerticesNum; i++){
		if( ( Edge[i] )==(4) ){
			if(  (LowExtremEast>=0)&&(LowExtremEast<VerticesNum)  ){
				if( (Vertex[1][i])<(Vertex[1][LowExtremEast]) ){
					LowExtremEast=i; 
				}
			}else{
				LowExtremEast=i;
 			}
		}
	}
	
	
	
//tora thelo na vro  ti thesi tou xamiloterou Notio extremetie
int LowExtremSouth=-1;
	for (i = 0; i < VerticesNum; i++){
		if( ( Edge[i] )==(7) ){
			if(  (LowExtremSouth>=0)&&(LowExtremSouth<VerticesNum)  ){
				if( (Vertex[0][i])<(Vertex[0][LowExtremSouth]) ){
					LowExtremSouth=i; 
				}
			}else{
				LowExtremSouth=i;
			}
		}
	}
	
	
//tora thelo na vro  ti thesi tou xamiloterou Ditiko extremetie
int LowExtremWest=-1;
	for (i = 0; i < VerticesNum; i++){
		if( ( Edge[i] )==(5) ){
			if(  (LowExtremWest>=0)&&(LowExtremWest<VerticesNum)  ){
				if( (Vertex[1][i])>(Vertex[1][LowExtremWest]) ){
					LowExtremWest=i; 
				}
			}else{
				LowExtremWest=i;
			}
		}
	}
	
		
//tora thelo na vro  ti thesi tou xamiloterou Voreio extremetie
int LowExtremNorth=-1;
	for (i = 0; i < VerticesNum; i++){
		if( ( Edge[i] )==(6) ){
			if(  (LowExtremNorth>=0)&&(LowExtremNorth<VerticesNum)  ){
				if( (Vertex[0][i])>(Vertex[0][LowExtremNorth]) ){
					LowExtremNorth=i; 
				}
            		}else{
                		LowExtremNorth=i;
            		}
		}
	}
	
	
//..................................................................................
//Exo Vrei plithos Kathe Extremetie,..Orizo 4 pinakes gia 4 katigories extremeties 
int **EastExtr = new int *[2];//pinakas Anatolika Extremities
	for (int i = 0; i < 2; i++){
		EastExtr[i] = new int[EastExtrNum];
	}
    
int **WestExtr = new int *[2];//pinakas Ditika Extremities
	for (int i = 0; i < 2; i++){
		WestExtr[i] = new int[WestExtrNum];
	}
    
int **NorthExtr= new int *[2];//pinakas Voreia Extremities
	for (int i = 0; i < 2; i++){
		NorthExtr[i] = new int[NorthExtrNum];
	}
    
int **SouthExtr= new int *[2];//pinakas Notia Extremities
	for (int i = 0; i < 2; i++){
		SouthExtr[i] = new int[SouthExtrNum];
	}
    
int EastCounter =0;//voithaei gia tin ekxorisi timon tous pinakes,tha einai kata ena megalitero tou plithun ton pinakon
int WestCounter =0;//voithaei gia tin ekxorisi timon tous pinakes,   ... //...
int NorthCounter=0;//voithaei gia tin ekxorisi timon tous pinakes,   ... //...
int SouthCounter=0;//voithaei gia tin ekxorisi timon tous pinakes,    ...//...
//..................................................................................
//kai tha valo ta extremeties xorista se 4 pinakes pou vrika to plithos tous pio prin
//mexri VerticesNum-1 eksetias Segmentation fault
//an kapoio elaxisto einai telos pinaka i proteleuteo pinaka thelei prosoxi
//giati iparxei kai o periorismos pou exo eksetias Segmentation fault diladi den mporo na diavaso olo to pinaka




//Auto einai giati isos valo to teliko simeio isos iso me kapoio elaxisto 
	if((LowExtremEast)==(VerticesNum-1)){
		EastExtr[0][EastCounter]=Vertex[1][VerticesNum-1];
		EastExtr[1][EastCounter]=Vertex[1][0];
		EastCounter=EastCounter+1;
	}
	if((LowExtremWest)==(VerticesNum-1)){
		WestExtr[0][WestCounter]=Vertex[1][VerticesNum-1];
		WestExtr[1][WestCounter]=Vertex[1][0];
		WestCounter=WestCounter+1;
	}
	if((LowExtremSouth)==(VerticesNum-1)){
		SouthExtr[0][SouthCounter]=Vertex[0][VerticesNum-1];
		SouthExtr[1][SouthCounter]=Vertex[0][0];
		SouthCounter=SouthCounter+1;
	}
	if((LowExtremNorth)==(VerticesNum-1)){
		NorthExtr[0][NorthCounter]=Vertex[0][VerticesNum-1];
		NorthExtr[1][NorthCounter]=Vertex[0][0];
		NorthCounter=NorthCounter+1;
	}

//edo isos valo to proteleuteo simeio isos iso me kapoio elaxisto
	if((LowExtremEast)==(VerticesNum-2)){
		EastExtr[0][EastCounter]=Vertex[1][VerticesNum-2];
		EastExtr[1][EastCounter]=Vertex[1][VerticesNum-1];
		EastCounter=EastCounter+1;
	}
	if((LowExtremWest)==(VerticesNum-2)){
		WestExtr[0][WestCounter]=Vertex[1][VerticesNum-2];
		WestExtr[1][WestCounter]=Vertex[1][VerticesNum-1];
		WestCounter=WestCounter+1;
	}
	if((LowExtremSouth)==(VerticesNum-2)){
		SouthExtr[0][SouthCounter]=Vertex[0][VerticesNum-2];
		SouthExtr[1][SouthCounter]=Vertex[0][VerticesNum-1];
		SouthCounter=SouthCounter+1;
	}
	if((LowExtremNorth)==(VerticesNum-2)){
		NorthExtr[0][NorthCounter]=Vertex[0][VerticesNum-2];
		NorthExtr[1][NorthCounter]=Vertex[0][VerticesNum-1];
		NorthCounter=NorthCounter+1;
	}
	
	


	
//molis ekana colcoount-1 kai VerticesNum-2 gia ta elaxista
// kai tora  tis periptoseis tis alles


//..1....Ektipose East Extremities apo Elaxisto mexri kai VerticesNum-3
	for (i = LowExtremEast; i < VerticesNum-2; i++){//12 simeia,apo 0 eos 11 ->(ginetai)-> 0 eos 10
		if( ( Edge[i] )==4 ){
			//Anatoliko Extremity
			EastExtr[0][EastCounter]=Vertex[1][i];
			EastExtr[1][EastCounter]=Vertex[1][i+1];
			EastCounter=EastCounter+1;
        	}
	}
//gia vale kai to VerticesNum-2 tora,An itan elaxisto bike pio prin
	if((LowExtremEast)!=(VerticesNum-2)){
		//VerticesNum-2 benei tora
		if( ( Edge[VerticesNum-2] )==4 ){
			EastExtr[0][EastCounter]=Vertex[1][VerticesNum-2];
			EastExtr[1][EastCounter]=Vertex[1][VerticesNum-1];
			EastCounter=EastCounter+1;
		}
	}
//gia vale kai to VerticesNum-1 tora,An itan elaxisto bike pio prin
	if((LowExtremEast)!=(VerticesNum-1)){
		//VerticesNum-1 benei tora
		if( ( Edge[VerticesNum-1] )==4 ){
			EastExtr[0][EastCounter]=Vertex[1][VerticesNum-1];		
			EastExtr[1][EastCounter]=Vertex[1][0];	
			EastCounter=EastCounter+1;
		}
	}
//gia vale kai 0 eos Elaxisto tora kai eimai koble gia East Extremity
	for (i = 0; i < LowExtremEast; i++){
		if( ( Edge[i] )==4 ){
			//Anatoliko_Extremity\n";
			EastExtr[0][EastCounter]=Vertex[1][i];
			EastExtr[1][EastCounter]=Vertex[1][i+1];
			EastCounter=EastCounter+1;
		}
 	}

//..2...Ektipose North Extremities apo Elaxisto mexri kai VerticesNum-3
	for (i = LowExtremNorth; i < VerticesNum-2; i++){
        	if( ( Edge[i] )==6 ){ 
			//South Extremity
			NorthExtr[0][NorthCounter]=Vertex[0][i];
			NorthExtr[1][NorthCounter]=Vertex[0][i+1];
			NorthCounter=NorthCounter+1;
		}
	}
//gia vale kai to VerticesNum-2 tora,An itan elaxisto bike pio prin
	if((LowExtremNorth)!=(VerticesNum-2)){
		//VerticesNum-2 benei tora
		if( ( Edge[VerticesNum-2] )==6 ){ 
			NorthExtr[0][NorthCounter]=Vertex[0][VerticesNum-2];
			NorthExtr[1][NorthCounter]=Vertex[0][VerticesNum-1];
			NorthCounter=NorthCounter+1;
		}
	}
//gia vale kai to VerticesNum-1 tora,An itan elaxisto bike pio prin
	if((LowExtremNorth)!=(VerticesNum-1)){
		//VerticesNum-1 benei tora
		if( ( Edge[VerticesNum-1] )==6 ){ 
			NorthExtr[0][NorthCounter]=Vertex[0][VerticesNum-1];
			NorthExtr[1][NorthCounter]=Vertex[0][0];
			NorthCounter=NorthCounter+1;
		}
	}
//gia vale kai 0 eos Elaxisto tora kai eimai koble gia North Extremity
	for (i = 0; i < LowExtremNorth; i++){
		if( ( Edge[i] )==6 ){
        		//North_Extremity
			NorthExtr[0][NorthCounter]=Vertex[0][i];
			NorthExtr[1][NorthCounter]=Vertex[0][i+1];
			NorthCounter=NorthCounter+1;
		}
	}


//..3...Ektipose West Extremities apo elaxisto mexri kai VerticesNum-3
	for (i = LowExtremWest; i < VerticesNum-2; i++){
		if( ( Edge[i] )==5 ){
			//West_Extremity
			WestExtr[0][WestCounter]=Vertex[1][i];
			WestExtr[1][WestCounter]=Vertex[1][i+1];
			WestCounter=WestCounter+1;
		}
	}
//gia vale kai to VerticesNum-2 tora,An itan elaxisto bike pio prin
	if((LowExtremWest)!=(VerticesNum-2)){
		//VerticesNum-2 benei tora
		if( ( Edge[VerticesNum-2] )==5 ){
			WestExtr[0][WestCounter]=Vertex[1][VerticesNum-2];
			WestExtr[1][WestCounter]=Vertex[1][VerticesNum-1];
			WestCounter=WestCounter+1;
		}
	}
//gia vale kai to VerticesNum-1 tora,An itan elaxisto bike pio prin
	if((LowExtremWest)!=(VerticesNum-1)){
		//VerticesNum-1 benei tora
		if( ( Edge[VerticesNum-1] )==5 ){
			WestExtr[0][WestCounter]=Vertex[1][VerticesNum-1];
			WestExtr[1][WestCounter]=Vertex[1][0];
			WestCounter=WestCounter+1;
		}
	}		
//gia vale kai 0 eos Elaxisto tora kai eimai koble gia North Extremity	
	for (i = 0; i < LowExtremWest; i++){
		if( ( Edge[i] )==5 ){
			//West_Extremity
			WestExtr[0][WestCounter]=Vertex[1][i];
			WestExtr[1][WestCounter]=Vertex[1][i+1];
			WestCounter=WestCounter+1;
		}
	}

//..4...Ektipose South Extremities apo Elaxisto mexri kai VerticesNum-3
	for (i = LowExtremSouth; i < VerticesNum-2; i++){
		if( ( Edge[i] )==7 ){
		//South_Extremity;
		SouthExtr[0][SouthCounter]=Vertex[0][i];
		SouthExtr[1][SouthCounter]=Vertex[0][i+1];
		SouthCounter=SouthCounter+1;
		}
	}
//gia vale kai to VerticesNum-2 tora,An itan elaxisto bike pio prin
	if((LowExtremSouth)!=(VerticesNum-2)){
		//VerticesNum-2 benei tora
		if( ( Edge[VerticesNum-2] )==7 ){
			SouthExtr[0][SouthCounter]=Vertex[0][VerticesNum-2];
			SouthExtr[1][SouthCounter]=Vertex[0][VerticesNum-1];
			SouthCounter=SouthCounter+1;
		}	
	}
//gia vale kai to VerticesNum-1 tora,An itan elaxisto bike pio prin
	if((LowExtremWest)!=(VerticesNum-1)){
		//VerticesNum-1 benei tora
		if( ( Edge[VerticesNum-1] )==7 ){
			SouthExtr[0][SouthCounter]=Vertex[0][VerticesNum-1];
			SouthExtr[1][SouthCounter]=Vertex[0][0];
			SouthCounter=SouthCounter+1;
		}
	}	
//gia vale kai 0 eos Elaxisto tora kai eimai koble gia South Extremity	
	for (i = 0; i < LowExtremSouth; i++){
		if( ( Edge[i] )==7 ){   
		//South_Extremity\n";
		SouthExtr[0][SouthCounter]=Vertex[0][i];
		SouthExtr[1][SouthCounter]=Vertex[0][i+1];
		SouthCounter=SouthCounter+1;
		}
	}

}










/*
* des an ta sinora einai monotona
*/
void check_monotonicity() {
	//******************************************************************************
	//******************************************************************************
	//                Tha eksetasto an ta sinora einai monotona
	//******************************************************************************
	//******************************************************************************
	int FlagKernel=0;//0 iparxei, 1 den iparxei
	int i, j;

//elenxo alatolika Extremeties
	
	cout <<"Checking monotonicity..\n";
	
	for (i = 1; i < EastExtrNum; i++){
		if(  (EastExtr[0][i])<(EastExtr[1][i-1])  ){
			FlagKernel=1; 
			
		}
	}
	
//elenxo voreia Extremeties   
	for (i = 1; i < NorthExtrNum; i++){
		if(  (NorthExtr[0][i]>NorthExtr[1][i-1])  ){
			FlagKernel=1; 
			
		}
	}
//elenxo ditika Extremeties 
	for (i = 1; i <  WestExtrNum; i++){
		if(  ( WestExtr[0][i])> (WestExtr[1][i-1])  ){
			FlagKernel=1; 
			
		}
	}
//elenxo notia Extremeties    
	for (i = 1; i < SouthExtrNum; i++){
		if(  (SouthExtr[0][i])<(SouthExtr[1][i-1])  ){
			FlagKernel=1;
			
		}
	}
//Here print if kernel exists or not
 	if((FlagKernel)==(0)){
		cout <<"Kernel is not empty\n"; 
	}else{
		cout <<"Kernel is empty\n"; 
	}
	
}










/*
* check what kind of Corners does the polygon have
*/
void checkCorners() {
//******************************************************************************
//******************************************************************************
//            Tora tha vro an oi gonies einai SE - SW - NE - NW
//******************************************************************************
//******************************************************************************
//0 -> Anatoliki
//1 -> Ditiki
//2 -> Boreia
//3 -> Notia
int i, j;
//alles tha einai oi deksies kai alles oi aristeres
HighSE=HighSW=HighNE=HighNW=-1;
LowSE=LowSW=LowNE=LowNW=-1;
		
//i=0,1,VerticesNum-1 na tis valo tora kai meta genika
//......................................tora periptosi i=0k kai meta ta alla

		//edo einai SE
		if( ( (Edge[VerticesNum-1])==(0) )&&( (Edge[0])==(3) ) ){

			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighSE)==(-1)){
				if( (Edge[1])==(4) ){
					HighSE=0;
				}
			}
			if((LowSE)==(-1)){
				if(  (Edge[VerticesNum-2])==(7) ){
					LowSE=0;
				}
			}
			//tora to pio psilo
			if( (Vertex[1][0])>(Vertex[1][HighSE]) ){
				if( (Edge[1])==(4) ){
					HighSE=0;
				}
			}
			//tora to pio xamilo
			if( (Vertex[0][0])<(Vertex[0][LowSE]) ){
				if( (Edge[VerticesNum-2])==(7) ){
					LowSE=0;
				}
			}
		}
		//edo einai SW
		if( ( (Edge[VerticesNum-1])==(3) )&&( (Edge[0])==(1) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if(HighSW==(-1)){
				if( (Edge[VerticesNum-2])==(5) ){
					HighSW=0;
				}
			}
			if((LowSW)==(-1)) {
				if( (Edge[1])==(7) ){
					LowSW=0;	
				}			
			}
			//tora to pio psilo
			if( (Vertex[1][0])>(Vertex[1][HighSW]) ){
				if( (Edge[VerticesNum-2])==(5) ){
					HighSW=0;	
				}					
					
			}
			//tora to pio xamilo
			if( (Vertex[0][0])>(Vertex[0][LowSW]) ) {
				if( (Edge[1])==(7) ){
					LowSW=0;	
				}
			}
		}
		//edo einai NE
		if( ( (Edge[VerticesNum-1])==(2) )&&( (Edge[0])==(0) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighNE)==(-1) ){
				if( (Edge[1])==(6) ){
					HighNE=0;					
				}
			}
			if( (LowNE)==(-1) ) {
				if( (Edge[VerticesNum-2])==(4) ){
					LowNE=0;					
				}			
			}
			//tora to pio psilo
			if(  (Vertex[0][0])<(Vertex[0][HighNE]) ){
				if( (Edge[1])==(6) ){
					HighNE=0;
				}
			}
			//tora to pio xamilo
			if( (Vertex[1][0])<(Vertex[1][LowNE]) ){
				if( (Edge[VerticesNum-2])==(4) ){
					LowNE=0;
				}
			}
		}
		//edo einai NW
		if( ( (Edge[VerticesNum-1])==(1) )&&( (Edge[0])==(2) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighNW)==(-1) ){
				if( (Edge[VerticesNum-2])==(6) ){
					HighNW=0;			
				}
			}
			if( (LowNW)==(-1) ){
				if( (Edge[1])==(5) ){
					LowNW=0;				
				}
			}
			//tora to pio psilo
			if( (Vertex[0][0])>(Vertex[0][HighNW]) ){
				if( (Edge[VerticesNum-2])==(6) ){
					HighNW=0;
				}
			}
			//tora to pio xamilo
			if( (Vertex[1][0])<(Vertex[1][LowNW]) ){
				if( (Edge[1])==(5) ){
					LowNW=0;
				}
			}
		}
		
		
		
		
			
//.	
//........................................................tora  periptosi gia  i=1
//.
		//edo einai SE
		if( ( (Edge[0])==(0) )&&( (Edge[1])==(3) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighSE)==(-1)){
				if( (Edge[2])==(4) ){
					HighSE=1;
				}
			}
			if((LowSE)==(-1)){
				if(  (Edge[VerticesNum-1])==(7) ){
					LowSE=1;
				}
			}
			//tora to pio psilo
			if( (Vertex[1][1])>(Vertex[1][HighSE]) ){
				if( (Edge[2])==(4) ){
					HighSE=1;
				}
			}
			//tora to pio xamilo
			if( (Vertex[0][1])<(Vertex[0][LowSE]) ){
				if( (Edge[VerticesNum-1])==(7) ){
					LowSE=1;	
				}
			}
		}
		//edo einai SW
		if( ( (Edge[0])==(3) )&&( (Edge[1])==(1) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if(HighSW==(-1)){
				if( (Edge[VerticesNum-1])==(5) ){
					HighSW=1;
				}
			}
			if((LowSW)==(-1)) {
				if( (Edge[2])==(7) ){
					LowSW=1;
				}			
			}
			//tora to pio psilo
			if( (Vertex[1][1])>(Vertex[1][HighSW]) ){
				if( (Edge[VerticesNum-1])==(5) ){
					HighSW=1;
				}					
					
			}
			//tora to pio xamilo
			if( (Vertex[0][1])>(Vertex[0][LowSW]) ) {
				if( (Edge[2])==(7) ){
					LowSW=1;
				}
			}
		}
		//edo einai NE
		if( ( (Edge[0])==(2) )&&( (Edge[1])==(0) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighNE)==(-1) ){
				if( (Edge[2])==(6) ){
					HighNE=1;				
				}
			}
			if( (LowNE)==(-1) ) {
				if( (Edge[VerticesNum-1])==(4) ){
					LowNE=1;			
				}			
			}
			//tora to pio psilo
			if(  (Vertex[0][1])<(Vertex[0][HighNE]) ){
				if( (Edge[2])==(6) ){
					HighNE=1;
				}
			}
			//tora to pio xamilo
			if( (Vertex[1][1])<(Vertex[1][LowNE]) ){
				if( (Edge[VerticesNum-1])==(4) ){
					LowNE=1;
				}
			}
		}
		//edo einai NW
		if( ( (Edge[0])==(1) )&&( (Edge[1])==(2) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighNW)==(-1) ){
				if( (Edge[VerticesNum-1])==(6) ){
					HighNW=1;			
				}
			}
			if( (LowNW)==(-1) ){
				if( (Edge[2])==(5) ){
					LowNW=1;				
				}
			}
			//tora to pio psilo
			if( (Vertex[0][1])>(Vertex[0][HighNW]) ){
				if( (Edge[VerticesNum-1])==(6) ){
					HighNW=1;
				}
			}
			//tora to pio xamilo
			if( (Vertex[1][1])<(Vertex[1][LowNW]) ){
				if( (Edge[2])==(5) ){
					LowNW=1;
				}
			}
		}
		
		
		
		
//......
//tora periptosi i=VerticesNum-1 kai meta tis genikes periotoseis
//......
		//edo einai SE
		if( ( (Edge[VerticesNum-2])==(0) )&&( (Edge[VerticesNum-1])==(3) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighSE)==(-1)){
				if( (Edge[0])==(4) ){
					HighSE=VerticesNum-1;
				}
			}
			if((LowSE)==(-1)){
				if(  (Edge[VerticesNum-3])==(7) ){
					LowSE=VerticesNum-1;
				}
			}
			//tora to pio psilo
			if( (Vertex[1][VerticesNum-1])>(Vertex[1][HighSE]) ){
				if( (Edge[0])==(4) ){
					HighSE=VerticesNum-1;
				}
			}
			//tora to pio xamilo
			if( (Vertex[0][VerticesNum-1])<(Vertex[0][LowSE]) ){
				if( (Edge[VerticesNum-3])==(7) ){
					LowSE=VerticesNum-1;
				}
			}
		}
		//edo einai SW
		if( ( (Edge[VerticesNum-2])==(3) )&&( (Edge[VerticesNum-1])==(1) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if(HighSW==(-1)){
				if( (Edge[VerticesNum-3])==(5) ){
					HighSW=VerticesNum-1;
				}
			}
			if((LowSW)==(-1)) {
				if( (Edge[0])==(7) ){
					LowSW=VerticesNum-1;
				}			
			}
			//tora to pio psilo
			if( (Vertex[1][VerticesNum-1])>(Vertex[1][HighSW]) ){
				if( (Edge[VerticesNum-3])==(5) ){
					HighSW=VerticesNum-1;
				}					
					
			}
			//tora to pio xamilo
			if( (Vertex[0][VerticesNum-1])>(Vertex[0][LowSW]) ) {
				if( (Edge[0])==(7) ){
					LowSW=VerticesNum-1;
				}
			}
		}
		//edo einai NE
		if( ( (Edge[VerticesNum-2])==(2) )&&( (Edge[VerticesNum-1])==(0) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighNE)==(-1) ){
				if( (Edge[0])==(6) ){
					HighNE=VerticesNum-1;				
				}
			}
			if( (LowNE)==(-1) ) {
				if( (Edge[VerticesNum-3])==(4) ){
					LowNE=VerticesNum-1;				
				}			
			}
			//tora to pio psilo
			if(  (Vertex[0][VerticesNum-1])<(Vertex[0][HighNE]) ){
				if( (Edge[0])==(6) ){
					HighNE=VerticesNum-1;
				}
			}
			//tora to pio xamilo
			if( (Vertex[1][VerticesNum-1])<(Vertex[1][LowNE]) ){
				if( (Edge[VerticesNum-3])==(4) ){
					LowNE=VerticesNum-1;
				}
			}
		}
		//edo einai NW
		if( ( (Edge[VerticesNum-2])==(1) )&&( (Edge[VerticesNum-1])==(2) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighNW)==(-1) ){
				if( (Edge[VerticesNum-3])==(6) ){
					HighNW=VerticesNum-1;		
				}
			}
			if( (LowNW)==(-1) ){
				if( (Edge[0])==(5) ){
					LowNW=VerticesNum-1;				
				}
			}
			//tora to pio psilo
			if( (Vertex[0][VerticesNum-1])>(Vertex[0][HighNW]) ){
				if( (Edge[VerticesNum-3])==(6) ){
					HighNW=VerticesNum-1;
				}
			}
			//tora to pio xamilo
			if( (Vertex[1][VerticesNum-1])<(Vertex[1][LowNW]) ){
				if( (Edge[0])==(5) ){
					LowNW=VerticesNum-1;
				}
			}
		}
		
		

//tora tha vro oles tis gonies(SE - SW - NE - NW) ekatos apo tin pano periptosi.
	for (i = 2; i < VerticesNum-1; i++){// den tis pairno oles tis akmes tora
		//edo einai SE
		if( ( (Edge[i-1])==(0) )&&( (Edge[i])==(3) ) ){	
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighSE)==(-1)){
				if( (Edge[i+1])==(4) ){
					HighSE=i;
				}
			}
			if((LowSE)==(-1)){
				if(  (Edge[i-2])==(7) ){
					LowSE=i;
				}
			}
			//tora to pio psilo
			if( (Vertex[1][i])>(Vertex[1][HighSE]) ){
				if( (Edge[i+1])==(4) ){
					HighSE=i;
				}
			}
			//tora to pio xamilo
			if( (Vertex[0][i])<(Vertex[0][LowSE]) ){
				if( (Edge[i-2])==(7) ){
					LowSE=i;
				}
			}
		}
		//edo einai SW
		if( ( (Edge[i-1])==(3) )&&( (Edge[i])==(1) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if(HighSW==(-1)){
				if( (Edge[i-2])==(5) ){
					HighSW=i;
				}
			}
			if((LowSW)==(-1)) {
				if( (Edge[i+1])==(7) ){
					LowSW=i;
				}			
			}
			//tora to pio psilo
			if( (Vertex[1][i])>(Vertex[1][HighSW]) ){
				if( (Edge[i-2])==(5) ){
					HighSW=i;	
				}					
					
			}
			//tora to pio xamilo
			if( (Vertex[0][i])>(Vertex[0][LowSW]) ) {
				if( (Edge[i+1])==(7) ){
					LowSW=i;					
				}
			}
		}
		//edo einai NE
		if( ( (Edge[i-1])==(2) )&&( (Edge[i])==(0) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighNE)==(-1) ){
				if( (Edge[i+1])==(6) ){
					HighNE=i;									
				}
			}
			if( (LowNE)==(-1) ) {
				if( (Edge[i-2])==(4) ){
					LowNE=i;					
				}			
			}
			//tora to pio psilo
			if(  (Vertex[0][i])<(Vertex[0][HighNE]) ){
				if( (Edge[i+1])==(6) ){
					HighNE=i;
				}
			}
			//tora to pio xamilo
			if( (Vertex[1][i])<(Vertex[1][LowNE]) ){
				if( (Edge[i-2])==(4) ){
					LowNE=i;
				}
			}
		}
		//edo einai NW
		if( ( (Edge[i-1])==(1) )&&( (Edge[i])==(2) ) ){
			//tora an den iparxei tipota vale auto kai psilo kai xamilo, giati isos pio pano na min bei
			if( (HighNW)==(-1) ){
				if( (Edge[i-2])==(6) ){
					HighNW=i;			
				}
			}
			if( (LowNW)==(-1) ){
				if( (Edge[i+1])==(5) ){
					LowNW=i;				
				}
			}
			//tora to pio psilo
			if( (Vertex[0][i])>(Vertex[0][HighNW]) ){
				if( (Edge[i-2])==(6) ){
					HighNW=i;
				}
			}
			//tora to pio xamilo
			if( (Vertex[1][i])<(Vertex[1][LowNW]) ){
				if( (Edge[i+1])==(5) ){
					LowNW=i;
				}
			}
		}
	}
	
}










/*
*Melkmans algorithm 
*/
void Melkman() {
//******************************************************************************
//****************************......_Melkman Alisides_...***********************
//******************************************************************************
//Step-1.. Initialize 4 pinakes me X,Y ton simeion ton alisidon
//theoro megethos kathe tetiou pinaka os ola ta simeia tou poligonou gia na
//mi grapso extra kwdika gia tin trexousa fasi toulaxiston
	int i, j;

	int **PointsSE = new int *[2]; //edo ta simeia mou X,Y gia alisida #SE#
	for (int i = 0; i < 2; i++){
		PointsSE[i] = new int[VerticesNum];
	}

	int **PointsNE = new int *[2]; //edo ta simeia mou X,Y gia alisida #NE#
	for (int i = 0; i < 2; i++){
		PointsNE[i] = new int[VerticesNum];
	}

	int **PointsSW = new int *[2]; //edo ta simeia mou X,Y gia alisida #SW#
	for (int i = 0; i < 2; i++){
		PointsSW[i] = new int[VerticesNum];
	}

	int **PointsNW = new int *[2]; //edo ta simeia mou X,Y gia alisida #NW#
	for (int i = 0; i < 2; i++){
		PointsNW[i] = new int[VerticesNum];
	}

int flag;
int TotalSE=0;
int TotalSW=0;
int TotalNE=0;
int TotalNW=0;


	flag=0;//prepei na arxikopiithei 0
	j=0;// einai kai pio pano opote as to kano 0 min ginei kana berdema

//SE Points to take for Maklaren Algorith, apo xamilo se psilo auto vazo
	if((HighSE>=0)&&(LowSE>=0)){
		for (i = LowSE; i < VerticesNum; i++){
			if(i==HighSE){//stop den thelo alla simeia
				flag=1;
				PointsSE[0][j]=Vertex[0][i];
				PointsSE[1][j]=Vertex[1][i];
				TotalSE=TotalSE+1;
			}
			if(flag==0){//ta theloume auta
				PointsSE[0][j]=Vertex[0][i];
				PointsSE[1][j]=Vertex[1][i];
				j=j+1;
				TotalSE=TotalSE+1;
			}
		}



		if(HighSE<LowSE){
			for (i = 0; i < LowSE; i++){
				if(i==HighSE){//stop den thelo alla simeia
					flag=1;
					PointsSE[0][j]=Vertex[0][i];
					PointsSE[1][j]=Vertex[1][i];
					TotalSE=TotalSE+1;
				}
				if(flag==0){//ta theloume auta
					PointsSE[0][j]=Vertex[0][i];
					PointsSE[1][j]=Vertex[1][i];
					j=j+1;
					TotalSE=TotalSE+1;
				}
			}
		}
	}	

		flag=0;
		j=0;
//SW Points to take for Maklaren Algorith, apo psilo se xamilo auto vazo
	if((HighSW>=0)&&(LowSW>=0)){
		for (i = HighSW; i < VerticesNum; i++){
			if(i==LowSW){//stop den thelo alla simeia
				flag=1;
				PointsSW[0][j]=Vertex[0][i];
				PointsSW[1][j]=Vertex[1][i];
				TotalSW=TotalSW+1;
			}
			if(flag==0){//ta theloume auta
				PointsSW[0][j]=Vertex[0][i];
				PointsSW[1][j]=Vertex[1][i];
				j=j+1;
				TotalSW=TotalSW+1;
			}
		}



		if(LowSW<HighSW){
			for (i = 0; i < HighSW; i++){
				if(i==LowSW){//stop den thelo alla simeia
					flag=1;
					PointsSW[0][j]=Vertex[0][i];
					PointsSW[1][j]=Vertex[1][i];
					TotalSW=TotalSW+1;
				}
				if(flag==0){//ta theloume auta
					PointsSW[0][j]=Vertex[0][i];
					PointsSW[1][j]=Vertex[1][i];
					j=j+1;
					TotalSW=TotalSW+1;
				}
			}
		}
	}
	
	flag=0;
	j=0;
//NE Points to take for Maklaren Algorith, apo xamilo se psilo auto vazo
	if((HighNE>=0)&&(LowNE>=0)){
		for (i = LowNE; i < VerticesNum; i++){
			if(i==HighNE){//stop den thelo alla simeia
				flag=1;
				PointsNE[0][j]=Vertex[0][i];
				PointsNE[1][j]=Vertex[1][i];
				TotalNE=TotalNE+1;
			}
			if(flag==0){//ta theloume auta
				PointsNE[0][j]=Vertex[0][i];
				PointsNE[1][j]=Vertex[1][i];
				j=j+1;
				TotalNE=TotalNE+1;
			}
		}



		if(HighNE<LowNE){
			for (i = 0; i < LowNE; i++){
				if(i==HighNE){//stop den thelo alla simeia
					flag=1;
					PointsNE[0][j]=Vertex[0][i];
					PointsNE[1][j]=Vertex[1][i];
					TotalNE=TotalNE+1;
				}
					if(flag==0){//ta theloume auta
					PointsNE[0][j]=Vertex[0][i];
					PointsNE[1][j]=Vertex[1][i];
					j=j+1;
					TotalNE=TotalNE+1;
				}
			}
		}
	}

	flag=0;
	j=0;
//NW Points to take for Maklaren Algorith, apo psilo se xamilo auto vazo
	if((HighNW>=0)&&(LowNW>=0)){
		for (i = HighNW; i < VerticesNum; i++){
			if(i==LowNW){//stop den thelo alla simeia
				flag=1;
				PointsNW[0][j]=Vertex[0][i];
				PointsNW[1][j]=Vertex[1][i];
				TotalNW=TotalNW+1;
			}
			if(flag==0){//ta theloume auta
				PointsNW[0][j]=Vertex[0][i];
				PointsNW[1][j]=Vertex[1][i];
				j=j+1;
				TotalNW=TotalNW+1;
			}
		}



		if(LowNW<HighNW){
			for (i = 0; i < HighNW; i++){
				if(i==LowNW){//stop den thelo alla simeia
					flag=1;
					PointsNW[0][j]=Vertex[0][i];
					PointsNW[1][j]=Vertex[1][i];
					TotalNW=TotalNW+1;
				}
				if(flag==0){//ta theloume auta
					PointsNW[0][j]=Vertex[0][i];
					PointsNW[1][j]=Vertex[1][i];
					j=j+1;
					TotalNW=TotalNW+1;
				}
			}
		}
	}



	flag=0;	

	
//tora exo ta simeia kai tha ta epeksergasto apo ton algorithmo tou Melkman
// initialize a deque D[] from bottom to top so that the
// 1st three vertices of P[] are a ccw triangle 
	
	
//.....................SE................................  
int **D1 = new int *[2]; //2 grammes

	for (int i = 0; i < 2; i++){
		D1[i] = new int[(2*TotalSE)+1];
	}
	
	int bot = (TotalSE-2);	
	int top = (bot+3);    // initial bottom and top deque indices
		
	D1[0][bot] = PointsSE[0][2];        // 3rd vertex is at both bot and top
	D1[0][top] = PointsSE[0][2];
	
	D1[1][bot] = PointsSE[1][2];
	D1[1][top] = PointsSE[1][2];

	//isLeft returns if later point is left right or on line from first 2 points
	if (isLeft(PointsSE[0][0], PointsSE[1][0], PointsSE[0][1], PointsSE[1][1], PointsSE[0][2], PointsSE[1][2]) > 0) {
		D1[0][bot+1] = PointsSE[0][0];
		D1[1][bot+1] = PointsSE[1][0];
		
		D1[0][bot+2] = PointsSE[0][1];
		D1[1][bot+2] = PointsSE[1][1];          
	}
	else {
		D1[0][bot+1] = PointsSE[0][1];
		D1[1][bot+1] = PointsSE[1][1];
		
		D1[0][bot+2] = PointsSE[0][0];
		D1[1][bot+2] = PointsSE[1][0];
	}

	for (int i=3; i < TotalSE; i++) {   	
		// test if next vertex is inside the deque hull
		if ((isLeft(D1[0][bot],D1[1][bot], D1[0][bot+1], D1[1][bot+1], PointsSE[0][i], PointsSE[1][i]) > 0) &&
			(isLeft(D1[0][top-1], D1[1][top-1], D1[0][top], D1[1][top], PointsSE[0][i], PointsSE[1][i]) > 0) ){
				continue;         // skip an interior vertex
				
		}			
		// incrementally add an exterior vertex to the deque hull
		// get the rightmost tangent at the deque bot
		while ( isLeft(D1[0][bot], D1[1][bot], D1[0][bot+1], D1[1][bot+1], PointsSE[0][i], PointsSE[1][i]) <= (0) ){
			bot=bot+1;                 // remove bot of deque
		}		
		bot=bot-1;		
		D1[0][bot] = PointsSE[0][i];           // insert P[i] at bot[x] of deque			
		D1[1][bot] = PointsSE[1][i];	      // insert P[i] at bot[y] of deque
	// get the leftmost tangent at the deque top
	while (isLeft(D1[0][top-1], D1[1][top-1], D1[0][top], D1[1][top], PointsSE[0][i], PointsSE[1][i]) <= 0)
		--top;                 // pop top of deque	
		top=top+1;
		D1[0][top] = PointsSE[0][i];           // push P[i] onto top of deque
		D1[1][top] = PointsSE[1][i];	
	}

int h;	// hull vertex counter
	chainCounterSE=0;
	for (h=0; h <= (top-bot); h++){
		if( ( (Vertex[0][LowSE])!=(D1[0][bot+h]) )||( (Vertex[1][LowSE])!=(D1[1][bot+h]) ) ){
			chainCounterSE=chainCounterSE+1;
		}else{
			chainCounterSE=chainCounterSE+1;
			break;
		}
		
	}
	
	for (int i = 0; i < 2; i++){//orizo pinaka alisidas NE
		chainSE[i] = new int[chainCounterSE];
	}
	
	int y1=0;
	for (h=0; h <= (top-bot); h++){
		if( ( (Vertex[0][LowSE])!=(D1[0][bot+h]) )||( (Vertex[1][LowSE])!=(D1[1][bot+h]) ) ){
			chainSE[0][y1]=D1[0][bot+h];
			chainSE[1][y1]=D1[1][bot+h];
			y1=y1+1;
		}else{
			chainSE[0][y1]=D1[0][bot+h];
			chainSE[1][y1]=D1[1][bot+h];
			y1=y1+1;
			break;
		}
		
	}
	
	if((HighSE>=0)&&(LowSE>=0)){
		for (i=0; i<chainCounterSE;i++){
			cout << "chainSE=";
			cout << chainSE[0][i];
			cout << "," ;
			cout << chainSE[1][i];
			cout <<"\n";
		}
	}
	cout << "\n";
//==============================================================================
//==================================  SW  ======================================
//==============================================================================  
int **D2 = new int *[2]; //2 grammes

	for (int i = 0; i < 2; i++){
		D2[i] = new int[(2*TotalSW)+1];
	}
	
	 bot = (TotalSW-2);	
	 top = (bot+3);    // initial bottom and top deque indices
		
	D2[0][bot] = PointsSW[0][2];        // 3rd vertex is at both bot and top
	D2[0][top] = PointsSW[0][2];
	
	D2[1][bot] = PointsSW[1][2];
	D2[1][top] = PointsSW[1][2];
	//isLeft returns if later point is left right or on line from first 2 points
	if (isLeft(PointsSW[0][0], PointsSW[1][0], PointsSW[0][1], PointsSW[1][1], PointsSW[0][2], PointsSW[1][2]) > 0) {
		D2[0][bot+1] = PointsSW[0][0];
		D2[1][bot+1] = PointsSW[1][0];
		
		D2[0][bot+2] = PointsSW[0][1];
		D2[1][bot+2] = PointsSW[1][1];          
	}
	else {
		D2[0][bot+1] = PointsSW[0][1];
		D2[1][bot+1] = PointsSW[1][1];
		
		D2[0][bot+2] = PointsSW[0][0];
		D2[1][bot+2] = PointsSW[1][0];
	}

	for (int i=3; i < TotalSW; i++) {   	
		// test if next vertex is inside the deque hull
		if ((isLeft(D2[0][bot],D2[1][bot], D2[0][bot+1], D2[1][bot+1], PointsSW[0][i], PointsSW[1][i]) > 0) &&
			(isLeft(D2[0][top-1], D2[1][top-1], D2[0][top], D2[1][top], PointsSW[0][i], PointsSW[1][i]) > 0) ){
				continue;         // skip an interior vertex
				
		}			
		// incrementally add an exterior vertex to the deque hull
		// get the rightmost tangent at the deque bot
		while ( isLeft(D2[0][bot], D2[1][bot], D2[0][bot+1], D2[1][bot+1], PointsSW[0][i], PointsSW[1][i]) <= (0) ){
			bot=bot+1;                 // remove bot of deque
		}		
		bot=bot-1;		
		D2[0][bot] = PointsSW[0][i];           // insert P[i] at bot[x] of deque			
		D2[1][bot] = PointsSW[1][i];	      // insert P[i] at bot[y] of deque
	// get the leftmost tangent at the deque top
	while (isLeft(D2[0][top-1], D2[1][top-1], D2[0][top], D2[1][top], PointsSW[0][i], PointsSW[1][i]) <= 0)
		--top;                 // pop top of deque	
		top=top+1;
		D2[0][top] = PointsSW[0][i];           // push P[i] onto top of deque
		D2[1][top] = PointsSW[1][i];	
	}

	chainCounterSW=0;
	for (h=0; h <= (top-bot); h++){
		if( ( (Vertex[0][HighSW])!=(D2[0][bot+h]) )||( (Vertex[1][HighSW])!=(D2[1][bot+h]) ) ){
			chainCounterSW=chainCounterSW+1;
		}else{
			chainCounterSW=chainCounterSW+1;
			break;
		}
		
	}
	
	for (int i = 0; i < 2; i++){//orizo pinaka alisidas NE
		chainSW[i] = new int[chainCounterSW];
	}
	
	y1=0;
	for (h=0; h <= (top-bot); h++){
		if( ( (Vertex[0][HighSW])!=(D2[0][bot+h]) )||( (Vertex[1][HighSW])!=(D2[1][bot+h]) ) ){
			chainSW[0][y1]=D2[0][bot+h];
			chainSW[1][y1]=D2[1][bot+h];
			y1=y1+1;
		}else{
			chainSW[0][y1]=D2[0][bot+h];
			chainSW[1][y1]=D2[1][bot+h];
			y1=y1+1;
			break;
		}
		
	}
	
	if((HighSW>=0)&&(LowSW>=0)){
		for (i=0; i<chainCounterSW;i++){
			cout << "chainSW=";
			cout << chainSW[0][i];
			cout << "," ;
			cout << chainSW[1][i];
			cout <<"\n";
		}
	}
	cout << "\n";
//==============================================================================	
//================================         NE         ==========================
//==============================================================================  
int **D3 = new int *[2]; //2 grammes
	for (int i = 0; i < 2; i++){
		D3[i] = new int[(2*TotalNE)+1];
	}	
	 bot = (TotalNE-2);	
	 top = (bot+3);    // initial bottom and top deque indices
		
	D3[0][bot] = PointsNE[0][2];        // 3rd vertex is at both bot and top
	D3[0][top] = PointsNE[0][2];
	
	D3[1][bot] = PointsNE[1][2];
	D3[1][top] = PointsNE[1][2];

	//isLeft returns if later point is left right or on line from first 2 points
	if (isLeft(PointsNE[0][0], PointsNE[1][0], PointsNE[0][1], PointsNE[1][1], PointsNE[0][2], PointsNE[1][2]) > 0) {
		D3[0][bot+1] = PointsNE[0][0];
		D3[1][bot+1] = PointsNE[1][0];
		
		D3[0][bot+2] = PointsNE[0][1];
		D3[1][bot+2] = PointsNE[1][1];          
	}
	else {
		D3[0][bot+1] = PointsNE[0][1];
		D3[1][bot+1] = PointsNE[1][1];
		
		D3[0][bot+2] = PointsNE[0][0];
		D3[1][bot+2] = PointsNE[1][0];
	}

	for (int i=3; i < TotalNE; i++) {   	
		// test if next vertex is inside the deque hull
		if ((isLeft(D3[0][bot],D3[1][bot], D3[0][bot+1], D3[1][bot+1], PointsNE[0][i], PointsNE[1][i]) > 0) &&
			(isLeft(D3[0][top-1], D3[1][top-1], D3[0][top], D3[1][top], PointsNE[0][i], PointsNE[1][i]) > 0) ){
				continue;         // skip an interior vertex
				
		}			
		// incrementally add an exterior vertex to the deque hull
		// get the rightmost tangent at the deque bot
		while ( isLeft(D3[0][bot], D3[1][bot], D3[0][bot+1], D3[1][bot+1], PointsNE[0][i], PointsNE[1][i]) <= (0) ){
			bot=bot+1;                 // remove bot of deque
		}		
		bot=bot-1;		
		D3[0][bot] = PointsNE[0][i];           // insert P[i] at bot[x] of deque			
		D3[1][bot] = PointsNE[1][i];	      // insert P[i] at bot[y] of deque
	// get the leftmost tangent at the deque top
	while (isLeft(D3[0][top-1], D3[1][top-1], D3[0][top], D3[1][top], PointsNE[0][i], PointsNE[1][i]) <= 0)
		--top;                 // pop top of deque	
		top=top+1;
		D3[0][top] = PointsNE[0][i];           // push P[i] onto top of deque
		D3[1][top] = PointsNE[1][i];	
	}
	chainCounterNE=0;//megethos stoixeion alisidas NE
	for (h=0; h <= (top-bot); h++){
		if( ( (Vertex[0][LowNE])!=(D3[0][bot+h]) )||( (Vertex[1][LowNE])!=(D3[1][bot+h]) ) ){

			chainCounterNE=chainCounterNE+1;
		}else{

			chainCounterNE=chainCounterNE+1;
			break;
		}
		
	}
	
	
	for (int i = 0; i < 2; i++){//orizo pinaka alisidas NE
		chainNE[i] = new int[chainCounterNE];
	}
	
	y1=0;
	for (h=0; h <= (top-bot); h++){
		if( ( (Vertex[0][LowNE])!=(D3[0][bot+h]) )||( (Vertex[1][LowNE])!=(D3[1][bot+h]) ) ){
			chainNE[0][y1]=D3[0][bot+h];
			chainNE[1][y1]=D3[1][bot+h];
			y1=y1+1;
		}else{
			chainNE[0][y1]=D3[0][bot+h];
			chainNE[1][y1]=D3[1][bot+h];
			y1=y1+1;
			break;
		}
		
	}
	
	if((HighNE>=0)&&(LowNE>=0)){
		for (i=0; i<chainCounterNE;i++){
			cout << "chainNE=";
			cout << chainNE[0][i];
			cout << "," ;
			cout << chainNE[1][i];
			cout <<"\n";
		}
	}
	cout << "\n";
//==============================================================================
//================================    Chain-NW         =========================
//==============================================================================

   
int **D4 = new int *[2]; //2 grammes

	for (int i = 0; i < 2; i++){
		D4[i] = new int[(2*TotalNW)+1];
	}

	
	 bot = (TotalNW-2);	
	 top = (bot+3);    // initial bottom and top deque indices
		
	D4[0][bot] = PointsNW[0][2];        // 3rd vertex is at both bot and top
	D4[0][top] = PointsNW[0][2];
	
	D4[1][bot] = PointsNW[1][2];
	D4[1][top] = PointsNW[1][2];
	//isLeft returns if later point is left right or on line from first 2 points
	if (isLeft(PointsNW[0][0], PointsNW[1][0], PointsNW[0][1], PointsNW[1][1], PointsNW[0][2], PointsNW[1][2]) > 0) {
		D4[0][bot+1] = PointsNW[0][0];
		D4[1][bot+1] = PointsNW[1][0];
		
		D4[0][bot+2] = PointsNW[0][1];
		D4[1][bot+2] = PointsNW[1][1];          
	}
	else {
		D4[0][bot+1] = PointsNW[0][1];
		D4[1][bot+1] = PointsNW[1][1];
		
		D4[0][bot+2] = PointsNW[0][0];
		D4[1][bot+2] = PointsNW[1][0];
	}

	for (int i=3; i < TotalNW; i++) {   	
		// test if next vertex is inside the deque hull
		if ((isLeft(D4[0][bot],D4[1][bot], D4[0][bot+1], D4[1][bot+1], PointsNW[0][i], PointsNW[1][i]) > 0) &&
			(isLeft(D4[0][top-1], D4[1][top-1], D4[0][top], D4[1][top], PointsNW[0][i], PointsNW[1][i]) > 0) ){
				continue;         // skip an interior vertex
				
		}			
		// incrementally add an exterior vertex to the deque hull
		// get the rightmost tangent at the deque bot
		while ( isLeft(D4[0][bot], D4[1][bot], D4[0][bot+1], D4[1][bot+1], PointsNW[0][i], PointsNW[1][i]) <= (0) ){
			bot=bot+1;                 // remove bot of deque
			
		}		
		bot=bot-1;		
		D4[0][bot] = PointsNW[0][i];           // insert P[i] at bot[x] of deque			
		D4[1][bot] = PointsNW[1][i];	      // insert P[i] at bot[y] of deque
	// get the leftmost tangent at the deque top
	while (isLeft(D4[0][top-1], D4[1][top-1], D4[0][top], D4[1][top], PointsNW[0][i], PointsNW[1][i]) <= 0)
		--top;// pop top of deque	
		top=top+1;
		D4[0][top] = PointsNW[0][i];// push P[i] onto top of deque
		D4[1][top] = PointsNW[1][i];	
	}	
	
	chainCounterNW=0;//plithos stoixeion alisidas
	for (h=0; h <= (top-bot); h++){
		if( ( (Vertex[0][HighNW])!=(D4[0][bot+h]) )||( (Vertex[1][HighNW])!=(D4[1][bot+h]) ) ){

			chainCounterNW=chainCounterNW+1;
		}else{

			chainCounterNW=chainCounterNW+1;
			break;
			
		}
		
	}
	
	for (int i = 0; i < 2; i++){//orizo pinaka alisidas NE
		chainNW[i] = new int[chainCounterNW];
	}
	
	y1=0;
	for (h=0; h <= (top-bot); h++){
		if( ( (Vertex[0][HighNW])!=(D4[0][bot+h]) )||( (Vertex[1][HighNW])!=(D4[1][bot+h]) ) ){
			chainNW[0][y1]=D4[0][bot+h];
			chainNW[1][y1]=D4[1][bot+h];
			y1=y1+1;
		}else{
			chainNW[0][y1]=D4[0][bot+h];
			chainNW[1][y1]=D4[1][bot+h];
			y1=y1+1;
			break;
		}
		
	}
	
	if((HighNW>=0)&&(LowNW>=0)){
		for (i=0; i<chainCounterNW;i++){
			cout << "chainNW=";
			cout << chainNW[0][i];
			cout << "," ;
			cout << chainNW[1][i];
			cout <<"\n";
		}
	}
	cout << "\n";	
}










/*
* vres esoterikes efaptomenes se zeugi ton allisidon/perivlimaton 
* Parameters: Null
* Return: Null
*/
void findTangent() {
//==============================================================================
// Diadikasia gia tin 1 Efaptomeni sto NW(den tin vrisko akomi edo)
//==============================================================================
	int prevJ;
	int i, j;
	int temp=0;//voithaei sto na ksekinao sto epomeno j
	int findTangent=0;
	i=0;//gia kathe SE  to i=0
	while(findTangent==0){//otan ginei 1 tha spasei afou tha exo vrei auto pou thelo
		for(j=temp;j<(chainCounterNW-1);j++){//koita ola ta NW
			if( (isLeft(chainSE[0][i], chainSE[1][i], chainNW[0][j], chainNW[1][j], chainNW[0][j+1], chainNW[1][j+1]))<0 ){//an einai deksiostrofa
				if(j==(chainCounterNW-2)){
					prevJ=temp;//auto to j prepei na to kratiso
					findTangent=1;
				}
			}
			else
			{	
				temp=temp+1;//an provlima arxina ksana meta apo epomeno j
				break;
			}
		}
		if((temp==(chainCounterNW-1))&&(findTangent==0)){		
			findTangent=1;
			prevJ=chainCounterNW-1;
			break;
		}
	}
//==============================================================================
//Parakato vrisko 1 efaptomeni sto SE,NW(edopera tha tin vro)
//==============================================================================
	findTangent=0;
	i=prevJ;//gia kathe SE 
	temp=0;
	while(findTangent==0){//otan ginei 0 tha spasei afou tha exo vrei auto pou thelo
		for(j=temp;j<(chainCounterSE-1);j++){//koita ola ta NW
			if( (isLeft(chainNW[0][i], chainNW[1][i], chainSE[0][j], chainSE[1][j], chainSE[0][j+1], chainSE[1][j+1]))<0 ){//an einai deksiostrofa
				if(j==(chainCounterSE-2)){
					prevJ=temp;//auto to j prepei na to kratiso				
					tangent1SeNw[0][0]=chainNW[0][i];
					tangent1SeNw[1][0]=chainNW[1][i];
					
					usebPosition=temp;
					unwbPosition=i;
					
					tangent1SeNw[0][1]=chainSE[0][temp];
					tangent1SeNw[1][1]=chainSE[1][temp];
					
					findTangent=1;
				}
			}
			else
			{	
				temp=temp+1;//an provlima arxina ksana meta apo epomeno j
				break;
			}
			
		}
		if((temp==(chainCounterSE-1))&&(findTangent==0)){
			tangent1SeNw[0][0]=chainNW[0][i];
			tangent1SeNw[1][0]=chainNW[1][i];
			
			usebPosition=temp;
			unwbPosition=i;
			
			tangent1SeNw[0][1]=chainSE[0][chainCounterSE-1];
			tangent1SeNw[1][1]=chainSE[1][chainCounterSE-1];
			
			findTangent=1;
			break;	
		}
	}
//==============================================================================
// 2 Efaptomeni sto NW
//==============================================================================
	//prevJ=-1;
	//j=-1;
	temp=(chainCounterNW-1);//voithaei sto na ksekinao sto epomeno j
	findTangent=0;
	i=(chainCounterSE-1);
	while(findTangent==0){//otan ginei 1 tha spasei afou tha exo vrei auto pou thelo
		for(j=temp;j>0;j--){
			if( (isLeft(chainSE[0][i], chainSE[1][i], chainNW[0][(j)], chainNW[1][(j)], chainNW[0][j-1], chainNW[1][j-1]))>0 ){//an einai 
				if(j==(1)){
					prevJ=temp;//auto to j prepei na to kratiso
					findTangent=1;
				}
			}
			else
			{
				temp=temp-1;//an provlima arxina ksana meta apo epomeno j
				break;
			}
		}
		if((temp==(0))&&(findTangent==0)){		
			prevJ=0;
			findTangent=1;
			break;
		}
	}
//==============================================================================
//2 Efaptomeni sto SE,NW
//==============================================================================
	findTangent=0;
	i=prevJ;//gia kathe SE 
	temp=(chainCounterSE-1);
	while(findTangent==0){//otan ginei 1 tha spasei afou tha exo vrei auto pou thelo
		for(j=temp;j>0;j--){//koita ola ta NW
			if( (isLeft(chainNW[0][i], chainNW[1][i], chainSE[0][j], chainSE[1][j], chainSE[0][j-1], chainSE[1][j-1]))>0 ){//an einai 
				if(j==(1)){
					prevJ=temp;//auto to j prepei na to kratiso
					findTangent=1;
					
					
					usetPosition=temp;
					unwtPosition=i;
					tangent2SeNw[0][0]=chainNW[0][i];
					tangent2SeNw[1][0]=chainNW[1][i];
					tangent2SeNw[0][1]=chainSE[0][temp];
					tangent2SeNw[1][1]=chainSE[1][temp];
				}
			}
			else
			{
				temp=temp-1;//an provlima arxina ksana meta apo epomeno j
				break;
			}
			
		}
		if((temp==(0))&&(findTangent==0)){	
			usetPosition=temp;
			unwtPosition=i;
		
			tangent2SeNw[0][0]=chainNW[0][i];
			tangent2SeNw[1][0]=chainNW[1][i];
			tangent2SeNw[0][1]=chainSE[0][0];
			tangent2SeNw[1][1]=chainSE[1][0];
			findTangent=1;
			break;	
		}
	}


//==============================================================================
//==============================================================================
// 1 esoteriki efaptomeni sto NE
//==============================================================================
//==============================================================================
	i=0;
	temp=0;//voithaei sto na ksekinao sto epomeno j
	findTangent=0;
	i=0;//gia kathe SW 
	while(findTangent==0){//otan ginei 1 tha spasei afou tha exo vrei auto pou thelo
		for(j=temp;j<(chainCounterNE-1);j++){//koita ola ta NW
			if( (isLeft(chainSW[0][i], chainSW[1][i], chainNE[0][j], chainNE[1][j], chainNE[0][j+1], chainNE[1][j+1]))<0 ){//an einai deksiostrofa
				if(j==(chainCounterNE-2)){
					prevJ=temp;//auto to j prepei na to kratiso
					findTangent=1;
				}
			}
			else
			{	
				temp=temp+1;//an provlima arxina ksana meta apo epomeno j
				break;
			}
		}
		if((temp==(chainCounterNE-1))&&(findTangent==0)){		
			prevJ=chainCounterNE-1;
			findTangent=1;
			break;
		}
	}
//==============================================================================
//1 esoteriki efaptomeni sto NE,SW
//==============================================================================
	findTangent=0;
	i=prevJ;//gia kathe SW 
	temp=0;
	while(findTangent==0){//otan ginei 1 tha spasei afou tha exo vrei auto pou thelo
		for(j=temp;j<(chainCounterSW-1);j++){//koita ola ta NW
			if( (isLeft(chainNE[0][i], chainNE[1][i], chainSW[0][j], chainSW[1][j], chainSW[0][j+1], chainSW[1][j+1]))<0 ){//an einai deksiostrofa
				if(j==(chainCounterSW-2)){
					prevJ=temp;//auto to j prepei na to kratiso
					findTangent=1;
					
					tangent1NeSw[0][0]=chainNE[0][i];
					tangent1NeSw[1][0]=chainNE[1][i];
					
					unebPosition=i;
					uswbPosition=temp;
					
					tangent1NeSw[0][1]=chainSW[0][temp];
					tangent1NeSw[1][1]=chainSW[1][temp];
				}
			}
			else
			{
				temp=temp+1;//an provlima arxina ksana meta apo epomeno j
				break;
			}
			
		}
		if((temp==(chainCounterSW-1))&&(findTangent==0)){	
			tangent1NeSw[0][0]=chainNE[0][i];
			tangent1NeSw[1][0]=chainNE[1][i];
			
			unebPosition=i;
			uswbPosition=temp;
			
			tangent1NeSw[0][1]=chainSW[0][chainCounterSW-1];
			tangent1NeSw[1][1]=chainSW[1][chainCounterSW-1];
			findTangent=1;
			break;	
		}
	}
//==============================================================================
// 2 esoteriki efaptomeni sto NE
//==============================================================================
	prevJ=-1;
	j=-1;
	temp=(chainCounterNE-1);//voithaei sto na ksekinao sto epomeno j
	findTangent=0;
	i=(chainCounterSW-1);
	while(findTangent==0){//otan ginei 1 tha spasei afou tha exo vrei auto pou thelo
		for(j=temp;j>0;j--){
			if( (isLeft(chainSW[0][i], chainSW[1][i], chainNE[0][j], chainNE[1][j], chainNE[0][j-1], chainNE[1][j-1]))>0 ){//an einai 
				if(j==(1)){
					prevJ=temp;//auto to j prepei na to kratiso
					findTangent=1;
				}
			}
			else
			{	
				temp=temp-1;//an provlima arxina ksana meta apo epomeno j
				break;
			}
		}
		if((temp==(0))&&(findTangent==0)){	
			prevJ=0;
			findTangent=1;
			break;
		}
	}
//==============================================================================
//2 esoteriki efaptomeni sto NE,SW
//==============================================================================
	findTangent=0;
	i=prevJ;//gia kathe SW 
	temp=(chainCounterSW-1);
	while(findTangent==0){//otan ginei 1 tha spasei afou tha exo vrei auto pou thelo
		for(j=temp;j>0;j--){//koita ola ta NW
			if( (isLeft(chainNE[0][i], chainNE[1][i], chainSW[0][j], chainSW[1][j], chainSW[0][j-1], chainSW[1][j-1]))>0 ){//an einai 
				if(j==(1)){
					prevJ=temp;//auto to j prepei na to kratiso
					findTangent=1;
					
					unetPosition=i;
					uswtPosition=temp;
					
					tangent2NeSw[0][0]=chainNE[0][i];
					tangent2NeSw[1][0]=chainNE[1][i];
					
					tangent2NeSw[0][1]=chainSW[0][temp];
					tangent2NeSw[1][1]=chainSW[1][temp];
				}
			}
			else
			{
				temp=temp-1;//an provlima arxina ksana meta apo epomeno j
				break;
			}
			
		}
		if((temp==(0))&&(findTangent==0)){
			findTangent=1;
			break;	
			
			unetPosition=i;
			uswtPosition=temp;
					
			tangent2NeSw[0][0]=chainNE[0][i];
			tangent2NeSw[1][0]=chainNE[1][i];
			
			tangent2NeSw[0][1]=chainSW[0][0];
			tangent2NeSw[1][1]=chainSW[1][0];
		}
	}
	
	//edo as ta ektiposo ta 4 lines diladi tous 4 pinakes mou 2x2
	
	cout << "\nPrinting 4 Tangents(4 Arrays with size 2x2)\n";

	if((HighSE>=0)&&(LowSE>=0)&&(HighNW>=0)&&(LowNW>=0)){
		cout << "Tangent1 of SE-NW=";
		cout << tangent1SeNw[0][0];//Unwb
		cout << ",";
		cout << tangent1SeNw[1][0];//
		cout << " & ";
		cout << tangent1SeNw[0][1];//Useb
		cout << ",";
		cout << tangent1SeNw[1][1];//
		cout << "\n";
	
		cout << "Tangent2 of SE-NW=";
		cout << tangent2SeNw[0][0];//Unwt
		cout << ",";
		cout << tangent2SeNw[1][0];//
		cout << " & ";
		cout << tangent2SeNw[0][1];//Uset
		cout << ",";
		cout << tangent2SeNw[1][1];//
		cout << "\n";
	}
	
	if((HighNE>=0)&&(LowNE>=0)&&(HighSW>=0)&&(LowSW>=0)){
		cout << "Tangent1 of NE-SW=";
		cout << tangent1NeSw[0][0];//Uneb
		cout << ",";
		cout << tangent1NeSw[1][0];//
		cout << " & ";
		cout << tangent1NeSw[0][1];//Uswb
		cout << ",";
		cout << tangent1NeSw[1][1];//
		cout << "\n";
	
		cout << "Tangent2 of NE-SW=";
		cout << tangent2NeSw[0][0];//Unet
		cout << ",";
		cout << tangent2NeSw[1][0];//
		cout << " & ";
		cout << tangent2NeSw[0][1];//Uswt
		cout << ",";
		cout << tangent2NeSw[1][1];//
		cout << "\n";
	}

	
//******************************************************************************
//    1 komati apo erotima 4
//******************************************************************************
	double x, y;
	double radians;

	
	//Check if SE and NW have intersection
	int flagCollision=1;//if 0 no intersecrion, if 1 intersection between SE-NW
	for(i=0;i<chainCounterSE;i++){
		for(j=1;j<chainCounterNW;j++){
			if( (isLeft(chainNW[0][j-1], chainNW[1][j-1], chainNW[0][j], chainNW[1][j], chainSE[0][i], chainSE[1][i]))>0 ){
				//prepei na isxiei gia ola ta j gia kathe i gia na temnontai
			}else{
				flagCollision=0;//esto 1 na min isxiei den temnontai
			}
		}
	}
	for(i=0;i<chainCounterNW;i++){
		for(j=1;j<chainCounterSE;j++){
			if( (isLeft(chainSE[0][j-1], chainSE[1][j-1], chainSE[0][j], chainSE[1][j], chainNW[0][i], chainNW[1][i]))>0 ){
				//prepei na isxiei gia ola ta j gia kathe i gia na temnontai
			}else{
				flagCollision=0;//esto 1 na min isxiei den temnontai
			}
		}
	}
	
	//Algorithm"Erotima4"
	if( ((LowNW==-1)&&(HighNW==-1))||((LowSE==-1)&&(HighSE==-1)) ){//Diladi an den exei perivlima 
		thetaMin1=0;
		thetaMax1=180;
		
	}
	else if(flagCollision==1){
		cout << " intersection  in SE-NW..Kernel is Empty for every theta in (0,180)";
	}
	else{
		Unwbx=tangent1SeNw[0][0];//uNWb
		Unwby=tangent1SeNw[1][0];
		
		Unwtx=tangent2SeNw[0][0];//uNWt
		Unwty=tangent2SeNw[1][0];//
	}
	
	if( chainNW[1][0]>chainSE[1][0]  ){
		thetaMin1=0;
	}
	else{		
		y=( tangent1SeNw[1][1]-tangent1SeNw[1][0] );
		x=( tangent1SeNw[0][1]-tangent1SeNw[0][0] );
		
		radians = atan2(y, x);// girnaei se radians
		thetaMin1=radians*(180.0/3.141592653589793238463);
		
	}
	
	//Find left most and right most of NW,SE
	int leftMostSE=0;
	int rightMostNW=0;
	for(i=1;i<chainCounterNW;i++){
		if(  (chainNW[0][i])>(chainNW[0][rightMostNW]) ){
			rightMostNW=i;
		}
	}
	for(i=1;i<chainCounterSE;i++){
		if(  (chainSE[0][i])<(chainSE[0][leftMostSE]) ){
			leftMostSE=i;
		}
	}
	
	if((chainNW[0][rightMostNW])<(chainSE[0][leftMostSE])){

		thetaMax1=90;

	}
	else{
		y=( tangent2SeNw[1][0]-tangent2SeNw[1][1] );
		x=( tangent2SeNw[0][0]-tangent2SeNw[0][1] );

		radians = (atan2(y, x));//girnaei se radians 
		thetaMax1=radians*(180.0/3.141592653589793238463);// kai ta kano se moires
	}
	
//******************************************************************************
//    2 komati apo erotima 4
//******************************************************************************
	
	//Check if SW and NE have intersection
	flagCollision=1;//if 0 no intersecrion, if 1 intersection between SE-NW
	for(i=0;i<chainCounterSW;i++){
		for(j=1;j<chainCounterNE;j++){
			if( (isLeft(chainNE[0][j-1], chainNE[1][j-1], chainNE[0][j], chainNE[1][j], chainSW[0][i], chainSW[1][i]))>0 ){//aristerostrofa
				//prepei na isxiei gia ola ta j gia kathe i gia na temnontai
			}else{
				flagCollision=0;//esto 1 na min isxiei den temnontai
			}
		}
	}
	for(i=0;i<chainCounterNE;i++){
		for(j=1;j<chainCounterSW;j++){
			if( (isLeft(chainSW[0][j-1], chainSW[1][j-1], chainSW[0][j], chainSW[1][j], chainNE[0][i], chainNE[1][i]))>0 ){//aristerostrofa
				//prepei na isxiei gia ola ta j gia kathe i gia na temnontai
			}else{
				flagCollision=0;//esto 1 na min isxiei den temnontai
			}
		}
	}

	
	if( ((LowNE==-1)&&(HighNE==-1))||((LowSW==-1)&&(HighSW==-1)) ){//Diladi an den exei perivlima 
		thetaMin2=0;
		thetaMax2=180;
	}
	else if(flagCollision==1){
		cout << " intersection  in SW-NE..Kernel is Empty for every theta in (0,180)";
	}
	else{
		Uswbx=tangent1NeSw[0][1];//Uswb
		Uswby=tangent1NeSw[1][1];
		
		Uswtx=tangent2NeSw[0][1];//Uswt
		Uswty=tangent2NeSw[1][1];//	
	}
	
	//Find left most and right most of NE,SW
	int leftMostNE=0;
	int rightMostSW=0;
	for(i=1;i<chainCounterSW;i++){
		if(  (chainSW[0][i])>(chainSW[0][rightMostSW]) ){
			rightMostSW=i;
		}
	}
	for(i=1;i<chainCounterNE;i++){
		if(  (chainNE[0][i])<(chainNE[0][leftMostNE]) ){
			leftMostNE=i;
		}
	}
	
	if((chainSW[0][rightMostSW])<(chainNE[0][leftMostNE])){
		thetaMin2=0;
	}else{		
		y=( tangent1NeSw[0][1]-tangent1NeSw[0][0] );
		x=( tangent1NeSw[1][0]-tangent1NeSw[1][1] );
		
		radians = atan2(y, x);// girnaei se radians
		thetaMin2=radians*(180.0/3.141592653589793238463);
		
	}

	if( chainSW[1][chainCounterSW-1]<chainNE[1][chainCounterNE-1] ){
		thetaMax2=90;
	}
	else{		
		y=( tangent2NeSw[0][0]-tangent2NeSw[0][1] );
		x=( tangent2NeSw[1][1]-tangent2NeSw[1][0] );
		
		radians = atan2(y, x);// girnaei se radians
		thetaMax2=radians*(180.0/3.141592653589793238463);
		
	}
	if(thetaMin1>thetaMin2){
		thetaMin=thetaMin1;
	}else{
		thetaMin=thetaMin2;
	}
	
	if(thetaMax1<thetaMax2){
		thetaMax=thetaMax1;
	}else{
		thetaMax=thetaMax2;
	}
	
}









/*
Plithos Gonion=counterSW
Plithos akmnon=counterSW
vima1=tha vro to plithos tous,meta ftiakse tous pinakes
vima2= tha tis valo se pinakes,ektipose tes
*/
void findAngles(){
	int flagSW=0;
	int flagSE=0;
	int flagNW=0;
	int flagNE=0;
	int counterSW=0;//plithos gonion pou thelo
	int counterSE=0;
	int counterNW=0;
	int counterNE=0;
	int temp=0;
	double x, y, radians, temp2;
	int i;
	

	


/*
Tora SW gonies
	//vres plithos ton eidikon gonion kai akmon 
	//meta arxikopoiise tes "tous pinakes tous"
*/	
	for(i=0;i<(chainCounterSW);i++){
		if( ((chainSW[0][i])==(tangent1NeSw[0][1]))&&((chainSW[1][i])==(tangent1NeSw[1][1])) ){//My algorithm must start from here
			flagSW=1;
		}
		if( ((chainSW[0][i])==(tangent2NeSw[0][1]))&&((chainSW[1][i])==(tangent2NeSw[1][1])) ){//my algorithm must end here and get out of for with break;"also make flag=0 for possible error in break"
			flagSW=0;
			break;
		}	
		if(flagSW==1){
//pairno ta dio akra tis akmis diladi chain(i),chain(i+1)
			counterSW=counterSW+1;
		}
	}
	
//vrikes to plithos ara Arxikopoihsh tora!
	AnglesSW        = new double [counterSW];
	edgeInAnglesSW = new int [counterSW];
	flagSW=0;
//Tora vazo times stous 2 pinakes me gonies,akmes
//xreiazome ena counter temp giati den antistoixei me to i
	for(i=0;i<(chainCounterSW);i++){
		if( ((chainSW[0][i])==(tangent1NeSw[0][1]))&&((chainSW[1][i])==(tangent1NeSw[1][1])) ){//My algorithm must start from here
			
			flagSW=1;
		}
		if( ((chainSW[0][i])==(tangent2NeSw[0][1]))&&((chainSW[1][i])==(tangent2NeSw[1][1])) ){//my algorithm must end here and get out of for with break;"also make flag=0 for possible error in break"
			
			flagSW=0;
			break;
		}	
		if(flagSW==1){
//pairno ta dio akra tis akmis diladi chain(i),chain(i+1)
			y=chainSW[0][i]-chainSW[0][i+1];
			x=chainSW[1][i+1]-chainSW[1][i];
			radians = atan2(y, x);// girnaei se radians
			AnglesSW[temp]=radians*(180.0/3.141592653589793238463);
			edgeInAnglesSW[temp]=i;
			temp=temp+1;	
			
		}
	}
	temp=0;

/*
Tora SE gonies
*/

	for(i=0;i<(chainCounterSE);i++){
		if( ((chainSE[0][i])==(tangent1SeNw[0][1]))&&((chainSE[1][i])==(tangent1SeNw[1][1])) ){//My algorithm must start from here
			flagSE=1;
		}
		if( ((chainSE[0][i])==(tangent2SeNw[0][1]))&&((chainSE[1][i])==(tangent2SeNw[1][1])) ){//my algorithm must end here and get out of for with break;"also make flag=0 for possible error in break"
			flagSE=0;
			break;
		}	
		if(flagSE==1){
			//pairno ta dio akra tis akmis diladi chain(i),chain(i+1)
			counterSE=counterSE+1;
		}
	}	
	
	//vrikes to plithos ara Arxikopoihsh tora!
	AnglesSE        = new double [counterSE];
	edgeInAnglesSE = new int [counterSE];
	
	//Tora vazo times stous 2 pinakes me gonies,akmes
	//xreiazome ena counter temp giati den antistoixei me to i
	for(i=0;i<(chainCounterSE);i++){
		if( ((chainSE[0][i])==(tangent1SeNw[0][1]))&&((chainSE[1][i])==(tangent1SeNw[1][1])) ){//My algorithm must start from here
			flagSE=1;
		}
		if( ((chainSE[0][i])==(tangent2SeNw[0][1]))&&((chainSE[1][i])==(tangent2SeNw[1][1])) ){//my algorithm must end here and get out of for with break;"also make flag=0 for possible error in break"
			flagSE=0;
			break;
		}	
		if(flagSE==1){
			//pairno ta dio akra tis akmis diladi chain(i),chain(i+1)
			y=chainSE[1][i]-chainSE[1][i+1];
			x=chainSE[0][i]-chainSE[0][i+1];
			radians = atan2(y, x);// girnaei se radians
			AnglesSE[temp]=radians*(180.0/3.141592653589793238463);
			edgeInAnglesSE[temp]=i;
			temp=temp+1;
		}
	}
	temp=0;
		
/*
Tora NE gonies
*/

	for(i=0;i<(chainCounterNE);i++){
		if( ((chainNE[0][i])==(tangent1NeSw[0][0]))&&((chainNE[1][i])==(tangent1NeSw[1][0])) ){//My algorithm must start from here
			flagNE=1;
		}
		if( ((chainNE[0][i])==(tangent2NeSw[0][0]))&&((chainNE[1][i])==(tangent2NeSw[1][0])) ){//my algorithm must end here and get out of for with break;"also make flag=0 for possible error in break"
			flagNE=0;
			break;
		}	
		if(flagNE==1){
			//pairno ta dio akra tis akmis diladi chain(i),chain(i+1)
			counterNE=counterNE+1;
		}
	}
	
	//vrikes to plithos ara Arxikopoihsh tora!
	AnglesNE        = new double [counterNE];
	edgeInAnglesNE = new int [counterNE];	
		
	//Tora vazo times stous 2 pinakes me gonies,akmes
	//xreiazome ena counter temp giati den antistoixei me to i
	for(i=0;i<(chainCounterNE);i++){
		if( ((chainNE[0][i])==(tangent1NeSw[0][0]))&&((chainNE[1][i])==(tangent1NeSw[1][0])) ){//My algorithm must start from here
			flagNE=1;
		}
		if( ((chainNE[0][i])==(tangent2NeSw[0][0]))&&((chainNE[1][i])==(tangent2NeSw[1][0])) ){//my algorithm must end here and get out of for with break;"also make flag=0 for possible error in break"
			flagNE=0;
			break;
		}	
		if(flagNE==1){
			//pairno ta dio akra tis akmis diladi chain(i),chain(i+1)
			y=chainNE[0][i+1]-chainNE[0][i];
			x=chainNE[1][i]-chainNE[1][i+1];
			radians = atan2(y, x);// girnaei se radians
			AnglesNE[temp]=radians*(180.0/3.141592653589793238463);
			edgeInAnglesNE[temp]=i;
			temp=temp+1;
		}
	}
	temp=0;

/*
Tora NW gonies
*/

	for(i=0;i<(chainCounterNW);i++){
		if( ((chainNW[0][i])==(tangent1SeNw[0][0]))&&((chainNW[1][i])==(tangent1SeNw[1][0])) ){//My algorithm must start from here
			flagNW=1;
		}
		if( ((chainNW[0][i])==(tangent2SeNw[0][0]))&&((chainNW[1][i])==(tangent2SeNw[1][0])) ){//my algorithm must end here and get out of for with break;"also make flag=0 for possible error in break"
			flagNW=0;
			break;
		}	
		if(flagNW==1){
			//pairno ta dio akra tis akmis diladi chain(i),chain(i+1)
			counterNW=counterNW+1;
		}
	}
	
	//vrikes to plithos ara Arxikopoihsh tora!
	AnglesNW        = new double [counterNW];
	edgeInAnglesNW = new int [counterNW];	

	//Tora vazo times stous 2 pinakes me gonies,akmes
	//xreiazome ena counter temp giati den antistoixei me to i
	for(i=0;i<(chainCounterNW);i++){
		if( ((chainNW[0][i])==(tangent1SeNw[0][0]))&&((chainNW[1][i])==(tangent1SeNw[1][0])) ){//My algorithm must start from here
			flagNW=1;
		}
		if( ((chainNW[0][i])==(tangent2SeNw[0][0]))&&((chainNW[1][i])==(tangent2SeNw[1][0])) ){//my algorithm must end here and get out of for with break;"also make flag=0 for possible error in break"
			flagNW=0;
			break;
		}	
		if(flagNW==1){
			//pairno ta dio akra tis akmis diladi chain(i),chain(i+1)
			y=chainNW[1][i+1]-chainNW[1][i];
			x=chainNW[0][i+1]-chainNW[0][i];
			radians = atan2(y, x);// girnaei se radians
			AnglesNW[temp]=radians*(180.0/3.141592653589793238463);
			edgeInAnglesNW[temp]=i;
			temp=temp+1;
		}
	}
	temp=0;	



	
	
	
	
		
//Tora tous 4 pinakes me akmes kai gonies tha tous enoso se 2 antistoixa pou tha tous xorane
//stin arxi kai telos tou Angles tha exo 2 nea stoixeia

	Angles        = new double [counterNW+counterNE+counterSW+counterSE+2];
	edgeInAngles = new int [counterNW+counterNE+counterSW+counterSE];
	anglesCategory = new int [counterNW+counterNE+counterSW+counterSE];//SW SE NW NE -> se poia apo autes anikei i kathe gonia?SW=0, SE=1, NW=2, NE=3
	
//Tora vale ta stoixeia pou prepei se autous tous 2 pinakes
	Angles[0]=thetaMin;
	
	int i1;
	for(i1=0;i1<counterSW;i1++){
		Angles[i1+1]=AnglesSW[i1];
		edgeInAngles[i1]=edgeInAnglesSW[i1];
		anglesCategory[i1]=0;
	}
	
	int i2;
	for(i2=0;i2<counterSE;i2++){
		Angles[i1+1+i2]=AnglesSE[i2];
		edgeInAngles[i1+i2]=edgeInAnglesSE[i2];
		anglesCategory[i1+i2]=1;
	}
	
	int i3;
	for(i3=0;i3<counterNW;i3++){
		Angles[i1+1+i2+i3]=AnglesNW[i3];
		edgeInAngles[i1+i2+i3]=edgeInAnglesNW[i3];
		anglesCategory[i1+i2+i3]=2;
	}
	
	int i4;
	for(i4=0;i4<counterNE;i4++){
		Angles[i1+1+i2+i3+i4]=AnglesNE[i4];
		edgeInAngles[i1+i2+i3+i4]=edgeInAnglesNE[i4];
		anglesCategory[i1+i2+i3+i4]=3;
	}	
	
	
	Angles[i1+i2+i3+i4+1]=thetaMax;
	
	
	
	
	totali=counterNE+counterNW+counterSE+counterSW+2;//Auto einai to plithos ton stoixeion mou
	
	
	int j;
	double Newtempi, Newtempj;
	int Newtemp2a, Newtemp2b; 
	int Newtemp3a, Newtemp3b;
	
	for(i=1;i<(totali-1);i++){// Giati den thelo thetaMin,Max
		for(j=(i+1);j<(totali-1);j++){
			if(Angles[j]<Angles[i]){
				Newtempi=Angles[i];
				Newtempj=Angles[j];
				Angles[i]=Newtempj;
				Angles[j]=Newtempi;
				
				Newtemp2a=edgeInAngles[i-1];
				Newtemp2b=edgeInAngles[j-1];
				edgeInAngles[i-1]=Newtemp2b;
				edgeInAngles[j-1]=Newtemp2a;

				Newtemp3a=anglesCategory[i-1];
				Newtemp3b=anglesCategory[j-1];
				anglesCategory[i-1]=Newtemp3b;
				anglesCategory[j-1]=Newtemp3a;
			}
		}
	}

	cout << "\nSorted Array of all Angles with their specific Edge and angle Category\n";
	for(i=0;i<totali;i++){
		cout << "\n Angle:";
		cout << Angles[i];
		if((i>0)&&(i<totali-1)){
			cout << "\tEdge:";
			cout << edgeInAngles[i-1];
			cout << "\tangle_Category:";
			cout << anglesCategory[i-1];
		}
	}



}









void computeKernel(){
	
	double Psex, Psey;//ta 4 simeia pou anaferei i ekfonisi
	double Pnwx, Pnwy;
	double Pnex, Pney;
	double Pswx, Pswy;
	
	double previousPsex, previousPsey;//ta 4 simeia pou anaferei i ekfonisi alla ta proigumena apo ta trexon pou exo enimerosei
	double previousPnwx, previousPnwy;
	double previousPnex, previousPney;
	double previousPswx, previousPswy;
	
	double fi, fi2, Y, X, Yprevious, Xprevious, tanfi, v1x, v1y, v2x, v2y;
	double Line1_Point1X, Line1_Point1Y, Line1_Point2X, Line1_Point2Y, Line2_Point1X, Line2_Point1Y, Line2_Point2X, Line2_Point2Y;//ta simeia tomis tis akmis me to poligono
	double PrevLine1_Point1X, PrevLine1_Point1Y, PrevLine1_Point2X, PrevLine1_Point2Y, PrevLine2_Point1X, PrevLine2_Point1Y, PrevLine2_Point2X, PrevLine2_Point2Y;//ta proigumena simeia tomis tis akmis me to poligono
	
	int isFirstTime=1;//proti fora pou tha psaksei gia to emvadon tou trigonou
	double MaxLine1_Point1X, MaxLine1_Point1Y, MaxLine1_Point2X, MaxLine1_Point2Y, MaxLine2_Point1X, MaxLine2_Point1Y, MaxLine2_Point2X, MaxLine2_Point2Y;//ta simeia tomis tis akmis me to poligono sta opoia emfanizete megisto emvadon tou trigonou
	 
	
	int z, i, intersectionFlag, condition;
	
	double t1, t2, t3, t4, t5, t6, t7, t8, t9, tmin, previoustmin;
	
	double y, x;
	double fiprevious, fi2previous;
 	double E1, E2, SumE1, SumE2;
 	
	int isZincreased, isUsebPositionIncreased, isUswbPositionIncreased, isUnebPositionIncreased, isUnwbPositionIncreased;//Z,usebposition auksanont
	int isSeUpdated, isSwUpdated, isNeUpdated, isNwUpdated;//an exei enimerothei
	
	int searchForX;
	
	int nextuswbPosition, nextusebPosition, nextunwbPosition, nextunebPosition;
	int nextuswtPosition, nextusetPosition, nextunwtPosition, nextunetPosition;
	int isfiUpdated, isfi2Updated;
	
	double NewTempX;
	double NewTempY;
	double a, b, theta;
	double d1, d2, d3, d4, d5, d6, d7, d8;
	
	int isPrevLine=0;
	int isIF=0;
	
	double Height1, Height2, Height3, Height4, Height5, Height6, Height7, Height8;
	int t1x, t1y, t2x, t2y, Prevt1x, Prevt1y, Prevt2x, Prevt2y;	
	int s1x, s1y, s2x, s2y, Prevs1x, Prevs1y, Prevs2x, Prevs2y;
	int dota=0;


//******************************************************************************
//I diadikasia tha trexei gia kathe gonia apo ton pinaka Angles
//prin to for tha doso kapoies arxikes times
//sto telos tou for me vasi kapoia pragmata tha tou dino tis nees times
//******************************************************************************
	fi=thetaMin1;//gonia fi pou exei klisi i eutheia mou
	Psey=tangent1SeNw[1][1];//Useb.y
	Psex=tangent1SeNw[0][1];//Useb.x
	Pnwy=tangent1SeNw[1][0];//Unwb.y
	Pnwx=tangent1SeNw[0][0];//Unwb.x
	
	fi2=thetaMin2;//gonia fi pou exei klisi i eutheia mou
	Pswy=tangent1NeSw[1][1];//Uswb.y
	Pswx=tangent1NeSw[0][1];//Uswb.x
	Pney=tangent1NeSw[1][0];//Uneb.y
	Pnex=tangent1NeSw[0][0];//Uneb.x
	
	
	
	//Sosti thesi tou Useb Position sto Poligono kai oxi stin Alisida
	for(i=0;i<(VerticesNum);i++){
		if( (Vertex[0][i]==tangent1SeNw[0][0])&&(Vertex[1][i]==tangent1SeNw[1][0]) ){
			nextunwbPosition=i;
		}
		if( (Vertex[0][i]==tangent1NeSw[0][0])&&(Vertex[1][i]==tangent1NeSw[1][0]) ){
			nextunebPosition=i;
		}
		if( (Vertex[0][i]==tangent1NeSw[0][1])&&(Vertex[1][i]==tangent1NeSw[1][1]) ){
			nextuswbPosition=i;
		}
		if( (Vertex[0][i]==tangent1SeNw[0][1])&&(Vertex[1][i]==tangent1SeNw[1][1]) ){
			nextusebPosition=i;
		}
		
		if( (Vertex[0][i]==tangent2SeNw[0][0])&&(Vertex[1][i]==tangent2SeNw[1][0]) ){
			nextunwtPosition=i;
		}
		if( (Vertex[0][i]==tangent2NeSw[0][0])&&(Vertex[1][i]==tangent2NeSw[1][0]) ){
			nextunetPosition=i;
		}
		if( (Vertex[0][i]==tangent2NeSw[0][1])&&(Vertex[1][i]==tangent2NeSw[1][1]) ){
			nextuswtPosition=i;
		}
		if( (Vertex[0][i]==tangent2SeNw[0][1])&&(Vertex[1][i]==tangent2SeNw[1][1]) ){
			nextusetPosition=i;
		}
	}
	
	
	
	z=1;// na do kai pote tha stamatisei
	//for(z=1;z<(totali);z++){
	while(z<totali){
	cout << "\n...................Z........................---->" << z;
	
//******************************************************************************
//                           Pame tora sto 1 komati apo ta 4
//******************************************************************************
	
	
	intersectionFlag=-1;//den exei vrethei kapoio simeio tomis euthias me poligono
	
	
	if(nextusebPosition==( VerticesNum-2 )){
		i=0;
	}else if(nextusebPosition==( VerticesNum-1 )){
		i=1;
	}else{
		i=nextusebPosition+2;
	}
	
	while((i!=nextusetPosition)&&(fi<=thetaMax1)){
		searchForX=0;
		if(i==0){
			Yprevious=Vertex[1][VerticesNum-1];
		}
		else{
			Yprevious=Vertex[1][i-1];
		}
		
		tanfi=tan (fi * (3.141592653589793238463) / 180.0);//apotelesma tis efaptomenis gonias se moires"ta pairnei se radians omos"
		//(180.0/3.141592653589793238463)
		Y=Psey+(Vertex[0][i]-Psex)*tanfi;//Simeio tomis eutheias me poligono "Y sintetagmeni", thelo na vro kai ti Yprevious
		
		if(  ((Yprevious>Y)&&(Y>Vertex[1][i]))||((Yprevious<Y)&&(Y<Vertex[1][i]))  ){
			
			if(intersectionFlag==0){//An exei vrethei mono 1
				Line1_Point2X=Vertex[0][i];
				Line1_Point2Y=Y;
				intersectionFlag=1;
				
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
				s2x=v2x;
				s2y=v2y;
				searchForX=1;
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				Line1_Point1X=Vertex[0][i];
				Line1_Point1Y=Y;
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
				s1x=v1x;
				s1y=v1y;
				searchForX=1;
			}
		}
		
		if(i==0){
			Xprevious=Vertex[0][VerticesNum-1];
		}
		else{
			Xprevious=Vertex[0][i-1];
		}
		
		if(fi==0){
			X=Vertex[0][i];
		}else{
			X=Psex+(Vertex[1][i]-Psey)*(1/tanfi);
		}
		

		if(  ( ((Xprevious<X)&&(X<Vertex[0][i]))||((Xprevious>X)&&(X>Vertex[0][i])) )&&(searchForX==0)  ){
		
			if(intersectionFlag==0){//An exei vrethei mono 1
				Line1_Point2X=X;
				Line1_Point2Y=Vertex[1][i];
				
				intersectionFlag=1;
				
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
				s2x=v2x;
				s2y=v2y;
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				Line1_Point1X=X;
				Line1_Point1Y=Vertex[1][i];
				
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
				s1x=v1x;
				s1y=v1y;
			}
		}
		
		if( (Y==Vertex[1][i])&&((Vertex[0][i]!=Unwbx)||(Vertex[1][i]!=Unwby))&&((Vertex[0][i]!=tangent1SeNw[0][1])||(Vertex[1][i]!=tangent1SeNw[1][1])) ){//an den vrethei tote aniksei se auti tin eidiki periptosi
					
			if(intersectionFlag==0){//An exei vrethei mono 1
				Line1_Point2X=Vertex[0][i];
				Line1_Point2Y=Vertex[1][i];
				
				intersectionFlag=1;
				
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
				s2x=v2x;
				s2y=v2y;
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				Line1_Point1X=Vertex[0][i];
				Line1_Point1Y=Vertex[1][i];
				
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
				s1x=v1x;
				s1y=v1y;
			}
		}
		if(i==VerticesNum-1 ){
			i=0;
		}else{
			i=i+1;
		}

	}//edo kleinei to arxiko for
	
	if(fi<=thetaMax1){

		y=v2y-Psey   ; 
		x= v2x-Psex  ; 
		
		if((x<=0)&&(y<=0)){
			x=-x;
			y=-y;
		}
		t1=atan2(y, x)*(180.0/3.141592653589793238463);//vgazei se radians kai to kano se moires
	
		y=Psey-v1y;
		x=Psex-v1x;
		if((x<=0)&&(y<=0)){
			x=-x;
			y=-y;
		}
		
		t2=atan2(y, x)*(180.0/3.141592653589793238463);
		if(t2<0){
			t2=180+t2;
		}
	}

//******************************************************************************
//                           Pame tora sto 2 komati apo ta 4
//******************************************************************************
	
	intersectionFlag=-1;//den exei vrethei kapoio simeio tomis euthias me poligono
	
	if(nextunwbPosition==( VerticesNum-2 )){
		i=0;
	}else if(nextunwbPosition==( VerticesNum-1 )){
		i=1;
	}else{
		i=nextunwbPosition+2;
	}
	
	while((i!=nextunwtPosition)&&(fi<=thetaMax1)){
		searchForX=0;
		if(i==0){
			Yprevious=Vertex[1][VerticesNum-1];
		}
		else{
			Yprevious=Vertex[1][i-1];
		}
		
		tanfi=tan (fi * (3.141592653589793238463) / 180.0);//apotelesma tis efaptomenis gonias se moires"ta pairnei se radians omos"
		//(180.0/3.141592653589793238463)
		
		Y=Pnwy+(Vertex[0][i]-Pnwx)*tanfi;//Simeio tomis eutheias me poligono "Y sintetagmeni", thelo na vro kai ti Yprevious
		
		if(  ((Yprevious>Y)&&(Y>Vertex[1][i]))||((Yprevious<Y)&&(Y<Vertex[1][i]))  ){
			
			if(intersectionFlag==0){//An exei vrethei mono 1
				Line2_Point2X=Vertex[0][i];
				Line2_Point2Y=Y;
				
				intersectionFlag=1;
				
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
				t2x=v2x;
				t2y=v2y;
				searchForX=1;
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				Line2_Point1X=Vertex[0][i];
				Line2_Point1Y=Y;
				
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
				t1x=v1x;
				t1y=v1y;
				
				searchForX=1;
			}	
		}
		
		if(i==0){
			Xprevious=Vertex[0][VerticesNum-1];
		}
		else{
			Xprevious=Vertex[0][i-1];
		}
		if(fi==0){
			X=Vertex[0][i];
		}else{
			X=Pnwx+(Vertex[1][i]-Pnwy)*(1/tanfi);
		}
		
		
		
		if(  (((Xprevious<X)&&(X<Vertex[0][i]))||((Xprevious>X)&&(X>Vertex[0][i])))&&(searchForX==0)  ){
		
			if(intersectionFlag==0){//An exei vrethei mono 1
				Line2_Point2X=X;
				Line2_Point2Y=Vertex[1][i];
				
				intersectionFlag=1;
				
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
				t2x=v2x;
				t2y=v2y;
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				Line2_Point1X=X;
				Line2_Point1Y=Vertex[1][i];
				
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
				t1x=v1x;
				t1y=v1y;
			}
		}
		
		if((Y==Vertex[1][i])&& ((Vertex[0][i]!=tangent1SeNw[0][1])||(Vertex[1][i]!=tangent1SeNw[1][1]))&&((Vertex[0][i]!=Unwbx)||(Vertex[1][i]!=Unwby)) ){//an den vrethei tote aniksei se auti tin eidiki periptosi
		
			if(intersectionFlag==0){//An exei vrethei mono 1
				Line2_Point2X=Vertex[0][i];
				Line2_Point2Y=Vertex[1][i];
				
				intersectionFlag=1;
				
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
				t2x=v2x;
				t2y=v2y;
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				Line2_Point1X=Vertex[0][i];
				Line2_Point1Y=Vertex[1][i];
				
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
				t1x=v1x;
				t1y=v1y;	
			}
		}
		
		if(i==VerticesNum-1 ){
			i=0;
		}else{
			i=i+1;
		}
		
	}//edo kleinei to arxiko for
	
	if(fi<=thetaMax1){
	
		y=v2y-Pnwy; 
		x= v2x-Pnwx; 
		
		if((x<=0)&&(y<=0)){
			x=-x;
			y=-y;
		}
		t3=atan2(y, x)*(180.0/3.141592653589793238463);//vgazei se radians kai to kano se moires
		
		y=Pnwy-v1y;
		x=Pnwx-v1x;

		if((x<=0)&&(y<=0)){
			x=-x;
			y=-y;
		}
		t4=atan2(y, x)*(180.0/3.141592653589793238463);
	}
	
	
//******************************************************************************
//                           Pame tora sto 3 komati apo ta 4
//******************************************************************************	
	
	intersectionFlag=-1;//den exei vrethei kapoio simeio tomis euthias me poligono
	
	if(nextuswbPosition==( VerticesNum-2 )){
		i=0;
	}else if(nextuswbPosition==( VerticesNum-1 )){
		i=1;
	}else{
		i=nextuswbPosition+2;
	}
	
	while((i!=nextuswtPosition)&&(fi2<=thetaMax2)){
	
		searchForX=0;
		if(i==0){
			Yprevious=Vertex[1][VerticesNum-1];
		}else{
			Yprevious=Vertex[1][i-1];
		}
		tanfi=tan (fi2 * (3.141592653589793238463) / 180.0);//apotelesma tis efaptomenis gonias se moires"ta pairnei se radians omos"
		//(180.0/3.141592653589793238463)
		Y=( (Pswx-Vertex[0][i])*(1/tanfi) )+Pswy;//Simeio tomis eutheias me poligono "Y sintetagmeni", thelo na vro kai ti Yprevious
		if(  ((Yprevious>Y)&&(Y>Vertex[1][i]))||((Yprevious<Y)&&(Y<Vertex[1][i]))  ){
		
			if(intersectionFlag==0){//An exei vrethei mono 1
				intersectionFlag=1;
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
				searchForX=1;
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				intersectionFlag=0;
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
				searchForX=1;
			}
			
		}
		
		if(i==0){
			Xprevious=Vertex[0][VerticesNum-1];
		}
		else{
			Xprevious=Vertex[0][i-1];
		}
		
		X=Pswx+(Pswy-Vertex[1][i])*(tanfi);
		if(  (((Xprevious<X)&&(X<Vertex[0][i]))||((Xprevious>X)&&(X>Vertex[0][i])))&&(searchForX==0)  ){
		
			if(intersectionFlag==0){//An exei vrethei mono 1
				intersectionFlag=1;
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
				
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				intersectionFlag=0;
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
			}
		}
		
		if((Y==Vertex[1][i])&& ((Vertex[0][i]!=tangent1NeSw[0][0])||(Vertex[1][i]!=tangent1NeSw[1][0]) )&&((Vertex[0][i]!=tangent1NeSw[0][1])||(Vertex[1][i]!=tangent1NeSw[1][1]))){//an den vrethei tote aniksei se auti tin eidiki periptosi
			
			if(intersectionFlag==0){//An exei vrethei mono 1
				intersectionFlag=1;
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];	
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena	
				intersectionFlag=0;
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
			}
		}
		
		if(i==VerticesNum-1 ){
			i=0;
		}else{
			i=i+1;
		}
	
	}//edo kleinei to arxiko for
	
	if(fi2<=(thetaMax2)){
		
		y=v1x-Pswx; 
		x=Pswy-v1y; 
		if((x<=0)&&(y<=0)){
			x=-x;
			y=-y;
		}
		t5=atan2(y, x)*(180.0/3.141592653589793238463);//vgazei se radians kai to kano se moires
	
		x=v2y-Pswy;
		y=Pswx-v2x;
		if((x<=0)&&(y<=0)){
			x=-x;
			y=-y;
		}
		t6=atan2(y, x)*(180.0/3.141592653589793238463);
	}
	
//******************************************************************************
//                           Pame tora sto 4 komati apo ta 4
//******************************************************************************
	
	
	intersectionFlag=-1;//den exei vrethei kapoio simeio tomis euthias me poligono
	
	if(nextunebPosition==( VerticesNum-2 )){
		i=0;
	}else if(nextunebPosition==( VerticesNum-1 )){
		i=1;
	}else{
		i=nextunebPosition+2;
	}
	
	//for(i=0;i<VerticesNum;i++){
	while((i!=nextunetPosition)&&(fi2<=thetaMax2)){
		searchForX=0;
		if(i==0){
			Yprevious=Vertex[1][VerticesNum-1];
		}
		else{
			Yprevious=Vertex[1][i-1];
		}
		tanfi=tan (fi2 * (3.141592653589793238463) / 180.0);//apotelesma tis efaptomenis gonias se moires"ta pairnei se radians omos"
		//(180.0/3.141592653589793238463)
		Y=( (Pnex-Vertex[0][i])*(1/tanfi) ) + Pney;//Simeio tomis eutheias me poligono "Y sintetagmeni", thelo na vro kai ti Yprevious
		
		
		if(  ((Yprevious>Y)&&(Y>Vertex[1][i]))||((Yprevious<Y)&&(Y<Vertex[1][i]))  ){
		
			if(intersectionFlag==0){//An exei vrethei mono 1
				intersectionFlag=1;

				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
					
				searchForX=1;
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
					
				searchForX=1;
			}
			
		}
	
		if(i==0){
			Xprevious=Vertex[0][VerticesNum-1];
		}
		else{
			Xprevious=Vertex[0][i-1];
		}
		X=Pnex+(Pney-Vertex[1][i])*(tanfi);
		if(  ((((Xprevious<X)&&(X<Vertex[0][i]))||((Xprevious>X)&&(X>Vertex[0][i])))&&(searchForX==0))  ){
		
			if(intersectionFlag==0){//An exei vrethei mono 1
				intersectionFlag=1;

				v2x=Vertex[0][i];
				v2y=Vertex[1][i];
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];
			}
		}
		
		if((Y==Vertex[1][i])&&( (Vertex[0][i]!=Uswbx)||(Vertex[1][i]!=Uswby) )&&((Vertex[0][i]!=tangent1NeSw[0][0])||(Vertex[1][i]!=tangent1NeSw[1][0]))){//an den vrethei tote aniksei se auti tin eidiki periptosi
			if(intersectionFlag==0){//An exei vrethei mono 1	
				intersectionFlag=1;
				
				v2x=Vertex[0][i];
				v2y=Vertex[1][i];	
			}
			
			if(intersectionFlag==(-1)){//An den exei vrethei kanena
				intersectionFlag=0;
				
				v1x=Vertex[0][i];
				v1y=Vertex[1][i];	
			}
		}
		
		if(i==VerticesNum-1 ){
			i=0;
		}else{
			i=i+1;
		}
	}//edo kleinei to arxiko for
	
	if(fi2<=thetaMax2){
		x=v2y-Pney; 
		y=Pnex-v2x; 
		
		if((x<=0)&&(y<=0)){
			x=-x;
			y=-y;
		}
		t7=atan2(y, x)*(180.0/3.141592653589793238463);//vgazei se radians kai to kano se moires
	
		y=v1x-Pnex;
		x=Pney-v1y;
		
		if((x<=0)&&(y<=0)){
			x=-x;
			y=-y;
		}
		t8=atan2(y, x)*(180.0/3.141592653589793238463);
		if(t8<0){
			t8=180+t8;		
		}
	}

//******************************************************************************
//Bres ti mikroteri gonia apo tis 9 
//******************************************************************************
	tmin = Angles[z];
	
	if(t1<tmin){
		tmin=t1;
	}	
	if(t2<tmin){
		tmin=t2;
	}
	if(t3<tmin){
		tmin=t3;
	}
	if(t4<tmin){
		tmin=t4;
	}
	if(t5<tmin){
		tmin=t5;
	}
	if(t6<tmin){
		tmin=t6;
	}
	if(t7<tmin){
		tmin=t7;
	}
	if(t8<tmin){
		tmin=t8;
	}
	
	isfiUpdated=0;
	isfi2Updated=0;
	
	isSeUpdated=0;
	isSwUpdated=0;
	isNeUpdated=0;
	isNwUpdated=0;
	
		
		
	condition=0;
	isZincreased=0;
	isUswbPositionIncreased=0;
		
		
		if(((anglesCategory[z-1]==0)||(anglesCategory[z-1]==3))&&(fi2<=thetaMax2)){//AN anikei sto SW
			if((Angles[z]==tmin)&&(anglesCategory[z-1]==0)){
				condition=1;
				
				if(uswbPosition<uswtPosition){
					uswbPosition=uswbPosition+1;
					isUswbPositionIncreased=1;
				}
				
				previousPswx=Pswx;
				previousPswy=Pswy;
				
				Pswx=chainSW[0][uswbPosition];
				Pswy=chainSW[1][uswbPosition];
				
				fi2previous=fi2;
				fi2=tmin;
				isfi2Updated=1;
				
				if(isZincreased==0){
					//z=z+1;
					isZincreased=1;
				}
				isSwUpdated=1;
			}else if(Angles[z]>tmin){
			
				if((uswbPosition<uswtPosition)&&(anglesCategory[z-1]==0)){
					
					uswbPosition=uswbPosition+1;
					isUswbPositionIncreased=1;
					
				}
				Pswx=chainSW[0][uswbPosition];
				Pswy=chainSW[1][uswbPosition];
				
				fi2previous=fi2;
				fi2=Angles[z];
				isfi2Updated=1;
				condition=1;
			}
			
			
			if((((Pswx==previousPswx)&&(Pswy==previousPswy))&&(tmin==previoustmin))&&(anglesCategory[z-1]==0)){
				if(uswbPosition<uswtPosition){
					if(isUswbPositionIncreased==0){
						uswbPosition=uswbPosition+1;
					}
				}
				previousPswx=Pswx;
				previousPswy=Pswy;
				
				Pswx=chainSW[0][uswbPosition];
				Pswy=chainSW[1][uswbPosition];	
				
				fi2previous=fi2;
				fi2=Angles[z];
				isfi2Updated=1;
				
				isSwUpdated=1;
			}
		}
		
		
		
		
		
		condition=0;
		isUsebPositionIncreased=0;
		if(((anglesCategory[z-1]==1)||(anglesCategory[z-1]==2))&&(fi<=thetaMax1)){//AN anikei sto SE
			
			
			if((Angles[z]==tmin)&&(anglesCategory[z-1]==1)){
				
				condition=1;//diladi bike
				
				if(usebPosition<usetPosition){
					
					usebPosition=usebPosition+1;
					isUsebPositionIncreased=1;
					
					if((anglesCategory[z])!=(anglesCategory[z+1])){
						if(fi==Angles[z]){
							usebPosition=usebPosition-1;//mikrine to kata 1
						}
					}
				}
				
				previousPsex=Psex;
				previousPsey=Psey;
				Psex=chainSE[0][usebPosition];
				Psey=chainSE[1][usebPosition];
				fiprevious=fi;
				if(fi<Angles[z]){
					
					fi=tmin;
				}else if(fi==Angles[z]){
					fi=Angles[z+1];
				}
				isfiUpdated=1;
				if(isZincreased==0){
					//z=z+1;
					isZincreased=1;
					
				}
				isSeUpdated=1;
			}else if(Angles[z]>tmin){
				if(fi<tmin){
					
					fiprevious=fi;
					fi=tmin;
					isfiUpdated=1;
				}
				
				
				condition=1;
				
				
			}
			
			if((((Psex==previousPsex)&&(Psey==previousPsey))&&(tmin==previoustmin))&&(anglesCategory[z-1]==1)){
				
				if(usebPosition<usetPosition){
				
					if(isUsebPositionIncreased==0){
						usebPosition=usebPosition+1;
					}
				}
				
				previousPsex=Psex;
				previousPsey=Psey;
				Psex=chainSE[0][usebPosition];
				Psey=chainSE[1][usebPosition];
				
				fiprevious=fi;
				fi=Angles[z];
				isfiUpdated=1;
				
				isSeUpdated=1;
			}
		}
		
	
	
		condition=0;
		isUnwbPositionIncreased=0;
		if(((anglesCategory[z-1]==2)||(anglesCategory[z-1]==1))&&(fi<=thetaMax1)){//AN anikei sto NW
			if((Angles[z]==tmin)&&(anglesCategory[z-1]==2)){
				condition=1;//diladi bike
				
				if(unwbPosition<unwtPosition){
					unwbPosition=unwbPosition+1;
					isUnwbPositionIncreased=1;
				}
				
				previousPnwx=Pnwx;
				previousPnwy=Pnwy;
				
				Pnwx=chainNW[0][unwbPosition];
				Pnwy=chainNW[1][unwbPosition];
				
				
				if(fi<Angles[z+1]){
					unwbPosition=unwbPosition-1;
				}
				
				if(fi<tmin){
					fiprevious=fi;
					fi=tmin;
					isfiUpdated=1;
				}
				
				
				if(isZincreased==0){
					//z=z+1;
					isZincreased=1;
				}
				isNwUpdated=1;
			}else if(Angles[z]>tmin){
				if(fi<tmin){
					fiprevious=fi;
					fi=tmin;
					isfiUpdated=1;	
				}
					
				condition=1;
			}
			if((((Pnwx==previousPnwx)&&(Pnwy==previousPnwy))&&(tmin==previoustmin))&&(anglesCategory[z-1]==2)){
			
				if(unwbPosition<unwtPosition){
					if(isUnwbPositionIncreased==0){
						unwbPosition=unwbPosition+1;
					}
				}
				
				previousPnwx=Pnwx;
				previousPnwy=Pnwy;
				
				Pnwx=chainNW[0][unwbPosition];
				Pnwy=chainNW[1][unwbPosition];
				
				fiprevious=fi;
				fi=Angles[z];
				isfiUpdated=1;
				

			isNwUpdated=1;	
			}
			
		}
		
		
		condition=0;
		isUnebPositionIncreased=0;
		if(((anglesCategory[z-1]==0)||(anglesCategory[z-1]==3))&&(fi2<=thetaMax2)){//AN anikei sto NE
			if((Angles[z]==tmin)&&(anglesCategory[z-1]==3)){
				condition=1;
				
				if(unebPosition<unetPosition){ 
					unebPosition=unebPosition+1;
					isUnebPositionIncreased=1;
				}
				
				previousPnex=Pnex;
				previousPney=Pney;
				
				Pnex=chainNE[0][unebPosition];
				Pney=chainNE[1][unebPosition];
				
				if(fi2<tmin){
					fi2previous=fi2;
					fi2=tmin;
					isfi2Updated=1;
				}
				
				if(isZincreased==0){
					//z=z+1;
					isZincreased=1;
				}
				
				condition=1;
				isNeUpdated=1;
			}else if(Angles[z]>tmin){
				
				
				if((unebPosition<unetPosition)&&(anglesCategory[z-1]==3)){
					
					unebPosition=unebPosition+1;
					isUnebPositionIncreased=1;
					
				}
				Pnex=chainNE[0][unebPosition];
				Pney=chainNE[1][unebPosition];
				if(tmin<=fi2){
					fi2previous=fi2;
					fi2=Angles[z];
					isZincreased=1;
					isfi2Updated=1;
				}else{
					fi2previous=fi2;
					fi2=tmin;
					isfi2Updated=1;
				}
				condition=1;
			}
			
			
			if((((Pnex==previousPnex)&&(Pney==previousPney))&&(tmin==previoustmin))&&(anglesCategory[z-1]==3)){
			
				if(unebPosition<unetPosition){
					if(isUnebPositionIncreased==0){
						nextunebPosition=nextunebPosition+1;	
					}
				}
				
				previousPnex=Pnex;
				previousPney=Pney;
				
				Pnex=chainNE[0][unebPosition];
				Pney=chainNE[1][unebPosition];
				
				fi2previous=fi2;
				fi2=Angles[z];
				isfi2Updated=1;
				
				isNeUpdated=1;
			}
			
		}
		
		
		if(isZincreased==1){
			z=z+1;
		}
		
	if(isfi2Updated=0){
		fi2previous=fi2;
	}
				
	previoustmin=tmin;
	
	if((isZincreased==0)&&(z==(totali-1))){
		z=z+1;
	}
	
	if( (anglesCategory[z-1]==0)||(anglesCategory[z-1]==3) ){	
		if((anglesCategory[z]==1)||(anglesCategory[z]==2)){
			if((fi2==fi2previous)&&(fi2<=thetaMax2)){
				
				if(isZincreased==0){
					z=z+1;
					fi2previous=fi2;
					fi2=Angles[z];	
				}
			}
		}
	}
	
	if( (anglesCategory[z-1]==1)||(anglesCategory[z-1]==2) ){
		if((anglesCategory[z]==0)||(anglesCategory[z]==3)){
			if((fi==fiprevious)&&(fi<=thetaMax1)){
				
				if(isZincreased==0){
					z=z+1;
					fiprevious=fi;
					fi=Angles[z];
					
				}
			}
		}
	}
	
	dota=dota+1;
	if(dota==10){
		break;
	}
	
//*****************************************************************************************************	
//Edo kato o telikos m kwdikas gia megistopiisi pirina
//*****************************************************************************************************
	isIF=0;
		
	//to pio aristera tha einai to Line1,Line2..Point1x 
	if(Line1_Point1X<Line1_Point2X){
		//do nothing its good
	}else{
		NewTempX=Line1_Point1X;
		Line1_Point1X=Line1_Point2X;
		Line1_Point2X=NewTempX;
		
		NewTempY=Line1_Point1Y;
		Line1_Point1Y=Line1_Point2Y;
		Line1_Point2Y=NewTempY;
		
		
	}
	
	if(isPrevLine==1){ 
		if(PrevLine1_Point1X<PrevLine1_Point2X){
			//do nothing its good
		}else{
			NewTempX=PrevLine1_Point1X;
			PrevLine1_Point1X=PrevLine1_Point2X;
			PrevLine1_Point2X=NewTempX;
		
			NewTempY=PrevLine1_Point1Y;
			PrevLine1_Point1Y=PrevLine1_Point2Y;
			PrevLine1_Point2Y=NewTempY;
		}
	}
		
	if(Line2_Point1X<Line2_Point2X){
		//do nothing its good
	}else{
		NewTempX=Line2_Point1X;
		Line2_Point1X=Line2_Point2X;
		Line2_Point2X=NewTempX;
		
		NewTempY=Line2_Point1Y;
		Line2_Point1Y=Line2_Point2Y;
		Line2_Point2Y=NewTempY;
	}
	
	if(isPrevLine==1){
		if(PrevLine2_Point1X<PrevLine2_Point2X){
			//do nothing its good
		}else{
			NewTempX=PrevLine2_Point1X;
			PrevLine2_Point1X=PrevLine2_Point2X;
			PrevLine2_Point2X=NewTempX;
		
			NewTempY=PrevLine2_Point1Y;
			PrevLine2_Point1Y=PrevLine2_Point2Y;
			PrevLine2_Point2Y=NewTempY;
		}
	}
	
	d1=(previousPsey - Line1_Point1Y);
	d2=(Line2_Point2Y - Pnwy);
	d3=(Line1_Point2Y - previousPsey);
	d4=(Pnwy - Line2_Point1Y);
	d5=(previousPsex - Line1_Point1X);
	d6=(Line2_Point2X - previousPnwx);
	d7=(Line1_Point2X - previousPsex);
	d8=(previousPnwx - Line2_Point1X);
	
	if(isPrevLine==1){//an exo vrei previous i oxi
	
		if( ((((Line1_Point1Y==PrevLine1_Point1Y)&&(Line2_Point2Y==PrevLine2_Point2Y))&&(Line1_Point2Y==PrevLine1_Point2Y))&&(Line2_Point1Y==PrevLine2_Point1Y)) ){
			if( Line1_Point1X!=PrevLine1_Point1X ){
				a=0;
				b=(0.5)*( (d1*d1)+(d2*d2)-(d3*d3)-(d4*d4) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1Y==PrevLine1_Point1Y)&&(Line2_Point2Y==PrevLine2_Point2Y))&&(Line1_Point2Y==PrevLine1_Point2Y))&&(Line2_Point1X==PrevLine2_Point1X)) ){
			if(Line1_Point1X!=PrevLine1_Point1X){
				a=-(0.5)*(d8*d8);
				b=(0.5)*( (d1*d1)+(d2*d2)-(d3*d3) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1Y==PrevLine1_Point1Y)&&(Line2_Point2Y==PrevLine2_Point2Y))&&(Line1_Point2X==PrevLine1_Point2X))&&(Line2_Point1Y==PrevLine2_Point1Y)) ){
			if(Line1_Point1X!=PrevLine1_Point1X){
				a=-(0.5)*(d7*d7);
				b=(0.5)*( (d1*d1)+(d2*d2)-(d4*d4) );
				isIF=1;
				
			}
		}
	
		if( ((((Line1_Point1Y==PrevLine1_Point1Y)&&(Line2_Point2Y==PrevLine2_Point2Y))&&(Line1_Point2X==PrevLine1_Point2X))&&(Line2_Point1X==PrevLine2_Point1X)) ){
			if(Line1_Point1X!=PrevLine1_Point1X){
				a=-(0.5)*( (d7*d7)+(d8*d8) );
				b=(0.5)*( (d1*d1)+(d2*d2) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1Y==PrevLine1_Point1Y)&&(Line2_Point2X==PrevLine2_Point2X))&&(Line1_Point2Y==PrevLine1_Point2Y))&&(Line2_Point1Y==PrevLine2_Point1Y)) ){
			if(Line1_Point1X!=PrevLine1_Point1X){
				a=-(0.5)*(d6*d6);
				b=(0.5)*( (d1*d1)-(d3*d3)-(d4*d4) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1Y==PrevLine1_Point1Y)&&(Line2_Point2X==PrevLine2_Point2X))&&(Line1_Point2Y==PrevLine1_Point2Y))&&(Line2_Point1X==PrevLine2_Point1X)) ){
			if(Line1_Point1X!=PrevLine1_Point1X){
				a=-(0.5)*( (d6*d6)+(d8*d8) );
				b=(0.5)*( (d1*d1)-(d3*d3) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1Y==PrevLine1_Point1Y)&&(Line2_Point2X==PrevLine2_Point2X))&&(Line1_Point2X==PrevLine1_Point2X))&&(Line2_Point1Y==PrevLine2_Point1Y)) ){
			if(Line1_Point1X!=PrevLine1_Point1X){
				a=(0.5)*( (d6*d6)-(d7*d7) );
				b=(0.5)*( (d1*d1)-(d4*d4) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1Y==PrevLine1_Point1Y)&&(Line2_Point2X==PrevLine2_Point2X))&&(Line1_Point2X==PrevLine1_Point2X))&&(Line2_Point1X==PrevLine2_Point1X)) ){
			if(Line1_Point1X!=PrevLine1_Point1X){
				a=(0.5)*( (d6*d6)-(d7*d7)-(d8*d8) );
				b=(0.5)*(d1*d1);
				isIF=1;
			}
		}

		if( ((((Line1_Point1X==PrevLine1_Point1X)&&(Line2_Point2Y==PrevLine2_Point2Y))&&(Line1_Point2Y==PrevLine1_Point2Y))&&(Line2_Point1Y==PrevLine2_Point1Y)) ){
			if(Line1_Point1Y!=PrevLine1_Point1Y){
				a=(0.5)*(d5*d5);
				b=(0.5)*( (d2*d2)-(d3*d3)-(d4*d4) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1X==PrevLine1_Point1X)&&(Line2_Point2Y==PrevLine2_Point2Y))&&(Line1_Point2Y==PrevLine1_Point2Y))&&(Line2_Point1X==PrevLine2_Point1X)) ){
			if(Line1_Point1Y!=PrevLine1_Point1Y){
				a=(0.5)*( (d5*d5)-(d8*d8) );
				b=(0.5)*( (d2*d2)-(d3*d3) );
				isIF=1;
			}	
		}
	
		if( ((((Line1_Point1X==PrevLine1_Point1X)&&(Line2_Point2Y==PrevLine2_Point2Y))&&(Line1_Point2X==PrevLine1_Point2X))&&(Line2_Point1Y==PrevLine2_Point1Y)) ){
			if(Line1_Point1Y!=PrevLine1_Point1Y){
				a=(0.5)*( (d5*d5)-(d7*d7) );
				b=(0.5)*( (d2*d2)-(d4*d4) );
				isIF=1;
			}	
		}
	
		if( ((((Line1_Point1X==PrevLine1_Point1X)&&(Line2_Point2Y==PrevLine2_Point2Y))&&(Line1_Point2X==PrevLine1_Point2X))&&(Line2_Point1X==PrevLine2_Point1X)) ){
			if(Line1_Point1Y!=PrevLine1_Point1Y){
				a=(0.5)*( (d5*d5)-(d7*d7)-(d8*d8) );
				b=(0.5)*( (d2*d2) );
				isIF=1;
			}	
		}
		
		if( ((((Line1_Point1X==PrevLine1_Point1X)&&(Line2_Point2X==PrevLine2_Point2X))&&(Line1_Point2X==PrevLine1_Point2X))&&(Line2_Point1Y==PrevLine2_Point1Y)) ){
			if(Line1_Point1Y!=PrevLine1_Point1Y){
				a=(0.5)*( (d5*d5)+(d6*d6)-(d7*d7) );
				b=-(0.5)*( (d4*d4) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1X==PrevLine1_Point1X)&&(Line2_Point2X==PrevLine2_Point2X))&&(Line1_Point2X==PrevLine1_Point2X))&&(Line2_Point1X==PrevLine2_Point1X)) ){
			if(Line1_Point1Y!=PrevLine1_Point1Y){
				a=(0.5)*( ((d5*d5)+(d6*d6))-((d7*d7)+(d8*d8)) );
				b=0;
				isIF=1;
				
			}
		}
	
		if( ((((Line1_Point1X==PrevLine1_Point1X)&&(Line2_Point2X==PrevLine2_Point2X))&&(Line1_Point2Y==PrevLine1_Point2Y))&&(Line2_Point1Y==PrevLine2_Point1Y)) ){
			if(Line1_Point1Y!=PrevLine1_Point1Y){
				a=(0.5)*( (d5*d5)+(d6*d6) );
				b=-(0.5)*( (d4*d4)+(d3*d3) );
				isIF=1;
			}
		}
	
		if( ((((Line1_Point1X==PrevLine1_Point1X)&&(Line2_Point2X==PrevLine2_Point2X))&&(Line1_Point2Y==PrevLine1_Point2Y))&&(Line2_Point1X==PrevLine2_Point1X)) ){
			if(Line1_Point1Y!=PrevLine1_Point1Y){
				a=(0.5)*( (d5*d5)+(d6*d6)-(d8*d8));
				b=-(0.5)*( (d3*d3) );
				isIF=1;
			}
		}
		
		if(isIF==0){//auto simenei oti den bike sta 16 if apo pano
		
			//taksinomise ta v1 aristera apo v2
			if(s1x<s2x){
				//do nothing its good
			}else{
				NewTempX=s1x;
				s1x=s2x;
				s2x=NewTempX;
		
				NewTempY=s1y;
				s1y=s2y;
				s2y=NewTempY;
			}
			
			if(t1x<t2x){
				//do nothing its good
			}else{
				NewTempX=t1x;
				t1x=t2x;
				t2x=NewTempX;
		
				NewTempY=t1y;
				t1y=t2y;
				t2y=NewTempY;
			}
			
			Height1=( (Psey-Prevs1y)*PrevLine1_Point1X-(Psex-Prevs1x)*PrevLine1_Point1Y+Prevs1y*Psex-Prevs1x*Psey )/(sqrt( (Psey-Prevs1y)*(Psey-Prevs1y)+(Psex-Prevs1x)*(Psex-Prevs1x) ));
			Height2=( (Psey-Prevs1y)*Line1_Point1X-(Psex-Prevs1x)*Line1_Point1Y+Prevs1y*Psex-Prevs1x*Psey )/(sqrt( (Psey-Prevs1y)*(Psey-Prevs1y)+(Psex-Prevs1x)*(Psex-Prevs1x) ));
			Height3=( (Psey-Prevs2y)*PrevLine1_Point2X-(Psex-Prevs2x)*PrevLine1_Point2Y+Prevs2y*Psex-Prevs2x*Psey )/(sqrt( (Psey-Prevs2y)*(Psey-Prevs2y)+(Psex-Prevs2x)*(Psex-Prevs2x) ));
			Height4=( (Psey-Prevs2y)*Line1_Point2X-(Psex-Prevs2x)*Line1_Point2Y+Prevs2y*Psex-Prevs2x*Psey )/(sqrt( (Psey-Prevs2y)*(Psey-Prevs2y)+(Psex-Prevs2x)*(Psex-Prevs2x) ));
		
			
			Height5=( (Pnwy-Prevt1y)*PrevLine2_Point1X-(Pnwx-Prevt1x)*PrevLine2_Point1Y+Prevt1y*Pnwx-Prevt1x*Pnwy )/(sqrt( (Pnwy-Prevt1y)*(Pnwy-Prevt1y)+(Pnwx-Prevt1x)*(Pnwx-Prevt1x) ));
			Height6=( (Pnwy-Prevt1y)*Line2_Point1X-(Pnwx-Prevt1x)*Line2_Point1Y+Prevt1y*Pnwx-Prevt1x*Pnwy )/(sqrt( (Pnwy-Prevt1y)*(Pnwy-Prevt1y)+(Pnwx-Prevt1x)*(Pnwx-Prevt1x) ));
			
			
			Height7=( (Pnwy-Prevt2y)*PrevLine2_Point2X-(Pnwx-Prevt2x)*PrevLine2_Point2Y+Prevt2y*Pnwx-Prevt2x*Pnwy )/(sqrt( (Pnwy-Prevt2y)*(Pnwy-Prevt2y)+(Pnwx-Prevt2x)*(Pnwx-Prevt2x) ));
			Height8=( (Pnwy-Prevt2y)*Line2_Point2X-(Pnwx-Prevt2x)*Line2_Point2Y+Prevt2y*Pnwx-Prevt2x*Pnwy )/(sqrt( (Pnwy-Prevt2y)*(Pnwy-Prevt2y)+(Pnwx-Prevt2x)*(Pnwx-Prevt2x) ));
			
			
			
			
			//kanta sigoura thetika
			if(Height1<0){
				Height1=-Height1;
			}
			if(Height2<0){
				Height2=-Height2;
			}
			if(Height3<0){
				Height3=-Height3;
			}
			if(Height4<0){
				Height4=-Height4;
			}
			
			if(Height5<0){
				Height5=-Height5;
			}
			if(Height6<0){
				Height6=-Height6;
			}
			if(Height7<0){
				Height7=-Height7;
			}
			if(Height8<0){
				Height8=-Height8;
			}		
			
			
			
			
			E1=(Height1+Height2)*(sqrt( (Psey-Prevs1y)*(Psey-Prevs1y)+(Psex-Prevs1x)*(Psex-Prevs1x) )) + (Height7+Height8)*(sqrt( (Pnwy-Prevt2y)*(Pnwy-Prevt2y)+(Pnwx-Prevt2x)*(Pnwx-Prevt2x) ));//prasino
			E2=(Height3+Height4)*(sqrt( (Psey-Prevs2y)*(Psey-Prevs2y)+(Psex-Prevs2x)*(Psex-Prevs2x) )) + (Height5+Height6)*(sqrt( (Pnwy-Prevt2y)*(Pnwy-Prevt2y)+(Pnwx-Prevt2x)*(Pnwx-Prevt2x) ));//kokkino
			
			
			
			if( ((Line1_Point1X==PrevLine1_Point1X)&&(Line1_Point1Y==PrevLine1_Point1Y))||(E2>E1)){//kokkino megalitero
				cout << "\n Kokkino Megalitero";
			}
			
			if(E1>E2){//prasino megalitero
				cout << "\n Prasino Megalitero";
				MaxLine1_Point1X=Line1_Point1X;
				MaxLine1_Point1Y=Line1_Point1Y;
				MaxLine1_Point2X=Line1_Point2X;
				MaxLine1_Point2Y=Line1_Point2Y;
				MaxLine2_Point1X=Line2_Point1X;
				MaxLine2_Point1Y=Line2_Point1Y;
				MaxLine2_Point2X=Line2_Point2X;
				MaxLine2_Point2Y=Line2_Point2Y;
			}
		}
		
		
		
		if(isIF==1){//TO ISIF=0 simenei den exo metakinisi euthias sto pirina
			theta=atan(sqrt(-(b/a)));
	
			if( ((a==0)&&(b==0))||((a==0)&&(b<0))||((a<0)&&(b<=0))||((a>0)&&(b<0)&&(theta>fi))||((a<0)&&(b>0)&&(theta<fiprevious)) ){
			}
	
			if( ((a==0)&&(b>0))||((a>0)&&(b<0)&&(theta<fiprevious))||((a<0)&&(b>0)&&(theta>fi))||((a>0)&&(b>=0)) ){
				MaxLine1_Point1X=Line1_Point1X;
				MaxLine1_Point1Y=Line1_Point1Y;
				MaxLine1_Point2X=Line1_Point2X;
				MaxLine1_Point2Y=Line1_Point2Y;
				MaxLine2_Point1X=Line2_Point1X;
				MaxLine2_Point1Y=Line2_Point1Y;
				MaxLine2_Point2X=Line2_Point2X;
				MaxLine2_Point2Y=Line2_Point2Y;
			}

			if( (a<0)&&(b>0)&&(theta>=fiprevious)&&(theta<fi) ){
				
				if( (Line1_Point1Y)==(PrevLine1_Point1Y) ){
					MaxLine1_Point1Y=Line1_Point1Y;
					MaxLine1_Point1X=(1/tan(theta))*(Line1_Point1Y-Psey+((tan(theta))*Psex));
				}
				if( (Line1_Point1X)==(PrevLine1_Point1X) ){
					MaxLine1_Point1X=Line1_Point1X;
					MaxLine1_Point1Y=tan(theta)*(Line1_Point1X-Psex)+Psey;
				}
				if( (Line1_Point2Y)==(PrevLine1_Point2Y) ){
					MaxLine1_Point2Y=Line1_Point2Y;
					MaxLine1_Point2X=(1/tan(theta))*(Line1_Point2Y-Psey+tan(theta)*Psex);
				}
				if( (Line1_Point2X)==(PrevLine1_Point2X) ){
					MaxLine1_Point2X=Line1_Point2X;
					MaxLine1_Point2Y=tan(theta)*(Line1_Point2X-Psex)+Psey;
				}
				//...
				if( (Line2_Point1Y)==(PrevLine2_Point1Y) ){
					MaxLine2_Point1Y=Line2_Point1Y;
					MaxLine2_Point1X=(1/tan(theta))*(Line2_Point1Y-Psey+tan(theta)*Psex);
				}
				if( (Line2_Point1X)==(PrevLine2_Point1X) ){
					MaxLine2_Point1X=Line2_Point1X;
					MaxLine2_Point1Y=tan(theta)*(Line2_Point1X-Psex)+Psey;
				}
				if( (Line2_Point2Y)==(PrevLine2_Point2Y) ){
					MaxLine2_Point2Y=Line2_Point2Y;
					MaxLine2_Point2X=(1/tan(theta))*(Line2_Point2Y-Psey+tan(theta)*Psex);
				}
				if( (Line2_Point2X)==(PrevLine2_Point2X) ){
					MaxLine2_Point2X=Line2_Point2X;
					MaxLine2_Point2Y=tan(theta)*(Line2_Point2X-Psex)+Psey;
				}
			}
	
			if( (a>0)&&(b<0)&&(theta>=fiprevious)&&(theta<=fi) ){
				//ola auta gia Line1
				if(Line1_Point1Y==PrevLine1_Point1Y){//orizontia akmi
					E1=(1/2)*((Psey-Line1_Point1Y)*(Psey-Line1_Point1Y))*((1/tan(fiprevious))-1/tan(fi));//prasino trigono
				}
				if(Line1_Point1X==PrevLine1_Point1X){//katakorifi akmi
					E1=(1/2)*((Line1_Point1X-Psex)*(Line1_Point1X-Psex))*(tan(fi)-tan(fiprevious));//prasino trigono
				}
				if(Line1_Point2Y==PrevLine1_Point2Y){//orizontia akmi
					E2=(1/2)*((Psey-Line1_Point2Y)*(Psey-Line1_Point2Y))*((1/tan(fiprevious))-1/tan(fi));//kokkino	
				}
				if((Line1_Point1X==PrevLine1_Point1X)&&(Line1_Point1X>Line1_Point2X)){//katakorifi akmi
					E2=(1/2)*((Line1_Point2X-Psex)*(Line1_Point2X-Psex))*(tan(fi)-tan(fiprevious));//kokkino	
				}
		
				SumE1=SumE1+E1;
				SumE2=SumE2+E2;
		
				//Ola auta gia Line2
				if(Line2_Point1Y==PrevLine2_Point1Y){//orizontia akmi
					E1=(1/2)*((Psey-Line2_Point1Y)*(Psey-Line2_Point1Y))*((1/tan(fiprevious))-1/tan(fi));//prasino trigono
				}
				if(Line2_Point1X==PrevLine2_Point1X){//katakorifi akmi
					E1=(1/2)*((Line2_Point1X-Psex)*(Line2_Point1X-Psex))*(tan(fi)-tan(fiprevious));//prasino trigono
				}
				if(Line2_Point2Y==PrevLine2_Point2Y){//orizontia akmi
					E2=(1/2)*((Psey-Line2_Point2Y)*(Psey-Line2_Point2Y))*((1/tan(fiprevious))-1/tan(fi));//kokkino	
				}
				if((Line2_Point1X==PrevLine2_Point1X)&&(Line2_Point1X>Line2_Point2X)){//katakorifi akmi
					E2=(1/2)*((Line2_Point2X-Psex)*(Line2_Point2X-Psex))*(tan(fi)-tan(fiprevious));//kokkino
				}
		
				SumE1=SumE1+E1;
				SumE2=SumE2+E2;
		
				if(SumE1>SumE2){//prasina trigona  pio megala ara neo megisto pirina
					
					MaxLine1_Point1X=Line1_Point1X;
					MaxLine1_Point1Y=Line1_Point1Y;
					MaxLine1_Point2X=Line1_Point2X;
					MaxLine1_Point2Y=Line1_Point2Y;
					MaxLine2_Point1X=Line2_Point1X;
					MaxLine2_Point1Y=Line2_Point1Y;
					MaxLine2_Point2X=Line2_Point2X;
					MaxLine2_Point2Y=Line2_Point2Y;
				}//Allios kokkina trigona pio megala ara den kano tpt
			}
		}//if(isIF==0){
	}//isPrevLine, an exo previous i oxi
	else{
		MaxLine1_Point1X=Line1_Point1X;
		MaxLine1_Point1Y=Line1_Point1Y;
		MaxLine1_Point2X=Line1_Point2X;
		MaxLine1_Point2Y=Line1_Point2Y;
		MaxLine2_Point1X=Line2_Point1X;
		MaxLine2_Point1Y=Line2_Point1Y;
		MaxLine2_Point2X=Line2_Point2X;
		MaxLine2_Point2Y=Line2_Point2Y;
	}
	//kathe treximo exei sto maxline ta megista
	

	PrevLine1_Point1X=Line1_Point1X;
	PrevLine1_Point1Y=Line1_Point1Y;
	 
	PrevLine1_Point2X=Line1_Point2X;
	PrevLine1_Point2Y=Line1_Point2Y;
	 
	PrevLine2_Point1X=Line2_Point1X;
	PrevLine2_Point1Y=Line2_Point1Y;
	 
	PrevLine2_Point2X=Line2_Point2X;
	PrevLine2_Point2Y=Line2_Point2Y;
	
	//korifes proigumenou treximatos
	Prevt1x=t1x;
	Prevt1y=t1y;
	
	Prevt2x=t2x;
	Prevt2y=t2y;
	
	Prevs1x=s1x;
	Prevs1y=s1y;
	
	Prevs2x=s2x;
	Prevs2y=s2y;
	
	isPrevLine=1;
	
	
	
	if(isNeUpdated==0){
		previousPnex=Pnex;
		previousPney=Pney;
	}
	
	if(isNwUpdated==0){
		previousPnwx=Pnwx;
		previousPnwy=Pnwy;
	}
	
	if(isSeUpdated==0){
		previousPsex=Psex;   
		previousPsey=Psey;
	}
	
	if(isSwUpdated==0){
		previousPswx=Pswx;
		previousPswy=Pswy;
	}
	
	if(isfiUpdated=0){
		fiprevious=fi;
	}
	
	//gia kathe treksimo
	//GLMaxLines[30][8]
	badz=badz+1;
	GLMaxLines[badz][0]=MaxLine1_Point1X;
	GLMaxLines[badz][1]=MaxLine1_Point1Y;
	GLMaxLines[badz][2]=MaxLine1_Point2X;
	GLMaxLines[badz][3]=MaxLine1_Point2Y;
	
	GLMaxLines[badz][4]=MaxLine2_Point1X;
	GLMaxLines[badz][5]=MaxLine2_Point1Y;
	GLMaxLines[badz][6]=MaxLine2_Point2X;
	GLMaxLines[badz][7]=MaxLine2_Point2Y;
	
	
	
	
	
	
	
	
	
}//mexri edo kanei ta treximata ton gonion
	GlMaxLine1_Point1X= MaxLine1_Point1X; 
	GlMaxLine1_Point1Y= MaxLine1_Point1Y;
	GlMaxLine1_Point2X= MaxLine1_Point2X; 
	GlMaxLine1_Point2Y= MaxLine1_Point2Y; 
	GlMaxLine2_Point1X= MaxLine2_Point1X; 
	GlMaxLine2_Point1Y= MaxLine2_Point1Y; 
	GlMaxLine2_Point2X= MaxLine2_Point2X; 
	GlMaxLine2_Point2Y= MaxLine2_Point2Y;
	cout << "\n_____Tipose Simeia gia megisto Pirina:_____\n";
	cout <<	"\nMaxLine1_Point1X=" << MaxLine1_Point1X;
	cout <<	"\nMaxLine1_Point1Y=" << MaxLine1_Point1Y;
	cout <<	"\nMaxLine1_Point2X=" << MaxLine1_Point2X;
	cout <<	"\nMaxLine1_Point2Y=" << MaxLine1_Point2Y;
	cout <<	"\nMaxLine2_Point1X=" << MaxLine2_Point1X;
	cout <<	"\nMaxLine2_Point1Y=" << MaxLine2_Point1Y;
	cout <<	"\nMaxLine2_Point2X=" << MaxLine2_Point2X;
	cout <<	"\nMaxLine2_Point2Y=" << MaxLine2_Point2Y;
	cout << "\n";
}//edo teleionei i sinartisi mou





//Apo edo kai kato ta grafika
void init(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 0);	// background color to black
	glMatrixMode(GL_PROJECTION);		// prameter provolhs
	gluOrtho2D(0.0, 1000, 0.0, 1000);
}

void DisplaySettings() {
	int i, j;
	
	//glClearColor(0, 0, 0, 0.0);//white
	for (i = 0; i < VerticesNum-1; i++){
		
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);//black
		glBegin(GL_LINES);
		glVertex2i(50*Vertex[0][i], 50*Vertex[1][i]);
		glVertex2i(50*Vertex[0][i+1], 50*Vertex[1][i+1]);
		glEnd();
	}
	
	
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);//black
	glBegin(GL_LINES);
		glVertex2i(50*Vertex[0][0], 50*Vertex[1][0]);
		glVertex2i(50*Vertex[0][VerticesNum-1], 50*Vertex[1][VerticesNum-1]);
	glEnd();
	//mexri edo emfanizete to poligono
	
	
	
	
	//emfanizon 2 lines gia kathe thesi tou pirina gia kathe treximo
	//for(j = 0; j < badz; j++){
	j = nextTimesClicked;
	cout << "\nj=" << j;
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
		glBegin(GL_LINES);
			glVertex2i(50*GLMaxLines[j][0], 50*GLMaxLines[j][1]);
			glVertex2i(50*GLMaxLines[j][2], 50*GLMaxLines[j][3]);
		glEnd();
	
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
		glBegin(GL_LINES);
			glVertex2i(50*GLMaxLines[j][4], 50*GLMaxLines[j][5]);
			glVertex2i(50*GLMaxLines[j][6], 50*GLMaxLines[j][7]);
		glEnd();
	
	//}
	
	
	
	
	
	
	
	
	
	
	
	//apo kato emfanizont oi 2 Lines gia megisto pirina Telikes
	//glClearColor(1.0, 1.0, 0.0f, 0.0f);//yellow
	/*glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
	glBegin(GL_LINES);
		glVertex2i(50*GlMaxLine1_Point1X, 50*GlMaxLine1_Point1Y);
		glVertex2i(50*GlMaxLine1_Point2X, 50*GlMaxLine1_Point2Y);
	glEnd();
	
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
	glBegin(GL_LINES);
		glVertex2i(50*GlMaxLine2_Point1X, 50*GlMaxLine2_Point1Y);
		glVertex2i(50*GlMaxLine2_Point2X, 50*GlMaxLine2_Point2Y);
	glEnd();	*/
}
	
/* All about the display */
void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	DisplaySettings();
	
	glutSwapBuffers ( );
	glFlush();
	
}


void keyboardFunc(GLubyte key, GLint xMouse, GLint yMouse) {
	
	switch (key) {
		case 27: // Esc
				exit(EXIT_SUCCESS);
			break;
		
		case 'n':
				if(nextTimesClicked == badz) {
					//nextTimesClicked = 0;
				}else {
					cout << "\nnextTimesClicked=" << nextTimesClicked;
					nextTimesClicked++;
					//glutDisplayFunc(displayFunc);
					displayFunc();
				}
			break;
		case 'N':
				if(nextTimesClicked == badz) {
					//nextTimesClicked = 0;
				}else {
					cout << "\nnextTimesClicked=" << nextTimesClicked;
					nextTimesClicked++;
					//glutDisplayFunc(displayFunc);
					displayFunc();
				}
			break;
		
		default:
			break;
	}
	glFlush ( );
}





/*
//==============================================================================
				Function_MAIN
//==============================================================================
*/
int main (int argc, char* argv[])
{
	int i;
	initialise();//Create & GivePoints, Create Edge 
	isOrthogon();//Is it orthogon or not?
	extremityEdge();//Find Extremities among other things
	check_monotonicity();//Find if a kernel exists in polygon or not
	checkCorners();//
	Melkman();//chains
	findTangent();//Tangents
	findAngles();//Angles between Chain's Edge and y+
	computeKernel();//compute maximum Kernel under rotation
	
	
	
	//apo edo kai kato gia Grafika se "OpenGL"
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
	glutInitWindowSize(1000, 1000); 
	glutInitWindowPosition(500, 200);
	glutCreateWindow ("Polygon");

		
	/* Initialize the window */
	init();

	glutDisplayFunc(displayFunc);
	glutKeyboardFunc(keyboardFunc);
	
	glutMainLoop();

	return 0;
//******************************************************************************
//**********************************END_OF_PROGRAM******************************
//******************************************************************************
}


