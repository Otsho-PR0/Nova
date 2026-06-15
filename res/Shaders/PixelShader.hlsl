float4 main(float4 vPos : SV_Position, float3 vNormal : NORMAL, float2 vTexCoords : TEXCOORD) : SV_Target
{
	return float4(vTexCoords.x, vTexCoords.y, 0.0f, 1.0f);
}
