#ifndef GAMEEE_H_
#define GAMEEE_H_


#include"XTexture.h"


#include<SDL.h>
#include<string>
#include<vector>

//����
const int SCREEN_WIDTH=1000;
const int SCREEN_HEIGHT=693;
//����
const int CANNON_POS_X=150;
const int CANNON_POS_Y=490;
const int CANNON_ADD_ANGLE=1;
const SDL_Point CANNON_CENTER={43,61};
const double DISTANCE_CENTER_TO_MOUTH=57.2;
const double CANNON_BARREL_ANGLE=40;
const double CANNON_BARREL_MOUTH_ANGLE=80;
const double CANNON_ANGLE_RANGE_L=-30;
const double CANNON_ANGLE_RANGE_H=50;

//�ڵ�
const int BOMB_WIDTH=40;
const int BOMB_HEIGHT=33;
const double BOMB_VELOCITY=6;
const double BOMB_G=0.04;
const int BOMB_LAUNCH_GAP=30 ;

//����
const int ENEMY_WIDTH=32;
const int ENEMY_HEIGHT=103;
const int ENEMY_FRAMES=4;
const int ENEMY_GESTURE_GAP=7;//����2������ͼƬ��ʱ���������Ըı���˶����Ŀ����������ƶ��ٶȣ�
const int ENEMY_VELOCITY=3;


//���˺��ڴ����ײ���뾶
const int COLLID_R=10;


const int EXPLODE_DURATION=10;
const int EXPLODE_WIDTH=85;
const int EXPLODE_HEIGHT=65;

//������Ӧtexture��Ϣ�Ľṹ����
struct cannon_struct
{
	double angle;
	double velocity;
};

struct bomb_struct
{
	double x;
	double y;
	double vx,vy;
	int gap;//���ڵ���2�η����ڵ�����Сʱ����
};
struct enemy_struct
{
	int x;
	int y;
	int frame;
	int gap;//���ڵ���2������֡��ʱ����
};

struct explode_struct
{
	int x;
	int y;
	int duration;
};




bool init();
bool load_bmp();
void close();

bool is_new_enemy(int &haha);
//void update_enemys(std::vector<enemy_struct> &enemys);
void render_enemys(std::vector<enemy_struct> &enemys);

//�����ڵ��ĽǶ� �����ڵ�����ĳ�ʼλ�úͽǶ�
void set_bomb_info(bomb_struct &binfo,const cannon_struct info);
//void update_bombs(std::vector<bomb_struct> &bombs);
void render_bombs(std::vector<bomb_struct> &bombs);

//void update_explodes(std::vector<explode_struct> &explodes);
void render_explodes(std::vector<explode_struct> &explodes);



void update(std::vector<enemy_struct> &enemys,
			std::vector<bomb_struct> &bombs,
			std::vector<explode_struct> &explodes);







bool is_bomb_land(bomb_struct &bomb);
bool is_hit_enemy(bomb_struct &bomb,enemy_struct &enemy);


#endif