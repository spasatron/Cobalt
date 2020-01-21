#type vertex
#version 330 core
			
	layout(location = 0) in vec3 a_position;
	layout(location = 1) in vec2 a_texture;
			
	uniform mat4 u_viewProjection;
	uniform mat4 u_Transform;
			
	out vec2 v_texture;

	void main(){
		v_texture = a_texture;
		gl_Position = u_viewProjection*u_Transform*vec4(a_position,1);

	}

#type fragment
#version 330 core
			
	layout(location = 0) out vec4 o_color;

	uniform sampler2D u_texture;			

	in vec2 v_texture;
			
	void main(){

		o_color = texture(u_texture, v_texture);

	}