uniform sampler2D texture;
uniform float width;

void main()
{

    float blurSample[20];
    blurSample[0] = 0.000611911;
    blurSample[1] = 0.0023841234;
    blurSample[2] = 0.0079155683;
    blurSample[3] = 0.0223948605;
    blurSample[4] = 0.0539917627;
    blurSample[5] = 0.1109224704;
    blurSample[6] = 0.1941889186;
    blurSample[7] = 0.2896958247;
    blurSample[8] = 0.368275571;
    blurSample[9] = 0.3989481634;
    blurSample[10] = 0.368275571;
    blurSample[11] = 0.2896958247;
    blurSample[12] = 0.1941889186;
    blurSample[13] = 0.1109224704;
    blurSample[14] = 0.0539917627;
    blurSample[15] = 0.0223948605;
    blurSample[16] = 0.0079155683;
    blurSample[17] = 0.0023841234;
    blurSample[18] = 0.000611911;
    blurSample[19] = 0.0001338322;

    float sum = 0.f;
    for(int ind = 0; ind < 20; ind ++) {
        sum += blurSample[ind];
    }

    vec4 pixel = vec4(0., 0., 0., 0.);

    vec2 pos = gl_TexCoord[0].xy;
    float posScreen = pos.x * width - 10.;
    for(int i = 0; i < 20; i ++) {
        pixel += texture2D(texture, vec2((posScreen+float(i))/width, pos.y)) * blurSample[i];
    }

    pixel /= sum;

    gl_FragColor =  gl_Color * pixel;

}
