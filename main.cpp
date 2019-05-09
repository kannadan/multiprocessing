#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200

#include <iostream>
#include <cmath>
#include <tgmath.h>
#include "lodepng/lodepng.h"
#include <sys/time.h>
#include <omp.h>
#include <CL/cl.hpp>


using namespace std;

struct image {
    unsigned error;
    unsigned char* image;
    unsigned width;
    unsigned height;

};



image reSize(image pic, int scale){

    image imageNew;
    imageNew.height = pic.height/scale;
    imageNew.width = pic.width/scale;
    imageNew.image = new unsigned char [imageNew.width * imageNew.height*4];

    cout << "image size " << sizeof(imageNew.image) << endl;




    for(int y = 0; y < pic.height; y += scale){
        //cout << pic.image[y] << endl;
        for (int x = 0; x < pic.width; x += scale){
            //cout << "old pic " << pic.image[x + y*pic.width] << endl;

            for(int i = 0; i < 4; i++){
                imageNew.image[i + (x/scale)*4 + (y/scale)*imageNew.width*4] = pic.image[i + x*4 +y*pic.width*4];
            }


        }

    }

    return imageNew;
}

image blackWhite(image img){
    image imageNew;
    imageNew.height = img.height;
    imageNew.width = img.width;
    imageNew.image = new unsigned char [(imageNew.width * imageNew.height)];

    for(int y = 0; y < img.height*img.width*4; y += 4){

        char color;
        color = (char) (0.2126 * img.image[0 + y] + 0.7152 * img.image[1 + y] +
                        0.0722 * img.image[2 + y]);
        imageNew.image[y/4] = color;

    }
    return imageNew;
}

double getAverage(image img, int x, int y, int n) {
    double avg = 0;
    for (int i=-n; i<=n; i++) {
        for (int j=-n; j<=n; j++) {
            avg += img.image[j+(x) + (y+i)*img.width];
        }
    }
    return(avg/((2*n+1)*(2*n+1)));
}

double getSd(image img, int x, int y, int n, double avg) {
    double sd = 0;
    for (int i=-n; i<=n; i++) {
        for (int j=-n; j<=n; j++) {
            sd += pow(img.image[j+(x) + (y+i)*img.width] - avg, 2);
        }
    }
    return sqrt(sd);
}

double getCov(image img1, image img2, int x, int y, int d, int n, double avg1, double avg2) {
    double cov = 0;
    for (int i=-n; i<=n; i++) {
        for (int j=-n; j<=n; j++) {
            cov += (img1.image[j+(x) + (y+i)*img1.width] - avg1) * (img2.image[j-d+(x) + (y+i)*img2.width] - avg2);
        }
    }
    return cov;
}

image normalize(image img){
    image imageNew;
    imageNew.height = img.height;
    imageNew.width = img.width;
    imageNew.image = new unsigned char [(imageNew.width * imageNew.height)];

    for(int y = 0; y < img.height*img.width; y++){
        imageNew.image[y] = (img.image[y]/260.0)*255;
    }
    return imageNew;
}

image zncc(image img1, image img2, int window){
    image imageNew;
    imageNew.height = img1.height;
    imageNew.width = img1.width;
    imageNew.image = new unsigned char [(imageNew.width * imageNew.height)];
    int ndisp = 260;

    int n = window/2;
    #pragma omp parallel for
    for(int i = 0; i < img1.height; i++){
        float avrg1, avrg2, sd1, sd2, cov;
        float maxZnnc;
        float zn = 0;
        int bestD;
        //cout << "im here " << i << endl;
        for(int j = 0; j < img1.width; j++){
            bestD = 0;
            maxZnnc = -10000;
            for(int d = 0; d < ndisp; d++){
                float sum1 = 0;
                float sum2 = 0;
                if(j - d > n && j < img1.width - n && i > n && i < img1.height- n) {

                    avrg1 = getAverage(img1, j, i, n);
                    avrg2 = getAverage(img2, j-d, i, n);

                    sd1 = getSd(img1, j, i, n, avrg1);
                    sd2 = getSd(img2, j-d, i, n, avrg2);

                    cov = getCov(img1, img2, j, i, d, n, avrg1, avrg2);

                    zn = cov / (sd1 * sd2);
                    //cout << avrg1 << " " << avrg2 << " " << sd1 << " " << sd2 << " " << cov << " " << zn << " " << d << endl;
                    if (zn > maxZnnc) {
                        maxZnnc = zn;
                        bestD = d;
                    }


                }

            }
            imageNew.image[j + i*img1.width] = bestD;
            /*if(i % 10 == 0){
                cout << bestD << endl;
            }*/
        }
    }
    return imageNew;
}

