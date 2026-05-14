struct VS_OUTPUT
{
	float4 pos : SV_Position;
	float3 color : COLOR;
};

VS_OUTPUT main(float2 vPos: POSITION, float3 vColor: COLOR)
{
	VS_OUTPUT ret;
	ret.pos = float4(vPos.x, vPos.y, 0.0f, 1.0f);
	ret.color = vColor;
	return ret;
}