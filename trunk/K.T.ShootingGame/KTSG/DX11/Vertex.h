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

// 
extern D3D11_INPUT_ELEMENT_DESC VertexDesc1[];

#endif // VERTEX_H