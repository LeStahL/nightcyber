void rect(in vec2 uv, in vec4 rect, in vec2 shift, in float phi, in float scale, in float distort, inout float d);
void glyph_w(in vec2 uv, in vec2 shift, in float phi, in float scale, in float distort, inout float d){
rect(uv,vec4(1,7,1,3),shift,phi,scale,distort,d);rect(uv,vec4(7,7,1,4),shift,phi,scale,distort,d);rect(uv,vec4(13,7,1,3),shift,phi,scale,distort,d);rect(uv,vec4(13,7,2,2),shift,phi,scale,distort,d);rect(uv,vec4(0,8,3,1),shift,phi,scale,distort,d);rect(uv,vec4(1,8,2,2),shift,phi,scale,distort,d);rect(uv,vec4(2,8,1,4),shift,phi,scale,distort,d);rect(uv,vec4(7,8,2,3),shift,phi,scale,distort,d);rect(uv,vec4(8,8,1,4),shift,phi,scale,distort,d);rect(uv,vec4(12,8,1,4),shift,phi,scale,distort,d);rect(uv,vec4(12,8,4,1),shift,phi,scale,distort,d);rect(uv,vec4(6,9,1,3),shift,phi,scale,distort,d);rect(uv,vec4(2,10,2,2),shift,phi,scale,distort,d);rect(uv,vec4(3,10,1,4),shift,phi,scale,distort,d);rect(uv,vec4(6,10,4,1),shift,phi,scale,distort,d);rect(uv,vec4(8,10,2,2),shift,phi,scale,distort,d);rect(uv,vec4(9,10,1,3),shift,phi,scale,distort,d);rect(uv,vec4(11,10,1,4),shift,phi,scale,distort,d);rect(uv,vec4(5,11,1,4),shift,phi,scale,distort,d);rect(uv,vec4(8,11,5,1),shift,phi,scale,distort,d);rect(uv,vec4(9,11,3,2),shift,phi,scale,distort,d);rect(uv,vec4(10,11,1,4),shift,phi,scale,distort,d);rect(uv,vec4(3,12,3,2),shift,phi,scale,distort,d);rect(uv,vec4(4,12,1,4),shift,phi,scale,distort,d);
}
