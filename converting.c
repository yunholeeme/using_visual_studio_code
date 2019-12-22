#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main(void)
{
    BITMAPFILEHEADER hf;
    BITMAPINFOHEADER hinfo;
    RGBQUAD          hRGB[256];

    FILE *fr;

    while ((fr = fopen("cameraman.bmp", "rb")) == NULL)
    {
        printf("Can't open a file a");
        exit(EXIT_FAILURE);
    }
    fread(&hf, sizeof(BITMAPFILEHEADER), 1, fr);
    fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, fr);
    fread(&hRGB, sizeof(RGBQUAD), 256, fr);
    int imageSize = hinfo.biWidth * hinfo.biHeight;
    BYTE *inputImage = (BYTE*)malloc(imageSize);
    BYTE *outputImage = (BYTE*)malloc(imageSize);
    fread(inputImage, sizeof(BYTE), imageSize, fr);
    fclose(fr);

    for (int i = 0; i < imageSize; ++i)
    {
        outputImage[i] = 255 - inputImage[i];
    }
    
    while ((fr = fopen("output_cameraman.bmp", "wb")) == NULL)
    {
        printf("Can't open a file");
        exit(EXIT_FAILURE);
    }
    fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fr);
    fwrite(&hinfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fr);
    fwrite(&hRGB, sizeof(RGBQUAD), 256, fr);
    fwrite(outputImage, sizeof(BYTE), imageSize, fr);
    fclose(fr);
    free(inputImage);
    free(outputImage);

    return 0;
}