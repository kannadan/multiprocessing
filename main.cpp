#include <iostream>
#include "lodepng/lodepng.h"

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

int main() {
    cout << "Hello, World!" << endl;

    image image1;
    image image2;
    unsigned error;

    image1.error = lodepng_decode32_file(&image1.image, &image1.width, &image1.height, "./im0.png");
    image2.error = lodepng_decode32_file(&image2.image, &image2.width, &image2.height, "./im1.png");

    if(!image1.error && !image2.error) {
        cout << "no errors!" << endl;
        cout << image1.width << endl;
    }
    else {
        cout << "decoder error " << image1.error << ": " << lodepng_error_text(image1.error) << endl;
        cout << "decoder error " << image2.error << ": " << lodepng_error_text(image2.error) << endl;
        return 1;
    }






    error = lodepng_encode_file("./im0Result.png", image1.image, image1.width, image1.height, LCT_RGBA, 8);
    if(error){
        cout << "virihe " << error << lodepng_error_text(error) <<endl;
    }

    image imageNew = reSize(image1, 4);
    imageNew = blackWhite(imageNew);
    error = lodepng_encode_file("./im0Smoll.png", imageNew.image, imageNew.width, imageNew.height, LCT_GREY, 8);
    if(error){
        cout << "virihe " << error << lodepng_error_text(error) <<endl;
    }



    return 0;
}

