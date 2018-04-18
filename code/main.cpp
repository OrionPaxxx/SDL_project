

#include"game.h"
#include<vector>
#include<iostream>

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;

extern XTexture g_background;
extern XTexture g_wall;

extern XTexture g_cannon;
extern cannon_struct g_cannon_info;

extern XTexture g_bomb;
extern bomb_struct g_bomb_info;

extern XTexture g_enemy;
extern enemy_struct g_enemy_info;

extern XTexture g_explode;

extern XTexture g_gameover;
extern XTexture g_note;

extern int haha;

int main(int argc, char* argv[])
{


	init();
	load_bmp();

	g_enemy_info.x=SCREEN_WIDTH-32;
	g_enemy_info.y=SCREEN_HEIGHT-130;
	g_enemy_info.frame=0;
	g_enemy_info.gap=10;

	g_cannon_info.angle=0;
	g_cannon_info.velocity=0;

	set_bomb_info(g_bomb_info,g_cannon_info);
	std::vector<enemy_struct> enemys;
	std::vector<bomb_struct> bombs;
	std::vector<explode_struct> explodes;





HERE:
	bool quit=false;
	SDL_Event e;

	while(!quit)
	{
		g_bomb_info.gap++;
		set_bomb_info(g_bomb_info,g_cannon_info);
		//为大炮旋转角度设定范围
		if((g_cannon_info.angle >= CANNON_ANGLE_RANGE_L)
			&&(g_cannon_info.angle <=CANNON_ANGLE_RANGE_H))
		{
			g_cannon_info.angle+=g_cannon_info.velocity;
		}
		//下面用于修复 为炮弹旋转角度设定范围导致的炮弹旋转到设定边界后不能回转的bug，
		if(g_cannon_info.angle<CANNON_ANGLE_RANGE_L)
		{
			g_cannon_info.angle+=CANNON_ADD_ANGLE;
			
		}
		else if(g_cannon_info.angle>CANNON_ANGLE_RANGE_H)
		{
			g_cannon_info.angle-=CANNON_ADD_ANGLE;
			
		}
		//handle event
		while(SDL_PollEvent(&e) !=0)
		{
			if(e.type==SDL_QUIT)
			{
				quit=true;
				exit(0);
			}
			else if(e.type==SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch( e.key.keysym.sym )
				{
				case SDLK_w:
					
						g_cannon_info.velocity=-CANNON_ADD_ANGLE;
						
						break;
					
					
				case SDLK_s:
					
						g_cannon_info.velocity=+CANNON_ADD_ANGLE;

						break;
				case SDLK_SPACE:
					if(g_bomb_info.gap >= BOMB_LAUNCH_GAP)
					{
						g_bomb_info.gap=0;
						bombs.push_back(g_bomb_info);
					}
				default:
					break;
				}
			}
			else if(e.type==SDL_KEYUP && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_w:
						g_cannon_info.velocity=0;

						break;
				case SDLK_s:
						g_cannon_info.velocity=0;

						break;
				case SDLK_SPACE:
					if(g_bomb_info.gap >= BOMB_LAUNCH_GAP)
					{
						g_bomb_info.gap=0;
						bombs.push_back(g_bomb_info);
					}
				default:
					break;
				}
			}
			
		}
		
		SDL_RenderClear(g_renderer);

		g_background.render(0,0);
		g_note.render(0,0);
		g_wall.render(0,SCREEN_HEIGHT-162);
		g_cannon.render(CANNON_POS_X,CANNON_POS_Y,
						g_cannon_info.angle,&CANNON_CENTER);
		
	
		
		update(enemys,bombs,explodes);

		render_enemys(enemys);
		render_bombs(bombs);
		render_explodes(explodes); 
		


		SDL_RenderPresent(g_renderer);
		//是否gameover
		for(int i=0;i<enemys.size();i++)
		{
			if(enemys[i].x <=g_wall.GetWidth()-50)
			{
				quit=true;
				enemys.clear();
				bombs.clear();
			}
		}
	}



	quit=false;
	while(!quit)
	{
		while(SDL_PollEvent(&e) !=0)
		{
			if(e.type==SDL_QUIT)
			{
				quit=true;
				exit(0);
			}
			else if(e.type=SDL_KEYDOWN)
			{
				switch ( e.key.keysym.sym )
				{
				case SDLK_RETURN:
					goto HERE;
					break;
				default:
					break;
				}
			}
		}
		SDL_RenderClear(g_renderer);
		g_background.render(0,0);
		g_wall.render(0,SCREEN_HEIGHT-162);
		g_gameover.render((SCREEN_WIDTH-g_gameover.GetWidth())/2,
							(SCREEN_HEIGHT-g_gameover.GetHeight())/2);
		SDL_RenderPresent(g_renderer);
	}
	return 0;
}





