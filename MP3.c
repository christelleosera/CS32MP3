#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct people {
	int coor[2];
	short int visited;
	short int dt;
	short int ft;
	short int pred;
	short int pred2;
	short int low;
	int key;
}people;

typedef struct edge {
	short int ends[2];
	short int tag;	
	int weight;
}edge;

int readcoor(char temp[], int b);
float disform(int a1, int a2, int b1, int b2);
void traverse(int x, int y);
void dfs(int x, int y);
int getindex(int a, int b);
int getmin(int x, int y);
void sort(int x[], int y);
void remove(int x[], int y, int z);

short int admatrix[100][100];
short int dfsstack[200];
edge edgearr[5000];
int counter=0, top =0, mover=1, edgecounter=0;
people person[100];
	
int main (){
	FILE *fp;
	FILE *fc;
	char holder[100][15];
	char temp[4];
	char temp2[50];
	int cutpoints[100];
	int i=0, j=1, k=0, a=0, x=0, y=0, z=0, numofp=0, c=0, d=0, index=0, g=0, pass = 0, a1=0;
	int start[2];
	int u[100];
	int uminusv[100];
	int ftqueue[100];

	double maxdis = 0, distance, mindis=0;
	double fractional = 0;
	int cost = 0;
	
	//FILE OPENING
	fc = fopen("201001634.txt", "w");
	fp = fopen("test.txt", "r");
	rewind (fp);

	//CLEAR
	for(i=0; i<100; i++)
	strcpy(holder[i], "\0");
	
	i=0;
	fgets(holder[i], 100, fp);
	rewind(fp);
	
while(!feof(fp) && strcmp(holder[i], "***END***") != 0){
		
		//CLEAR
		while(strcmp(holder[i],"\0")!=0) {
			strcpy(holder[i], "\0"); i++; }
		for(i=0; i<100; i++){
			person[i].visited = 0;
			person[i].dt =0;
			person[i].ft =0;
			person[i].pred=-1;
			person[i].pred2=-1;
			person[i].low=0;
			person[i].key = 999999;
			cutpoints[i] =0;
			ftqueue[i] =0;
			u[i]=0;
			uminusv[i]=0;
			for(j=0; j<100; j++)admatrix[i][j] = 0;	
		}
		for(i=0; i<edgecounter; i++) {
			edgearr[i].ends[0]=0;
			edgearr[i].ends[1]=0;
			edgearr[i].tag=0;
		}
		for(i=0; i<200; i++){
			dfsstack[i] =0;
		}  
		
		i=0; j=1; k=0; a=0; z=0; x=0; y=0; numofp=0; c=0; d=0; index=0; edgecounter =0; counter=0; top =0; mover=1; a1=0;
		maxdis = 0; distance=0; mindis=0; fractional = 0; cost = 0;
		fgets(holder[i], 100, fp);
		while(strcmp(holder[i], "\n") != 0 && !feof(fp) && strcmp(holder[i], "***END***") != 0){
			i++;
			fgets(holder[i], 100, fp);	
		}
		
		i--;
		for(j=0; j<4; j++){
			temp[j] = '\0';
		}
		j=1;
		
		//GET COORDINATES OF START
		while(holder[i][j] != ','){
			temp[k] = holder[i][j];
			j++; k++;
		}
		start[0] = readcoor(temp, k);	
		k=0;
		
		j++;
		while(holder[i][j] != ')'){
			temp[k] = holder[i][j];
			j++; k++;
		}
		start[1] = readcoor(temp, k);
		k=0;
		
		
		//GET MAX DISTANCE
		i--;
		j=0;
		while(holder[i][j] != '\n' && holder[i][j] !='.'){
				temp[k]= holder[i][j];
				k++; j++;
		}
		maxdis = readcoor(temp, k);
		if(holder[i][j] == '.'){
		j++;
		k=1;
		while(holder[i][j] != '\n'){
			temp2[k]= holder[i][j];
			temp2[k]= temp2[k] -48;
			fractional = temp2[k]*(1/(pow(10, k)));
			maxdis = maxdis + fractional;
			k++; j++;
		}
			
		}
		
		
		//GET COORDINATES
		i--;c=0;
		while(z<=i){
			d=0;
			person[a].visited=0;
			j=1;
			k=0;
			while(holder[z][j] != ','){
			temp[k] = holder[z][j];
			j++; k++;
			}
			person[a].coor[0] = readcoor(temp, k);
			j++;
			k=0;
			while(holder[z][j] != ')'){
				temp[k] = holder[z][j];
				j++; k++;
			}
			person[a].coor[1] = readcoor(temp, k);
			
			
			for(y=0; y<z; y++){
				if(person[y].coor[0] == person[a].coor[0] && person[y].coor[1] == person[a].coor[1])d++;
			}
			
			z++;	
			a++;
			
//					if(d>c){ a--; c++;}
			
		}
		
		y =0; d=0;
		numofp = a;
		
		y=0;
		
		//GET INDEX OF START
		mindis = disform(person[0].coor[0],person[0].coor[1], start[0], start[1]);
		for(i=1; i<a; i++){
			distance = disform(person[i].coor[0],person[i].coor[1], start[0], start[1]);
			if(distance < mindis){
			mindis = distance;
			index = i;}
		}
		
		//ADJACENCY MATRIX
		for(c=0; c<a; c++){
			for(d=0; d<a; d++){
				if(c==d) admatrix[c][d] = 0;	
				else if(disform(person[c].coor[0], person[c].coor[1], person[d].coor[0], person[d].coor[1]) < maxdis){
					 admatrix[c][d] = 1; 
					 if(getindex(d,c) == -1 && getindex(c,d) == -1){
					 edgearr[edgecounter].ends[0] = c; edgearr[edgecounter].ends[1] = d; edgecounter++; }
				}
			}
		}
	
		//DFS
		do{
			for(i=0; i<a; i++){
				c=0;
				for(j=0; j<counter; j++){
					if(dfsstack[j] == i) c++;
				}
				if(c==0)break;
			}
			dfs(i, a);
			g++;
		}while(counter < 2*a);
		if(dfsstack[0] == dfsstack[counter-1]){
			if(pass==0)fprintf(fc, "YES\n");
			else if(pass>0)fprintf(fc, "\n\nYES\n");
			a1++;
			}
		else {
			if(pass==0)	fprintf(fc,"NOT POSSIBLE\n");
			if(pass>0) fprintf(fc,"\n\nNOT POSSIBLE\n");
		}

	if(a1 == 1){

		//LOW
		for(i=0; i<a; i++){
			ftqueue[i] = person[i].ft;	
		}
		
		for(i=0; i<a; i++) {
			for(j=a-1; j>0; j--) {
				if(ftqueue[j]<ftqueue[j-1]){
					y = ftqueue[j];
					ftqueue[j] = ftqueue[j-1];
					ftqueue[j-1] = y;	}
			}
		}
		
		
		for(y=0;y<a;y++){
			for(k=0; k<a; k++){
				if(person[k].ft == ftqueue[y]) break;	
			}
			ftqueue[y] = k;
			}
		
		x=0;
		
		while(x<a){
			i=ftqueue[x];
			person[i].low = person[i].dt;
			x++;
		}
		x=0;
		while(x<a){
			i=ftqueue[x];
			for(k=0; k<edgecounter; k++){
				if(edgearr[k].tag == -1 && i == edgearr[k].ends[0] && edgearr[k].ends[0] != edgearr[k].ends[1]){
						if(person[i].low > person[edgearr[k].ends[1]].low) person[i].low = person[edgearr[k].ends[1]].low;
						else if (person[edgearr[k].ends[1]].low > person[i].low) person[edgearr[k].ends[1]].low = person[i].low;
					
				}		
			}
			x++;
		}
		x=0;
		while(x<a){
			i=ftqueue[x];
			for(j=a-1; j>=0; j--){
				if(i == person[j].pred){
					if(person[j].low < person[i].low) person[i].low = person[j].low;
					}
			}
			x++;
		}
			
		// ARTICULATION POINT
		z=0;
		x=0;
		//for roots
		k=0; 
		for(i=0; i<a; i++)if(person[i].pred == 0) k++;
		if(k >= 2){cutpoints[z] = 0; z++;}
		//for others
		for(i=1; i<a; i++){
			for(j=1; j<a; j++){
				d=0;
				if(i == person[j].pred){
					if(person[i].dt <= person[j].low){
						for(y=0; y<z; y++){if(cutpoints[y] == i){d++;}}
								if(d==0){
								cutpoints[z] = i;
								z++;
								}
							}	
					}
				}
		}
		
		if(z>0) {
		 fprintf(fc, "YES ");
		 for(x=0; x<z; x++){
			if(x == z-1) fprintf(fc, "(%d,%d)\n", person[cutpoints[x]].coor[0], person[cutpoints[x]].coor[1]);
			else fprintf(fc, "(%d,%d),", person[cutpoints[x]].coor[0], person[cutpoints[x]].coor[1]);	 
		 }
		}
		else fprintf(fc, "NONE\n");
	
	}
	else {fprintf(fc, "NONE\n");}

	
		//COMPUTE WEIGHTS
		for(i=0; i<edgecounter; i++){
			distance = disform(person[edgearr[i].ends[0]].coor[0], person[edgearr[i].ends[0]].coor[1], person[edgearr[i].ends[1]].coor[0], person[edgearr[i].ends[1]].coor[1]);
			if(distance <= 10){
				edgearr[i].weight = 	5;
			}
			else{
				edgearr[i].weight = 5;
				distance = distance - 10;	
				while(distance > 0){
				edgearr[i].weight = edgearr[i].weight + 1;
				distance = distance -1;
				}
			}
		}

		//MINIMUM SPANNING TREE
		for(i=0; i<a; i++){
			uminusv[i] = i;
		}
		y=a;
		u[0] = index;
		remove(uminusv, y, index);
		y--;
		j=0;
		
		while(j< a){
			for(i=0; i<y; i++){
				if(admatrix[u[j]][uminusv[i]] == 1){
					if(person[uminusv[i]].key > edgearr[getindex(u[j], uminusv[i])].weight){
					person[uminusv[i]].key = edgearr[getindex(u[j], uminusv[i])].weight;
					person[uminusv[i]].pred2 = u[j];	
					}
				}
			}
			c = uminusv[y-1];
			for(i=0; i<y; i++){
				if(person[uminusv[i]].key < person[c].key) c=uminusv[i];
			}
			
			j++;
			
			u[j] = c;
			remove(uminusv, y, c);
			y--;
		}
		for(i=1; i<j; i++){
		cost = cost + edgearr[getindex(u[i], person[u[i]].pred2)].weight;}
		
		if(a1==1) fprintf(fc, "%d", cost);
		else fprintf(fc,"NOT POSSIBLE");
		pass++;
}
	fclose(fp);
	fclose(fc);
	return 0;
}

