/*
========================================================
 CS213 - Assignment 1 - Part 1
 Team Submission

 Section   : (No section yet)
 
 Team Members:
 - Ahmed Osama Salem (ID: 20240010) : Filters 1(Grayscale), 4(Merge)
 - Kareem Osama Hamed (ID: 20240418)   : Filters 2(Black and White), 5(Flip Image)
 - Omar Sayed Amin (ID: 20240775)  : Filters 3(Invert), 6(Rotate), 17(bonus: Infrared), The menu

 File Description:
 This file contains the implementation of 6 filters required
 for Part 1 of the assignment in additon to a filter from the bonus tasks.
 The program provides a menu for the user to choose a filter and applies it to the input image
 and allows the user to load another image or save the current image at any time through
 the running of the application, it also loops until the user request to exit the program.
========================================================
*/

#include <bits/stdc++.h>
#include "Image_class.h"
using namespace std;
int working = 1;
Image image1;
string image_name;
bool check_name(string name)
{
    bool file_name;
    bool file_ext = false;
    int dot_place = -1;
    for(int i = name.size() - 1; i >= 0; i--)
    {
        if(name[i] == '.')
        dot_place = i;
    }
    if(dot_place == -1)
    return false;
    string ext;
    for(int i = dot_place + 1; i < name.size(); i++)
    {
        ext += name[i];
    }
    string extentions[5] = {"png","jpg","bmp","tga","jpeg"};
    for(int i = 0; i < 5; i++)
    {
        if(file_ext == true)
            break;
        if(ext == extentions[i])
            file_ext = true;
    }
    bool file_exist = std::filesystem::exists(name);
    return file_ext && file_exist;
}
void first_load()
{
    cout << "Welcome to our image proccesing application.\n";
    cout << "Please enter the image's name to load it:\n";
    cin >> image_name;
    if(!check_name(image_name))
    {
        cout << "The image's name is incorrect or the file doesn't exist, Please try again.\n";
        first_load();
    }
    else
    {
    image1.loadNewImage(image_name);
    cout << "Image loaded succesfully.\n";
    }
}
void load_image()
{
    cout << "Please Enter the image's name: \n";
    cin >> image_name;
    if(!check_name(image_name))
    {
        cout << "Image's name is incorrect or the file doesn't exist, Please try again.\n";
        load_image();
    }
    else
    {
    image1.loadNewImage(image_name);
    cout << "Image loaded succesfully.\n";
    }
}
Image resize( Image input_image, int new_Width, int new_Height) 
{
    Image resized_image(new_Width, new_Height); 
    double scaleX = (double)input_image.width / new_Width;
    double scaleY = (double)input_image.height / new_Height;
    for (int y = 0; y < new_Height; y++) 
    {
       for (int x = 0; x < new_Width; x++) 
       {
         int org_width  = x * scaleX;
         int org_height = y * scaleY;

           for (int c = 0; c < 3; c++)
           {
            unsigned char value = input_image.getPixel(org_width, org_height, c);
            resized_image.setPixel(x, y, c, value);
           }
        }
    }
    return resized_image;
}
Image merge( Image img1, Image img2)
{
    Image merged(img1.width, img1.height);
    for (int y = 0; y < img1.height; y++) 
    {
        for (int x = 0; x < img1.width; x++)
         {
            for (int c = 0; c < 3 ; c++)
            {
                unsigned char p1 = img1.getPixel(x, y, c);
                unsigned char p2 = img2.getPixel(x, y, c);
                unsigned char avg = ((p1 + p2) / 2);
                merged.setPixel(x, y, c, avg);
            }
        }
    }
    return merged;
}
void load_images_4merge()
{
    cout << "Choose one of the following: \n";
    cout << "1. Use the already loaded image and load the second one.\n";
    cout << "2. Load 2 new images.\n";
    int op;
    cin >> op;
    string image2_name;
    if(op == 2)
    {
        load_image();
    }
    bool name = false;
    while(name == false)
    {
    cout << "Please Enter the second image's name: \n";
    cin >> image2_name;
    if(!check_name(image2_name))
        cout << "Image's name is incorrect or the file doesn't exist, Please try again.\n";
    else
        name = true;
    }
    Image image2(image2_name);
    cout << "Both images are loaded succesfully.\n";
    if (image1.width != image2.width || image1.height != image2.height) 
    {
        image2 = resize(image2, image1.width, image1.height);
    }
    Image merged = merge(image1, image2);
    image1 = merged;
    cout << "Images merged successfully.\n";
    cout << "If saved as in the same file it will be saved in the first image's file.\n";
}

