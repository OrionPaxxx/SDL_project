


#include<SDL.h>
#include"game.h"

#include<vector>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

SDL_Window* g_window;
SDL_Renderer* g_renderer;

XTexture g_background;
XTexture g_wall;

//大炮
XTexture g_cannon;
cannon_struct g_cannon_info;
//炮弹
XTexture g_bomb;
bomb_struct g_bomb_info;
//敌人
XTexture g_enemy[4];
enemy_struct g_enemy_info;


XTexture g_explode;
explode_struct g_explode_info;


XTexture g_gameover;
XTexture g_note;



int haha=0;
bool init()
{
	//初始化
	SDL_Init(SDL_INIT_VIDEO);
	//创建窗口
	g_window=SDL_CreateWindow("defence--created by qdy with.",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							SCREEN_WIDTH,
							SCREEN_HEIGHT,
							SDL_WINDOW_SHOWN);
	//创建rendering context
	g_renderer=SDL_CreateRenderer( g_window, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor( g_renderer, 0, 0, 0xFF, 0xFF );
	return true;
}



void close()
{

	g_explode.Free();

	g_enemy[0].Free();
	g_enemy[1].Free();
	g_enemy[2].Free();
	g_enemy[3].Free();

	g_bomb.Free();
	g_cannon.Free();
	g_wall.Free();
	g_background.Free();

	
	SDL_DestroyRenderer( g_renderer );
	SDL_DestroyWindow( g_window );
	g_window = NULL;
	g_renderer = NULL;

	SDL_Quit();
}


bool load_bmp()
{
	g_background.LoadFromBMP("pic/background.bmp",
							SDL_FALSE,
							0,0,0);
	g_wall.LoadFromBMP("pic/wall.bmp",
						SDL_TRUE,
						246,246,246);
	g_cannon.LoadFromBMP("pic/cannon.bmp",
						SDL_TRUE,
						255,255,255);
	g_bomb.LoadFromBMP("pic/bomb.bmp",
						SDL_TRUE,
						246,246,246);
	g_enemy[0].LoadFromBMP("pic/enemy0.bmp",
						SDL_TRUE,
						0,0xFF,0xFF);
	g_enemy[1].LoadFromBMP("pic/enemy1.bmp",
						SDL_TRUE,
						0,0xFF,0xFF);
	g_enemy[2].LoadFromBMP("pic/enemy2.bmp",
						SDL_TRUE,
						0,0xFF,0xFF);
	g_enemy[3].LoadFromBMP("pic/enemy3.bmp",
						SDL_TRUE,
						0,0xFF,0xFF);
	g_explode.LoadFromBMP("pic/explode.bmp",
							SDL_TRUE,
							246,246,246);
	g_gameover.LoadFromBMP("pic/gameover.bmp",SDL_TRUE,1,1,1);
	g_note.LoadFromBMP("pic/note.bmp",SDL_TRUE,255,255,255);
	return true;
}


bool is_new_enemy(int &haha)
{
	/*srand(time(NULL));
	int tmp=rand()%1000+1;
	std::cout<<tmp<<std::endl;
	if(tmp  <=1000)
	{
		return true;
	}
	else
	{
		return false;
	}*/
	haha+=1;
	if(haha>=50)
	{
		haha=0;
		return true;
	}
	else
	{
		return false;
	}
	
}

void set_bomb_info(bomb_struct &binfo,const cannon_struct cinfo)
{
	binfo.x=CANNON_POS_X+CANNON_CENTER.x+
			DISTANCE_CENTER_TO_MOUTH*cos((cinfo.angle-CANNON_BARREL_MOUTH_ANGLE)/360*2*3.14159);
	binfo.y=CANNON_POS_Y+CANNON_CENTER.y+
			DISTANCE_CENTER_TO_MOUTH*sin((cinfo.angle-CANNON_BARREL_MOUTH_ANGLE)/360*2*3.14159);
	binfo.vx=BOMB_VELOCITY*cos((cinfo.angle-CANNON_BARREL_ANGLE)/360*2*3.14159);
	binfo.vy=BOMB_VELOCITY*sin((cinfo.angle-CANNON_BARREL_ANGLE)/360*2*3.14159);
}

void render_enemys(std::vector<enemy_struct> &enemys)
{
	for(int i=0;i<enemys.size();i++)
	{
		g_enemy[enemys[i].frame].render(enemys[i].x,enemys[i].y);
	}
}

void render_bombs(std::vector<bomb_struct> &bombs)
{
	for(int i=0;i<bombs.size();i++)
	{
		g_bomb.render(bombs[i].x,bombs[i].y);
	}
}




void render_explodes(std::vector<explode_struct> &explodes)
{
	for(int i=0;i<explodes.size();i++)
	{
		g_explode.render(explodes[i].x,explodes[i].y);
	}
}




void update(std::vector<enemy_struct> &enemys,
			std::vector<bomb_struct> &bombs,
			std::vector<explode_struct> &explodes)
{
	//update_enemys
	if(is_new_enemy(haha))
	{
		enemys.push_back(g_enemy_info);
	}
	for(int i=0;i<enemys.size();i++)
	{
		enemys[i].x-=ENEMY_VELOCITY;
		enemys[i].gap++;
		if(enemys[i].gap>=ENEMY_GESTURE_GAP)
		{
			enemys[i].gap=0;
			enemys[i].frame++;
			if(enemys[i].frame >=ENEMY_FRAMES)
			{
				enemys[i].frame=0;
			}
		}
	}
	//update bombs
	for(int i=0;i<bombs.size();i++)
	{
		//清除到屏幕外的炮弹
		if((bombs[i].x > SCREEN_WIDTH) || (bombs[i].y > SCREEN_HEIGHT))
		{
			bombs.erase(bombs.begin()+i);
			continue;
		}
		//炮弹移动到下一个位置
		bombs[i].vx=bombs[i].vx;
		bombs[i].vy=bombs[i].vy+BOMB_G;
		bombs[i].x=bombs[i].x+bombs[i].vx;
		bombs[i].y=bombs[i].y+bombs[i].vy;
		//炮弹是否落地，如果落地，去掉这个炮弹并且添加一个爆炸画面
		if(is_bomb_land(bombs[i]))
		{
			explode_struct tmp={bombs[i].x-EXPLODE_WIDTH/2,bombs[i].y-EXPLODE_HEIGHT/2,0};
			explodes.push_back(tmp);
			bombs.erase(bombs.begin()+i);
		}

		
		
	}
	//炮弹和敌人碰撞
	/*
	std::vector<bomb_struct>::iterator biter;
	std::vector<enemy_struct>::iterator eitor;
	for(biter=bombs.begin();biter != bombs.end();biter++)
	{
		for(eitor=enemys.begin();eitor != enemys.end();eitor++)
		{
			if(is_hit_enemy(*biter,*eitor))
			{
				explode_struct tmp={eitor->x,eitor->y,0};
				explodes.push_back(tmp);
				bombs.erase(biter);
				enemys.erase(eitor);
				break;
			}
		}

	}
	*/
	for(int i=0;i<bombs.size();i++)
	{
		for(int j=0;j<enemys.size();j++)
		{
			
			if(is_hit_enemy(bombs[i],enemys[j]))
			{
				explode_struct tmp={enemys[j].x,enemys[j].y,0};
				explodes.push_back(tmp);
				
				bombs.erase(bombs.begin()+i);
				
				enemys.erase(enemys.begin()+j);
				
				break;
			}
		}
	}
	//update explodes
	for(int i=0;i<explodes.size();i++)
	{
		explodes[i].duration++;
		if(explodes[i].duration >= EXPLODE_DURATION)
		{
			explodes.erase(explodes.begin()+i);
		}
	}
}




























bool is_bomb_land(bomb_struct &bomb)
{
	if(bomb.y >=SCREEN_HEIGHT-BOMB_HEIGHT)
	{
		return true;
	}
	else
		return false;
}

bool is_hit_enemy(bomb_struct &bomb,enemy_struct &enemy)
{
	double tmp_x=bomb.x+BOMB_WIDTH/2;
	double tmp_y=bomb.y+BOMB_HEIGHT/2;
	if( 
		   tmp_x>=enemy.x
		&& tmp_x<=enemy.x+ENEMY_WIDTH
		&& tmp_y>=enemy.y
		&& tmp_y<=enemy.y+ENEMY_HEIGHT
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}