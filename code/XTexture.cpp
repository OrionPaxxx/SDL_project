

#include"XTexture.h"


XTexture::XTexture()
{
	m_texture=NULL;
	m_width=0;
	m_height=0;
}
XTexture::~XTexture()
{
	Free();
}




bool XTexture::LoadFromBMP(std::string path,
					SDL_bool bo,
					int r,int g,int b)
{
	Free();
	SDL_Surface* temp_surface=SDL_LoadBMP(path.c_str());
	SDL_SetColorKey(temp_surface,
					bo,
					SDL_MapRGB( temp_surface->format, r, g, b ));
	m_texture=SDL_CreateTextureFromSurface(g_renderer,temp_surface);
	m_width=temp_surface->w;
	m_height=temp_surface->h;
	SDL_FreeSurface(temp_surface);
	return m_texture != NULL;
}

void XTexture::render(const int x,const int y,
				const double angle,
				const SDL_Point* center,
				const SDL_Rect* clip,const int s,
				const SDL_RendererFlip flip)
	{
		SDL_Rect temp_rect={x,y,m_width*s,m_height*s};//放置图片的位置和尺寸
		SDL_RenderCopyEx( g_renderer, m_texture,
						clip, &temp_rect,
						angle,center,flip);
	}

void XTexture::Free() 
{
	if(m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture=NULL;
		m_width=0;
		m_height=0;
	}
}


int XTexture::GetWidth()
{
	return m_width;
}

int XTexture::GetHeight()
{
	return m_height;
}