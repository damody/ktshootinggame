#ifndef VERTEX_H
#define VERTEX_H

#include "d3dutil.h"

// Vertex format
struct VertexPoint
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
	D3DXVECTOR3 direction;
};

#endif // VERTEX_H