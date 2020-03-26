#type vertex
#version 330 core
			
	layout(location = 0) in vec3 a_position;
	layout(location = 1) in vec4 a_color;
	layout(location = 2) in vec2 a_textureCoord;
			
	uniform mat4 u_viewProjection;

	out vec2 v_textureCoord;
	out vec4 v_color;

	void main(){
		gl_Position = u_viewProjection*vec4(a_position,1);
		v_color = a_color;
		v_textureCoord = a_textureCoord;
	}

#type fragment
#version 330 core
			
	layout(location = 0) out vec4 o_color;
			
	in vec2 v_textureCoord;
	in vec4 v_color;
			
	void main(){
		o_color = v_color;
	}