#type vertex
#version 330 core
			
	layout(location = 0) in vec2 a_position;
			
	uniform mat4 u_viewProjection;
	uniform mat4 u_transform;

	out vec2 v_position;

	void main(){
		
		gl_Position = u_viewProjection*u_transform*vec4(a_position, 0 , 1);
		v_position = vec2(gl_Position.x, gl_Position.y);
		v_position = a_position;
		
	}



#type fragment
#version 330 core
			
	layout(location = 0) out vec4 o_color;
			
	in vec2 v_position;
			
	void main(){
		vec2 v = v_position*2;
		float t = 0;
		while(t < 200){
			if(length(v) > 2){
				break;
			}
		float v_x = v.x*v.x - v.y*v.y + v_position.x*2;
		v.y = 2*v.x*v.y + v_position.y*2;
		v.x = v_x;
		++t;
		}
		
		o_color = vec4(t/200, t/200, t/200, 1);
	}