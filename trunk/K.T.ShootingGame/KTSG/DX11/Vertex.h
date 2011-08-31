#ifndef VERTEX_H
#define VERTEX_H

#include "stdafx.h"

// Vertex format
struct DXVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
};

// Vertex format
struct BulletVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
	D3DXVECTOR4 picpos; // x, y, w, h
};

// 
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_DXVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_BulletVertex[];

#endif // VERTEX_H