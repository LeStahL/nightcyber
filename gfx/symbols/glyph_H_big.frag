void rect(in vec2 uv, in vec4 rect, in vec2 shift, in float phi, in float scale, in float distort, inout float d);
void glyph_H_big(in vec2 uv, in vec2 shift, in float phi, in float scale, in float distort, inout float d){
rect(uv,vec4(4,1,1,6),shift,phi,scale,distort,d);rect(uv,vec4(10,1,1,7),shift,phi,scale,distort,d);rect(uv,vec4(3,3,1,10),shift,phi,scale,distort,d);rect(uv,vec4(9,3,1,8),shift,phi,scale,distort,d);rect(uv,vec4(2,5,1,11),shift,phi,scale,distort,d);rect(uv,vec4(8,6,1,10),shift,phi,scale,distort,d);rect(uv,vec4(6,8,4,2),shift,phi,scale,distort,d);rect(uv,vec4(7,8,1,9),shift,phi,scale,distort,d);rect(uv,vec4(2,9,4,2),shift,phi,scale,distort,d);rect(uv,vec4(1,10,1,7),shift,phi,scale,distort,d);rect(uv,vec4(7,13,3,2),shift,phi,scale,distort,d);rect(uv,vec4(0,15,1,3),shift,phi,scale,distort,d);
}
