void rect(in vec2 uv, in vec4 rect, in vec2 shift, in float phi, in float scale, in float distort, inout float d);
void glyph_V_big(in vec2 uv, in vec2 shift, in float phi, in float scale, in float distort, inout float d){
rect(uv,vec4(1,1,1,4),shift,phi,scale,distort,d);rect(uv,vec4(0,2,2,1),shift,phi,scale,distort,d);rect(uv,vec4(9,2,1,5),shift,phi,scale,distort,d);rect(uv,vec4(9,2,2,2),shift,phi,scale,distort,d);rect(uv,vec4(1,3,2,2),shift,phi,scale,distort,d);rect(uv,vec4(2,3,1,10),shift,phi,scale,distort,d);rect(uv,vec4(8,3,1,6),shift,phi,scale,distort,d);rect(uv,vec4(8,3,4,1),shift,phi,scale,distort,d);rect(uv,vec4(1,6,2,3),shift,phi,scale,distort,d);rect(uv,vec4(1,7,3,2),shift,phi,scale,distort,d);rect(uv,vec4(2,7,2,6),shift,phi,scale,distort,d);rect(uv,vec4(3,7,1,11),shift,phi,scale,distort,d);rect(uv,vec4(7,7,1,5),shift,phi,scale,distort,d);rect(uv,vec4(6,8,1,5),shift,phi,scale,distort,d);rect(uv,vec4(5,12,1,3),shift,phi,scale,distort,d);rect(uv,vec4(3,13,2,4),shift,phi,scale,distort,d);rect(uv,vec4(2,15,3,2),shift,phi,scale,distort,d);
}