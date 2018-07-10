#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
unsigned char image1[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char image4[SIZE][SIZE][RGB];
void loadImage ();
void loadImage3 ();
void saveImage1 ();
void saveImage3 ();
void saveImage2();
void BlackAndWhiteImage ();
void FlipImage();
void Detect();
void invert();
void Rotate ();
void enlarge();
void Equal();
void Merge();
void shrink();
void DarkenAndLightenImage();
int main()
{
char imageFileName[100];
while(true)
{
 loadImage();
 while(true)
{
  int t;
  cout<<"Which Filter you want ? \n 1-Black And White \n 2-Invert \n 3-Merge \n 4-Flip \n 5-Rotate \n 6-Darken and Lighten \n 7-detect \n 8-Enlarge \n 9-Shrink \n 10-New photo \n ";
  cin>>t;
  if (t==1)
  {
  BlackAndWhiteImage();
  saveImage1();
  }
  else if (t==2)
  {
  invert();
  saveImage2();
  }
  else if(t==7)
  {
  Detect();
  saveImage1();
  }
  else if (t==4)
  {
  FlipImage();
  saveImage2();
  }
  else if (t==5)
  {
  Rotate();
  saveImage2();
  }
  else if (t==6)
  {
  DarkenAndLightenImage();
  saveImage2();
  }
  else if (t==8)
  {
  enlarge();
  saveImage2();
  }
  else if (t==3)
  {
  loadImage3();
  Merge();
  saveImage2();
  }
  else if (t==9)
  {
  shrink();
  saveImage2();
  }
else if (t==10)
  {
  break;
  }

}
}
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
}
void loadImage3 ()
 {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the second image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image4);
}

//_________________________________________
void saveImage1()
{
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image1);
}
void saveImage3() {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image3);
}
void saveImage2() {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, image2);
}
void saveImage4()
{

   for (int i = 0; i < 255; i++)
    {
    for (int j = 0; j< 255; j++)
    {
    for (int y= 0; y< 255; y++)
    {
    image2[i][j][y]=image[i][j][y];
    }
    }
    }
}


//_________________________________________
void BlackAndWhiteImage()
{
    for (int i = 0; i < SIZE; i++)
    {
    for (int j = 0; j< SIZE; j++)
    {
    for (int y= 0; y< 1; y++)
    {
    if(image[i][j][y]<128  && image[i][j][y]<128 && image[i][j][y]<128)
    {
    image1[i][j]=0;
    }
else
    {
    image1[i][j]=255;
    }
    }
    }
    }
}

void FlipImage()
{
    int r;
    cout<<"do you want to flip the image\n 1-horizontally \n 2-vertically\n";
    cin>>r;
    if (r==1)
    {
    for (int i = 0; i < 255; i++)
    {
    for (int j = 0; j< 255; j++)
    {
    for (int y= 0; y< 3; y++)
    {
    image2[i][j][y]=image[255-i][j][y];
    }
    }
    }
    }
    else if (r==2)
    {
    for (int j = 0; j < 255; j++)
    {
    for (int i = 0; i< 255; i++)
    {
    for (int y= 0; y< 255; y++)
    {
    image2[j][i][y]=image[j][255-i][y];
    }
    }
    }
    }
}

