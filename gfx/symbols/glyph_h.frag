void rect(in vec2 uv, in vec4 rect, in vec2 shift, in float phi, in float scale, in float distort, inout float d);
void glyph_h(in vec2 uv, in vec2 shift, in float phi, in float scale, in float distort, inout float d){
rect(uv,vec4(2,3,1,5),shift,phi,scale,distort,d);rect(uv,vec4(2,5,2,3),shift,phi,scale,distort,d);rect(uv,vec4(3,5,1,9),shift,phi,scale,distort,d);rect(uv,vec4(2,7,3,1),shift,phi,scale,distort,d);rect(uv,vec4(3,7,2,4),shift,phi,scale,distort,d);rect(uv,vec4(3,9,5,1),shift,phi,scale,distort,d);rect(uv,vec4(7,9,1,2),shift,phi,scale,distort,d);rect(uv,vec4(2,10,1,6),shift,phi,scale,distort,d);rect(uv,vec4(7,10,2,1),shift,phi,scale,distort,d);rect(uv,vec4(8,10,1,6),shift,phi,scale,distort,d);rect(uv,vec4(8,11,2,4),shift,phi,scale,distort,d);rect(uv,vec4(1,12,3,1),shift,phi,scale,distort,d);
}