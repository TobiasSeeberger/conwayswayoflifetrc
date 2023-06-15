#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define P_SCREEN0 ((unsigned char *)0x2000)
#define P_COLOR0  ((unsigned char *)0x0400)

#define P_SCREEN1 ((unsigned char *)0x6000)
#define P_COLOR1  ((unsigned char *)0x4400)

//HighRes Mode 300x200px
#define XMAX 40
#define YMAX 25
#define BOXSIZE 3
#define ROUNDS 100

void findNachbarn(register unsigned char x,register unsigned char y,char spielfeld[][YMAX],char nachbarn[][BOXSIZE]);

static char temp[XMAX][YMAX];
static char nachbarn[BOXSIZE][BOXSIZE];

//static const char array[XMAX][YMAX] 
static char spielfeld[XMAX][YMAX]= {
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
};

int main(void)
{
  clock_t       t;
  unsigned long sec;
  unsigned      sec10;
  unsigned long fps;
  unsigned      fps10;
  unsigned char background;
  unsigned char text;
        
	register unsigned char x, y, lebende;
	register unsigned char round = 0;

  clrscr();
	background = bgcolor(COLOR_BLACK);
	text = textcolor(COLOR_WHITE);
	for(y = 0; y< YMAX; y++){
        for(x = 0; x< XMAX; x++){
              revers(spielfeld[x][y]);  
             cputcxy (x, y, 32);
        }
    }
	
	t = clock();
	while(round < ROUNDS && !kbhit()){
		for(y = 0; y< YMAX; y++){
			for(x = 0; x< XMAX; x++){
				findNachbarn(x,y,spielfeld,nachbarn);
				
				lebende = 0;
				lebende += nachbarn[0][0];
				lebende += nachbarn[1][0];
				lebende += nachbarn[2][0];
				lebende += nachbarn[0][1];
				lebende += nachbarn[2][1];
				lebende += nachbarn[0][2];
				lebende += nachbarn[1][2];
				lebende += nachbarn[2][2];
				
				if(spielfeld[x][y] == 0 )
				{
					if(lebende == 3)
					{
						temp[x][y] = 1;
					}
				}
				
	switch (lebende){

                case 2: 
				temp[x][y] = spielfeld[x][y];
                break;

                case 3: 
				temp[x][y] = 1; 
                break;

                default: temp[x][y] = 0;
                }
			}
		}

		memcpy(spielfeld,temp,XMAX*YMAX);
	
		round++;
		//for(y = 0; y< YMAX; y++){
		//	for(x = 0; x< XMAX; x++){
		//		revers(spielfeld[x][y]);
		//		cputcxy (x, y, 32);
		//	}
		//}
		
		y=0;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=1;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=2;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=3;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=4;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=5;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=6;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=7;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=8;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=9;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=10;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=11;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=12;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=13;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=14;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=15;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=16;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=17;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=18;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=19;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=20;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=21;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=22;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=23;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
		
		y=24;
		
		revers(spielfeld[0][y]);
		cputcxy (0, y, 32);
		
		revers(spielfeld[1][y]);
		cputcxy (1, y, 32);
		
		revers(spielfeld[2][y]);
		cputcxy (2, y, 32);
		
		revers(spielfeld[3][y]);
		cputcxy (3, y, 32);
		
		revers(spielfeld[4][y]);
		cputcxy (4, y, 32);
		
		revers(spielfeld[5][y]);
		cputcxy (5, y, 32);
		
		revers(spielfeld[6][y]);
		cputcxy (6, y, 32);
		
		revers(spielfeld[7][y]);
		cputcxy (7, y, 32);
		
		revers(spielfeld[8][y]);
		cputcxy (8, y, 32);
		
		revers(spielfeld[9][y]);
		cputcxy (9, y, 32);
		
		revers(spielfeld[10][y]);
		cputcxy (10, y, 32);
		
		revers(spielfeld[11][y]);
		cputcxy (11, y, 32);
		
		revers(spielfeld[12][y]);
		cputcxy (12, y, 32);
		
		revers(spielfeld[13][y]);
		cputcxy (13, y, 32);
		
		revers(spielfeld[14][y]);
		cputcxy (14, y, 32);
		
		revers(spielfeld[15][y]);
		cputcxy (15, y, 32);
		
		revers(spielfeld[16][y]);
		cputcxy (16, y, 32);
		
		revers(spielfeld[17][y]);
		cputcxy (17, y, 32);
		
		revers(spielfeld[18][y]);
		cputcxy (18, y, 32);
		
		revers(spielfeld[19][y]);
		cputcxy (19, y, 32);
		
		revers(spielfeld[20][y]);
		cputcxy (20, y, 32);
		
		revers(spielfeld[21][y]);
		cputcxy (21, y, 32);
		
		revers(spielfeld[22][y]);
		cputcxy (22, y, 32);
		
		revers(spielfeld[23][y]);
		cputcxy (23, y, 32);
		
		revers(spielfeld[24][y]);
		cputcxy (24, y, 32);
		
		revers(spielfeld[25][y]);
		cputcxy (25, y, 32);
		
		revers(spielfeld[26][y]);
		cputcxy (26, y, 32);
		
		revers(spielfeld[27][y]);
		cputcxy (27, y, 32);
		
		revers(spielfeld[28][y]);
		cputcxy (28, y, 32);
		
		revers(spielfeld[29][y]);
		cputcxy (29, y, 32);
		
		revers(spielfeld[30][y]);
		cputcxy (30, y, 32);
		
		revers(spielfeld[31][y]);
		cputcxy (31, y, 32);
		
		revers(spielfeld[32][y]);
		cputcxy (32, y, 32);
		
		revers(spielfeld[33][y]);
		cputcxy (33, y, 32);
		
		revers(spielfeld[34][y]);
		cputcxy (34, y, 32);
		
		revers(spielfeld[35][y]);
		cputcxy (35, y, 32);
		
		revers(spielfeld[36][y]);
		cputcxy (36, y, 32);
		
		revers(spielfeld[37][y]);
		cputcxy (37, y, 32);
		
		revers(spielfeld[38][y]);
		cputcxy (38, y, 32);
		
		revers(spielfeld[39][y]);
		cputcxy (39, y, 32);
	}
		t = clock() - t;
	
  /* Reset screen colors */
    bgcolor (background);
    textcolor (text);
    clrscr ();

    /* Calculate stats */
    sec   = (t * 10) / CLK_TCK;
    sec10 = sec % 10;
    sec  /= 10;
    fps   = (round * (CLK_TCK * 10)) / t;
    fps10 = fps % 10;
    fps  /= 10;

    /* Output stats */
    gotoxy (0, 0); cprintf ("time  : %lu.%us", sec, sec10);
    gotoxy (0, 1); cprintf ("frames: %lu", round);
    gotoxy (0, 2); cprintf ("fps   : %lu.%u", fps, fps10);

    /* Wait for a key, then end */
    cputsxy (0, 4, "Press any key when done...");
    (void) cgetc ();

    /* Done */
    return EXIT_SUCCESS;
}

void findNachbarn(register unsigned char x, register unsigned char y, char spielfeld[][YMAX], char nachbarn[][BOXSIZE]){
	//gehe über alle nachbarn
	register unsigned char osx, ix;
	register unsigned char osy, iy; 
	register signed char ofy;
	register signed char ofx;
	
	for(ofy = y-1, iy=0; ofy <= (signed char)y+1; ++ofy , ++iy){
		for(ofx = x-1,ix = 0; ofx <= (signed char)x+1; ++ofx , ++ix){
	
			if( ofy < 0)	{
				osy = YMAX-1;
			}
			else if( ofy > YMAX-1)	{
					osy = 0;
				}
				else {
					osy = ofy;
				}
			
			
			if( ofx < 0)	{
				osx = XMAX-1;
			} else if( ofx > XMAX-1)	{
					osx = 0;
				}
				else {
					osx = ofx;
				}
			nachbarn[ix][iy] = spielfeld[osx][osy];				
		}//for ofx
	}//for ofy	

}
