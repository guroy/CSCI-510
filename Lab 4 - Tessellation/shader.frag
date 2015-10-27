#version 120

varying vec4 color;

void main()
{
    // gl_FragColor = vec4( 0.0, 0.0, 0.0, 1.0 );

    // P1 Phosphor screen (green monochrome) effect
    gl_FragColor = vec4( 0.0, 1.0, 0.0, 1.0 );

    // P2 Phosphor screen (Blue - green monochrome) effect
    // gl_FragColor = vec4( 0.0, 1.0, 0.8, 1.0 );

    // P3 Phosphor screen (Amber monochrome) effect
    // gl_FragColor = vec4( 1.0, 0.745, 0.0, 1.0 );

    // P4 Phosphor screen (White monochrome) effect
    // gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0 );
}
