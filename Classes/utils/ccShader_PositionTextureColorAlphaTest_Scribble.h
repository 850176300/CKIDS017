/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2011 Brian Chapados
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

"															\n\
#ifdef GL_ES												\n\
precision highp float;										\n\
#endif														\n\
															\n\
varying vec4 v_fragmentColor;								\n\
varying vec2 v_texCoord;									\n\
uniform sampler2D CC_Texture0;								\n\
uniform sampler2D CC_Texture1;								\n\
uniform float CC_alpha_value;								\n\
uniform float CC_alpha_value1;								\n\
uniform vec2 v_texCoord1;									\n\
uniform vec2 v_texSize;                                     \n\
uniform vec2 v_texSize1;									\n\
uniform bool v_solid;                                       \n\
															\n\
void main()													\n\
{															\n\
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);		\n\
															\n\
	// mimic: glAlphaFunc(GL_GREATER)						\n\
	// pass if ( incoming_pixel >= CC_alpha_value ) => fail if incoming_pixel < CC_alpha_value                  \n\
															\n\
	if ( texColor.a <= CC_alpha_value )						\n\
		discard;											\n\
    vec2 v_texCoord2 = (v_texCoord1 * v_texSize1 + v_texCoord * v_texSize) / v_texSize1;                       \n\
    vec4 texColor1 = texture2D(CC_Texture1, v_texCoord2);		\n\
    if ( texColor1.a < CC_alpha_value1 )                                  \n\
        discard;											\n\
															\n\
	vec4 lColor = texColor1 * v_fragmentColor;				\n\
    if(v_solid)                                             \n\
    {                                                       \n\
        gl_FragColor = lColor;                              \n\
    }                                                       \n\
    else                                                    \n\
    {                                                       \n\
        float lRate = distance(v_texCoord, vec2(0));        \n\
        lRate /= 2.0;                                        \n\
        gl_FragColor =  vec4(lColor.r, lColor.g, lColor.b, lColor.a * lRate);\n\
    }\n\
}															\n\
";
