void rect(in vec2 uv, in vec4 rect, in vec2 shift, in float phi, in float scale, in float distort, inout float d);

void glyph_2(in vec2 uv, in vec2 shift, in float phi, in float scale, in float distort, inout float d){
rect(uv,vec4(4,1,3,2),shift,phi,scale,distort,d);rect(uv,vec4(3,2,1,2),shift,phi,scale,distort,d);rect(uv,vec4(3,2,5,1),shift,phi,scale,distort,d);rect(uv,vec4(7,2,1,2),shift,phi,scale,distort,d);rect(uv,vec4(2,3,1,2),shift,phi,scale,distort,d);rect(uv,vec4(7,3,2,1),shift,phi,scale,distort,d);rect(uv,vec4(8,3,1,9),shift,phi,scale,distort,d);rect(uv,vec4(1,4,1,4),shift,phi,scale,distort,d);rect(uv,vec4(8,4,2,6),shift,phi,scale,distort,d);rect(uv,vec4(7,9,1,4),shift,phi,scale,distort,d);rect(uv,vec4(6,11,1,5),shift,phi,scale,distort,d);rect(uv,vec4(4,13,3,3),shift,phi,scale,distort,d);rect(uv,vec4(10,13,1,4),shift,phi,scale,distort,d);rect(uv,vec4(2,14,2,3),shift,phi,scale,distort,d);rect(uv,vec4(2,14,10,2),shift,phi,scale,distort,d);rect(uv,vec4(9,14,2,3),shift,phi,scale,distort,d);rect(uv,vec4(0,15,12,1),shift,phi,scale,distort,d);rect(uv,vec4(1,15,3,2),shift,phi,scale,distort,d);
}