void infrared_image()
{
    for(int i = 0; i < image1.width; i++)
    {
        for(int j = 0; j < image1.height; j++)
        {
            image1(i,j,0) = 255;
            image1(i,j,1) = 255 - image1(i,j,1);
            image1(i,j,2) = 255 - image1(i,j,2);
        }
    }
    cout << "The image is now infrared.\n";
}
void black_and_white_building(Image image) 
{
    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            int result = (avg > 128) ? 255 : 0;
            for (int k = 0; k < image.channels; k++) 
            {
                image(i, j, k) = result;
            }
        }
    }
    image1 = image;
    cout << "Image is now black and white.\n";
}
Image Flipped_Horizontaly(Image image) 
{
    Image newimage(image.width, image.height);
    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            for (int k = 0; k < image.channels; k++) 
            {
                newimage(i, j, k) = image(image.width - 1 - i, j, k);
            }
        }
    }
    return newimage;
}
Image Flipped_Vertical(Image image) 
{
    Image newimage(image.width, image.height);
    for (int i = 0; i < image.width; i++) 
    {
        for (int j = 0; j < image.height; j++) 
        {
            for (int k = 0; k < image.channels; k++) 
            {
                newimage(i, j, k) = image(i , image.height-1-j , k);
            }
        }
    }
    return newimage;
}
void flip_image()
{
    cout << "Choose one of the following: \n";
    cout << "1. Flip the image vertically. \n";
    cout << "2. Flip the image Horizontaly. \n";
    int op;
    cin >> op;
    if(op == 1)
    {
        image1 = Flipped_Vertical(image1);
        cout << "Image flipped succesfully.\n";
    }
    else if(op == 2)
    {
        image1 = Flipped_Horizontaly(image1);
        cout << "Image flipped succesfully.\n";
    }
    else
    {
        cout << "Wrong number, Please try again.\n";
        flip_image();
    }
}
void gray_scale()
{
   for ( int i = 0 ; i < image1.width ; i++)
    {
        for ( int j = 0 ; j < image1.height ; j++)
        {
            int avg = image1(i,j,0) ; 
            avg += image1(i,j,1) ; 
            avg += image1(i,j,2) ; 
            avg = avg/3 ;  
            for ( int k = 0 ; k < 3 ; k++)
            {
                image1(i,j,k) = avg ; 
            }
        }
    }
    cout << "Conversion Done Succesfully.\n";
} 
void invert_image()
{
    for(int i = 0; i < image1.width; i++)
    {
        for(int j = 0; j < image1.height; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                image1(i,j,k) = 255 - image1(i,j,k);
            }
        }
    }
    cout << "Image colors inverted succesfully.\n";
}
void rotate_image()
{
    cout << "Please choose the rotation amount: \n";
    cout << "1. Rotate the image by 90° clockwise\n";
    cout << "2. Rotate the image by 180° clockwise\n";
    cout << "3. Rotate the image by 270° clockwise\n";
    int op;
    cin >> op;
    while(op--)
    {
        Image image2(image1.height,image1.width);
        for(int i = 0; i < image1.width; i++)
        {
            for(int j = 0; j < image1.height; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    int img2_wdith = image1.height - 1 - j;
                    image2(img2_wdith,i,k) = image1(i,j,k);
                }
            }
        }
    image1 = image2;
    }
    cout << "Image succesfully rotated.\n";
}
void save_image()
{
    cout << "Please choose one of the following: \n";
    cout <<"1. Save in the same file.\n";
    cout <<"2. Save in a new file.\n";
    int op;
    cin >> op;
    if(op == 2)
    {
        cout << "Enter the new file's name : \n";
        cin >> image_name;
    }
    image1.saveImage(image_name);
    cout << "Image saved succefully.\n";
}
void menu()
{
    int operation = -1;
    while(operation == -1)
    {
    cout << "Please choose an operation from below: \n";
    cout << "1. Load a new image.\n";
    cout << "2. Grayscale Conversion Filter.\n";
    cout << "3. Black and White Filter.\n";
    cout << "4. Invert colors Filter.\n";
    cout << "5. Merge 2 Images.\n";
    cout << "6. Rotate Image.\n";
    cout << "7. Make the image infrared.\n";
    cout << "8. Flip the image vertically or horizontaly.\n";
    cout << "9. Save Image.\n";
    cout << "10. Exit.\n";
    cin >> operation;
    if (operation < 1 || operation > 10)
    {
        cout << "invalid operation number, Please try again.\n";
        operation = -1;
    }
    }
    if(operation == 1)
        load_image();
    if(operation == 2)
        gray_scale();
    if(operation == 3)
        black_and_white_building(image1);
    if(operation == 4)
        invert_image();
    if(operation == 5)
        load_images_4merge();
    if(operation == 6)
        rotate_image();
    if(operation == 7)
        infrared_image();
    if(operation == 8)
        flip_image();
    if(operation == 9)
        save_image();
    if(operation == 10)
        working = 0;
}
int main()
{
    first_load();
    while (working)
    {
        int operation = -1;
        menu();
        if(working == 0)
        {
            cout << "See you soon.";
            break;
        }
    }
    return 0;
}
