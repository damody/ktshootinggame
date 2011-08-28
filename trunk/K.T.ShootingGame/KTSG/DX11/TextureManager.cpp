#include "stdafx.h"
#include "TextureManager.h"
#include "d3dApp.h"

TextureManager::TextureManager(void):m_index(0)
{
}

TextureManager::~TextureManager(void)
{
}

int TextureManager::AddTexture( std::string path, int index )
{
	if (index == NO_INDEX)
	{
		// check index has been insert {
		TextureMaps::iterator it = m_TextureMaps.find(m_index);
		for (;it != m_TextureMaps.end();)
		{
			it = m_TextureMaps.find(++m_index);
		}
		// check index has been insert }
		m_TextureMaps.insert(std::make_pair(m_index, Texture_Sptr(new Texture(path)) ));
		return m_index++;
	}
	else
	{
		// check index has been insert {
		TextureMaps::iterator it = m_TextureMaps.find(index);
		for (;it != m_TextureMaps.end();)
		{
			it = m_TextureMaps.find(++index);
		}
		// check index has been insert }
		m_TextureMaps.insert(std::make_pair(index, Texture_Sptr(new Texture(path)) ));
		return index;
	}
}

int TextureManager::AddTexture( std::wstring path, int index )
{
	if (index == NO_INDEX)
	{
		// check index has been insert {
		TextureMaps::iterator it = m_TextureMaps.find(m_index);
		for (;it != m_TextureMaps.end();)
		{
			it = m_TextureMaps.find(++m_index);
		}
		// check index has been insert }
		m_TextureMaps.insert(std::make_pair(m_index, Texture_Sptr(new Texture(path)) ));
		return m_index++;
	}
	else
	{
		// check index has been insert {
		TextureMaps::iterator it = m_TextureMaps.find(index);
		for (;it != m_TextureMaps.end();)
		{
			it = m_TextureMaps.find(++index);
		}
		// check index has been insert }
		m_TextureMaps.insert(std::make_pair(index, Texture_Sptr(new Texture(path)) ));
		return index;
	}
}

ID3D11ShaderResourceView* TextureManager::GetTexture( int index )
{
	TextureMaps::iterator it = m_TextureMaps.find(m_index);
	if (it != m_TextureMaps.end())
	{
		return *it->second;
	}
	return NULL;
}

Texture::Texture( std::string path )
{
	assert(g_d3dDevice!=0); // check init ok
	FILE* file = fopen(path.c_str(), "r");
	assert(file!=0); // check file ok
	fclose(file);
	if (g_d3dDevice)
		D3DX11CreateShaderResourceViewFromFileA(g_d3dDevice, path.c_str(), 0, 0, &texture, 0);
}

Texture::Texture( std::wstring path )
{
	assert(g_d3dDevice!=0); // check init ok
	FILE* file = _wfopen(path.c_str(), L"r");
	assert(file!=0); // check file ok
	fclose(file);
	if (g_d3dDevice)
		D3DX11CreateShaderResourceViewFromFileW(g_d3dDevice, path.c_str(), 0, 0, &texture, 0);
}

Texture::~Texture()
{
	ReleaseCOM(texture);
}