void Detect()
{

    for (int i = 0; i < 255; i++)
    {
    for (int j = 0; j< 255; j++)
    {
    for (int y= 0; y<1; y++)
    {
    if (((image[i][j][y]-image[i][j+1][y])>=15)||((image[i][j][y]-image[i+1][j][y])>=15)||((image[i][j][y]-image[i][j-1][y])>=15)||((image[i][j][y]-image[i-1][j][y])>=15))
    {
    image1[i][j]=0;
    }
    else
    {
    image1[i][j]= 255;
    }
    }
    }
    }
}
void invert()
{
    for (int i = 0; i < 255; i++)
    {
    for (int j = 0; j< 255; j++)
    {
    for (int y = 0; y< 255; y++)
    {
    image2[i][j][y]=255-image[i][j][y];
    }
    }
}
}
void Rotate ()
{
    int q;
    cout<<"rotate the image clockwise by 90 or 180 or 270  \n";
    cin>>q;
    if(q==90)
    {
    for (int j = 0; j < 255; j++)
    {
    for (int i = 0; i< 255; i++)
    {
    for (int y= 0; y< 3; y++)
    {
    image2[j][i][y]=image[255-i][j][y];
    }
    }
    }
    }
    else if(q==180)
    {
    for (int j = 0; j < 255; j++)
    {
    for (int i = 0; i< 255; i++)
    {
    for (int y= 0; y< 3; y++)
    {
    image2[j][i][y]=image[255-j][i][y];
    }
    }
    }
    }
    else if(q==270)
    {
    for (int j = 0; j < 255; j++)
    {
    for (int i = 0; i< 255; i++)
    {
    for (int y= 0; y< 3; y++)
    {
    image2[j][i][y]=image[i][j][y];
    }
    }
    }
    }
}
void enlarge()
{
    for (int i = 0; i < 255; i+=1)
    {
    for (int j = 0; j< 255; j+=1)
    {
    for (int y = 0; y< 10; y+=1)
    {
    image2[i][j][y]=0;
    }
    }
    }
    int z;
    cout<<"part 1\npart 2\npart3\npart4\n";
    cin>>z;
    if (z==1)
    {
    for (int i = 0; i < 127; i++)
    {
    for (int j = 0; j< 127; j++)
    {
    for (int y= 0; y< 4; y++)
    {
    image2[i*2][j*2][y]=image[i][j][y];
    }
    }
    }
    }
    else if (z==2)
    {
    for (int i = 0; i < 127; i++)
    {
    for (int j = 127; j< 255; j++)
    {
    for (int y= 0; y< 4; y++)
    {
    image2[i*2][j*2][y]=image[i][j][y];
    }
    }
    }
    }
    else if (z==3)
    {
    for (int i = 127; i < 255; i++)
    {
    for (int j = 0; j< 127; j++)
    {
    for (int y= 0; y< 255; y++)
    {
    image2[i][j][y]=image[i][j][y];
    }
    }
    }
    }
    else if (z==4)
    {
    for (int i = 127; i < 255; i++)
    {
    for (int j = 127; j< 255; j++)
    {
    for (int y= 0; y< 4; y++)
    {
    image2[i][j][y]=image[i][j][y];
    }
    }
    }
    }
}
void DarkenAndLightenImage()
{
    int r;
    cout<<"1-dark\n2-light\n";
    cin>>r;
     if (r==1)
    {
    for (int i = 0; i < 255; i++)
    {
    for (int j = 0; j< SIZE; j++)
    {
    for (int y= 0; y< SIZE; y++)
    {
    image2[i][j][y]=image[i][j][y]/3;
    }
    }
    }
    }

   else if (r==2)
    {
    for (int i = 0; i < 255; i++)
    {
    for (int j = 0; j< SIZE; j++)
    {
    for (int y= 0; y< SIZE; y++)
    {
    image2[i][j][y]=(image[i][j][y])*2;
    }

    }
    }
    }
}
void Merge()
{
    for (int i = 0; i < 255; i++)
    {
    for (int j = 0; j< SIZE; j++)
    {
    for (int y= 0; y< SIZE; y++)
    {
    image2[i][j][y]=(image[i][j][y]+image4[i][j][y])/2;
    }

    }
    }
}
void shrink()
{
    for (int i = 0; i < 255; i+=1)
    {
    for (int j = 0; j< 255; j+=1)
    {
    for (int y = 0; y< 10; y+=1)
    {
    image2[i][j][y]=0;
    }
    }
    }
    int r;
    cout<<"shrink to \n1-1/2\n2-1/4\n3-1/3\n";
    cin>>r;
    if (r==1)
    {
    for (int i = 0; i < 255; i+=1)
    {
    for (int j = 0; j< 255; j+=1)
    {
    for (int y = 0; y< 10; y+=1)
    {
    image2[i/2][j/2][y]=(image[i][j][y]);
    }
    }
    }
    }
    else if (r==2)
    {
    for (int i = 0; i < 255; i+=1)
    {
    for (int j = 0; j< 255; j+=1)
    {
    for (int y = 0; y< 4; y+=1)
    {
    image2[i/4][j/4][y]=(image[i][j][y]);
    }
    }
    }
    }
    else if (r==3)
    {
    for (int i = 0; i < 255; i+=1)
    {
    for (int j = 0; j< 255; j+=1)
    {
    for (int y = 0; y< 4; y+=1)
    {
    image2[i/5][j/5][y]=(image[i][j][y]);
    }
    }
    }
    }
}

