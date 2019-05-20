void kernel grayScaleGPU(global const unsigned char* img, global unsigned char* imgOut){

    int y = get_global_id(0)*4;

    char color;
    color = (char) (0.2126 * img[0 + y] + 0.7152 * img[1 + y] +
                    0.0722 * img[2 + y]);
    imgOut[y/4] = color;


}