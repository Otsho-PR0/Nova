float4 main(float4 vPos : SV_Position, float3 vNormal : NORMAL, float2 vTexCoords : TEXCOORD) : SV_Target
{
	return float4((vNormal + float3(1.0f, 1.0f, 1.0f)) / float3(2.0f, 2.0f, 2.0f), 1.0f);
}
