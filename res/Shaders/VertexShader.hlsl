cbuffer c
{
	row_major matrix mvp;
};

struct VSOUTPUT
{
	float4 vPos : SV_Position;
	float3 vNormal : NORMAL;
	float2 vTexCoords : TEXCOORD;
};

VSOUTPUT main(float3 vPos: POSITION, float3 vNormal: NORMAL, float2 texCoords : TEXCOORD)
{
	VSOUTPUT vo;
	vo.vPos = mul(float4(vPos, 1.0f), mvp);
	vo.vNormal = vNormal;
	vo.vTexCoords = texCoords;
	return vo;
}
