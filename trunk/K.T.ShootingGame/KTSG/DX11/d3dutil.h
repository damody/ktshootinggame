#include"headfile.h"



#ifndef D3DUTIL_H
#define D3DUTIL_H

typedef std::vector<D3DXVECTOR3> VertexList;
typedef std::vector<DWORD> IndexList;

//*****************************************************************************
// Constants
//*****************************************************************************
void BuildGeoSphere(
	UINT numSubdivisions,
	float radius,
	std::vector<D3DXVECTOR3>& vertices, 
	std::vector<DWORD>& indices);
const float INFINITY = FLT_MAX;
const float PI       = 3.14159265358979323f;
const float MATH_EPS = 0.0001f;

const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 0.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);

const D3DXCOLOR BEACH_SAND(1.0f, 0.96f, 0.62f, 1.0f);
const D3DXCOLOR LIGHT_YELLOW_GREEN(0.48f, 0.77f, 0.46f, 1.0f);
const D3DXCOLOR DARK_YELLOW_GREEN(0.1f, 0.48f, 0.19f, 1.0f);
const D3DXCOLOR DARKBROWN(0.45f, 0.39f, 0.34f, 1.0f);

//*****************************************************************************
// Light
//*****************************************************************************
struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}

	D3DXVECTOR3 pos;
	float pad1;      // not used
	D3DXVECTOR3 dir;
	float pad2;      // not used
	D3DXCOLOR ambient;
	D3DXCOLOR diffuse;
	D3DXCOLOR specular;
	D3DXVECTOR3 att;
	float spotPow;
	float range;
};


/*
struct VertexPN
{
	VertexPN()
		:pos(0.0f, 0.0f, 0.0f),
		normal(0.0f, 0.0f, 0.0f){}
	VertexPN(float x, float y, float z, 
		float nx, float ny, float nz,float u,float v):pos(x,y,z), normal(nx,ny,nz),tex0(u,v){}
	VertexPN(const D3DXVECTOR3& v, const D3DXVECTOR3& n)
		:pos(v),normal(n){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
		D3DXVECTOR2 tex0;

			static IDirect3DVertexDeclaration9* Decl;
			static const DWORD FVF;


};

struct VertexPT
{
	VertexPT()
		:pos(0.0f, 0.0f, 0.0f),
		tex0(0.0f, 0.0f){}
	VertexPT(float x, float y, float z, 
		float u, float v):pos(x,y,z), tex0(u,v){}
	VertexPT(const D3DXVECTOR3& v, const D3DXVECTOR2& uv)
		:pos(v), tex0(uv){}

	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex0;

	static IDirect3DVertexDeclaration9* Decl;
};

struct GrassVertex
{
      GrassVertex()
            :pos(0.0f, 0.0f, 0.0f),
            tex0(0.0f, 0.0f),
            amplitude(0.0f){}
      GrassVertex(const D3DXVECTOR3& v,
            const D3DXVECTOR2& uv, float amp)
            :pos(v), tex0(uv), amplitude(amp){}
      D3DXVECTOR3 pos;
      D3DXVECTOR3 quadPos;
      D3DXVECTOR2 tex0;
      float amplitude; // for wind oscillation.
      D3DCOLOR colorOffset;

      static IDirect3DVertexDeclaration9* Decl;
};

struct Particle
{
	D3DXVECTOR3 initialPos;
	D3DXVECTOR3 initialVelocity;
	float       initialSize; // In pixels.
	float       initialTime;
	float       lifeTime;
	float       mass;
	D3DCOLOR    initialColor;

	static IDirect3DVertexDeclaration9* Decl;
};


struct NMapVertex
{
      D3DXVECTOR3 pos;
      D3DXVECTOR3 tangent;
      D3DXVECTOR3 binormal;
      D3DXVECTOR3 normal;
      D3DXVECTOR2 tex0;

      static IDirect3DVertexDeclaration9* Decl;
};

struct WaterDMapVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 scaledTexC;     // [a, b]
	D3DXVECTOR2 normalizedTexC; // [0, 1]

	static IDirect3DVertexDeclaration9* Decl;

};

struct VertexCol
{
	VertexCol():pos(0.0f, 0.0f, 0.0f),col(0x00000000){}
	VertexCol(float x, float y, float z, D3DCOLOR c):pos(x,y,z), col(c){}
	VertexCol(const D3DXVECTOR3& v, D3DCOLOR c):pos(v),col(c){}

	D3DXVECTOR3 pos;
	D3DCOLOR    col;
	static IDirect3DVertexDeclaration9* Decl;
};
*/
float GetRandomFloat(float a, float b);

