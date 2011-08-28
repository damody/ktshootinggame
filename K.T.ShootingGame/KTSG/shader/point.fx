
cbuffer cbPerFrame
{
	float width;
	float height;
	float time;
};
 
Texture2D gMap;
SamplerState gTriLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_IN
{
	float3 position: POSITION;
	float2 size: SIZE;
	float  angle : PI;
	float3 direction : DIR;
};

struct VS_OUT
{
	float4 pos   : SV_POSITION;
	float2 size  : TEXCOORD0;
	float  angle : TEXCOORD1;
};

struct GS_OUT
{
	float4 posH : SV_POSITION;
	float2 texcoord : TEXCOORD0;

};
 
VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
	// set z = w so that z/w = 1 (i.e., skydome always on far plane).
	vIn.position.xy=(vIn.position.xy+time*vIn.direction.xy)/float2(width,height);
	vOut.pos =float4(vIn.position*2-1,1);
	// use local vertex position as cubemap lookup vector.
	vOut.size = vIn.size;
	vOut.angle = vIn.angle;
	return vOut;
}


[maxvertexcount (6)]
void gs_main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	float x = input[0].angle*3.14159/180;
	float2x2 mat = {cos(x), -sin(x), sin(x), cos(x)};
	float2 size = {1/width,1/height};
	GS_OUT out5;
	out5.posH=float4(input[0].pos.xy-mul(float2(-input[0].size.x,-input[0].size.y), mat)*size ,0,1);
	out5.texcoord=float2(0,0);
	triStream.Append( out5 );
	out5.posH=float4(input[0].pos.xy-mul(float2(-input[0].size.x,input[0].size.y), mat)*size,0,1);
	out5.texcoord=float2(0,1);
	triStream.Append( out5 );
	out5.posH=float4(input[0].pos.xy-mul(float2(input[0].size.x,-input[0].size.y), mat)*size,0,1);
	out5.texcoord=float2(1,0);
	triStream.Append( out5 );
	
	out5.posH=float4(input[0].pos.xy-mul(float2(-input[0].size.x,input[0].size.y), mat)*size,0,1);
	out5.texcoord=float2(0,1);
	triStream.Append( out5 );
	out5.posH=float4(input[0].pos.xy-mul(float2(input[0].size.x,-input[0].size.y), mat)*size,0,1);
	out5.texcoord=float2(1,0);
	triStream.Append( out5 );
	out5.posH=float4(input[0].pos.xy-mul(float2(input[0].size.x,input[0].size.y), mat)*size,0,1);
	out5.texcoord=float2(1,1);
	triStream.Append( out5 );

	triStream.RestartStrip( );
}

float4 PS(GS_OUT pIn) : SV_Target
{
	float4 color=gMap.Sample( gTriLinearSam, pIn.texcoord );
	//discard;
	//color.a = color.r;
	return color;
}

RasterizerState NoCull
{
	CullMode = None;
};

DepthStencilState LessEqualDSS
{
	// Make sure the depth function is LESS_EQUAL and not just LESS.  
	// Otherwise, the normalized depth values at z = 1 (NDC) will 
	// fail the depth test if the depth buffer was cleared to 1.
	DepthFunc = LESS_EQUAL;
};

technique11 PointTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( CompileShader( gs_4_0, gs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
		SetRasterizerState(NoCull);
		SetDepthStencilState(LessEqualDSS, 0);
	}
}
