#include "stdafx.h"
#include "d3d9Wrapper.h"

IDirect3D9 *APIENTRY Direct3DCreate9(UINT SDKVersion)
{
    return oDirect3DCreate9(SDKVersion);
}