void GetRandomVec(D3DXVECTOR3& out);

//void InitAllVertexDeclarationsx();
//void DestroyAllVertexDeclarationsx();



struct Mtrl
{
      Mtrl()
            :ambient(WHITE), diffuse(WHITE),
            spec(WHITE), specPower(8.0f){}
      Mtrl(const D3DXCOLOR& a, const D3DXCOLOR& d,
            const D3DXCOLOR& s, float power)
            :ambient(a), diffuse(d), spec(s), specPower(power){}

      D3DXCOLOR ambient;
      D3DXCOLOR diffuse;
      D3DXCOLOR spec;
  
	  
	  float specPower;
};






struct AABB
{
      // Initialize to an infinitely small AABB.
      AABB()
            : minPt(INFINITY, INFINITY, INFINITY),
              maxPt(-INFINITY, -INFINITY, -INFINITY){}

       D3DXVECTOR3 center()const
	{
		return (minPt+maxPt)*0.5f;
	}

	D3DXVECTOR3 extent()const
	{
		return (maxPt-minPt)*0.5f;
	}

	void xform(const D3DXMATRIX& M, AABB& out)
	{
		// Convert to center/extent representation.
		D3DXVECTOR3 c = center();
		D3DXVECTOR3 e = extent();

		// Transform center in usual way.
		D3DXVec3TransformCoord(&c, &c, &M);

		// Transform extent.
		D3DXMATRIX absM;
		D3DXMatrixIdentity(&absM);
		absM(0,0) = fabsf(M(0,0)); absM(0,1) = fabsf(M(0,1)); absM(0,2) = fabsf(M(0,2));
		absM(1,0) = fabsf(M(1,0)); absM(1,1) = fabsf(M(1,1)); absM(1,2) = fabsf(M(1,2));
		absM(2,0) = fabsf(M(2,0)); absM(2,1) = fabsf(M(2,1)); absM(2,2) = fabsf(M(2,2));
		D3DXVec3TransformNormal(&e, &e, &absM);

		// Convert back to AABB representation.
		out.minPt = c - e;
		out.maxPt = c + e;
	}
      D3DXVECTOR3 minPt;
      D3DXVECTOR3 maxPt;
};



/*
void LoadXFile(
      const std::string& filename,
      ID3DXMesh** meshOut,
      std::vector<Mtrl>& mtrls,
      std::vector<IDirect3DTexture9*>& texs);
*/
struct DirLight
{
	D3DXCOLOR ambient;
	D3DXCOLOR diffuse;
	D3DXCOLOR spec;
	D3DXVECTOR3 dirW;
};

struct SpotLight
{
	D3DXCOLOR ambient;
	D3DXCOLOR diffuse;
	D3DXCOLOR spec;
	D3DXVECTOR3 posW;
	D3DXVECTOR3 dirW;  
	float  spotPower;
};



struct Object3D
{
	Object3D()
	{
		mesh = 0;
	}
	~Object3D()
	{
		ReleaseCOM(mesh);
		for(UINT i = 0; i < textures.size(); ++i)
			ReleaseCOM(textures[i]);
	}

	ID3DXMesh* mesh;
	std::vector<Mtrl> mtrls;
	std::vector<IDirect3DTexture9*> textures;
	AABB box;
};

//void PrintMeshDeclaration(ID3DXMesh* pMesh);
//void AddTangentBinormal(ID3DXMesh** pMesh);

template<typename T>
D3DX11INLINE T Min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template<typename T>
D3DX11INLINE T Max(const T& a, const T& b)
{
	return a > b ? a : b;
}
 

#endif D3DUTIL_H