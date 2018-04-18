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


	//����s:�Ŵ�ı�����s>1,���s<1,texture ���ᱻrender
	/*����clip��the source SDL_Rect structure
			or NULL for the entire texture 
			(���Ǵ�texture��ȡһ�飩*/
	void render(const int x,const int y,//λ��
				const double angle=0,//��ת�Ƕ�
				const SDL_Point* center=NULL,//��ת����
				const SDL_Rect* clip=NULL,const int s=1,
				const SDL_RendererFlip flip=SDL_FLIP_NONE);
	
	void Free();
	int GetWidth();
	int GetHeight();
};

#endif