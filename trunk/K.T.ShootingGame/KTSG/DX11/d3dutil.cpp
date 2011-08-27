#include"d3dutil.h"

void Subdivide(VertexList& vertices, IndexList& indices)
{
	VertexList vin = vertices;
	IndexList  iin = indices;

	vertices.resize(0);
	indices.resize(0);

	//       v1
	//       *
	//      / \
	//     /   \
	//  m0*-----*m1
	//   / \   / \
	//  /   \ /   \
	// *-----*-----*
	// v0    m2     v2

	UINT numTris = (UINT)iin.size()/3;
	for(UINT i = 0; i < numTris; ++i)
	{
		D3DXVECTOR3 v0 = vin[ iin[i*3+0] ];
		D3DXVECTOR3 v1 = vin[ iin[i*3+1] ];
		D3DXVECTOR3 v2 = vin[ iin[i*3+2] ];

		D3DXVECTOR3 m0 = 0.5f*(v0 + v1);
		D3DXVECTOR3 m1 = 0.5f*(v1 + v2);
		D3DXVECTOR3 m2 = 0.5f*(v0 + v2);

		vertices.push_back(v0); // 0
		vertices.push_back(v1); // 1
		vertices.push_back(v2); // 2
		vertices.push_back(m0); // 3
		vertices.push_back(m1); // 4
		vertices.push_back(m2); // 5
 
		indices.push_back(i*6+0);
		indices.push_back(i*6+3);
		indices.push_back(i*6+5);

		indices.push_back(i*6+3);
		indices.push_back(i*6+4);
		indices.push_back(i*6+5);

		indices.push_back(i*6+5);
		indices.push_back(i*6+4);
		indices.push_back(i*6+2);

		indices.push_back(i*6+3);
		indices.push_back(i*6+1);
		indices.push_back(i*6+4);
	}
}


void BuildGeoSphere(UINT numSubdivisions, float radius, VertexList& vertices, IndexList& indices)
{
	// Put a cap on the number of subdivisions.
	numSubdivisions = Min(numSubdivisions, UINT(5));

	// Approximate a sphere by tesselating an icosahedron.

	const float X = 0.525731f; 
	const float Z = 0.850651f;

	D3DXVECTOR3 pos[12] = 
	{
		D3DXVECTOR3(-X, 0.0f, Z),  D3DXVECTOR3(X, 0.0f, Z),  
		D3DXVECTOR3(-X, 0.0f, -Z), D3DXVECTOR3(X, 0.0f, -Z),    
		D3DXVECTOR3(0.0f, Z, X),   D3DXVECTOR3(0.0f, Z, -X), 
		D3DXVECTOR3(0.0f, -Z, X),  D3DXVECTOR3(0.0f, -Z, -X),    
		D3DXVECTOR3(Z, X, 0.0f),   D3DXVECTOR3(-Z, X, 0.0f), 
		D3DXVECTOR3(Z, -X, 0.0f),  D3DXVECTOR3(-Z, -X, 0.0f)
	};

	DWORD k[60] = 
	{
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,    
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,    
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0, 
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7 
	};

	vertices.resize(12);
	indices.resize(60);

	for(int i = 0; i < 12; ++i)
		vertices[i] = pos[i];

	for(int i = 0; i < 60; ++i)
		indices[i] = k[i];

	for(UINT i = 0; i < numSubdivisions; ++i)
		Subdivide(vertices, indices);

	// Project vertices onto sphere and scale.
	for(size_t i = 0; i < vertices.size(); ++i)
	{
		D3DXVec3Normalize(&vertices[i], &vertices[i]);
		vertices[i] *= radius;
	}
}


float GetRandomFloat(float a, float b)
{
      if( a >= b ) // bad input
            return a;

      // Get random float in [0, 1] interval.
      float f = (rand()%10001) * 0.0001f;

      return (f*(b-a))+a;
}
void GetRandomVec(D3DXVECTOR3& out)
{
      out.x = GetRandomFloat(-1.0f, 1.0f);
      out.y = GetRandomFloat(-1.0f, 1.0f);
      out.z = GetRandomFloat(-1.0f, 1.0f);

      // Project onto unit sphere.
      D3DXVec3Normalize(&out, &out);
}

/*
void PrintMeshDeclaration(ID3DXMesh* pMesh)
{
	using namespace std;

	ofstream			g_debug("Mesh_declare.txt");

	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	pMesh->GetDeclaration(decl);

	g_debug << "\n\nMesh Declaration\n--------------------\n";

	for(int i=0; i<MAX_FVF_DECL_SIZE; i++)
	{
		if(decl[i].Type != D3DDECLTYPE_UNUSED)
		{
			g_debug << "Offset: " << (int)decl[i].Offset << ", Type: " << (int)decl[i].Type << ", Usage: " << (int)decl[i].Usage << "\n";
		}
		else break;
	}
	g_debug.close();
}

void AddTangentBinormal(ID3DXMesh** pMesh)
{
	using namespace std;
	ofstream			g_debug("Add_Binormal.txt");

	//Get vertex declaration from mesh
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	(*pMesh)->GetDeclaration(decl);

	//Find the end index of the declaration
	int index = 0;
	while(decl[index].Type != D3DDECLTYPE_UNUSED)
	{
		index++;
	}

	//Get size of last element
	int size = 0;

	switch(decl[index - 1].Type)
	{
		case D3DDECLTYPE_FLOAT1:
			size = 4;
			break;

		case D3DDECLTYPE_FLOAT2:
			size = 8;
			break;

		case D3DDECLTYPE_FLOAT3:
			size = 12;
			break;

		case D3DDECLTYPE_FLOAT4:
			size = 16;
			break;

		case D3DDECLTYPE_D3DCOLOR:
			size = 4;
			break;

		case D3DDECLTYPE_UBYTE4:
			size = 4;
			break;

		default:
			g_debug << "Unhandled declaration type: " << decl[index - 1].Type << "\n";
	};

	//Create Tangent Element
	D3DVERTEXELEMENT9 tangent = 
	{
		0, 
		decl[index - 1].Offset + size,
		D3DDECLTYPE_FLOAT3, 
		D3DDECLMETHOD_DEFAULT, 
		D3DDECLUSAGE_TANGENT, 
		0
	};

	//Create BiNormal Element
	D3DVERTEXELEMENT9 binormal = 
	{
		0, 
		tangent.Offset + 12, 
		D3DDECLTYPE_FLOAT3, 
		D3DDECLMETHOD_DEFAULT, 
		D3DDECLUSAGE_BINORMAL, 
		0
	};

	//End element
	D3DVERTEXELEMENT9 endElement = D3DDECL_END();

	//Add new elements to vertex declaration
	decl[index++] = tangent;
	decl[index++] = binormal;
	decl[index] = endElement;

	//Convert mesh to the new vertex declaration
	ID3DXMesh* pNewMesh = NULL;

	if(FAILED((*pMesh)->CloneMesh((*pMesh)->GetOptions(), 
					    decl,
					    pd3ddevice,
					    &pNewMesh)))
	{
		g_debug << "Failed to clone mesh\n";
		return;
	}

	//Compute the tangents & binormals
	HR(D3DXComputeTangentFrame(pNewMesh, NULL));
	if(FAILED(D3DXComputeTangentFrame(pNewMesh, NULL)))
	{
		g_debug << "Failed to compute tangents & binormals for new mesh\n";
		return;
	}

	//Release old mesh
	(*pMesh)->Release();

	//Assign new mesh to the mesh pointer
	*pMesh = pNewMesh;

	g_debug.close();
}
*/