float disform(int a1, int b1, int a2, int b2){
	double x = 0;
	x = (sqrt(pow((a2 - a1), 2) + pow((b2 - b1), 2)));
	return x;
}	

int readcoor(char temp[], int b){
	int result = 0;
		
	if(b==3){
	result = (temp[0] - 48)*100 + (temp[1] - 48)*10 + (temp[2] - 48);
	}
	else if(b==2){
	result = (temp[0] - 48)*10 + (temp[1] - 48);
	}
	else if(b==1){
	b=0;
	result = (temp[0] - 48);
	}
	return result;
}
int getindex(int a, int b){
	int i;
	for(i=0; i<edgecounter; i++){
		if((edgearr[i].ends[0] == a && edgearr[i].ends[1] == b) || (edgearr[i].ends[0] == b && edgearr[i].ends[1] == a)) return i;	
	}
	return -1;
	
}
void dfs(int x, int y){
	int i;
	person[x].visited = 1;
	dfsstack[counter] = x;
	person[x].dt=counter;

	counter++;
	i=0;
	while(i<y) {
	if(admatrix[x][i] == 1 && person[i].visited == 0){
	person[i].pred=x;
	edgearr[getindex(x, i)].tag=1;
	dfs(i, y);}
	else if(admatrix[x][i] == 1 && person[i].visited == 1 && edgearr[getindex(x, i)].tag==0){
		edgearr[getindex(x, i)].tag=-1;i++;
		}
	else i++;
	}

	dfsstack[counter]=x;
	person[x].ft=counter;
	mover++;
	top=counter-mover;
	mover++;
	counter++;
	i=0;
	while(i<y) {
	if(admatrix[dfsstack[top]][i] == 1 && person[i].visited == 0){
		person[i].pred=dfsstack[top];
		edgearr[getindex(dfsstack[top], i)].tag=1;
		dfs(i, y);
	}
	else if(admatrix[dfsstack[top]][i] == 1 && person[i].visited == 1 && edgearr[getindex(dfsstack[top], i)].tag==0){
		edgearr[getindex(dfsstack[top], i)].tag=-1;i++;
		}
	else i++;
	}

}
int getmin(int x, int y){
	int temp[100] , c =0, i;
	double min= 100;
	for(i=0; i<y; i++){
		if(admatrix[i][x] == 1){
			temp[c]= i; c++;
		}
	}
	for(i=0; i<c; i++){
		if(edgearr[getindex(temp[i],x)].weight < min && person[temp[i]].visited == 0 && person[x].visited == 0) min = edgearr[getindex(temp[i],x)].weight;
	}
	for(i=0; i<c; i++){
		if(edgearr[temp[i]].weight == min ){person[temp[i]].visited = 1; person[x].visited = 1; return getindex(temp[i], x);	}
	}
	return -1;
}
void sort(int x[], int y){
	int i = y-1;
	int key = x[y-1];
	
	for(; i>0; i--) {
		if(x[i-1]<key) break; 
		x[i] = x[i-1];	
	}
	
	x[i] = key;	
	
}
void remove(int x[], int y, int z){
	int i;
	for(i=0; i<y; i++){
		if(x[i] == z) break;	
	}	
	while(i<y){
		x[i] = x[i+1];
		i++;	
	}
}