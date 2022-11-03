#ifdef GL_ES
precision mediump float;
#endif

uniform vec3 aPos;


void main(){
//aPos.x = 10.0;
//aPos.y = 4.0;
//aPos.z = 0.0;
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

