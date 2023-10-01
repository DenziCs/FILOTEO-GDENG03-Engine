struct PS_INPUT {
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0) {
	float coefficient;
};

/*
cbuffer constant: register(b0) {
	float time;
};
*/

float4 psmain(PS_INPUT input) : SV_TARGET {
	return float4(lerp(input.color, input.color1, coefficient), 1.0f);
	// return float4(lerp(input.position, input.position1, 0.5f * (sin(time) + 1.f)), 1.f);
}