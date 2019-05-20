void kernel reSizeGPU(global const unsigned char* img, global unsigned char* imgOut, const int scale, const int width){

    int x = get_global_id(0)*4;
    int y = get_global_id(1);

    for(int i = 0; i < 4; i++){
        imgOut[i + x + y * (width*4/scale)] = img[i + x*scale +y*width*4*scale];
    }


}