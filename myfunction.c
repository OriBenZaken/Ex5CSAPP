
//todo: added MACRO functions

#include "readBMP.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define calcIndex(i,j,n) ((i)*(n)+(j))
#define Mult9(a) (((a) << 3) + (a))

typedef struct {
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
	//todo : remove anything connetected to num
    //int num;
} pixel_sum;


/**
 * Blurring the image.
 * since we know for sure that every element in the kernel is 1, the kernel scale is 9
 * and the kernel size is 3 we gave up on passing this arguments to the function and we refer
 * this values as constants. We performed loop unrolling to the whole process so we have one 2 for nested
 * loops, in each iteration we calculate two pixels or one pixel, depends if m is even or odd.
 */
void blurImg(pixel *src, pixel *dst) {
	int i, j;
    // kernel size is always 3, therefore 3/2 is always 1.
	i = 1;
    // calculate m - 1 once instead of every iteration in the head of the for-loop.
	int limit = m - 1;
    // since the loop unrooling, and the fact that we calculating the value of sum
    // in one command and not accumulating the value of sum with each inner iterations it is
    // enough to define sum and current_pixel, too, once here and give up on initializing sum.
    pixel_sum sum;
    pixel current_pixel;
    // i++ was changed to ++i since it's more fast.
    if (m % 2 == 0) { // m is even
        for (; i < limit; ++i) {
            j =  1;
            int index = calcIndex(i, j, m);
            for (; j < limit; ++j) {
                // calculating first pixel - calculating in each iteration two pixels
                register int index1 = calcIndex(i-1, j - 1, m);
                pixel p1 = src[index1];
                pixel p2 = src[index1 + 1];
                pixel p3 = src[index1 + 2];
                pixel p4 = src[index1 + m];
                pixel p5 = src[index1 + m + 1];
                pixel p6 = src[index1 + m + 2];
                pixel p7 = src[index1 + m + m];
                pixel p8 = src[index1 + m + m + 1];
                pixel p9 = src[index1 + m + m + 2];

                sum.red = ((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                          ((int) p4.red) + ((int) p5.red) + ((int) p6.red) +
                          ((int) p7.red) + ((int) p8.red) + ((int) p9.red);
                sum.green = ((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                            ((int) p4.green) + ((int) p5.green) + ((int) p6.green) +
                            ((int) p7.green) + ((int) p8.green) + ((int) p9.green);
                sum.blue = ((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                           ((int) p4.blue) + ((int) p5.blue) + ((int) p6.blue) +
                           ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue);

                // assign kernel's result to pixel at [i,j]
                // divide by kernel's weight
                sum.red = sum.red / 9;
                sum.green = sum.green / 9;
                sum.blue = sum.blue / 9;

                // pixels sum in blur method will always be positive since we the kernel in the
                //is positive. In addition it is sufficient to assign sum after dividing.
                // at the word case : 255*9/9=255. thats why min(sum.red,255) = sum.red
                // and similarly to sum.blue and sum.green
                current_pixel.red = (unsigned char) (sum.red);
                current_pixel.green = (unsigned char) (sum.green);
                current_pixel.blue = (unsigned char) (sum.blue);
                //

                dst[index] = current_pixel;
                ++index;

                // calculating second pixel
                ++j;
                index1 = calcIndex(i-1, j - 1, m);
                p1 = src[index1];
                p2 = src[index1 + 1];
                p3 = src[index1 + 2];
                p4 = src[index1 + m];
                p5 = src[index1 + m + 1];
                p6 = src[index1 + m + 2];
                p7 = src[index1 + m + m];
                p8 = src[index1 + m + m + 1];
                p9 = src[index1 + m + m + 2];

                sum.red = ((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                          ((int) p4.red) + ((int) p5.red) + ((int) p6.red) +
                          ((int) p7.red) + ((int) p8.red) + ((int) p9.red);
                sum.green = ((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                            ((int) p4.green) + ((int) p5.green) + ((int) p6.green) +
                            ((int) p7.green) + ((int) p8.green) + ((int) p9.green);
                sum.blue = ((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                           ((int) p4.blue) + ((int) p5.blue) + ((int) p6.blue) +
                           ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue);

                // assign kernel's result to pixel at [i,j]
                // divide by kernel's weight
                sum.red = sum.red / 9;
                sum.green = sum.green / 9;
                sum.blue = sum.blue / 9;

                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (sum.red);
                current_pixel.green = (unsigned char) (sum.green);
                current_pixel.blue = (unsigned char) (sum.blue);

                dst[index] = current_pixel;
                ++index;
            }
        }
    } else { // m is odd - calculating in each iteration a single pixel
        for (; i < limit; ++i) {
            j =  1;
            int index = calcIndex(i, j, m);
            for (; j < limit; ++j) {
                // calculating first pixel
                register int index1 = calcIndex(i - 1, j - 1, m);
                pixel p1 = src[index1];
                pixel p2 = src[index1 + 1];
                pixel p3 = src[index1 + 2];
                pixel p4 = src[index1 + m];
                pixel p5 = src[index1 + m + 1];
                pixel p6 = src[index1 + m + 2];
                pixel p7 = src[index1 + m + m];
                pixel p8 = src[index1 + m + m + 1];
                pixel p9 = src[index1 + m + m + 2];

                sum.red = ((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                          ((int) p4.red) + ((int) p5.red) + ((int) p6.red) +
                          ((int) p7.red) + ((int) p8.red) + ((int) p9.red);
                sum.green = ((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                            ((int) p4.green) + ((int) p5.green) + ((int) p6.green) +
                            ((int) p7.green) + ((int) p8.green) + ((int) p9.green);
                sum.blue = ((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                           ((int) p4.blue) + ((int) p5.blue) + ((int) p6.blue) +
                           ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue);

                // assign kernel's result to pixel at [i,j]
                // divide by kernel's weight
                sum.red = sum.red / 9;
                sum.green = sum.green / 9;
                sum.blue = sum.blue / 9;

                // pixels sum in blur method will always be positive since we the kernel in the
                //is positive. In addition it is sufficient to assign sum after dividing.
                // at the word case : 255*9/9=255. thats why min(sum.red,255) = sum.red
                // and similarly to sum.blue and sum.green
                current_pixel.red = (unsigned char) (sum.red);
                current_pixel.green = (unsigned char) (sum.green);
                current_pixel.blue = (unsigned char) (sum.blue);

                dst[index] = current_pixel;
                ++index;
            }
        }
    }
}

/**
 * Sharping the image.
 * since we know for sure that every element in the kernel is -1, except kernel[1][1] = 9, the kernel scale is 1
 * and the kernel size is 3 we gave up on passing this arguments to the function and we refer
 * this values as constants. We performed loop unrolling to the whole process so we have one 2 for nested
 * loops, in each iteration we calculate two pixels or one pixel, depends if m is even or odd.
 */
void sharpImg(pixel *src, pixel *dst) {
    int i, j;
    // kernel size is always 3, therefore 3/2 is always 1.
    i = 1;
    // calculate m - 1 once instead of every iteration in the head of the for-loop.
    int limit = m - 1;
    //todo: changed i++ to ++i

    // since the loop unrooling, and the fact that we calculating the value of sum
    // in one command and not accumulating the value of sum with each inner iterations it is
    // enough to define sum and current_pixel, too, once here and give up on initializing sum.
    pixel_sum sum;
    pixel current_pixel;
    // i++ was changed to ++i since it's more fast.
    if (m % 2 == 0) { // m is even
        for (; i < limit; ++i) {
            j =  1;
            int index = calcIndex(i, j, m);
            for (; j < limit; ++j) {
                register int index1 = calcIndex(i - 1, j - 1, m);
                pixel p1 = src[index1];
                pixel p2 = src[index1 + 1];
                pixel p3 = src[index1 + 2];
                pixel p4 = src[index1 + m];
                pixel p5 = src[index1 + m + 1];
                pixel p6 = src[index1 + m + 2];
                pixel p7 = src[index1 + m + m];
                pixel p8 = src[index1 + m + m + 1];
                pixel p9 = src[index1 + m + m + 2];

                sum.red = -(((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                            ((int) p4.red) +  ((int) p6.red) +
                            ((int) p7.red) + ((int) p8.red) + ((int) p9.red)) + Mult9(((int) p5.red));
                sum.green = -(((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                              ((int) p4.green) + ((int) p6.green) +
                              ((int) p7.green) + ((int) p8.green) + ((int) p9.green)) + Mult9(((int) p5.green));
                sum.blue = -(((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                             ((int) p4.blue) + ((int) p6.blue) +
                             ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue)) + Mult9(((int) p5.blue));

                // assign kernel's result to pixel at [i,j]
                // kernel scale in this case is 1 so there is no need to divide the sum by 1

                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                //

                dst[index] = current_pixel;
                ++index;

                ++j;
                index1 = calcIndex(i-1, j - 1, m);
                p1 = src[index1];
                p2 = src[index1 + 1];
                p3 = src[index1 + 2];
                p4 = src[index1 + m];
                p5 = src[index1 + m + 1];
                p6 = src[index1 + m + 2];
                p7 = src[index1 + m + m];
                p8 = src[index1 + m + m + 1];
                p9 = src[index1 + m + m + 2];

                sum.red = -(((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                            ((int) p4.red) +  ((int) p6.red) +
                            ((int) p7.red) + ((int) p8.red) + ((int) p9.red)) + Mult9(((int) p5.red));
                sum.green = -(((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                              ((int) p4.green) + ((int) p6.green) +
                              ((int) p7.green) + ((int) p8.green) + ((int) p9.green)) + Mult9(((int) p5.green));
                sum.blue = -(((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                             ((int) p4.blue) + ((int) p6.blue) +
                             ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue)) + Mult9(((int) p5.blue));

                // assign kernel's result to pixel at [i,j]
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                //

                dst[index] = current_pixel;
                ++index;
            }
        }
    } else {    // m is odd - calculating in each iteration a single pixel
        for (; i < limit; ++i) {
            j =  1;
            int index = calcIndex(i, j, m);
            for (; j < limit; ++j) {
                register int index1 = calcIndex(i - 1, j - 1, m);
                pixel p1 = src[index1];
                pixel p2 = src[index1 + 1];
                pixel p3 = src[index1 + 2];
                pixel p4 = src[index1 + m];
                pixel p5 = src[index1 + m + 1];
                pixel p6 = src[index1 + m + 2];
                pixel p7 = src[index1 + m + m];
                pixel p8 = src[index1 + m + m + 1];
                pixel p9 = src[index1 + m + m + 2];

                sum.red = -(((int) p1.red) + ((int) p2.red) + ((int) p3.red)+
                            ((int) p4.red) +  ((int) p6.red) +
                            ((int) p7.red) + ((int) p8.red) + ((int) p9.red)) + Mult9(((int) p5.red));
                sum.green = -(((int) p1.green) + ((int) p2.green) + ((int) p3.green) +
                              ((int) p4.green) + ((int) p6.green) +
                              ((int) p7.green) + ((int) p8.green) + ((int) p9.green)) + Mult9(((int) p5.green));
                sum.blue = -(((int) p1.blue) + ((int) p2.blue) + ((int) p3.blue) +
                             ((int) p4.blue) + ((int) p6.blue) +
                             ((int) p7.blue) + ((int) p8.blue) + ((int) p9.blue)) + Mult9(((int) p5.blue));

                // assign kernel's result to pixel at [i,j]
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));

                dst[index] = current_pixel;
                ++index;
            }
        }
    }


}

void doConvolution(Image *image, int kernelScale) {

    int size = m*n;
    int tripleSize = size + size + size;
    //pixel* pixelsImg = malloc(m*n*sizeof(pixel));
    pixel* backupOrg = malloc(tripleSize);

    //charsToPixels(image, pixelsImg);
    pixel* pixelsImg = (pixel*) image->data;
    //for ()

    //Took advice from Liz Aharonian that memcpy was more efficient in running time than copyPixels
    memcpy(backupOrg, pixelsImg, tripleSize);

    //copyPixels(pixelsImg, backupOrg);
    if (kernelScale == 9) {
        blurImg(backupOrg, pixelsImg);
    } else {
        sharpImg(backupOrg, pixelsImg);

    }

    //pixelsToChars(pixelsImg, image);

    //free(pixelsImg);
    free(backupOrg);
}




/**
 * We found it not necessary allocating blurKernel and sharpKernel since their values are known.
 * Also we decreases the number of arguments to doConvolution.
 */
void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName) {

    // blur image
    doConvolution(image, 9);

    // write result image to file
    writeBMP(image, srcImgpName, blurRsltImgName);
    
    // sharpen the resulting image
    doConvolution(image, 1);

    // write result image to file
    writeBMP(image, srcImgpName, sharpRsltImgName);
}