void saveImage(image img, char* name, LodePNGColorType colortype, unsigned bitdepth){
    unsigned error;
    error = lodepng_encode_file(name, img.image, img.width, img.height, colortype, bitdepth);
    if(error){
        cout << "virihe " << error << lodepng_error_text(error) <<endl;
    }

}

image crossCheck(image img1, image img2, int threshold){

    image imageNew;
    imageNew.height = img1.height;
    imageNew.width = img1.width;
    imageNew.image = new unsigned char [(imageNew.width * imageNew.height)];

    for(int y = 0; y < img1.height*img1.width; y++){
        int absolute = abs(img1.image[y] - img2.image[y]);
        imageNew.image[y] = absolute < threshold ? img1.image[y] : 0;
    }
    return imageNew;

}


int getClosest(image img, int x, int y){
    int result;
    float minDist = 10000;
    for(int j = 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {
            if (img.image[i + j * img.width]) {
                if (abs(i - x) + abs(j - y) < minDist) {
                    minDist = abs(i - x) + abs(j - y);
                    result = img.image[i + j * img.width];
                }
            }
        }
    }
    return result;

}

image occulsion(image img){
    cout << "occulsion going" << endl;
    image imageNew;
    imageNew.height = img.height;
    imageNew.width = img.width;
    imageNew.image = new unsigned char [(imageNew.width * imageNew.height)];
    #pragma omp parallel for
    for(int y = 0; y < img.height; y++){
        //cout << "im here ocluding " << y << endl;
        for(int x = 0; x < img.width; x++){
            if (int(img.image[x + y*img.width]) == 0){
                imageNew.image[x + y*img.width] = getClosest(img, x, y);
            }
            else{
                imageNew.image[x + y*img.width] = img.image[x + y*img.width];
            }
        }

    }
    return imageNew;

}


