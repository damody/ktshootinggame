#pragma once
#include "stdafx.h"
#include <vector>
#include <map>
#include <cassert>
#include <cstdio>
#include <windows.h>
#include "common/shared_ptr.h"

struct Texture
{
	Texture(std::string path);
	Texture(std::wstring path);
	Texture(ID3D11ShaderResourceView* t):texture(t){}
	~Texture();
	ID3D11ShaderResourceView* texture;
	operator ID3D11ShaderResourceView*()
	{
		return texture;
	}
};
SHARE_PTR(Texture)

typedef std::vector<Texture_Sptr> Textures;
typedef std::map<int, Texture_Sptr> TextureMaps;

class TextureManager
{
public:
	enum {
		NO_INDEX=-999
	};
	TextureManager(void);
	~TextureManager(void);
	int AddTexture(std::string path, int index = NO_INDEX);
	int AddTexture(std::wstring path, int index = NO_INDEX);
	ID3D11ShaderResourceView* GetTexture(int index);
private:
	TextureMaps	m_TextureMaps;
	int		m_index;
};
