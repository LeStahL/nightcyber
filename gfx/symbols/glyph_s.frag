void rect(in vec2 uv, in vec4 rect, in vec2 shift, in float phi, in float scale, in float distort, inout float d);
void glyph_s(in vec2 uv, in vec2 shift, in float phi, in float scale, in float distort, inout float d){
rect(uv,vec4(4,6,1,4),shift,phi,scale,distort,d);rect(uv,vec4(4,6,5,1),shift,phi,scale,distort,d);rect(uv,vec4(3,7,2,2),shift,phi,scale,distort,d);rect(uv,vec4(4,9,2,1),shift,phi,scale,distort,d);rect(uv,vec4(5,9,1,2),shift,phi,scale,distort,d);rect(uv,vec4(5,10,3,1),shift,phi,scale,distort,d);rect(uv,vec4(7,10,1,5),shift,phi,scale,distort,d);rect(uv,vec4(7,11,2,3),shift,phi,scale,distort,d);rect(uv,vec4(1,13,1,2),shift,phi,scale,distort,d);rect(uv,vec4(6,13,2,2),shift,phi,scale,distort,d);rect(uv,vec4(1,14,7,1),shift,phi,scale,distort,d);rect(uv,vec4(3,14,3,2),shift,phi,scale,distort,d);rect(uv,vec4(9,7,1,1),shift,phi,scale,distort,d);
}