int main() {
    cout << "Hello, World!" << endl;
    cout << CL_DEVICE_LOCAL_MEM_SIZE << endl;
    cout << CL_DEVICE_LOCAL_MEM_TYPE << endl;


    /*
     * Device info code from https://gist.github.com/courtneyfaulkner/7919509 and
     * https://gist.github.com/tzutalin/51a821f15a735024f16b
     */
    int i, j;
    char* value;
    size_t valueSize;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
    cl_uint maxComputeUnits;
    cl_uint maxClockFreq;

    // get all platforms
    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);

    cout << platformCount << endl;

    for (i = 0; i < platformCount; i++) {
        printf("Platform: %d\n", i + 1);
        // get all devices
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = (cl_device_id *) malloc(sizeof(cl_device_id) * deviceCount);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);


        for (j = 0; j < deviceCount; j++) {

            // print device name
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            printf("%d. Device: %s\n", j+1, value);
            free(value);

            // print hardware device version
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            printf(" %d.%d Hardware version: %s\n", j+1, 1, value);
            free(value);

            // print software driver version
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
            printf(" %d.%d Software version: %s\n", j+1, 2, value);
            free(value);

            // print c version supported by compiler for device
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
            printf(" %d.%d OpenCL C version: %s\n", j+1, 3, value);
            free(value);

            // print parallel compute units
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                            sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf(" %d.%d Parallel compute units: %d\n", j+1, 4, maxComputeUnits);

            //print local memory type
            clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_TYPE, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_TYPE, valueSize, value, NULL);
            printf(" %d.%d Local memory type %u\n", j+1, 5, *value);
            free(value);

            //print local memory size
            cl_ulong mem_size;
            clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(mem_size), &mem_size, NULL);
            printf(" %d.%d Local memory size %ukB\n", j+1, 6, mem_size / 1024);

            //print clockspeed
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY,
                            sizeof(maxClockFreq), &maxClockFreq, NULL);
            printf(" %d.%d Max clock frequency: %d\n", j+1, 7, maxClockFreq);

            // buffer size
            cl_ulong buffSize;
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
                            sizeof(buffSize), &buffSize, NULL);
            printf(" %d.%d Max Constant buffer size: %dkB\n", j+1, 8, buffSize / 1024);

            // max work group size
            size_t groupSize;
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE,
                            sizeof(groupSize), &groupSize, NULL);
            printf(" %d.%d Max Group size: %d\n", j+1, 9, groupSize);

            // item dimensions
            size_t workitem_dims;
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(workitem_dims), &workitem_dims, NULL);
            printf(" %d.%d Max item dimensions: %u\n", j+1, 10, workitem_dims);

            //item sizes
            size_t itemSize[int(workitem_dims)];
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES,
                            sizeof(itemSize), &itemSize, NULL);
            printf(" %d.%d Max item sizes:\n", j+1, 11);
            for(int t = 0; t < int(workitem_dims); t++){
                printf("  %d.%d.%d Max item size:%u\n", j+1, 11, t+1, itemSize[t]);
            }
        }

        free(devices);

    }

    /*#pragma omp parallel for
    for(int n=0; n<10; ++n)
    {
        int p = 0;
        p = 0;

        ostringstream oss;

        for(int x=0; x<10; ++x)
        {
            oss << p << " ";
            p++;
        }
        cout << oss.str() << endl;
    }
    printf(".\n");*/

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int msa = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << msa/1000 << endl;

    image image1;
    image image2;
    unsigned error;
    image1.error = lodepng_decode32_file(&image1.image, &image1.width, &image1.height, "./im0.png");
    image2.error = lodepng_decode32_file(&image2.image, &image2.width, &image2.height, "./im1.png");

    gettimeofday(&tp, NULL);
    long int mse = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "images loaded " << (mse - msa) / 1000.0 << endl;

    if(!image1.error && !image2.error) {
        cout << "no errors!" << endl;
        cout << image1.width << endl;
    }
    else {
        cout << "decoder error " << image1.error << ": " << lodepng_error_text(image1.error) << endl;
        cout << "decoder error " << image2.error << ": " << lodepng_error_text(image2.error) << endl;
        return 1;
    }


    image image1S = reSize(image1, 4);
    image image2S = reSize(image2, 4);
/*
    saveImage(image1, "./im0real.png", LCT_RGBA, 8);
    saveImage(image1S, "./im0smoll.png", LCT_RGBA, 8);
    saveImage(image2S, "./im1smoll.png", LCT_RGBA, 8);
*/
    image image1B = blackWhite(image1S);
    image image2B = blackWhite(image2S);

    gettimeofday(&tp, NULL);
    mse = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "Resize and black and white" << (mse - msa) / 1000.0 << endl;

/*
    saveImage(image1B, "./im0Black.png", LCT_GREY, 8);
    saveImage(image2B, "./im1Black.png", LCT_GREY, 8);*/

    gettimeofday(&tp, NULL);
    long int msS = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    image znccImage1 = zncc(image1B, image2B, 9);
    image znccImage2 = zncc(image2B, image1B, 9);
    image normal1 = normalize(znccImage1);
    image normal2 = normalize(znccImage2);

    gettimeofday(&tp, NULL);
    mse = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "Zncc and normalization" << (mse - msS) / 1000.0 << endl;

    saveImage(normal1, "./imZnccN.png", LCT_GREY, 8);
    saveImage(normal2, "./im2ZnccN.png", LCT_GREY, 8);

    gettimeofday(&tp, NULL);
    msS = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    image crossImg = crossCheck(znccImage1, znccImage2, 8);
    saveImage(crossImg, "./imcross.png", LCT_GREY, 8);

    gettimeofday(&tp, NULL);
    mse = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "Cross Image" << (mse - msS) / 1000.0 << endl;

    gettimeofday(&tp, NULL);
    msS = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    image occulsionImg = occulsion(crossImg);
    saveImage(occulsionImg, "./imgOcc.png", LCT_GREY, 8);

    gettimeofday(&tp, NULL);
    mse = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "Occulsion " << (mse - msS) / 1000.0 << endl;

    gettimeofday(&tp, NULL);
    mse = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "Running time " << (mse - msa) / 1000.0 << endl;

    return 0;
}

