#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{

	
	//vec4 normalColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);  
    //normalColor *= vec4(0.8, 0.8, 0.8, 0.9);  
    
    //gl_FragColor = normalColor;  
	
	vec4 c = texture2D(CC_Texture0, v_texCoord);

    float greyNum = 1.5;

    vec4 final = c;

    final.r = c.r * greyNum;

    //final.g = c.g * greyNum;

    final.b = c.b * greyNum;

    gl_FragColor = final;
	
}