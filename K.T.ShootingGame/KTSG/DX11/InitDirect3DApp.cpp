
#include "InitDirect3DApp.h"

//�������
bool stop=false;
//�O�_��ܻ���
bool show=false;

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
: D3DApp(hInstance), mWidth(0), mHeight(0)
{
}

InitDirect3DApp::~InitDirect3DApp()
{
	if( mDeviceContext )
		mDeviceContext->ClearState();
	ReleaseCOM(mDiffuseMapRV);
}

void InitDirect3DApp::initApp()
{
	D3DApp::initApp();
	D3DX11CreateShaderResourceViewFromFile(md3dDevice, _T("pic//crate.jpg"), 0, 0, &mDiffuseMapRV, 0);
	buildPointFX();
	buildPoint();
	onResize();
}

void InitDirect3DApp::onResize()
{
	D3DApp::onResize();
	if (mWidth!=NULL && mHeight!=NULL)
	{
		mWidth->SetFloat(mClientWidth);
		mHeight->SetFloat(mClientHeight);
	}
}

void InitDirect3DApp::updateScene(float dt)
{
	D3DApp::updateScene(dt);
}

void InitDirect3DApp::drawScene()
{
	static float time = 0.0;
	time += 0.01f;
	D3DApp::drawScene();
	mTime->SetFloat(time);
	mPMap->SetResource(mDiffuseMapRV);
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	mDeviceContext->IASetInputLayout(mPLayout);
	mPTech->GetPassByIndex(0)->Apply(0,mDeviceContext);
	UINT stride = sizeof(VertexPoint);
	UINT offset = 0;
	mDeviceContext->IASetVertexBuffers(0, 1, &m_Points, &stride, &offset);
	mDeviceContext->Draw(4, 0);
	mSwapChain->Present(0, 0);
}

void InitDirect3DApp::buildPointFX()
{
	ID3D10Blob* pCode;
	ID3D10Blob* pError;
	HRESULT hr = 0;
	hr=D3DX11CompileFromFile(_T("shader\\point.fx"), NULL, NULL, NULL, 
		"fx_5_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_DEBUG, NULL, NULL, &pCode, &pError, NULL );
	if(FAILED(hr))
	{
		if( pError )
		{
			MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
			ReleaseCOM(pError);
		}
		DXTrace(__FILE__, __LINE__, hr, _T("D3DX10CreateEffectFromFile"), TRUE);
	} 
	HR(D3DX11CreateEffectFromMemory( pCode->GetBufferPointer(), pCode->GetBufferSize(), NULL, md3dDevice, &mTFX2));
	mPTech = mTFX2->GetTechniqueByName("PointTech");
	mWidth = mTFX2->GetVariableByName("width")->AsScalar();
	mHeight =mTFX2->GetVariableByName("height")->AsScalar();
	mPMap =mTFX2->GetVariableByName("gMap")->AsShaderResource();
	mTime =mTFX2->GetVariableByName("time")->AsScalar();

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"SIZE",   0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"PI", 0, DXGI_FORMAT_R32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"DIR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	D3DX11_PASS_DESC PassDesc;
	mPTech->GetPassByIndex(0)->GetDesc(&PassDesc);
	HR(md3dDevice->CreateInputLayout(vertexDesc, 4, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &mPLayout));
}

void InitDirect3DApp::buildPoint()
{
	std::vector<VertexPoint> Vertex;
	VertexPoint point;
	point.position=D3DXVECTOR3(50,50,0);
	point.size=D3DXVECTOR2(10,20);
	point.angle=0;
	point.direction=D3DXVECTOR3(1,1,0);

	Vertex.push_back(point);

	point.position=D3DXVECTOR3(100,100,0);
	point.size=D3DXVECTOR2(20,10);
	point.angle=10;
	point.direction=D3DXVECTOR3(0,1,0);

	Vertex.push_back(point);

	point.position=D3DXVECTOR3(300,300,0);
	point.size=D3DXVECTOR2(55,55);
	point.angle=30;
	point.direction=D3DXVECTOR3(-1,0,0);

	Vertex.push_back(point);

	point.position=D3DXVECTOR3(300,200,0);
	point.size=D3DXVECTOR2(20,20);
	point.angle=45;
	point.direction=D3DXVECTOR3(0,-1,0);

	Vertex.push_back(point);

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(VertexPoint)*Vertex.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride=sizeof(VertexPoint);

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &Vertex[0];
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &m_Points));
}

/*
void InitDirect3DApp::doSlice()
{
D3DX11_TECHNIQUE_DESC techDesc;
mSlTech->GetDesc( &techDesc );
mDeviceContext->IASetInputLayout(mSliceLayout);
float slicevalue=0.1f;
gCamera->pos()=D3DXVECTOR3(3.0f,3.0f,0.0f);

for(int i=0;i<64;i++)
{



gCamera->setLens(D3DX_PI * 0.25f, (float)mClientWidth/mClientHeight, i*slicevalue+0.0001f,(i+1)*slicevalue);

mTest.beginArray(i);
mSlWVPVar->SetMatrix((float*)&(gCamera->viewProj()));
for(UINT p = 0; p < techDesc.Passes; ++p)
{

mSlTech->GetPassByIndex( p )->Apply(0,mDeviceContext);

mSphere.draw();
}


}


}
*/


//mfxWorldVar->SetMatrix((float*)&mCrateWorld);
//	mfxWVPVar->SetMatrix((float*)&(mCrateWorld* gCamera->viewProj()));

//mTexTech->GetDesc( &techDesc );

//doSlice();
/*
mTest.beginArray(1);
mSlTech->GetDesc( &techDesc );
mDeviceContext->IASetInputLayout(mSliceLayout);



mSlWVPVar->SetMatrix((float*)&(mCrateWorld*gCamera->viewProj()));
for(UINT p = 0; p < techDesc.Passes; ++p)
{
mSlTech->GetPassByIndex( p )->Apply(0,mDeviceContext);

mSphere.draw();

}
*/
//mTest.end();
