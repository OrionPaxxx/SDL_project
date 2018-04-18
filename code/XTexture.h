#ifndef XTEXTURE_H_
#define XTEXTURE_H_

#include<SDL.h>

#include<string>


extern SDL_Renderer* g_renderer;

class XTexture
{
private:
	int m_width;
	int m_height;
	SDL_Texture* m_texture;
public:
	XTexture();
	~XTexture();
	bool LoadFromBMP(std::string path,
					SDL_bool,
					int r,int g,int b);


	//参数s:放大的比例，s>1,如果s<1,texture 不会被render
	/*参数clip：the source SDL_Rect structure
			or NULL for the entire texture 
			(就是从texture截取一块）*/
	void render(const int x,const int y,//位置
				const double angle=0,//旋转角度
				const SDL_Point* center=NULL,//旋转中心
				const SDL_Rect* clip=NULL,const int s=1,
				const SDL_RendererFlip flip=SDL_FLIP_NONE);
	
	void Free();
	int GetWidth();
	int GetHeight();
};

#endif