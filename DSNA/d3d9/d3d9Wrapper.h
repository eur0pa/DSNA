#pragma once

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>

typedef IDirect3D9 *(APIENTRY *tDirect3DCreate9)(UINT SDKVersion);
extern tDirect3DCreate9 oDirect3DCreate9;