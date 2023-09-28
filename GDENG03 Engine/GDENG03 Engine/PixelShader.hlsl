struct PS_INPUT {
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0) {
	float coefficient;
};

float4 psmain(PS_INPUT input) : SV_TARGET {
	return float4(lerp(input.color, input.color1, coefficient), 1.0f);
}